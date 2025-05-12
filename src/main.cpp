#include <iostream>
#include <stdexcept>
#include <string>

#include "app/app.h"

int main(const int argc, const char** argv)
{
    // if user wants to see the version of the program
    if (argc == 2 && std::string(argv[1]) == "-version")
    {
        std::cout << "Luna Renderer v" << LUNA_VERSION << "\n";
        std::cout << "© 2025 Cyberbrain. All Rights Reserved.\n";

        return 0;
    }

    std::string pathToModel;

    // if user wants to load and to render a model
    if (argc == 3 && std::string(argv[1]) == "-f")
    {
        pathToModel = argv[2];
    }
    else
    {
        // if arguments are incorrect
        std::cerr << "luna-renderer: Invalid arguments" << std::endl;
        return -1;
    }

    // Running an application
    try
    {
        application::App app{pathToModel};
        app.run();
    }
    catch (const std::runtime_error& ex)
    {
        std::cerr << "luna-renderer: " << ex.what() << std::endl;
        return -2;
    }

    return 0;
}