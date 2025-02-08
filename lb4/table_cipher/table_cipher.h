/** @file
* @author Солдатенков А.Д.
* @version 1.0
* @date 08.01.2025
* @copyright ИБСТ ПГУ
* @brief Определение класса table_cipher для шифрования методом табличной перестановки.
*/

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

/**
 * @class table_cipher
 * @brief Класс для шифрования и дешифрования методом табличной перестановки.
 */
class table_cipher
{
public:
    uint key; ///< Ключ шифрования (количество столбцов в таблице)
    double rows; ///< Количество строк в таблице
    std::string t; ///< Исходный текст без пробелов
    std::vector<std::vector<std::string>> str_matrix; ///< Двумерный вектор для хранения таблицы шифрования

    /**
     * @brief Конструктор класса table_cipher
     * Происходит установка ключа, обработка ошибок текста и ключа
     * @param text Исходный текст
     * @param k Ключ (количество столбцов)
     * @throws table_cipher_error в случае некорректного ключа или текста
     */
    table_cipher(std::string text, uint k);

    /**
     * @brief Функция шифрования текста
     * Шифрование происходит путем считывания с матрицы, заполненной открытым текстом, в порядке сверху вниз справа налево
     * @return Зашифрованный текст
     */
    std::string encrypt();

    /**
     * @brief Функция расшифрования текста
     * Расшифрование просходит путем заполнения матрицы в порядке слева направо сверху вниз
     * Затем происходит "транспонирование матрицы" - последний столбец становится первой строкой и т.д
     * После матрица считывается в порядке слева направо сверху вниз
     * @return Расшифрованный текст
     */
    std::string decrypt();

    /**
     * @brief Заполняет матрицу символами для шифрования в порядке слева направо сверху вниз
     * @param v Двумерный вектор, в который записывается текст
     * @param text Исходный текст для заполнения матрицы
     */
    void fillVector(std::vector<std::vector<std::string>> &v, const std::string &text);

    /**
     * @brief Заполняет матрицу символами для дешифрования. Просходит транспонирование.
     * Последний столбец становится первой строкой и т.д.
     * @param v Двумерный вектор, в который записывается текст
     * @param text Зашифрованный текст для заполнения матрицы
     */
    void fillVector_for_decrypt(std::vector<std::vector<std::string>> &v, const std::string &text);

    /**
     * @brief Проверяет и преобразует текст перед шифрованием. Проверяется наличие посторонних символов и является ли строка пустой
     * @param text Исходный текст
     * @throws table_cipher_error в случае наличия недопустимых символов
     */
    void text_validation(std::string &text);

    /**
     * @brief Проверяет корректность ключа шифрования. Проверяется длина ключа
     * @param key Ключ шифрования
     * @param text Исходный текст
     * @throws table_cipher_error в случае некорректного ключа
     */
    void key_validation(uint &key, std::string &text);
};

/**
 * @class table_cipher_error
 * @brief Класс исключений для обработки ошибок в table_cipher.
 */
class table_cipher_error: public std::invalid_argument
{
public:
    /**
     * @brief Конструктор с сообщением об ошибке
     * @param what_arg Сообщение об ошибке
     */
    explicit table_cipher_error (const std::string& what_arg):
        std::invalid_argument(what_arg) {}
    
    /**
     * @brief Конструктор с сообщением об ошибке
     * @param what_arg Сообщение об ошибке
     */
    explicit table_cipher_error (const char* what_arg):
        std::invalid_argument(what_arg) {}
};
