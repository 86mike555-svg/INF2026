#include <stdio.h>    

using RUB = long long int;
//using Percent = float;

struct Dog {
    RUB feed;
    RUB others; 
};
struct Dog Jack;

struct Car {
    RUB value;
    RUB gas;
    RUB washing;
};
struct Car Subaru;

struct Bank {
    RUB bank_account; // текущий банковский счет
    RUB deposit;  
    float pp = 14.5;  
};
struct Bank Rusbank; 

struct NewYearExpenses {
    RUB gifts;
    RUB food;
    RUB entertainment;
};

struct Person {
    RUB salary;
    RUB food; 
    Car car; 
    Dog dog; 
    NewYearExpenses new_year;
};
struct Person Alice;


void alice_salary (const int month, const int year) {
    if ((month == 8) && (year == 2026)) // 
    {
        Alice.salary *= 1.5;
    }
    Rusbank.bank_account += Alice.salary; 
}


void alice_food(float inflation) {
    Rusbank.bank_account -= Alice.food; 
    Alice.food *= (1 + (inflation) / 100);
}


void alice_car(float inflation) {
    Subaru.value *= (1 + (inflation) / 100);
    Rusbank.bank_account -= Subaru.gas;
    Rusbank.bank_account -= Subaru.washing;
    Subaru.gas *= (1 + (inflation) / 100);
    Subaru.washing *= (1 + (inflation) / 100);
}


void alice_pet(float inflation) {
    Rusbank.bank_account -= Jack.feed;
    Rusbank.bank_account -= Jack.others;
    Jack.feed *= (1 + (inflation) / 100);
    Jack.others *= (1 + (inflation) / 100);
}


void alice_bank_interest() {
    RUB interest = Rusbank.deposit * Rusbank.pp / 12.0 / 100.0;
    Rusbank.deposit += interest;
}


void alice_new_year(int month, float inflation) {
    if (month == 12) { 
        Rusbank.bank_account -= Alice.new_year.gifts;
        Rusbank.bank_account -= Alice.new_year.food;
        Rusbank.bank_account -= Alice.new_year.entertainment;
        
        Alice.new_year.gifts *= (1 + inflation / 100);
        Alice.new_year.food *= (1 + inflation / 100);
        Alice.new_year.entertainment *= (1 + inflation / 100);
    }
}


void simulation() { 
    int month = 2;
    int year = 2026;

    float inflation = 5.6; 
    
    while (!(month == 2 && year == 2031)) {
        alice_salary(month, year); 
        alice_food(inflation);   
        alice_car(inflation);              
        alice_pet(inflation);     
        alice_bank_interest();             
        alice_new_year(month, inflation);  
        ++month;
        if (month == 13) {
            month = 1;
            ++year;
        }
    }
}


void alice_init()
{
    Alice.salary = 195'000; 
    Alice.food = 20'000;   

    Rusbank.bank_account = 1'000'000;   
    Rusbank.deposit = 2'000'000;  

    Subaru.value = 5'500'000; 
    Subaru.gas = 12'000;                     
    Subaru.washing = 3'000; 

    Jack.feed = 2000;      
    Jack.others = 1'000;   
    
    Alice.new_year.gifts = 20'000;
    Alice.new_year.food = 15'000;
    Alice.new_year.entertainment = 6'500;
}
 
void print_results() {
    printf("Salary = %lld\n", Alice.salary);
    printf("Current bank account = %lld", Rusbank.bank_account); 
}


int main()
{
    alice_init();
    simulation();
    print_results();
}





