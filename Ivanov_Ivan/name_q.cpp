#include <stdio.h>

using RUB = long long;

struct Car {
    RUB value;
    RUB gas;
};

struct Pet {
    RUB food;
};

struct Bank {
    RUB account;     // обычный счет
    RUB deposit;     // вклад
    float deposit_percent;
};

struct Person {
    RUB salary;
    RUB food;
    struct Car car;
    struct Pet pet;
    struct Bank bank;
};

struct Person Alice;

// процент по вкладу
float deposit_pp = 10.0;

// инфляция годовая
float inflation = 12.0;



void alice_salary(int month, int year) {
    if ((month == 8) && (year == 2026)) {
        Alice.salary = Alice.salary * 1.5;  // повышение
    }

    Alice.bank.account += Alice.salary;  // зарплата на счет
}



void alice_food() {
    Alice.bank.account -= Alice.food;
}

void alice_car() {
    Alice.bank.account -= Alice.car.gas;
}

void alice_pet() {
    Alice.bank.account -= Alice.pet.food;
}



void alice_deposit_transfer() {
    RUB transfer = 50000;  //  фиксированная сумма

    if (Alice.bank.account >= transfer) {
        Alice.bank.account -= transfer;
        Alice.bank.deposit += transfer;
    }
}



void alice_deposit_interest() {
    Alice.bank.deposit +=
        Alice.bank.deposit * (deposit_pp / 12.0 / 100.0);
}



void alice_inflation() {
    // инфляция раз в год в январе
    Alice.food += Alice.food * (inflation / 100.0);
    Alice.car.gas += Alice.car.gas * (inflation / 100.0);
    Alice.car.value += Alice.car.value * (inflation / 100.0);
    Alice.pet.food += Alice.pet.food * (inflation / 100.0);
}



void alice_init() {
    Alice.salary = 180000;
    Alice.food = 20000;

    Alice.car.value = 2400000;
    Alice.car.gas = 15000;

    Alice.pet.food = 5000;

    Alice.bank.account = 0;
    Alice.bank.deposit = 0;
    Alice.bank.deposit_percent = deposit_pp;
}



void print_results() {
    printf("Salary = %lld\n", Alice.salary);
    printf("Bank account = %lld\n", Alice.bank.account);
    printf("Deposit = %lld\n", Alice.bank.deposit);
    printf("Car price = %lld\n", Alice.car.value);
}



void simulation() {
    int month = 2;
    int year = 2026;

    while (!((month == 3) && (year == 2027))) {

        alice_salary(month, year);

        alice_food();
        alice_car();
        alice_pet();

        alice_deposit_transfer();
        alice_deposit_interest();

        if (month == 1) {
            alice_inflation();
        }

        ++month;
        if (month == 13) {
            month = 1;
            ++year;
        }
    }
}



int main() {
    alice_init();
    simulation();
    print_results();
}
