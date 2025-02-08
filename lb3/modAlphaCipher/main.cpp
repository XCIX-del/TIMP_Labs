#include <iostream>
#include <clocale>
#include "modAlphaCipher.h"
using namespace std;
int main(int argc, char **argv)
{
    try
    {
        locale loc("ru_RU.UTF-8");
        locale::global(loc);
        wstring key;
        wstring text;
        unsigned op;
        wcout << L"Cipher ready. Input key: ";
        wcin >> key;
        wcout << L"Key loaded\n";
        modAlphaCipher cipher;
        do
        {
            wcout << L"Cipher ready. Input operation (0-exit, 1-encrypt, 2-decrypt): ";
            wcin >> op;
            if (op > 2)
            {
                wcout << L"Illegal operation\n";
            }
            else if (op > 0)
            {
                wcout << L"Cipher ready. Input text: ";
                wcin >> text;
                cipher.start(cipher.key_validation(key, text));
                if (op == 1)
                {
                    wcout << L"Encrypted text: " << cipher.encrypt(text) << endl;
                }
                else
                {
                    wcout << L"Decrypted text: " << cipher.decrypt(text) << endl;
                }
            }
        } while (op != 0);
    }
    catch (const cipher_error &e)
    {
        cerr << "Error: " << e.what() << endl;
        exit(1);
    }
    return 0;
}