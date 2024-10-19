#include "Request.h"
#include <string>
#include <string_view>

Request::Request(const std::string &method, const std::string &uri,
                 const std::string &version,
                 const std::unordered_map<std::string, std::string> &headers,
                 const std::string &body)
    : method_(method), uri_(uri), version_(version), headers_(headers),
      body_(body) {}

Request::Request(const std::string_view &raw) {}

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
