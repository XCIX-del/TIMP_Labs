#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

class table_cipher
{
public:
    uint key;
    double rows;
    std::string t;
    std::vector<std::vector<std::string>> str_matrix;
    std::string encrypt();
    std::string decrypt();
    void fillVector(std::vector<std::vector<std::string>> &v, const std::string &text);
    void fillVector_for_decrypt(std::vector<std::vector<std::string>> &v, const std::string &text);
    void text_validation(std::string &text);
    void key_validation(uint &key,std::string &text);
    table_cipher(std::string text, uint k);
};
class table_cipher_error: public std::invalid_argument
{
public:
    explicit table_cipher_error (const std::string& what_arg):
        std::invalid_argument(what_arg) {}
    explicit table_cipher_error (const char* what_arg):
        std::invalid_argument(what_arg) {}
};