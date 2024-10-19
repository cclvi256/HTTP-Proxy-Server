#include "Response.h"
#include "util.h"
#include <stdexcept>

struct StatusLine {
  std::string version;
  std::string status;
  std::string message;
};

StatusLine parse_status_line(std::string_view raw) {
  auto total_length = raw.size();
  auto linebreak = raw.find("\r\n");

  auto version_start = raw.find_first_not_of(" \t");
  auto version_end = raw.find(' ', version_start);
  if (version_end == std::string::npos) {
    throw std::runtime_error("Invalid response line");
  }

  auto status_start = version_end + 1;
  auto status_end = raw.find(' ', status_start);
  if (status_end == std::string::npos) {
    throw std::runtime_error("Invalid response line");
  }

  auto message_start = status_end + 1;
  auto message_end = linebreak;
  if (message_end == std::string::npos) {
    throw std::runtime_error("Invalid response line");
  }

  std::string version =
      std::string(raw.substr(version_start, version_end - version_start));
  std::string status =
      std::string(raw.substr(status_start, status_end - status_start));
  std::string message =
      std::string(raw.substr(message_start, message_end - message_start));

  return {version, status, message};
}

Response::Response(const std::string &version, const std::string &status,
                   const std::string &message,
                   const std::unordered_map<std::string, std::string> headers,
                   const std::string body)
    : version_(version), status_(status), message_(message), headers_(headers),
      body_(body) {}

Response::Response(const std::string_view raw) {
  auto total_length = raw.size();
  auto linebreak = raw.find("\r\n");

  if (linebreak == std::string::npos) {
    throw std::runtime_error("Invalid response");
  }

  StatusLine status_line = parse_status_line(raw.substr(0, linebreak));
  version_ = status_line.version;
  status_ = status_line.status;
  message_ = status_line.message;

  auto headers_start = linebreak + 2;
  auto headers_end = raw.find("\r\n\r\n", headers_start);
  if (headers_end == std::string::npos) {
    throw std::runtime_error("Invalid response");
  }

  headers_ =
      parse_headers(raw.substr(headers_start, headers_end - headers_start));

  auto body_start = headers_end + 4;

  body_ = std::string(raw.substr(body_start, total_length - body_start));
}

Response::Response(const Response &response) {
  version_ = response.version_;
  status_ = response.status_;
  message_ = response.message_;
  headers_ = response.headers_;
  body_ = response.body_;
}

Response::Response(Response &&response) {
  version_ = std::move(response.version_);
  status_ = std::move(response.status_);
  message_ = std::move(response.message_);
  headers_ = std::move(response.headers_);
  body_ = std::move(response.body_);
}

const std::string Response::version() const { return version_; }

const std::string Response::status() const { return status_; }

const std::string Response::message() const { return message_; }

const std::string Response::body() const { return body_; }

const std::unordered_map<std::string, std::string> Response::headers() const {
  return headers_;
}

const std::string Response::header_query(const std::string &key) const {
  auto it = headers_.find(key);
  if (it == headers_.end()) {
    return "";
  }

  return it->second;
}

const std::string Response::to_string() const {
  std::string response_text =
      version_ + " " + status_ + " " + message_ + "\r\n";
  for (const auto &[key, value] : headers_) {
    response_text += key + ": " + value + "\r\n";
  }
  response_text += "\r\n" + body_;

  return response_text;
}
