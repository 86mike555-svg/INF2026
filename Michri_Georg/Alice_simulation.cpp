#include <stdio.h>

//typedef int RUB;  // C
using RUB = long long int;  // C++

struct Bank{
    RUB salary_account;
    RUB savings_account;
};


struct Car {
    RUB value;
    RUB gas;
};


struct Person {
    RUB salary;
    struct Bank B_account;
    RUB food;
    RUB hobby;
    struct Car car;
};
struct Person Alice;


float pp = 14.5;  // 115 -1 +


void alice_salary(const int month, const int year) {
    if ((month == 8) && (year == 2026)) {  // Promotion
        Alice.salary *= 1.5;
    }

    Alice.B_account.salary_account += Alice.salary;    
}


void print_results()
{
    printf("Salary = %lld\n", Alice.salary);
    printf("Capital = %lld", Alice.B_account.salary_account+Alice.B_account.savings_account);
}


void alice_bank_interest()
{
    Alice.B_account.savings_account += Alice.B_account.savings_account * (pp / 12.0 / 100.0);  // Bank interest
}


void alice_food()
{
    Alice.B_account.salary_account -= Alice.food;
}


void alice_car()
{
    Alice.B_account.salary_account -= Alice.car.gas;
}

void alice_hobby()
{
    Alice.B_account.salary_account -= Alice.hobby;
}




void translate_to_savings(){
    Alice.B_account.savings_account+=Alice.B_account.salary_account;
    Alice.B_account.salary_account=0;
}

void alice_init()
{
    Alice.B_account.salary_account = 0;
    Alice.B_account.savings_account = 0;
    Alice.salary = 180'000;
    Alice.food = 20'000;
    Alice.hobby = 30'000;
    Alice.car.value = 2'400'000;
    Alice.car.gas = 15'000;
}


void simulation()
{
    int month = 2;
    int year = 2026;
    
    while ( !((month == 3) && (year == 2127)) ) {
        
        alice_bank_interest();
        alice_salary(month, year);
        alice_food();
        alice_car();
        alice_hobby();
        translate_to_savings();
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
