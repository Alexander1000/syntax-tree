#include <syntax-tree.h>
#include <string>

namespace SyntaxTree
{
    Config::Config(int argc, char **argv)
    {
        // defaults:
        this->is_help = false;
        this->syntaxFile = nullptr;

        // initialize parameters
        for (int i = 1; i < argc; i++) {
            std::string paramName(argv[i]);

            if (paramName == "-h" || paramName == "--help") {
                this->is_help = true;
                break;
            }

            if (paramName == "-s" || paramName == "--syntax") {
                i++;
                int len = strlen(argv[i]);
                this->syntaxFile = (char*) malloc(sizeof(char) * (len + 1));
                memset(this->syntaxFile, 0, sizeof(char) * (len + 1));
                memcpy(this->syntaxFile, argv[i], len * sizeof(char));
                continue;
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

    char* Config::getSyntaxFile() {
        return this->syntaxFile;
    }
}
