#include <stdio.h>


using Percent = float;

using RUB = long long int;
using USD = long long int;


struct Car {
    RUB value;
    RUB gas;
    RUB STO;
    RUB OSAGO;
    RUB tires;
    RUB washing;
    RUB parking_space;
};


struct Flat {
    RUB rent;
    RUB household_supplies;
    RUB housing_and_communal_services;
    RUB furniture;
    RUB cleaning;
    RUB repair;
    RUB deposit;
    RUB realtors_commission;
};


struct Bank {
    RUB account_rub;
    USD account_usd;
    float rate_usd_rub;
};


struct Person {
    Bank vtb;
    RUB salary;
    RUB food;
    Car car;
    Flat flat;
};
struct Person alice;


void alice_init()
{
    alice.vtb.rate_usd_rub = 78.76;
    alice.vtb.account_rub = 0;
    alice.vtb.account_usd = 1000;

    alice.salary = 180000;
    alice.food = 3000;

    alice.car.value = 2'400'000;
    alice.car.gas = 15'000;
    alice.car.OSAGO = 5'000;
    alice.car.STO = 10'000;
    alice.car.tires = 15'000;
    alice.car.washing = 500;
    alice.car.parking_space = 12'000;
}


void alice_car(const int month, const int year)
{
    Percent inflation = 5.0;
    switch (year) {
    case 2026: inflation = 6.5; break;
    case 2027: inflation = 7.0; break;
    case 2028: inflation = 8.0; break;
    case 2029: inflation = 7.5; break;
    }
    alice.car += alice.car * (inflation / 100. / 5.);

    alice.vtb.account_rub -= alice.car;
}

void alice_food(const int month, const int year)
{
    if (month == 12) alice.vtb.account_rub -= 2000; //christmas party

    Percent inflation = 12.0;
    switch (year) {
    case 2026: inflation = 12.5; break;
    case 2027: inflation = 14.0; break;
    case 2028: inflation = 13.0; break;
    case 2029: inflation = 11.5; break;
    }
    alice.food += alice.food * (inflation / 100. / 12.);

    alice.vtb.account_rub -= alice.food;
}


void alice_salary(const int month, const int year)
{
    if (month == 3) {
        alice.salary *= 1.5;
    }

    if (month == 2 and year == 2026) {
        alice.vtb.account_rub += 5000;
    }

    alice.vtb.account_rub += alice.salary;  // capital = capital + salary
}


void print_results()
{
    printf("Salary = %lld\n", alice.salary);

    RUB capital = 0;
    capital += alice.vtb.account_rub;
    capital += alice.vtb.account_usd * alice.vtb.rate_usd_rub;
    capital += alice.car.value;
    printf("Capital = %lld", capital);
}


void alice_car(const int month, const int year)
{
    if (month == 10 and year == 2026) {
        alice.vtb.account_rub -= alice.car.tires;
    }

    if (month == 2, 4, 6, 8, 10, 12) {
        alice.vtb.account_rub -= alice.car.washing;
    }

    if (month != 12) {
        alice.vtb.account_rub -= alice.car.parking_space;
    }

    alice.vtb.account_rub -= alice.car.gas;
    alice.vtb.account_rub -= alice.car.STO;
    alice.vtb.account_rub -= alice.car.OSAGO;
}


void simulation()
{
    int year = 2026;
    int month = 2;

    while (!(year == 2027 && month == 2) ) {
        alice_salary(month, year);
        alice_car(month, year);
        // my_cat();
        // my_trip();
        // my_rent();
        // my_mortgage();
        alice_food(month, year);

        ++month;
        if (month == 13) {
            ++year;
            month = 1;
        }
    }
}


int main()
{
    alice_init();
    simulation();
    print_results();
}