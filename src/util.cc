#include "util.h"

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