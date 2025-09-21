#include <sstream>
#include <string>
#include <vector>

inline std::vector<std::string> split(const std::string str,
                                      const char delimiter) {
  std::vector<std::string> tokens;
  std::stringstream ss(str);
  std::string token;

  while (std::getline(ss, token, delimiter)) {
    tokens.push_back(token);
  }

  return tokens;
}

// trim
inline std::string trim(std::string str) {
  std::string s_copy(str);
  s_copy.erase(0, str.find_last_not_of(" \n\r\t"));
  s_copy.erase(0, str.find_first_not_of(" \n\r\t") + 1);
  return s_copy;
}

// ltrim
inline std::string ltrim(const std::string str) {
  std::string s_copy(str);
  s_copy.erase(0, str.find_last_not_of(" \n\r\t"));
  return s_copy;
}

// rtrim
inline std::string rtrim(const std::string str) {
  std::string s_copy(str);
  s_copy.erase(0, str.find_first_not_of(" \n\r\t"));
  return s_copy;
}
