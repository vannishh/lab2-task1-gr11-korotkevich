#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
 * @file task3.c
 * @brief Программа для работы со структурой PURCHASER
 * @author Иванов Иван, группа 11
 * @version 1.0
 */

#define MAX_PURCHASERS 100

/**
 * @brief Структура для хранения даты рождения
 */
typedef struct {
    int year;   /* Год рождения */
    int month;  /* Месяц рождения */
    int day;    /* День рождения */
} DATE;

/**
 * @brief Структура для хранения адреса
 */
typedef struct {
    char postal_code[10];   /* Почтовый индекс */
    char country[50];       /* Страна */
    char region[50];        /* Область */
    char district[50];      /* Район */
    char city[50];          /* Город */
    char street[100];       /* Улица */
    char house[10];         /* Дом */
    char apartment[10];     /* Квартира */
} ADDRESS;

/**
 * @brief Структура, содержащая информацию о покупателе
 */
typedef struct {
    char surname[50];           /* Фамилия */
    char name[50];              /* Имя */
    char patronymic[50];        /* Отчество */
    char gender[10];            /* Пол */
    char nationality[30];       /* Национальность */
    int height;                 /* Рост (см) */
    int weight;                 /* Вес (кг) */
    DATE birth_date;            /* Дата рождения */
    char phone[20];             /* Номер телефона */
    ADDRESS address;            /* Домашний адрес */
    char credit_card[20];       /* Номер кредитной карточки */
    char bank_account[30];      /* Номер банковского счета */
} PURCHASER;

/**
 * @brief Ввод данных о покупателе с клавиатуры
 * @param purchaser Указатель на структуру PURCHASER
 */
void input_purchaser(PURCHASER* purchaser) {
    printf("Введите фамилию: ");
    scanf("%s", purchaser->surname);

    printf("Введите имя: ");
    scanf("%s", purchaser->name);

    printf("Введите отчество: ");
    scanf("%s", purchaser->patronymic);

    printf("Введите пол (М/Ж): ");
    scanf("%s", purchaser->gender);

    printf("Введите национальность: ");
    scanf("%s", purchaser->nationality);

    printf("Введите рост (см): ");
    scanf("%d", &(purchaser->height));

    printf("Введите вес (кг): ");
    scanf("%d", &(purchaser->weight));

    printf("Введите дату рождения (год месяц день): ");
    scanf("%d %d %d", &(purchaser->birth_date.year),
          &(purchaser->birth_date.month),
          &(purchaser->birth_date.day));

    printf("Введите номер телефона: ");
    scanf("%s", purchaser->phone);

    printf("--- Введите адрес ---\n");
    printf("Почтовый индекс: ");
    scanf("%s", purchaser->address.postal_code);
    printf("Страна: ");
    scanf("%s", purchaser->address.country);
    printf("Область: ");
    scanf("%s", purchaser->address.region);
    printf("Район: ");
    scanf("%s", purchaser->address.district);
    printf("Город: ");
    scanf("%s", purchaser->address.city);
    printf("Улица: ");
    scanf("%s", purchaser->address.street);
    printf("Дом: ");
    scanf("%s", purchaser->address.house);
    printf("Квартира: ");
    scanf("%s", purchaser->address.apartment);

    printf("Введите номер кредитной карточки: ");
    scanf("%s", purchaser->credit_card);

    printf("Введите номер банковского счета: ");
    scanf("%s", purchaser->bank_account);
}

/**
 * @brief Проверка, проживает ли покупатель в городе Брест
 * @param purchaser Указатель на структуру PURCHASER
 * @return true если покупатель из Бреста, false в противном случае
 */
bool is_from_brest(const PURCHASER* purchaser) {
    return (strcmp(purchaser->address.city, "Брест") == 0 ||
            strcmp(purchaser->address.city, "Brest") == 0);
}

/**
 * @brief Вывод информации о покупателе
 * @param purchaser Указатель на структуру PURCHASER
 */
void print_purchaser(const PURCHASER* purchaser) {
    printf("\n========================================\n");
    printf("ФИО: %s %s %s\n", purchaser->surname, 
           purchaser->name, purchaser->patronymic);
    printf("Пол: %s, Национальность: %s\n", 
           purchaser->gender, purchaser->nationality);
    printf("Рост: %d см, Вес: %d кг\n", 
           purchaser->height, purchaser->weight);
    printf("Дата рождения: %02d.%02d.%d\n", 
           purchaser->birth_date.day,
           purchaser->birth_date.month,
           purchaser->birth_date.year);
    printf("Телефон: %s\n", purchaser->phone);
    printf("Адрес: %s, %s, %s, %s, г. %s, ул. %s, д. %s, кв. %s\n",
           purchaser->address.postal_code,
           purchaser->address.country,
           purchaser->address.region,
           purchaser->address.district,
           purchaser->address.city,
           purchaser->address.street,
           purchaser->address.house,
           purchaser->address.apartment);
    printf("Кредитная карта: %s\n", purchaser->credit_card);
    printf("Банковский счет: %s\n", purchaser->bank_account);
    printf("========================================\n");
}

/**
 * @brief Вывод покупателей из города Брест
 * @param purchasers Массив структур PURCHASER
 * @param size Размер массива
 * @return Количество покупателей из Бреста
 */
int print_brest_purchasers(const PURCHASER* purchasers, int size) {
    int count = 0;
    printf("\n=== Покупатели из города Брест ===\n");

    for (int i = 0; i < size; i++) {
        if (is_from_brest(&purchasers[i])) {
            print_purchaser(&purchasers[i]);
            count++;
        }
    }

    if (count == 0) {
        printf("Покупателей из города Брест не найдено.\n");
    } else {
        printf("\nВсего покупателей из Бреста: %d\n", count);
    }

    return count;
}

/**
 * @brief Вывод всех покупателей
 * @param purchasers Массив структур PURCHASER
 * @param size Размер массива
 */
void print_all_purchasers(const PURCHASER* purchasers, int size) {
    printf("\n=== Список всех покупателей ===\n");
    for (int i = 0; i < size; i++) {
        printf("\nПокупатель %d:", i + 1);
        print_purchaser(&purchasers[i]);
    }
}

/**
 * @brief Главная функция программы
 * @param argc Количество аргументов командной строки
 * @param argv Аргументы командной строки
 * @return 0 при успешном выполнении
 */
int main(int argc, char* argv[]) {
    PURCHASER purchasers[MAX_PURCHASERS];
    int count = 0;
    int n;

    /* Проверка аргументов командной строки */
    if (argc != 2) {
        printf("Использование: %s <количество_покупателей>\n", argv[0]);
        return EXIT_FAILURE;
    }

    n = atoi(argv[1]);
    if (n <= 0 || n > MAX_PURCHASERS) {
        printf("Ошибка: количество покупателей должно быть от 1 до %d\n", 
               MAX_PURCHASERS);
        return EXIT_FAILURE;
    }

    /* Ввод данных о покупателях */
    printf("=== Ввод данных о покупателях ===\n");
    for (int i = 0; i < n; i++) {
        printf("\nПокупатель %d:\n", i + 1);
        input_purchaser(&purchasers[i]);
        count++;
    }

    /* Вывод всех покупателей */
    print_all_purchasers(purchasers, count);

    /* Вывод покупателей из Бреста */
    print_brest_purchasers(purchasers, count);

    return EXIT_SUCCESS;
}