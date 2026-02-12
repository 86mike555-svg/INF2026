#include <stdio.h>

using RUB = long int;

struct Car {
    RUB value;
    RUB gas;
};

struct Cat {
    RUB feed;
};

struct Person {
    RUB salary;
    RUB capital;
    RUB food;
    Car car;
    Cat cat;
};

struct Person Alice;

const float pp = 14.5;
const float cash_inflation_per_month = 1.0125; //15%
const float salary_inflation_per_month = 1.01; //12%

void alice_cat() {
    Alice.capital -= Alice.cat.feed;
}
void alice_car() {
    Alice.capital -= Alice.car.gas;
}

void alice_salary(const int month, const int year) {
    if ((month == 8) && (year == 2026)) { // Promotion
        Alice.salary = Alice.salary * 1.5;
    }
    Alice.capital += Alice.salary;  
}

void alice_food() {
    Alice.capital -= Alice.food;
}

void alice_bank() {
    Alice.capital += Alice.capital * (pp / 12.0 / 100.0);
}

void alice_init() {
    Alice.capital = 0;
    Alice.salary = 180000;
    Alice.food = 20000;

    Alice.car.value = 1000000;
    Alice.car.gas = 15000;

    Alice.cat.feed = 2000;
}

void inflation() {
    Alice.car.value = static_cast<int> (Alice.car.value * cash_inflation_per_month);
    Alice.car.gas = static_cast<int> (Alice.car.gas * cash_inflation_per_month);
    Alice.cat.feed = static_cast<int> (Alice.cat.feed * cash_inflation_per_month);
    Alice.food = static_cast<int> (Alice.food * cash_inflation_per_month);
    Alice.salary = static_cast<int> (Alice.salary * salary_inflation_per_month);
}

void simulation() {
    int month = 2;
    int year = 2026;

    while (!((month == 3) && (year == 2027))) {
        alice_cat();
        alice_food();
        alice_car();
        alice_bank();
        alice_salary(month, year);
        inflation();
        ++month;
        if (month == 13) {
        month = 1;
        ++year;
        }
    }
}

void print_results() {
    printf("Capital = %ld\n", Alice.capital);
    printf("Salary = %ld\n", Alice.salary);
    printf("Feed = %ld\n", Alice.cat.feed);
    printf("Food = %ld\n", Alice.food);
    printf("Car value = %ld\n", Alice.car.value);
    printf("Car gas = %ld", Alice.car.gas);
}

int main() { 
    alice_init();

    simulation();
  
    print_results();
}
