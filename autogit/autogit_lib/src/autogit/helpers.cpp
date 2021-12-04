#include "autogit/helpers.hpp"

#include <array>
#include <ctime>
#include <memory>
#include <stdexcept>
#include <cstdio>

namespace autogit {

std::string exec(const char *cmd) {
  // Run cli and return stdout
  std::array<char, 128> buffer;
  std::string result;
  std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
  if (!pipe) {
    throw std::runtime_error("popen() failed!");
  }
  while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
    result += buffer.data();
  }
  return result;
}

void rmTrailingNewline(std::string &s) {
  int pos;
  if ((pos = s.find('\n')) != std::string::npos)
    s.erase(pos);
}

std::string getCurrentTime() {
  std::time_t now = std::time(nullptr);
  std::string nowstr = std::ctime(&now);
  rmTrailingNewline(nowstr); // Using inline operation might be a bad idea
  return nowstr;
}

} // namespace autogit
