#include <iostream>

using RUB = long long int;  // C++

struct Bank {
	RUB balance;
	RUB deposit;
	RUB procent;
};


struct Car {
    RUB value;
    RUB gas;
};


struct Person {
    RUB salary;
    RUB capital;
    RUB food;
    struct Car car;
	struct Bank AliceBank;
};
struct Person Alice;


void alice_salary(const int month, const int year) {
    if ((month == 8) && (year == 2026)) {
        Alice.salary *= 1.5;
    }

    Alice.AliceBank.balance += Alice.salary;    
}


void print_results() {
    printf("Salary = %lld\n", Alice.salary);
    printf("Capital = %lld", Alice.capital);
}


void alice_deposit() {
    Alice.AliceBank.deposit += Alice.AliceBank.deposit * (Alice.AliceBank.procent / 12.0 / 100.0);
}


void alice_food() {
    Alice.AliceBank.balance -= Alice.food;
}


void alice_car() {
    Alice.AliceBank.balance -= Alice.car.gas;
}

void alice_capital() {
	Alice.capital = Alice.AliceBank.balance + Alice.AliceBank.deposit + Alice.car.value;
}


void alice_init() {
    Alice.AliceBank.balance = 0;
	Alice.AliceBank.deposit = 100'000;
	Alice.AliceBank.procent = 16;
    Alice.salary = 180'000;
    Alice.food = 20'000;

    Alice.car.value = 2'400'000;
    Alice.car.gas = 15'000;
}


void simulation() {
    int month = 2;
    int year = 2026;
    
    while ( !((month == 3) && (year == 2027)) ) {
        // my_cat();
        // my_trip();
        alice_food();
        alice_car();
        alice_deposit();
        alice_salary(month, year);
		alice_capital();
        
        ++month;
        if (month == 13) {
            month = 1;
            ++year;
        }
    }
}


int main()
{
    alice_init();
    
    simulation();
    
    print_results();
}
