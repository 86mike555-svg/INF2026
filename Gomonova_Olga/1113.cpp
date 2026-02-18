#include <stdio.h>


using Percent = float;

using RUB = long long int;
using USD = long long int;


//идеи: кв в ипотеку, болезнь, собака, хомяк, еду расписать, работа черная, лотерея, бабкино завещание, участок земли, дача, брак, развод, ребенок, завещание дедка и его долги

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


struct Cat {
    RUB purchase;
    RUB cat_food;
    RUB cat_litter;
    RUB toys;
    RUB tray;
    RUB little_house;
    RUB scratching_post;
    RUB grooming;
    RUB veterinarian;
    RUB vitamins;
    RUB treats;
    RUB carrier;
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
    Cat cat;
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

    alice.flat.rent = 45'000;
    alice.flat.household_supplies = 2'000;
    alice.flat.housing_and_communal_services = 8'000;
    alice.flat.furniture = 10'000;
    alice.flat.cleaning = 15'000;
    alice.flat.repair = 5'000;
    alice.flat.deposit = 45'000;
    alice.flat.realtors_commission = 30'000;

    alice.cat.purchase = 5'000;
    alice.cat.cat_food = 3'000;
    alice.cat.cat_litter = 500;
    alice.cat.toys = 2'000;
    alice.cat.tray = 1'000;
    alice.cat.little_house = 1'500;
    alice.cat.scratching_post = 5'000;
    alice.cat.grooming = 2'000;
    alice.cat.veterinarian = 2'000;
    alice.cat.vitamins = 2'000;
    alice.cat.treats = 500;
    alice.cat.carrier = 2'500;
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


void alice_car_gas(const int month, const int year)
{
    Percent inflation = 5.0;
    switch (year) {
    case 2026: inflation = 6.5; break;
    case 2027: inflation = 7.0; break;
    case 2028: inflation = 8.0; break;
    case 2029: inflation = 7.5; break;
    }

    alice.car.gas += alice.car.gas * (inflation / 100. / 5.);

    alice.vtb.account_rub -= alice.car.gas;
}


void alice_flat(const int month, const int year)
{
    alice.vtb.account_rub -= alice.flat.rent;

    alice.vtb.account_rub -= alice.flat.housing_and_communal_services;

    if (month % 6 == 0) {
        alice.vtb.account_rub -= alice.flat.household_supplies;
    }

    if (month == 6 or month == 11) {
        alice.vtb.account_rub -= alice.flat.furniture;
    }

    if (month == 12) {
        alice.vtb.account_rub -= alice.flat.repair;
    }

    if (month == 5 or month == 10) {
        alice.vtb.account_rub -= alice.flat.cleaning;
    }

    if (month == 1 and year == 2026) {
        alice.vtb.account_rub -= alice.flat.deposit;

        alice.vtb.account_rub -= alice.flat.realtors_commission;
    }
}


void alice_cat(const int month, const int year)
{
    if (month % 2 == 0) {
        alice.vtb.account_rub -= alice.cat.cat_food;

        alice.vtb.account_rub -= alice.cat.cat_litter;
    }

    if (month % 6 == 0) {
        alice.vtb.account_rub -= alice.cat.toys;
    }

    if (month == 1 and year == 2026) {
        alice.vtb.account_rub -= alice.cat.purchase;

        alice.vtb.account_rub -= alice.cat.tray;

        alice.vtb.account_rub -= alice.cat.little_house;

        alice.vtb.account_rub -= alice.cat.scratching_post;

        alice.vtb.account_rub -= alice.cat.carrier;
    }

    if (month % 4 == 0) {
        alice.vtb.account_rub -= alice.cat.grooming;

        alice.vtb.account_rub -= alice.cat.veterinarian;

        alice.vtb.account_rub -= alice.cat.vitamins;
    }

    if (month % 6 == 0) {
        alice.vtb.account_rub -= alice.cat.treats;
    }
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


void alice_car(const int month, const int year)
{
    if (month == 10 and year == 2026) {
        alice.vtb.account_rub -= alice.car.tires;
    }

    if (month % 2 == 0) {
        alice.vtb.account_rub -= alice.car.washing;
    }

    if (month != 12) {
        alice.vtb.account_rub -= alice.car.parking_space;
    }

    alice.vtb.account_rub -= alice.car.gas;

    alice.vtb.account_rub -= alice.car.STO;

    alice.vtb.account_rub -= alice.car.OSAGO;
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


void simulation()
{
    int year = 2026;
    int month = 2;

    while (!(year == 2027 && month == 2) ) {
        alice_salary(month, year);
        alice_car(month, year);
        alice_cat(month, year);
        alice_flat(month, year);
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