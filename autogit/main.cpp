#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <string_view>
#include <array>
#include <ctime>
#include <boost/algorithm/string.hpp>

std::string ROAMSPACE = "~/Documents/org/roam/";


std::string exec(const char* cmd) {
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

void rmTrailingNewline (std::string &s)
{
    int pos;
    if((pos=s.find('\n')) != std::string::npos)
            s.erase(pos);
}

std::string getCurrentTime()
{
    std::time_t now = std::time(nullptr);
    std::string nowstr = std::ctime(&now);
    rmTrailingNewline(nowstr); // Using inline operation might be a bad idea
    return nowstr;
}

void updateRoam() {
    std::cout << "Check roam workspace status" << std::endl;
    std::string stdout;
    std::string gitstatus = "git -C " + ROAMSPACE + " status";
    stdout = exec((gitstatus).c_str());
    stdout += "\n";
    bool has_changes = boost::algorithm::contains(stdout, "git add <file>");
    if (!has_changes) {
        std::cout << "No new changes, return..." << std::endl;
    } else {
        // git add all but remove any dotfile
        std::string gitAddAll = "git -C " + ROAMSPACE + " add -- . \':!.*\'";
        std::string gitCommit =
          "git -C " + ROAMSPACE + " commit -m \"" + getCurrentTime() + "\"";
        std::string gitPush = "git -C " + ROAMSPACE + " push";
        std::cout << gitAddAll << std::endl;
        stdout = exec((gitAddAll).c_str());
        std::cout << gitCommit << std::endl;
        stdout = exec((gitCommit).c_str());
        stdout = exec((gitPush).c_str());
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

