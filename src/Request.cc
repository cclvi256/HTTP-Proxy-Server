#include "Request.h"
#include <string>

void Request::parse_request_line(const std::string &request_line,
                                 std::string &version_o,
                                 std::variant<Method, std::string> &method_o,
                                 std::string &uri_o) {
  

  // TODO
}

std::variant<Method, std::string> Request::method_from_string(const std::string &method_str) {
  static std::unordered_map<std::string, Method> method_map = {
      {"GET", Method::GET},         {"POST", Method::POST},
      {"PUT", Method::PUT},         {"DELETE", Method::DELETE},
      {"OPTIONS", Method::OPTIONS}, {"HEAD", Method::HEAD},
      {"PATCH", Method::PATCH},     {"CONNECT", Method::CONNECT}};
  auto it = method_map.find(method_str);

  if (it != method_map.end()) {
    return it->second;
  }

  return std::string(method_str);
}

Request::Request(std::string &request_str) {
  std::size_t request_line_end = request_str.find("\r\n");
  std::size_t header_end = request_str.find("\r\n\r\n");

  // TODO
}

std::string Request::version() const { return version_; }

std::variant<Method, std::string> Request::method() const { return method_; }

std::string Request::uri() const { return uri_; }

std::unordered_map<std::string, std::string> Request::headers() const {
  return headers_;
}

std::string Request::header_by_key(const std::string &key) const {
  auto it = headers_.find(key);
  if (it != headers_.end()) {
    return it->second;
  }

  return std::string();
}

void Request::add_header(const std::string &key, const std::string &value) {
  headers_.insert({key, value});
}

bool Request::remove_header(const std::string &key) {
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

Request Request::parse(const std::string &raw) {
  // TODO
  return Request();
}
