#include "Request.h"

// Private accessory methods

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

const std::string_view Request::request_line() const {
  auto delimiter = raw_.find("\r\n");

  if (delimiter == std::string::npos) {
    return std::string_view();
  }

  return std::string_view(raw_.c_str(), delimiter);
}

// Constructors

Request::Request()
    : raw_(""), method_(raw_.c_str(), 0), uri_(raw_.c_str(), 0),
      version_(raw_.c_str(), 0), headers_({}), body_(raw_.c_str(), 0) {}

Request::Request(const std::string &raw) : raw_(raw) {
  // Parse the raw HTTP request text by slicing
}
