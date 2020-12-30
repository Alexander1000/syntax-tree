#include <syntax-tree.h>
#include <string>

namespace SyntaxTree
{
    Config::Config(int argc, char **argv)
    {
        // defaults:
        this->is_help = false;
        this->syntaxFile = nullptr;
        this->injectFile = nullptr;

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

            if (paramName == "-i" || paramName == "--inject") {
                i++;
                int len = strlen(argv[i]);
                this->injectFile = (char*) malloc(sizeof(char) * (len + 1));
                memset(this->injectFile, 0, sizeof(char) * (len + 1));
                memcpy(this->injectFile, argv[i], len * sizeof(char));
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

    char* Config::getInjectFile() {
        return this->injectFile;
    }
}
