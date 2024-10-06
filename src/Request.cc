#include "Request.h"

const void Request::parse_request_line() {
  auto request_line = this->request_line();

  auto start = request_line.find_first_not_of(" \t");

  if (start == std::string::npos) {
    return;
  }

  auto end = request_line.find_last_not_of(" \t");
  auto trimmed = request_line.substr(start, end - start + 1);

  auto method_end = trimmed.find(' ');
  method_ = trimmed.substr(0, method_end);

  auto uri_start = trimmed.find_first_not_of(' ', method_end);
  auto uri_end = trimmed.find(' ', uri_start);
  uri_ = trimmed.substr(uri_start, uri_end - uri_start);

  auto version_start = trimmed.find_first_not_of(' ', uri_end);
  version_ = trimmed.substr(version_start);
}

const std::string_view Request::request_line() const {
  auto delimiter = raw_.find("\r\n");

  if (delimiter == std::string::npos) {
    return std::string_view();
  }

  return std::string_view(raw_.c_str(), delimiter);
}

const std::string_view Request::headers() const {
  auto delimiter = raw_.find("\r\n");

  if (delimiter == std::string::npos) {
    return std::string_view();
  }

  auto headers_start = delimiter + 2;
  auto headers_end = raw_.find("\r\n\r\n");

  if (headers_end == std::string::npos || headers_end <= headers_start) {
    return std::string_view();
  }

  return std::string_view(raw_.c_str() + headers_start,
                          headers_end - headers_start);
}

const std::string_view Request::body() const {
  auto delimiter = raw_.find("\r\n\r\n");

  if (delimiter == std::string::npos) {
    return std::string_view();
  }

  auto body_start = delimiter + 4;
  auto raw_length = raw_.length();

  if (body_start >= raw_length) {
    return std::string_view();
  }

  return std::string_view(raw_.c_str() + body_start, raw_length - body_start);
}

// Constructors

Request::Request()
    : raw_(""), method_(raw_.c_str(), 0), uri_(raw_.c_str(), 0),
      version_(raw_.c_str(), 0), headers_({}), body_(raw_.c_str(), 0) {}

Request::Request(const std::string &raw) : raw_(raw) {
  // Parse the raw HTTP request text by slicing
}
