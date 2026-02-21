#include <stdio.h>

using RUB = long long int;
using INFLATION = double;

struct BankAccount {
    RUB deposit;       
    RUB checking;      
    double deposit_rate; 
};

struct Car {
    RUB value;
    RUB gas;
    INFLATION gas_inflation;
};

struct Dog {
    RUB value;
    RUB expenses;       
    INFLATION expenses_inflation;
};

struct Hamster {
    RUB value;
    RUB expenses;
    INFLATION expenses_inflation;
};

struct Person {
    RUB salary;
    RUB food;
    INFLATION food_inflation;
    INFLATION salary_indexation;
    Car car;
    Dog dog;
    Hamster hamster;
    BankAccount bank;
    RUB fathers_money;
};

struct Person Alice;

void alice_car() {
    Alice.car.gas = Alice.car.gas * (100 + Alice.car.gas_inflation) / 100;
    Alice.bank.checking -= Alice.car.gas;
}

void alice_salary(const int month, const int year) {

    if (month == 1 && year > 2026) {
        Alice.salary = Alice.salary * (100 + Alice.salary_indexation) / 100;
    }
    if ((month == 8) && (year == 2026)) {
        Alice.bank.checking += Alice.salary * 0.5;
    }
    Alice.bank.checking += Alice.salary;
}

void alice_food() {
    Alice.food = Alice.food * (100 + Alice.food_inflation) / 100;
    Alice.bank.checking -= Alice.food;
}

void alice_dog() {
    Alice.dog.expenses = Alice.dog.expenses * (100 + Alice.dog.expenses_inflation) / 100;
    Alice.bank.checking -= Alice.dog.expenses;
}

void alice_hamster() {
    Alice.hamster.expenses = Alice.hamster.expenses * (100 + Alice.hamster.expenses_inflation) / 100;
    Alice.bank.checking -= Alice.hamster.expenses;
}

void bank_interest() {
    Alice.bank.deposit += Alice.bank.checking;  
    Alice.bank.checking = 0;                    

    Alice.bank.deposit *= (100 + Alice.bank.deposit_rate) / 100;
}

void alice_dog_inflation() {
    Alice.dog.expenses *= (100 + Alice.dog.expenses_inflation) / 100;
}

void alice_car_inflation() {
    Alice.car.gas *= (100 + Alice.car.gas_inflation) / 100;
}

void alice_hamster_inflation() {
    Alice.hamster.expenses *= (100 + Alice.hamster.expenses_inflation) / 100;
}

void alice_food_inflation() {
    Alice.food *= (100 + Alice.food_inflation) / 100;
}

void print_results() {
    printf("Salary: %lld RUB\n", Alice.salary);
    printf("Deposit: %lld RUB\n", Alice.bank.deposit);
    printf("Payment account: %lld RUB\n", Alice.bank.checking);
    printf("Capital: %lld RUB\n", Alice.bank.deposit + Alice.bank.checking);
}

void alice_init() {
    Alice.bank.deposit = 50000;     
    Alice.bank.checking = 0;            
    Alice.bank.deposit_rate = 11.0;    
    Alice.fathers_money = 5000000;

    Alice.salary = 180000;
    Alice.salary_indexation = 2.0;      
    Alice.food = 20000;
    Alice.food_inflation = 1.2;

    Alice.car.value = 2400000;
    Alice.car.gas = 15000;
    Alice.car.gas_inflation = 0.4;

    Alice.dog.value = 5000;
    Alice.dog.expenses = 4000;
    Alice.dog.expenses_inflation = 1.0;

    Alice.hamster.value = 2000;
    Alice.hamster.expenses = 3000;
    Alice.hamster.expenses_inflation = 1.0;

    
    Alice.bank.deposit -= (Alice.car.value + Alice.dog.value + Alice.hamster.value);
}

void simulation() {
    int month = 2;
    int year = 2026;
    alice_salary(1, 2026);
    Alice.bank.checking -= (Alice.car.value + Alice.dog.value + Alice.hamster.value)+Alice.fathers_money;

    while (!((month == 3) && (year == 2037))) {

        alice_salary(month, year);
        
        alice_dog();
        alice_hamster();
        alice_food();
        alice_car();

        
        ++month;
        if (month == 13) {
            month = 1;
            ++year;
            
            bank_interest();
            alice_dog_inflation();
            alice_hamster_inflation();
            alice_food_inflation();
            alice_car_inflation();
            
        }
    }
}

int main() {
    alice_init();
    simulation();
    print_results();

    return 0;
}