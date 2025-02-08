#include <iostream>
#include <cctype>
#include <clocale>
#include <string>
#include "table_cipher.h"
#include "ui.h"
#include <boost/program_options.hpp>

int main(int argc, char **argv)
{
    try{
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
    }
    catch (po::error& e) {
        std::cout << e.what() << std::endl;
        exit(1);
    }
    catch(const table_cipher_error & e){
        std::cerr<<"Ошибка: "<<e.what()<<std::endl;
        exit(1);
    }
    return 0;
}
