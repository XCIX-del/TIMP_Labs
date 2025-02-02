#include "table_cipher.h"
table_cipher::table_cipher(std::string text, uint k) : key(k)
{
    text.erase(std::remove(text.begin(), text.end(), ' '), text.end());
    t = text;
    rows = std::ceil(static_cast<double>(t.length()) / key);
    str_matrix.assign(rows, std::vector<std::string>(key, " "));
}
void table_cipher::fillVector(std::vector<std::vector<std::string>> &v, const std::string &text)
{
    int l = 0;
    for (int i = 0; i < v.size(); i++)
    {
        for (int j = 0; j < v[i].size(); ++j)
        {
            if (l < text.length())
            {
                v[i][j] = text[l];
                l++;
            }
        }
    }
}
void table_cipher::fillVector_for_decrypt(std::vector<std::vector<std::string>> &v, const std::string &text)
{
    int l = 0;
    for (int j = key - 1; j >= 0; j--)
    {
        for (int i = 0; i < rows; i++)
        {
            if (l < text.length())
            {
                if (v[i][j] == " ")
                {
                    continue;
                }
                v[i][j] = text[l];
                l++;
            }
            else
            {
                break;
            }
        }
    }
}
std::string table_cipher::encrypt()
{
    fillVector(str_matrix, t);
    std::string res;
    for (int j = key - 1; j >= 0; j--)
    {
        for (int i = 0; i < rows; i++)
        {
            res += str_matrix[i][j];
        }
    }
    res.erase(std::remove(res.begin(), res.end(), ' '), res.end());
    return res;
}
std::string table_cipher::decrypt()
{
    fillVector(str_matrix, t);
    fillVector_for_decrypt(str_matrix, t);
    std::string res;
    for (int i = 0; i < str_matrix.size(); i++)
    {
        for (int j = 0; j < str_matrix[i].size(); ++j)
        {
            res += str_matrix[i][j];
        }
    }
    res.erase(std::remove(res.begin(), res.end(), ' '), res.end());
    return res;
}
