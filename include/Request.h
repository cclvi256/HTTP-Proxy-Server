#ifndef REQUEST_H_
#define REQUEST_H_

#include <map>
#include <string>
#include <unordered_map>
#include <variant>

enum class Method {
  GET,
  POST,
  PUT,
  DELETE,
  OPTIONS,
  HEAD,
  PATCH,
  CONNECT,
  OTHER
};

class Request {
 private:
  std::string version_;
  std::variant<Method, std::string> method_;
  std::string path_;
  std::unordered_map<std::string, std::string> headers_;

 public:
  Request() = default;
  Request(std::string version, std::variant<Method, std::string> method,
                 std::string path,
                 std::unordered_map<std::string, std::string> headers)
      : version_(version), method_(method), path_(path), headers_(headers) {};
  Request(std::string request_str);

  std::string version() const;
  std::variant<Method, std::string> method() const;
  std::string path() const;
  std::unordered_map<std::string, std::string> headers() const;

  /// @brief Get the value of a header by its name
  /// @param key Name of the header
  /// @return Value to the key's name
  std::string header_by_key(const std::string &key) const;
  void add_header(const std::string &key, const std::string &value);
  bool remove_header(const std::string &key);

  std::string to_string() const;
  static Request parse(const std::string &raw);

  virtual ~Request() = default;
};

#endif // REQUEST_H_
