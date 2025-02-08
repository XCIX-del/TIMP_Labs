/** @file
* @author Солдатенков А.Д.
* @version 1.0
* @date 08.01.2025
* @copyright ИБСТ ПГУ
* @brief Исполняемый файл класса ui
*/
#include <iostream>
#include <cctype>
#include <clocale>
#include <string>
#include <boost/program_options.hpp>
#include "ui.h"
UI::UI(int argc, char *argv[])
{
    desc.add_options()
    ("help,h", "Помощь")
    ("string,s", po::value<std::vector<std::string>>()->multitoken(), "Строка для проведения операции")
    ("action,a", po::value<std::vector<uint>>()->multitoken(), "1-encrypt, 2-decrypt")
    ("key,k", po::value<std::vector<double>>()->multitoken(), "Количество столбцов в таблице");

    try
    {
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);
        if (vm.count("help") or !vm.count("string") or !vm.count("action") or !vm.count("key"))
        {
            std::cout << desc << std::endl;
            exit(0);
        }
    }
    catch (po::error &e)
    {
        std::cout << e.what() << std::endl;
    }
}

uint UI::get_action()
{
    if (vm.count("action"))
    {
        const std::vector<uint> &action = vm["action"].as<std::vector<uint>>();
        return action.back();
    }
    else
    {
        std::cout << desc << std::endl;
        std::exit(1);
    }
}

double UI::get_key()
{
    if (vm.count("key"))
    {
        const std::vector<double> &key = vm["key"].as<std::vector<double>>();
        return key.back();
    }
    else
    {
        std::cout << desc << std::endl;
        std::exit(1);
    }
}

std::string UI::get_string()
{
    if (vm.count("string"))
    {
        const std::vector<std::string> &string = vm["string"].as<std::vector<std::string>>();
        return string.back();
    }
    else
    {
        std::cout << desc << std::endl;
        return "";
        std::exit(1);
    }
}
