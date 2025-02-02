#include <iostream>
#include <cctype>
#include <clocale>
#include <string>
#include "table_cipher.h"
#include "ui.h"
#include <boost/program_options.hpp>

int main(int argc, char **argv)
{
    UI interface(argc, argv);
    double key = interface.get_key();
    std::string word = interface.get_string();
    uint act = interface.get_action();
    table_cipher cipher(word, key);
    if (act == 1)
    {
        std::cout << cipher.encrypt() << std::endl;
    }
    else if (act == 2)
    {
        std::cout << cipher.decrypt() << std::endl;
    }
    return 0;
}
