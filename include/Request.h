#pragma once

#include <string>
#include <string_view>
#include <unordered_map>
class Request {
private:
  std::string method_;
  std::string uri_;
  std::string version_;
  std::unordered_map<std::string, std::string> headers_;
  std::string body_;

public:
  Request() = default;
  Request(const std::string &method, const std::string &uri,
          const std::string &version,
          const std::unordered_map<std::string, std::string> &headers,
          const std::string &body);
  Request(const std::string_view &raw);
  Request(const Request &request);
  Request(Request &&request);
  
  virtual ~Request() = default;

  const std::string method() const;
  const std::string uri() const;
  const std::string version() const;
  const std::unordered_map<std::string, std::string> headers() const;
  const std::string header_query(const std::string &key) const;
  const std::string body() const;

  const std::string to_string() const;
};
