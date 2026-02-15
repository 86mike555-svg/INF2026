#include <stdio.h>

using RUB = long long;

float bank_rate = 14.5;     // % по депозиту (годовых)
float inflation = 8.0;      // инфляция % в год

struct Car {
    RUB value;
    RUB gas;
};

struct Bank {
    RUB account;   // обычный счет
    RUB deposit;   // вклад 
};

struct Person {
    RUB salary;
    RUB food;
    Car car;
    Bank bank;
};


struct Person Alice;

void alice_init()
{
    Alice.salary = 180'000;
    Alice.food = 20'000;

    Alice.car.value = 2'400'000;
    Alice.car.gas = 15'000;

    Alice.bank.account = 0;
    Alice.bank.deposit = 0;
}


void alice_salary(int month, int year)
{
    if (month == 8 && year == 2026) {
        Alice.salary *= 1.5;   
    }

    Alice.bank.account += Alice.salary;
}


void alice_expenses()
{
    Alice.bank.account -= Alice.food;
    Alice.bank.account -= Alice.car.gas;
}


void alice_transfer_to_deposit()
{
    RUB amount = Alice.bank.account / 2; //перевод половины на вклад
    Alice.bank.account -= amount;
    Alice.bank.deposit += amount;
}

void bank_interest()
{
    Alice.bank.deposit += 
        Alice.bank.deposit * (bank_rate / 12.0 / 100.0);
}

void apply_inflation()
{
    float k = inflation / 12.0 / 100.0;

    Alice.food += Alice.food * k;
    Alice.car.gas += Alice.car.gas * k;
    Alice.car.value += Alice.car.value * k;
}

void simulation()
{
    int month = 2;
    int year = 2026;

    while (!(month == 3 && year == 2027)) {

        apply_inflation();        // рост цен
        alice_salary(month, year);// зарплата
        alice_expenses();         // расходы
        alice_transfer_to_deposit();// перевод на вклад
        bank_interest();          // проценты

        ++month;
        if (month == 13) {
            month = 1;
            ++year;
        }
    }
}


void print_results()
{
    printf("Salary: %lld\n", Alice.salary);
    printf("Bank account: %lld\n", Alice.bank.account);
    printf("Deposit: %lld\n", Alice.bank.deposit);
    printf("Car price: %lld\n", Alice.car.value);
}

int main()
{
    alice_init();
    simulation();
    print_results();
}
