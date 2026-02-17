#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

using RUB = long long int;
using Percent = float;

struct Cat
{
    string color;
    int age;
    RUB cat_food;
    RUB cat_veterinar;
};


struct Car
{
    RUB value;
    RUB gas;
};


struct Work
{
    RUB salary;
    float promotion;
};


struct VTB
{
    RUB balance;
    RUB deposit;
    Percent percent;
};

struct Person
{
    Work work;
    RUB food;
    Car car;
    VTB VTB;
    RUB deposit_sum;
    Cat Pushok;
};

Person Alice;
void alice_cat()
{
    double min = 10.5, max = 11.3;
    double inflation_on_cat_food = (double)rand() / RAND_MAX * (max - min) + min;
    Alice.VTB.balance -= Alice.Pushok.cat_food*(1+inflation_on_cat_food/100/12);
    min = 11.5, max = 12.2;
    double inflation_on_cat_doctor= (double)rand() / RAND_MAX * (max - min) + min;
    Alice.VTB.balance -= Alice.Pushok.cat_veterinar*(1+inflation_on_cat_doctor/100/12);
}


void alice_car_gas()
{
    double min = 9.8, max = 10.6;
    double inflation_on_gas= (double)rand() / RAND_MAX * (max - min) + min;
    Alice.VTB.balance -= Alice.car.gas*(1+inflation_on_gas/100/12);   
    
}

void alice_salary(const int month, const int year)
{
    if ((month == 8) && (year == 2026))
    {
        Alice.work.salary = Alice.work.salary * Alice.work.promotion;
    }
    Alice.VTB.balance += Alice.work.salary;
}


void alice_food()
{
    double min = 10.5, max = 11.3;
    double inflation_on_food = (double)rand() / RAND_MAX * (max - min) + min;
    Alice.VTB.balance -= Alice.food*(1+inflation_on_food/100/12);
}


void alice_VTB_deposit()
{
    Alice.VTB.deposit += Alice.deposit_sum;
    Alice.VTB.balance -= Alice.deposit_sum;
}


void alice_deposit_percent()
{
    Alice.VTB.deposit += Alice.VTB.deposit * (Alice.VTB.percent / 12 / 100);
}


void print_results()
{

    printf("Salary = %lld\n", Alice.work.salary);
    printf("Capital = %lld\n", Alice.VTB.balance);
    printf("Deposit = %lld", Alice.VTB.deposit);
}


void simulation()
{
    int month = 2;
    int year = 2026;
    bool firstIteration = true;
    while (!((month == 3) && (year == 2030)))
    {
        alice_cat();
        alice_food();
        alice_car_gas();
        alice_deposit_percent();
        alice_salary(month, year);
        alice_VTB_deposit();
        ++month;
        if (month == 13)
        {
            month = 1;
            ++year;
        }
    }
}


void alice_init()
{
    Alice.VTB.balance = 60000;
    Alice.VTB.deposit = 0;
    Alice.work.salary = 180000;
    Alice.food = 30000;
    Alice.car.value = 2400000;
    Alice.work.promotion = 1.2;
    Alice.deposit_sum = 40000;
    Alice.VTB.percent = 14;
    Alice.Pushok.cat_food = 6000;
    Alice.Pushok.cat_veterinar = 3000;
    Alice.Pushok.age = 3;
    Alice.Pushok.color = "white";
}


int main()
{
    srand(time(NULL));
    alice_init();
    simulation();
    print_results();
}