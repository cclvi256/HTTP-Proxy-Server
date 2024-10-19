#pragma once

#include <string>
#include <string_view>
#include <unordered_map>

class Response {
private:
  std::string version_;
  std::string status_;
  std::string message_;
  std::unordered_map<std::string, std::string> headers_;
  std::string body_;

public:
  explicit Response() = default;
  explicit Response(const std::string &version, const std::string &status,
                    const std::string &message,
                    const std::unordered_map<std::string, std::string> headers,
                    const std::string body);

  explicit Response(const std::string_view raw);
  explicit Response(const Response &response);
  explicit Response(Response &&response);

  const std::string version() const;
  const std::string status() const;
  const std::string message() const;
  const std::string body() const;
  const std::unordered_map<std::string, std::string> headers() const;
  const std::string header_query(const std::string &key) const;

  const std::string to_string() const;
};
