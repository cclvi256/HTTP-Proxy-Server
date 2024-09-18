#include "Request.h"

Request::Request(std::string request_str) {
  // TODO
}

std::string Request::version() const { return version_; }

std::variant<Method, std::string> Request::method() const { return method_; }

std::string Request::path() const { return path_; }

std::unordered_map<std::string, std::string> Request::headers() const {
  return headers_;
}

std::string Request::header_by_key(const std::string& key) const {
  auto it = headers_.find(key);
  if (it != headers_.end()) {
    return it->second;
  }

  return std::string();
}

void Request::add_header(const std::string& key, const std::string& value) {
  headers_.insert({key, value});
}

bool Request::remove_header(const std::string& key) {
  auto it = headers_.find(key);
  if (it != headers_.end()) {
    headers_.erase(it);
    return true;
  }
  return false;
}

std::string Request::to_string() const {
  // TODO
  return std::string();
}

Request Request::parse(const std::string& raw) {
  // TODO
  return Request();
}
