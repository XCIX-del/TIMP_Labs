/** @file
* @author Солдатенков А.Д.
* @version 1.0
* @date 08.01.2025
* @copyright ИБСТ ПГУ
* @brief Определение класса modAlphaCipher для шифрования и дешифрования методом простой замены.
*/
#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <cctype>
#include <locale>
#include <algorithm>

/**
 * @class modAlphaCipher
 * @brief Класс для шифрования и дешифрования текста методом простой замены на основе алфавита.
 */
class modAlphaCipher
{
private:
    std::wstring numAlpha = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"; ///< Русский алфавит
    std::map<wchar_t, int> alphaNum; ///< Словарь соответствий символов алфавита их числовым значениям
    std::vector<int> key; ///< Вектор числовых значений ключа
    
    /**
     * @brief Конвертирует строку в вектор числовых значений.
     * @param s Строка для конвертации.
     * @return Вектор числовых значений.
     */
    std::vector<int> convert(const std::wstring& s);
    
    /**
     * @brief Конвертирует вектор числовых значений обратно в строку.
     * @param v Вектор числовых значений.
     * @return Строка.
     */
    std::wstring convert(const std::vector<int>& v);

public:
    /**
     * @brief Универсальная функция проверки правильности строки.
     * Небуквенные символы пропускаются. Если строка пустая или содержит буквы из нерусского алфавита, то возбуждается исключение
     * @param s Входная строка.
     * @return Очищенная и валидная строка.
     */
    std::wstring getValidString(const std::wstring& s);

    /**
     * @brief Проверка ключа. Используется метод getValidString, затем ключ дополняется до необходимой длины
     * @param key Ключ для проверки.
     * @param text Исходный текст.
     * @return Скорректированный ключ.
     */
    std::wstring key_validation(std::wstring key, const std::wstring& text);

    /**
     * @brief Инициализация объекта класса заданным ключом.
     * @param skey Ключ шифрования.
     */
    void start(const std::wstring& skey);

    /**
     * @brief Конструктор по умолчанию.
     * Используется для внедрения корректной обработки ошибок ключа
     */
    modAlphaCipher();

        /**
     * @brief Шифрует переданный открытый текст с использованием алфавитного шифра.
     * 
     * Функция принимает открытый текст, преобразует его в числовые значения, 
     * выполняет поэлементное сложение с ключом по модулю длины алфавита 
     * и возвращает зашифрованный текст.
     * 
     * @param open_text Открытый текст, который необходимо зашифровать.
     * @return std::wstring Зашифрованный текст, полученный в результате шифрования.
     * @throw cipher_error Если входной текст содержит недопустимые символы или является пустым.
     */
    std::wstring encrypt(const std::wstring& open_text);

    /**
     * @brief Дешифрует переданный зашифрованный текст с использованием алфавитного шифра.
     * 
     * Функция принимает зашифрованный текст, преобразует его в числовые значения, 
     * выполняет поэлементное вычитание ключа по модулю длины алфавита 
     * и возвращает расшифрованный текст.
     * 
     * @param cipher_text Зашифрованный текст, который необходимо расшифровать.
     * @return std::wstring Расшифрованный текст, полученный в результате дешифрования.
     * @throw cipher_error Если входной текст содержит недопустимые символы или является пустым.
     */
    std::wstring decrypt(const std::wstring& cipher_text);

};

/**
 * @class cipher_error
 * @brief Класс исключений для ошибок шифрования.
 */
class cipher_error: public std::invalid_argument
{
public:
    /**
     * @brief Конструктор исключения с сообщением.
     * @param what_arg Сообщение об ошибке.
     */
    explicit cipher_error(const std::string& what_arg) : std::invalid_argument(what_arg) {}
    
    /**
     * @brief Конструктор исключения с сообщением.
     * @param what_arg Сообщение об ошибке.
     */
    explicit cipher_error(const char* what_arg) : std::invalid_argument(what_arg) {}
};
