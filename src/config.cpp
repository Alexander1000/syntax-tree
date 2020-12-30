#include <syntax-tree.h>
#include <string>

namespace SyntaxTree
{
    Config::Config(int argc, char **argv)
    {
        // defaults:
        this->is_help = false;

        // initialize parameters
        for (int i = 1; i < argc; i++) {
            std::string paramName(argv[i]);

            if (paramName == "-h" || paramName == "--help") {
                this->is_help = true;
                break;
            }
        }
    }

    bool Config::isHelp() {
        return this->is_help;
    }

    const char* Config::getHelpText() {
        return "Usage: syntax-tree [OPTIONS]\n"
               "Common options:\n"
               "    -h, --help                 Show this message and exit.\n"
               "    -s, --syntax [file]        Syntax tree file (eg. file.s).\n"
               "    -i, --inject [file]        File for inject.\n"
               "    -v, --version              Print version and exit.";
    }
}
