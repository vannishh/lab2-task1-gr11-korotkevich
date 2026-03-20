#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * @file task1.c
 * @brief Программа для поиска шестизначных счастливых номеров
 * @author Иванов Иван, группа 11
 * @version 1.0
 */

/**
 * @brief Проверяет, является ли число счастливым
 * @param number Шестизначное число для проверки
 * @return true если число счастливое, false в противном случае
 */
bool is_lucky_number(int number) {
    /* Проверка, что число шестизначное */
    if (number < 100000 || number > 999999) {
        return false;
    }

    /* Вычисление суммы первых трех цифр */
    int first_three_sum = 0;
    int temp = number;

    for (int i = 0; i < 3; i++) {
        first_three_sum += temp % 10;
        temp /= 10;
    }

    /* Вычисление суммы последних трех цифр */
    int last_three_sum = 0;
    for (int i = 0; i < 3; i++) {
        last_three_sum += temp % 10;
        temp /= 10;
    }

    return (first_three_sum == last_three_sum);
}

/**
 * @brief Выводит счастливый номер в форматированном виде
 * @param number Счастливый номер
 */
void print_lucky_number(int number) {
    printf("%06d\n", number);
}

/**
 * @brief Главная функция программы
 * @param argc Количество аргументов командной строки
 * @param argv Аргументы командной строки
 * @return 0 при успешном выполнении
 */
int main(int argc, char* argv[]) {
    int count = 0;

    printf("Шестизначные счастливые номера:\n");
    printf("================================\n\n");

    /* Перебор всех шестизначных чисел */
    for (int number = 100000; number <= 999999; number++) {
        if (is_lucky_number(number)) {
            print_lucky_number(number);
            count++;
        }
    }

    printf("\n================================\n");
    printf("Общее количество счастливых номеров: %d\n", count);

    return EXIT_SUCCESS;
}