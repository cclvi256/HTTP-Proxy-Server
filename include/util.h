#pragma once

#include <unordered_map>
#include <string>

struct RequestLine {
  std::string method;
  std::string uri;
  std::string version;
};

struct StatusLine {
  std::string version;
  std::string status;
  std::string message;
};

std::unordered_map<std::string, std::string>
parse_headers(std::string_view raw);
