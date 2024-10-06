#pragma once
#ifndef REQUEST_H_
#define REQUEST_H_

#include <unordered_map>
#include <string>
#include <string_view>

class Request {
private:
  std::string raw_;
  std::string_view method_;
  std::string_view uri_;
  std::string_view version_;
  std::unordered_map<std::string_view, std::string_view> headers_;
  std::string_view body_;

  const std::string_view body() const;
  const std::string_view headers() const;
  const std::string_view request_line() const;

public:
  explicit Request();
  explicit Request(const std::string &raw);

  virtual ~Request() = default;

  std::string_view method() const;

};

#endif /* REQUEST_H_ */
