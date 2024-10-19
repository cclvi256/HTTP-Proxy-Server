#include "Request.h"
#include <stdexcept>
#include <string>
#include <string_view>

struct RequestLine {
  std::string method;
  std::string uri;
  std::string version;
};

RequestLine parse_request_line(std::string_view raw) {
  auto total_length = raw.size();
  auto linebreak = raw.find("\r\n");

  auto method_start = raw.find_first_not_of(" \t");
  auto method_end = raw.find(' ', method_start);
  if (method_end == std::string::npos) {
    throw std::runtime_error("Invalid response line");
  }

  auto uri_start = method_end + 1;
  auto uri_end = raw.find(' ', uri_start);
  if (uri_end == std::string::npos) {
    throw std::runtime_error("Invalid response line");
  }

  auto version_start = uri_end + 1;
  auto version_end = linebreak;
  if (version_end == std::string::npos) {
    throw std::runtime_error("Invalid response line");
  }

  std::string method =
      std::string(raw.substr(method_start, method_end - method_start));
  std::string uri = std::string(raw.substr(uri_start, uri_end - uri_start));
  std::string version =
      std::string(raw.substr(version_start, version_end - version_start));

  return {method, uri, version};
}

std::unordered_map<std::string, std::string>
parse_headers(std::string_view raw) {
  std::unordered_map<std::string, std::string> headers;
  auto total_length = raw.size();
  auto linebreak = raw.find("\r\n");

  auto start = linebreak + 2;
  while (start < total_length) {
    auto colon = raw.find(':', start);
    if (colon == std::string::npos) {
      break;
    }

    auto key_start = start;
    auto key_end = colon;
    auto value_start = colon + 2;
    auto value_end = raw.find("\r\n", value_start);

    std::string key = std::string(raw.substr(key_start, key_end - key_start));
    std::string value =
        std::string(raw.substr(value_start, value_end - value_start));

    headers[key] = value;
    start = value_end + 2;
  }

  return headers;
}

Request::Request(const std::string &method, const std::string &uri,
                 const std::string &version,
                 const std::unordered_map<std::string, std::string> &headers,
                 const std::string &body)
    : method_(method), uri_(uri), version_(version), headers_(headers),
      body_(body) {}

Request::Request(const std::string_view &raw) {
  auto total_length = raw.size();
  auto linebreak = raw.find("\r\n");

  if (linebreak == std::string::npos) {
    throw std::runtime_error("Invalid request");
  }

  RequestLine request_line = parse_request_line(raw.substr(0, linebreak));
  method_ = request_line.method;
  uri_ = request_line.uri;
  version_ = request_line.version;

  auto headers_start = linebreak + 2;
  auto headers_end = raw.find("\r\n\r\n", headers_start);
  if (headers_end == std::string::npos) {
    throw std::runtime_error("Invalid request");
  }

  headers_ =
      parse_headers(raw.substr(headers_start, headers_end - headers_start));

  auto body_start = headers_end + 4;

  body_ = std::string(raw.substr(body_start, total_length - body_start));
}

Request::Request(const Request &request) {
  method_ = request.method_;
  uri_ = request.uri_;
  version_ = request.version_;
  headers_ = request.headers_;
  body_ = request.body_;
}

Request::Request(Request &&request) {
  method_ = std::move(request.method_);
  uri_ = std::move(request.uri_);
  version_ = std::move(request.version_);
  headers_ = std::move(request.headers_);
  body_ = std::move(request.body_);
}

const std::string Request::method() const { return method_; }

const std::string Request::uri() const { return uri_; }

const std::string Request::version() const { return version_; }

const std::unordered_map<std::string, std::string> Request::headers() const {
  return headers_;
}
const std::string Request::header_query(const std::string &key) const {
  auto it = headers_.find(key);
  if (it == headers_.end()) {
    return "";
  }

  return it->second;
}

const std::string Request::body() const { return body_; }

const std::string Request::to_string() const {
  std::string raw = method_ + " " + uri_ + " " + version_ + "\r\n";
  for (const auto &[key, value] : headers_) {
    raw += key + ": " + value + "\r\n";
  }
  raw += "\r\n" + body_;

  return raw;
}
