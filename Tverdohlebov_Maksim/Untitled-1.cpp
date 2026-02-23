#include <stdio.h>

using RUB = long long int;
using Percent = float;

struct Car {
    bool have_car;
    RUB value;  
    RUB gas;   
};


struct Bank {
    RUB money;   
    RUB deposit;
    Percent pp = 14.5;    
};


struct Pet {
    bool have_pet;
    RUB food;
    RUB vet;
};


struct Person {
    RUB salary;
    RUB capital;          
    RUB food;
    RUB taxes;                   
    struct Car car;
    struct Bank VTB;
    struct Bank Sber;
    struct Pet cat;
    struct Pet humster;
    RUB hobby;
    RUB tax;       
};


struct Person Alice;
struct Person Ben; 


float pr_inflation = 0.015;


void alice_salary(const int month, const int year) 
{
    if ((month == 8) && (year >= 2026)) 
    {  
        Alice.salary *= 1.5;
    }
    Alice.VTB.money += Alice.salary;    
}


void alice_food() 
{
    Alice.VTB.money -= Alice.food;
    Alice.food += RUB (Alice.food * pr_inflation);
}


void alice_car() 
{
    if (Alice.car.have_car)
    {
        Alice.VTB.money -= Alice.car.gas;
        Alice.car.gas += RUB (Alice.car.gas * pr_inflation);
    }
}


void alice_cat(int month) 
{
    if (Alice.cat.have_pet)
    {
        Alice.VTB.money -= Alice.cat.food;
        if (month % 3 == 0) 
        {
            Alice.VTB.money -= Alice.cat.vet;
        }
        Alice.cat.food += RUB (Alice.cat.food * pr_inflation);
        Alice.cat.vet += RUB (Alice.cat.vet * pr_inflation);
    }
}


void alice_hobby() 
{
    Alice.VTB.money -= Alice.hobby;
    Alice.hobby += RUB (Alice.hobby * pr_inflation);
}


void alice_bank_interest()
{
    Alice.VTB.deposit += RUB (Alice.VTB.deposit * (Alice.VTB.pp / 12 / 100));
}


void alice_deposit()
{
    if (Alice.VTB.money >= 0) 
    {
        Alice.VTB.deposit += Alice.VTB.money;
        Alice.VTB.money -= Alice.VTB.money;
    }
}

void alice_init() 
{
    Alice.salary = 180'000;
    Alice.food = 23'000;
    Alice.hobby = 25'000;

    Alice.car.value = 2'000'000;
    Alice.car.gas = 15'000;
    Alice.car.have_car = 0;

    Alice.cat.food = 5'000;
    Alice.cat.vet = 12'000;
    Alice.cat.have_pet = 1;

    Alice.VTB.money = 0;
    Alice.VTB.deposit = 0;  
}


void ben_salary(const int month, const int year) 
{
    if (month == 12) 
    {  
        Ben.salary *= 1.35;
    }
    Ben.Sber.money += Ben.salary;    
}


void ben_food() 
{
    Ben.Sber.money -= Ben.food;
    Ben.food += RUB (Ben.food * pr_inflation);
}


void ben_car() 
{
    if (Ben.car.have_car)
    {
        Ben.Sber.money -= Ben.car.gas;
    }
    Ben.car.gas += RUB (Ben.car.gas * pr_inflation);
    Ben.car.value += RUB (Ben.car.value * pr_inflation);
}


void ben_cat(int month) 
{
    if (Ben.humster.have_pet)
    {
        Ben.Sber.money -= Ben.humster.food;
        if (month % 3 == 0) 
        {
            Ben.Sber.money -= Ben.humster.vet;
        }
    }
    Ben.humster.food += RUB (Ben.humster.food * pr_inflation);
    Ben.humster.vet += RUB (Ben.humster.vet * pr_inflation);
}


void ben_hobby() 
{
    Ben.Sber.money -= Ben.hobby;
    Ben.hobby += RUB (Ben.hobby * pr_inflation);
}


void ben_bank_interest() 
{
    Ben.Sber.deposit += RUB (Ben.Sber.deposit * (Ben.Sber.pp / 12 / 100));
}


void ben_deposit()
{
    if (Ben.Sber.money >= 0) 
    {
        Ben.Sber.deposit += Ben.Sber.money;
        Ben.Sber.money -= Ben.Sber.money;
    }
} 


void buy_car_Alice()
{
    if (!(Alice.car.have_car) && (Alice.VTB.deposit > Alice.car.value))
    {
        Alice.VTB.deposit -= Alice.car.value;
        Alice.car.have_car = 1;
    }
}


void buy_car_Ben()
{
    if (!(Ben.car.have_car) && (Ben.Sber.deposit > Ben.car.value))
    {
        Ben.Sber.deposit -= Ben.car.value;
        Ben.car.have_car = 1;
    }
}


void ben_init() {
    Ben.salary = 200'000;
    Ben.food = 25'000;
    Ben.hobby = 15'000;

    Ben.car.value = 1'500'000;
    Ben.car.gas = 12'000;
    Ben.car.have_car = 0;

    Ben.humster.food = 4'000;
    Ben.humster.vet = 10'000;
    Ben.humster.have_pet = 1;

    Ben.Sber.money = 0;
    Ben.Sber.deposit = 0;
    Ben.Sber.pp = 10.0;  
}


void simulation() {
    int month = 2;
    int year = 2026;
    
    while ( !((month == 3) && (year == 2027))) 
    {         
        // Алиса
        alice_salary(month, year);
        alice_food();
        alice_car();
        alice_cat(month);                
        alice_hobby();
        alice_bank_interest();
        alice_deposit();
        buy_car_Alice();  

        // Бен
        ben_salary(month, year);
        ben_food();
        ben_car();
        ben_cat(month);
        ben_hobby();
        ben_bank_interest(); 
        ben_deposit(); 
        buy_car_Ben();

        ++month;
        if (month == 13) 
        {
            month = 1;
            ++year;
        }
    }
}


void print_results() {
    printf("Алиса:\n");
    printf("Зарплата = %lld\n", Alice.salary);
    printf("Деньги на счету в банке ВТБ = %lld\n", Alice.VTB.money);
    printf("Депозит = %lld\n", Alice.VTB.deposit);
    printf("\nБен:\n");
    printf("Зарплата = %lld\n", Ben.salary);
    printf("Деньги на счету в банке Сбер = %lld\n", Ben.Sber.money);
    printf("Депозит = %lld\n", Ben.Sber.deposit);
}


int main() {
    alice_init();
    ben_init();
    simulation();
    print_results();
    return 0;
}
