#include<iostream>

#include <cstdlib>
#include <ctime>

using Percent = float;

using RUB = long long int;
using USD = long long int;


struct World_Economy
{
    Percent inflation;
    Percent income_tax;

    float rate_usd_rub;
};
struct World_Economy economy;


void economy_init()
{
    economy.inflation = 12.0;
    economy.income_tax = 13.0;

    economy.rate_usd_rub = 78.76;
}


struct Freelance
{
    Percent chance_of_work;

    USD min_income;
    USD max_income;
};
struct Freelance freelance;


void freelance_init()
{
    freelance.chance_of_work = 35.0;

    freelance.min_income = 200;
    freelance.max_income = 800;
}


struct Car
{
    RUB value;
    RUB gas;
};


struct Bank 
{
    RUB account_rub;
    USD account_usd;
};


struct Animals
{
    RUB humster;
    RUB cat;
    RUB dog;
    RUB man;
};

struct Person {
    Bank vtb;

    Animals home_zoo;

    RUB food;
    RUB salary;

    Car car;    
};
struct Person alice;


void alice_init()
{   
    alice.vtb.account_rub = 0;
    alice.vtb.account_usd = 1'000;
    
    alice.salary = 180'000;
    alice.food = 3'000;

    alice.home_zoo.cat = 1'500 + 1'500; // food + toilet
    alice.home_zoo.humster = 500 + 200;
    alice.home_zoo.man = 200; //micro-gifts

    alice.car.value = 2'400'000;
    alice.car.gas = 15'000;
}


void switch_tax(const int year, Percent &tax)
{
    if (year >= 2028) tax = 14.0;
}


void alice_my_salary(const int month, const int year)
{
    if (month == 3) {
        alice.salary *= 1.5; //повышение зп
    }

    if (month == 2 && year == 2026) {
            alice.vtb.account_rub += 5000; //премия
    }
    
    switch_tax(year, economy.income_tax);
    alice.vtb.account_rub += alice.salary * ((100 - economy.income_tax)/100);
}


void alice_freelance()
{
    int roll = rand() % 100; 

    if (roll < freelance.chance_of_work) alice.vtb.account_usd += freelance.min_income + rand() % (freelance.max_income - freelance.min_income + 1);
}


void switch_inflation_food(const int year, Percent &inflation)
{
    switch (year)
    {
    case 2026: inflation = 12.0; break;
    case 2027: inflation = 14.0; break;
    case 2028: inflation = 13.0; break;
    case 2029: inflation = 11.5; break;
    default: inflation = 12.0; break;
    }
}


void alice_food_cost(const int month, const int year) 
{
    if (month == 12) alice.vtb.account_rub -= 2000; // christmass party

    switch_inflation_food(year, economy.inflation);

    alice.food += alice.food * (economy.inflation / 100 / 12);

    alice.vtb.account_rub -= alice.food;
}


void alice_animals_cost(const int month, const int year)
{
    if (month == 12 or month == 2 or month == 5) alice.vtb.account_rub -= 2000; //gifts for man: new year, Defender of the Fatherland Day, birthday

    switch_inflation_food(year, economy.inflation);
    alice.vtb.account_rub -= alice.home_zoo.cat * (1 - economy.inflation / 100 / 12);
    alice.vtb.account_rub -= alice.home_zoo.humster * (1 - economy.inflation / 100 / 12);
    alice.vtb.account_rub -= alice.home_zoo.man * (1 - economy.inflation / 100 / 12);
}

void alice_car()
{
    alice.vtb.account_rub -= alice.car.gas;
}


void simulation()
{
    int year = 2026;
    int month = 2;

    while ( !(year == 2027 && month == 2) ) {
        alice_my_salary(month, year);
        alice_freelance();

        alice_food_cost(month, year);
        alice_animals_cost(month, year);

        alice_car();

        ++month;
        if (month == 13) {
            ++year;
            month = 1;
        }
    }   
}


void print_results()
{
    printf("Salary = %lld\n", alice.salary);

    RUB capital = 0;

    capital += alice.vtb.account_rub;
    capital += alice.vtb.account_usd * economy.rate_usd_rub;

    capital += alice.car.value;
        
    printf("Capital = %lld\n", capital);
}


int main() 
{
    srand(time(0));

    economy_init();

    alice_init();
    freelance_init();

    simulation();

    print_results();
}
