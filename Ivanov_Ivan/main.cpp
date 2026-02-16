#include <stdio.h>

using RUB = long long;

// ====================== СТРУКТУРЫ ======================

struct BankAccount {
    RUB balance;      // обычный банковский счет
};

struct Deposit {
    RUB balance;      // вклад
    float percent;    // годовая ставка %
};

struct Bank {
    BankAccount account;
    Deposit deposit;
};

struct Car {
    RUB value;        // стоимость машины
    RUB gas;          // расходы на бензин в месяц
};

struct Pet {
    RUB cost;         // стоимость питомца
    RUB food;         // расходы на еду
};

struct Person {
    RUB salary;
    RUB food;         // расходы на еду человека

    Car car;
    Pet pet;
    Bank bank;
};

Person Alice;

// ====================== НАСТРОЙКИ ======================

float inflation = 10.0;     // инфляция 10% в год
float deposit_rate = 14.0;  // ставка по вкладу 14% годовых


// ====================== ФУНКЦИИ ======================

// Зарплата приходит на банковский счет
void alice_salary(int month, int year)
{
    if ((month == 8) && (year == 2026)) {
        Alice.salary *= 1.5;  // повышение
    }

    Alice.bank.account.balance += Alice.salary;
}


// Перевод денег с банковского счета на вклад
void alice_to_deposit(RUB amount)
{
    if (Alice.bank.account.balance >= amount) {
        Alice.bank.account.balance -= amount;
        Alice.bank.deposit.balance += amount;
    }
}


// Начисление процентов на вклад
void alice_deposit_interest()
{
    Alice.bank.deposit.balance +=
        Alice.bank.deposit.balance * (Alice.bank.deposit.percent / 12.0 / 100.0);
}


// Расходы списываются с банковского счета
void alice_food()
{
    Alice.bank.account.balance -= Alice.food;
}

void alice_car()
{
    Alice.bank.account.balance -= Alice.car.gas;
}

void alice_pet()
{
    Alice.bank.account.balance -= Alice.pet.food;
}


// Инфляция (раз в год — в январе)
void inflation_update(int month)
{
    if (month == 1) {
        float k = 1 + inflation / 100.0;

        Alice.food *= k;
        Alice.car.gas *= k;
        Alice.car.value *= k;
        Alice.pet.food *= k;
        Alice.pet.cost *= k;
    }
}


// Инициализация
void alice_init()
{
    Alice.salary = 180000;
    Alice.food = 20000;

    Alice.car.value = 2400000;
    Alice.car.gas = 15000;

    Alice.pet.cost = 20000;
    Alice.pet.food = 5000;

    Alice.bank.account.balance = 0;
    Alice.bank.deposit.balance = 0;
    Alice.bank.deposit.percent = deposit_rate;
}


// Симуляция жизни
void simulation()
{
    int month = 2;
    int year = 2026;

    while (!((month == 3) && (year == 2027)))
    {
        inflation_update(month);

        alice_food();
        alice_car();
        alice_pet();

        alice_deposit_interest();
        alice_salary(month, year);

        // пример: каждый месяц откладываем 50 000 на вклад
        alice_to_deposit(50000);

        ++month;
        if (month == 13) {
            month = 1;
            ++year;
        }
    }
}


// Вывод результатов
void print_results()
{
    printf("Salary = %lld\n", Alice.salary);
    printf("Bank account = %lld\n", Alice.bank.account.balance);
    printf("Deposit = %lld\n", Alice.bank.deposit.balance);
    printf("Car price (inflated) = %lld\n", Alice.car.value);
}


// ====================== MAIN ======================

int main()
{
    alice_init();
    simulation();
    print_results();
}

