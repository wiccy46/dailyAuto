#include "autogit/helpers.hpp"
#include "autogit/roam/Update.hpp"
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <cstdio>
#include <string_view>


namespace autogit::roam {

std::string ROAMSPACE = "~/Documents/org/roam/";

void addAndPush(bool amend) {
  std::cout << "Update Roam: Step 1. Git status" << std::endl;
  std::string stdout;
  std::string gitstatus = "git -C " + ROAMSPACE + " status";
  stdout = autogit::exec((gitstatus).c_str());
  stdout += "\n";
  bool has_changes = boost::algorithm::contains(stdout, "git add <file>");
  if (!has_changes) {
    std::cout << "No new changes, return..." << std::endl;
  } else {
    // git add all but remove any dotfile
    std::string gitAddAll = "git -C " + ROAMSPACE + " add -- . \':!.*\'";
    std::string gitCommit;
    std::string gitPush;
    if (!amend)
    {
      gitCommit = "git -C " + ROAMSPACE + " commit -m \"" +
                              autogit::getCurrentTime() + "\"";
      gitPush = "git -C " + ROAMSPACE + " push";
    } else 
    {
      gitCommit = "git -C " + ROAMSPACE + " commit --amend -m \"" +
                              autogit::getCurrentTime() + "\"";

      gitPush = "git -C " + ROAMSPACE + " push --force";
    }
    std::cout << gitAddAll << std::endl;
    stdout = autogit::exec((gitAddAll).c_str());
    std::cout << gitCommit << std::endl;
    stdout = autogit::exec((gitCommit).c_str());
    stdout = autogit::exec((gitPush).c_str());
    std::cout << stdout << std::endl;
  }
}

} // namespace autogit::roam
