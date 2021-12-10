#include <autogit/roam/Update.hpp>
#include <iostream>


int main(int argc, char *argv[]) {
    // argv
    if ( argc == 2) {
        std::string opt = argv[1];
        if (opt == "roam") {
            autogit::roam::addAndPush();
        } else {
            std::cout << "Not Matched" << std::endl;
        }
    } else {
        std::cout << "No command given, options: roam" << std::endl;
    }
    std::cout << "Finished." << std::endl;
}

