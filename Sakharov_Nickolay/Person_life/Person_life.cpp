#include <stdio.h>
#include <iostream>
// typedef int RUB; // Ключевое слово, зарезервировано под функции языка, используют в С
using RUB = long long int; // Используют в С++, можно из одного места поменять типы данных многих переменных

struct Car
{
    RUB value;
    RUB gas;
};
struct Work
{
    RUB salary;
    float raising;
};
struct Bank
{
    RUB balance;
    RUB deposit;
    float percent;
};

struct Person
{ // создали свой тип данных
    Work work;
    RUB food;
    Car car;
    Bank bank;
    RUB deposit_sum;
};

Person Alice; // создали переменную типа данных Person

void alice_car()
{
    Alice.bank.balance -= Alice.car.gas;
}

void alice_salary(const int month, const int year)
{
    if ((month == 8) && (year == 2026))
    { // Promotion
        Alice.work.salary = Alice.work.salary * Alice.work.raising;
    }
    Alice.bank.balance += Alice.work.salary;
}
void alice_food()
{
    Alice.bank.balance -= Alice.food;
}
void alice_bank_interest()
{
    Alice.bank.deposit += Alice.deposit_sum;
    Alice.bank.balance -= Alice.deposit_sum;
}
void alice_deposit_percent()
{
    Alice.bank.deposit += Alice.bank.deposit * (Alice.bank.percent / 12 / 100);
}
void print_results()
{

    printf("Salary = %lld\n", Alice.work.salary);
    printf("Capital = %lld", Alice.bank.balance);
}
void simulation()
{

    int month = 2;
    int year = 2026;
    bool firstIteration = true;
    //  for (int month = 1; month < 19; ++month) {
    while (!((month == 3) && (year == 2127)))
    {
        // my_cat()
        // my_trip()
        alice_food();
        alice_car();
        alice_salary(month, year);

        if (!firstIteration)
        {
            alice_deposit_percent();
        }
        firstIteration = false;
        //
        alice_bank_interest();
        ++month;
        if (month == 13)
        {
            month = 1;
            ++year;
        }
    }
}
void alice_init()   
{
    Alice.bank.balance = 0;
    Alice.bank.deposit = 0;
    Alice.work.salary = 180000;
    Alice.food = 20000;
    Alice.car.value = 2400000;
    Alice.work.raising = 1.5;
    Alice.deposit_sum = 40000;
    Alice.bank.percent = 14;
}
int main()
{
    alice_init();

    simulation();

    print_results();
}

