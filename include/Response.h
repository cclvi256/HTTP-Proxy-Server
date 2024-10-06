#ifndef RESPONSE_H_
#define RESPONSE_H_

#include <map>
#include <string>
#include <unordered_map>

class Response {
 private:
  std::string version;
  int status_code;
  std::string message;

 public:
  inline Response(std::string version, int status_code, std::string message)
      : version(version), status_code(status_code), message(message) {};
  Response(std::string content);

  std::string getVersion() const;
  int getStatusCode() const;
  std::string getMessage() const;

  void setVersion(const std::string &version);
  void setStatusCode(int status_code);
  void setMessage(const std::string &message);

  std::string toString() const;
  static Response parse(const std::string &raw);

  virtual ~Response() = default;
};

#endif // RESPONSE_H_
