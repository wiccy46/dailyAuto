#include <autogit/roam/Update.hpp>
#include <iostream>
#include <cxxopts.hpp>


int main(int argc, char *argv[]) {
    cxxopts::Options options("Automate", "Collection of some daily automations");

    options.add_options()
        ("r,roam", "Sync roam", cxxopts::value<bool>()->default_value("false"))
        ("a,amend", "amend, then force push", cxxopts::value<bool>()->default_value("false"))
        ;
    
    try
    {
        auto result = options.parse(argc, argv);
        if (result.arguments().size() == 0 && argc > 1)
        {
            throw std::invalid_argument("No valid arguments given");
        }
        if (result.count("help"))
        {
            std::cout << options.help() << std::endl;
        }
        bool roam = result["roam"].as<bool>();
        bool amend = result["amend"].as<bool>();
        if (roam) 
        {
            autogit::roam::addAndPush(amend);
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    std::cout << "Finished." << std::endl;
}

