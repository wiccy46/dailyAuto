#pragma once

#include <string>

namespace autogit {

  std::string exec(const char *cmd);
  std::string getCurrentTime();
  void rmTrailingNewline (std::string &s);

  }  // namespace autogit
