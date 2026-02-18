#include <stdio.h>
#include <stdlib.h>

using Percent = float;

using RUB = long long int;
using USD = long long int;
using BTC = double;

struct Economy {
    Percent inflation;
    double rate_usd_rub;

    bool crisis;
};

struct Car {
    RUB value;
    RUB gas;
};

struct Crypto {
    BTC balance;
    double exchange_rate_usd;
};


struct Bank {
    RUB account_rub;
    USD account_usd;
    float monthly_loan_payment;
};

struct Housing {
    RUB value;
    RUB rent;
};

struct Health {
    short happines;
    short health;
    short max_age;
    bool is_alive;
};

struct Family
{
    bool has_partner;
    bool has_parents;
    short children_amount;
};

struct Person {
    Bank vtb;
    Crypto crypto_account;
    Car car;
    Housing home;

    RUB salary;
    RUB monthly_food_cost;
    RUB monthly_lifestyle_cost;

    Health health;
    Family family;
    
};

struct Economy russia;
struct Person alice;
struct Person bogdan;

void init()
{
    // Global
    Russia_economy.rate_usd_rub = 78.76;

    // Alice
    alice.vtb.account_rub = 0;
    alice.vtb.account_usd = 1'000;

    alice.salary = 180'000;
    alice.food = 3'000;

    alice.car.value = 2'400'000;
    alice.car.gas = 15'000;

    // Bogdan

}

double get_random(double min, double max) {
    return min + (double)(rand()) / ((double)(RAND_MAX / (max - min)));
}

void alice_expenses(const int month, const int year)
{
    if (month == 12) alice.vtb.account_rub -= 2000;  // christmas party

    Percent inflation = 0.75;
}
alice.food += alice.food * (inflation / 100. / 12.);

alice.vtb.account_rub -= alice.food;
}


void alice_salary(const int month, const int year)
{
    if (month == 3) {
        alice.salary *= 1.5;
    }

    if (month == 2 && year == 2026) {
        alice.vtb.account_rub += 5000;  // bonus
    }

    alice.vtb.account_rub += alice.salary;
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


void alice_car()
{
    alice.vtb.account_rub -= alice.car.gas;
}


void simulation()
{
    int year = 2026;
    int month = 2;

    while (alice.is_alive && bogdan.is_alive) ) {
        // World

        // Alice
        if (alice.is_alive) {
            alice_salary(month, year);
            alice_car();
            // my_cat();
            // my_trip();
            // my_rent();
            // my_mortgage();
            alice_expenses(month, year);
        }

        //Bogdan
        if (bogdan.is_alive) {
            bogdan_salary(month, year);
        }

        ++month;
        if (month == 13) {
            ++year;
            month = 1;
        }
    }
}


int main()
{
    init();
    simulation();
    print_results();
}