#include "modAlphaCipher.h"
modAlphaCipher::modAlphaCipher()
{
}
void modAlphaCipher::start(const std::wstring &skey)
{
    for (unsigned i = 0; i < numAlpha.size(); i++)
    {
        alphaNum[numAlpha[i]] = i;
    }
    key = convert(skey);
}
std::wstring modAlphaCipher::key_validation(std::wstring key, const std::wstring &text){
    key = getValidString(key);
    while (key.length() < text.length()) {
        key += key.substr(0, text.length() - key.length()); 
    }
    //std::wcout <<L"Key: "<< key <<L" text: "<<text<< std::endl;
    return key;
}
std::wstring modAlphaCipher::encrypt(const std::wstring &open_text)
{
    std::wstring temp = getValidString(open_text);
    std::vector<int> work = convert(temp);
    for (unsigned i = 0; i < work.size(); i++)
    {
        work[i] = (work[i] + key[i % key.size()]) % alphaNum.size();
    }
    return convert(work);
}
std::wstring modAlphaCipher::decrypt(const std::wstring &cipher_text)
{
    std::wstring temp = getValidString(cipher_text);
    std::vector<int> work = convert(temp);
    for (unsigned i = 0; i < work.size(); i++)
    {
        work[i] = (work[i] + alphaNum.size() - key[i % key.size()]) % alphaNum.size();
    }
    return convert(work);
}
inline std::vector<int> modAlphaCipher::convert(const std::wstring &s)
{
    std::vector<int> result;
    for (auto c : s)
    {
        result.push_back(alphaNum[c]);
    }
    return result;
}
inline std::wstring modAlphaCipher::convert(const std::vector<int> &v)
{
    std::wstring result;
    for (auto i : v)
    {
        result.push_back(numAlpha[i]);
    }
    return result;
}
inline std::wstring modAlphaCipher::getValidString(const std::wstring &s)
{
    if (s.empty())
        throw cipher_error("Пустые данные");

    std::wstring tmp;
    for (auto &c : s)
    {
        if (!iswalpha(c)){
            //throw cipher_error("В данных присутствуют символы не из алфавита ");
            continue;
        }
        tmp.push_back(towupper(c));
    }

    for (int i = 0; i < tmp.length(); i++)
    {
        if (numAlpha.find(tmp[i]) == std::wstring::npos)
        {
            throw cipher_error("Алфавит данных не русский ");
        }
    }
    tmp.erase(remove(tmp.begin(), tmp.end(), L' '), tmp.end());
    return tmp;
}
