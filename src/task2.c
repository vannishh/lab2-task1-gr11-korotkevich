#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
 * @file task2.c
 * @brief Программа для работы со структурой STUDENT
 * @author Иванов Иван, группа 11
 * @version 1.0
 */

#define STUDENTS_COUNT 7
#define GRADES_COUNT 4

/**
 * @brief Структура, содержащая информацию о студенте
 */
typedef struct {
    char surname[50];           /* Фамилия и инициалы */
    int group_number;           /* Номер группы */
    int grades[GRADES_COUNT];   /* Успеваемость (4 оценки) */
} STUDENT;

/**
 * @brief Ввод данных о студенте с клавиатуры
 * @param student Указатель на структуру STUDENT
 */
void input_student(STUDENT* student) {
    printf("Введите фамилию и инициалы: ");
    getchar(); /* Очистка буфера */
    fgets(student->surname, sizeof(student->surname), stdin);
    /* Удаление символа новой строки */
    student->surname[strcspn(student->surname, "\n")] = '\0';

    printf("Введите номер группы: ");
    scanf("%d", &(student->group_number));

    printf("Введите 4 оценки (через пробел): ");
    for (int i = 0; i < GRADES_COUNT; i++) {
        scanf("%d", &(student->grades[i]));
        /* Проверка корректности оценки */
        if (student->grades[i] < 1 || student->grades[i] > 5) {
            printf("Ошибка: оценка должна быть от 1 до 5\n");
            i--; /* Повторный ввод */
        }
    }
}

/**
 * @brief Создание массива студентов (ввод данных)
 * @param students Массив структур STUDENT
 * @param size Размер массива
 */
void create_students_array(STUDENT* students, int size) {
    printf("\n=== Ввод данных о студентах ===\n");
    for (int i = 0; i < size; i++) {
        printf("\nСтудент %d:\n", i + 1);
        input_student(&students[i]);
    }
}

/**
 * @brief Вычисление среднего балла студента
 * @param student Указатель на структуру STUDENT
 * @return Средний балл студента
 */
float calculate_average_grade(const STUDENT* student) {
    int sum = 0;
    for (int i = 0; i < GRADES_COUNT; i++) {
        sum += student->grades[i];
    }
    return (float)sum / GRADES_COUNT;
}

/**
 * @brief Сортировка студентов по убыванию среднего балла
 * @param students Массив структур STUDENT
 * @param size Размер массива
 */
void sort_by_average_grade(STUDENT* students, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            float avg1 = calculate_average_grade(&students[j]);
            float avg2 = calculate_average_grade(&students[j + 1]);

            if (avg1 < avg2) {
                /* Обмен элементов */
                STUDENT temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}

/**
 * @brief Вывод информации о студенте
 * @param student Указатель на структуру STUDENT
 */
void print_student(const STUDENT* student) {
    printf("%-25s | Группа: %-5d | Оценки: ", 
           student->surname, student->group_number);
    for (int i = 0; i < GRADES_COUNT; i++) {
        printf("%d ", student->grades[i]);
    }
    printf("| Средний балл: %.2f\n", calculate_average_grade(student));
}

/**
 * @brief Вывод студентов, имеющих только оценки 4 и 5
 * @param students Массив структур STUDENT
 * @param size Размер массива
 * @return Количество студентов с оценками 4 и 5
 */
int print_excellent_students(const STUDENT* students, int size) {
    int count = 0;
    printf("\n=== Студенты с оценками только 4 и 5 ===\n");

    for (int i = 0; i < size; i++) {
        bool has_only_good_grades = true;

        for (int j = 0; j < GRADES_COUNT; j++) {
            if (students[i].grades[j] < 4) {
                has_only_good_grades = false;
                break;
            }
        }

        if (has_only_good_grades) {
            print_student(&students[i]);
            count++;
        }
    }

    if (count == 0) {
        printf("Студентов с оценками только 4 и 5 не найдено.\n");
    }

    return count;
}

/**
 * @brief Удаление студента с минимальным средним баллом
 * @param students Массив структур STUDENT
 * @param size Указатель на размер массива
 * @return true если удаление выполнено успешно
 */
bool remove_student_with_min_average(STUDENT* students, int* size) {
    if (*size <= 0) {
        return false;
    }

    /* Поиск студента с минимальным средним баллом */
    int min_index = 0;
    float min_average = calculate_average_grade(&students[0]);

    for (int i = 1; i < *size; i++) {
        float current_avg = calculate_average_grade(&students[i]);
        if (current_avg < min_average) {
            min_average = current_avg;
            min_index = i;
        }
    }

    printf("\nУдаляется студент с минимальным средним баллом (%.2f):\n", 
           min_average);
    print_student(&students[min_index]);

    /* Сдвиг элементов влево */
    for (int i = min_index; i < *size - 1; i++) {
        students[i] = students[i + 1];
    }

    (*size)--;
    return true;
}

/**
 * @brief Вывод всех студентов
 * @param students Массив структур STUDENT
 * @param size Размер массива
 */
void print_all_students(const STUDENT* students, int size) {
    printf("\n=== Список всех студентов ===\n");
    for (int i = 0; i < size; i++) {
        printf("%d. ", i + 1);
        print_student(&students[i]);
    }
}

/**
 * @brief Главная функция программы
 * @param argc Количество аргументов командной строки
 * @param argv Аргументы командной строки
 * @return 0 при успешном выполнении
 */
int main(int argc, char* argv[]) {
    STUDENT students[STUDENTS_COUNT];
    int current_size = STUDENTS_COUNT;

    /* 1. Создание массива студентов */
    create_students_array(students, STUDENTS_COUNT);

    /* 2. Вывод всех студентов */
    print_all_students(students, current_size);

    /* 3. Вывод студентов с оценками только 4 и 5 */
    print_excellent_students(students, current_size);

    /* 4. Сортировка по убыванию среднего балла */
    sort_by_average_grade(students, current_size);
    printf("\n=== После сортировки по убыванию среднего балла ===\n");
    print_all_students(students, current_size);

    /* 5. Удаление студента с минимальным средним баллом */
    if (remove_student_with_min_average(students, &current_size)) {
        printf("\n=== После удаления студента ===\n");
        print_all_students(students, current_size);
    }

    return EXIT_SUCCESS;
}