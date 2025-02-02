#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <boost/program_options.hpp>
#include "table_cipher.h"

namespace po = boost::program_options;

class UI {
public:
    // Конструктор для обработки аргументов командной строки
    UI(int argc, char* argv[]);

    // Методы для получения параметров
    uint get_action();
    double get_key();
    std::string get_string();

private:
    po::options_description desc;  // Описание доступных аргументов
    po::variables_map vm;          // Карта параметров командной строки
};
