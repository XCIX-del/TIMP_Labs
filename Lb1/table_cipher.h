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
    table_cipher(std::string text, uint k);
};
