#include <stdio.h>


using RUB = long long int;

struct Person {
    RUB salary;
    RUB bank_acc;
    RUB deposit; // вклад
    RUB to_deposit; // Part of the money set aside for the deposit
    RUB capital;
    RUB food;
    RUB car;
    RUB gas;
};

struct Person Alice;
float pp = 14.5;

void init() {
    Alice.capital = 0;
    Alice.salary = 100'000;
    Alice.deposit = 0;
    Alice.to_deposit = 10'000;
    Alice.car = 2'500'000;
    Alice.gas = 15'000;
    Alice.food = 20'000;
}

void Alice_salary(const int month, const int year) {
    if ((month == 6) && (year ==2026)){ // повышение
        Alice.salary = Alice.salary * 1.5;
    }
    Alice.bank_acc += (Alice.salary - Alice.to_deposit - Alice.gas - Alice.food); // зп на аккаунт
    Alice.deposit += Alice.to_deposit; // часть зп на вклад
}

void result(){
    printf("Депозит = %lld\n", Alice.deposit);
    printf("Банк = %lld\n", Alice.bank_acc);
    printf("Зарплата = %lld\n", Alice.salary);
    printf("Капитал = %lld\n", Alice.capital);
}

void infl() {
    Alice.car *= 1.0083; // 10% в год
    Alice.gas *= 1.0125; // 15% в год
    Alice.food *= 1.00041; // 5% в год
}

void simulation() {
    int month = 1;
    int year = 2026;
    while (!((month == 2) && (year == 2027))) {
        Alice.deposit += Alice.deposit * (pp / 12.0 / 100.0); // проценты
        Alice_salary(month, year);
        infl();
        ++month;
        if (month == 13) {
            month = 1;
            ++year;
        }
    }
    Alice.capital += Alice.car + Alice.deposit;
}

int main() {
    init();
    simulation();
    result();
}

// + повышение
// + зп зачисл на банковский аккаунт
// + зп зачисл на вклад
// + проценты зачисл
// + инфляция
// + продукты
// + машина
// + продукты
// - кошки
//
