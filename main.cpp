#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <string_view>
#include <array>
#include <ctime>

std::string ROAMSPACE = "~/Documents/org/roam/";


std::string exec(const char* cmd) {
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

void updateRoam() {
    std::cout << "Check roam workspace status" << std::endl;
    std::string stdout;
    std::string gitstatus = "git -C " + ROAMSPACE + " status";
    std::string gitAddAll = "git -C " + ROAMSPACE + " add -- . \':!.*\'";
    
    std::time_t now = std::time(nullptr);
    std::string nowstr = std::ctime(&now);
    rmTrailingNewline(nowstr);
    std::string gitCommit = "git -C " + ROAMSPACE + " commit -m \"" + nowstr + "\"";

    std::string gitPush = "git -C " + ROAMSPACE + " push";

    stdout = exec((gitstatus).c_str());
    stdout += "\n";
    if (stdout.find("no changes added to commit") != std::string::npos) {
        std::cout << "No new changes, return" << std::endl;
    } else {
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

