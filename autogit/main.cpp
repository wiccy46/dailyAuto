// #include <cstdio>
// #include <string_view>
#include <autogit/helpers.hpp>
#include <boost/algorithm/string.hpp>
#include <iostream>

std::string ROAMSPACE = "~/Documents/org/roam/";


void updateRoam() {
    std::cout << "Check roam workspace status" << std::endl;
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
        std::string gitCommit =
          "git -C " + ROAMSPACE + " commit -m \"" + autogit::getCurrentTime() + "\"";
        std::string gitPush = "git -C " + ROAMSPACE + " push";
        std::cout << gitAddAll << std::endl;
        stdout = autogit::exec((gitAddAll).c_str());
        std::cout << gitCommit << std::endl;
        stdout = autogit::exec((gitCommit).c_str());
        stdout = autogit::exec((gitPush).c_str());
        std::cout << stdout << std::endl;
    }
}

int main(int argc, char *argv[]) {
    // argv
    if ( argc == 2) {
        std::string opt = argv[1];
        if (opt == "roam") {
            updateRoam();
        } else {
            std::cout << "Not Matched" << std::endl;
        }
    } else {
        std::cout << "No command run, options: roam" << std::endl;
    }
    std::cout << "Finished." << std::endl;
}

