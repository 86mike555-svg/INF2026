#include <stdio.h>

using RUB = long long;

// =======================
// ГЛОБАЛЬНЫЕ ПЕРЕМЕННЫЕ
// =======================

RUB salary;

RUB bank_account;
RUB bank_deposit;

RUB food_cost;
RUB car_price;
RUB car_gas;

RUB hamster_cost;

float deposit_percent = 10.0;
float inflation_percent = 12.0;


// =======================
// ИНИЦИАЛИЗАЦИЯ
// =======================

void init_salary() {
    salary = 180000;
}

void init_bank() {
    bank_account = 0;
    bank_deposit = 0;
}

void init_food() {
    food_cost = 20000;
}

void init_car() {
    car_price = 2400000;
    car_gas = 15000;
}

void init_hamster() {
    hamster_cost = 5000;
}

void init_all() {
    init_salary();
    init_bank();
    init_food();
    init_car();
    init_hamster();
}


// =======================
// ЗАРПЛАТА
// =======================

void salary_promotion(int month, int year) {
    if (month == 8 && year == 2026) {
        salary = salary * 15 / 10;
    }
}

void salary_to_bank() {
    bank_account = bank_account + salary;
}

void salary_process(int month, int year) {
    salary_promotion(month, year);
    salary_to_bank();
}


// =======================
// РАСХОДЫ
// =======================

void pay_food() {
    bank_account = bank_account - food_cost;
}

void pay_car_gas() {
    bank_account = bank_account - car_gas;
}

void pay_hamster() {
    bank_account = bank_account - hamster_cost;
}

void pay_all() {
    pay_food();
    pay_car_gas();
    pay_hamster();
}


// =======================
// ВКЛАД
// =======================

void transfer_to_deposit() {
    RUB transfer = 50000;

    if (bank_account >= transfer) {
        bank_account = bank_account - transfer;
        bank_deposit = bank_deposit + transfer;
    }
}

void deposit_interest_one_month() {
    RUB percent_money;
    percent_money = bank_deposit * deposit_percent / 100 / 12;
    bank_deposit = bank_deposit + percent_money;
}


// =======================
// ИНФЛЯЦИЯ
// =======================

void inflation_food() {
    food_cost = food_cost + food_cost * inflation_percent / 100;
}

void inflation_car_gas() {
    car_gas = car_gas + car_gas * inflation_percent / 100;
}

void inflation_car_price() {
    car_price = car_price + car_price * inflation_percent / 100;
}

void inflation_hamster() {
    hamster_cost = hamster_cost + hamster_cost * inflation_percent / 100;
}

void inflation_all() {
    inflation_food();
    inflation_car_gas();
    inflation_car_price();
    inflation_hamster();
}


// =======================
// ПЕЧАТЬ
// =======================

void print_salary() {
    printf("Salary = %lld\n", salary);
}

void print_bank_account() {
    printf("Bank account = %lld\n", bank_account);
}

void print_deposit() {
    printf("Deposit = %lld\n", bank_deposit);
}

void print_car_price() {
    printf("Car price = %lld\n", car_price);
}

void print_food_cost() {
    printf("Food cost = %lld\n", food_cost);
}

void print_hamster_cost() {
    printf("Hamster cost = %lld\n", hamster_cost);
}

void print_all() {
    print_salary();
    print_bank_account();
    print_deposit();
    print_car_price();
    print_food_cost();
    print_hamster_cost();
}


// =======================
// СИМУЛЯЦИЯ
// =======================

void simulation() {

    int month = 2;
    int year = 2026;

    while (!(month == 3 && year == 2027)) {

        salary_process(month, year);

        pay_all();

        transfer_to_deposit();

        deposit_interest_one_month();

        if (month == 1) {
            inflation_all();
        }

        month = month + 1;

        if (month == 13) {
            month = 1;
            year = year + 1;
        }
    }
}


// =======================
// MAIN
// =======================

int main() {

    init_all();

    simulation();

    print_all();

    return 0;
}
