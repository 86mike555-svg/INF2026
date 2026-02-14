#include <stdio.h>    

using RUB = long long int;
float annual_inflation = 5.6; // годовая инфляция
float pp = 10.05;

struct BankAccount {
    RUB bank_account; // текущий счет
    RUB deposit; // депозит
};
struct BankAccount Alice_account; 

struct Car {
    RUB value;
    RUB gas;
    RUB maintenance; // техническое обслуживание
    RUB car_washing; // мойка
};
struct Car Audi;
struct Car Mercedes;

struct Humster {
    RUB feed; // корм 
    RUB veterinar; // ветеринар
    RUB other; // прочие расходы
};
struct Humster Holli; 

struct Person {
    RUB capital; // деньги не в банке
    RUB salary;
    RUB food; 
    Car car;
    Humster humster;
};
struct Person Alice;

void update_capital() {
    Alice.capital = Alice_account.bank_account + Alice_account.deposit + Alice.car.value + Alice.salary; // Можно добавить и другие активы при необходимости
}

void print_results() {
    printf("Salary = %lld\n", Alice.salary);
    printf("Capital = %lld\n", Alice.capital); 
    printf("Current bank account = %lld", Alice_account.bank_account); 
}

void alice_salary (const int month, const int year) {
    if ((month == 8) && (year == 2026)) // 
    {
        Alice.salary *= 1.5;
    }
    Alice_account.bank_account += Alice.salary; 
    update_capital();
}

void alice_food() {
    Alice_account.bank_account -= Alice.food; 
    update_capital();
}

void alice_car() {
    Alice_account.bank_account -= Alice.car.gas;
    Alice_account.bank_account -= Alice.car.maintenance;
    Alice_account.bank_account -= Alice.car.car_washing;
    update_capital();
}

void alice_pet() {
    Alice_account.bank_account -= Alice.humster.feed;
    Alice_account.bank_account -= Alice.humster.veterinar;
    Alice_account.bank_account -= Alice.humster.other;
    update_capital();
}

void alice_bank_interest() {
    RUB interest = Alice_account.deposit * pp / 12.0 / 100.0;
    Alice_account.deposit += interest;
    RUB small_interest = Alice_account.deposit * 0.21 / 12.0 / 100.0;
    Alice_account.deposit += small_interest;
    update_capital();
}

void apply_inflation(int month, int year) {
    if (month == 1) 
    {
        Alice.car.value = Alice.car.value * (100 + annual_inflation) / 100;
        Alice.car.gas = Alice.car.gas * (100 + annual_inflation) / 100;
        Alice.car.maintenance = Alice.car.maintenance * (100 + annual_inflation) / 100;
        Alice.car.car_washing = Alice.car.car_washing * (100 + annual_inflation) / 100;
        Alice.humster.feed = Alice.humster.feed * (100 + annual_inflation) / 100;
        Alice.humster.veterinar = Alice.humster.veterinar * (100 + annual_inflation) / 100;
        Alice.humster.other = Alice.humster.other * (100 + annual_inflation) / 100;
        Alice.food = Alice.food * (100 + annual_inflation) / 100;
        Alice.salary = Alice.salary * (100 + annual_inflation/2) / 100;
        update_capital();
    }
}

void simulation() {
    int month = 2;
    int year = 2026;
    
    while (!(month == 2 && year == 2126)) {
        alice_salary(month, year); 
        alice_food();   
        alice_car();              
        alice_pet();            
        alice_bank_interest();           
        //auto_transfer_to_deposit();        
        apply_inflation(month, year);  

        if (month == 12 && year == 2026) {
            Alice_account.bank_account -= 35000; // траты на новый год
            update_capital();
        }
    
        ++month;
        if (month == 13) {
            month = 1;
            ++year;
            
        }
    }
}

void alice_init()
{
    Alice.capital = 0; 
    Alice.salary = 180'000; 
    Alice.food = 20000;   
    Alice_account.bank_account = 0;   
    Alice_account.deposit = 0;    
    Audi.value = 7'500'000; 
    Audi.gas = 15000;               
    Audi.maintenance = 10500;        
    Audi.car_washing = 4500;        
    Holli.feed = 700;      
    Holli.veterinar = 2000; 
    Holli.other = 1000;           
    Alice.car = Audi;
    Alice.humster = Holli;
    update_capital();
}
 
int main()
{
    alice_init();
    simulation();
    print_results();
}
