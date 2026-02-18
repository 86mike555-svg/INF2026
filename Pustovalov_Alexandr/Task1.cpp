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
    RUB yearly_tax;
};

struct Crypto {
    BTC balance;
    double exchange_rate_usd;
};

struct Loan {
    RUB body_debt;
    RUB monthly_payment;
    Percent interest_rate;
    bool is_active;
};

struct Bank {
    RUB account_rub;
    USD account_usd;
    
    Loan mortgage;
    Loan consumer_credit;
};

struct Housing {
    RUB value;
    RUB rent;
    RUB monthly_utilities;
};

struct Health {
    short happines;
    short physical_health;
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
    russia.rate_usd_rub = 76.75;
    russia.inflation = 5.59;
    russia.crisis = false;

    // Alice
    alice.salary = 200'000;
    alice.vtb.account_rub = 150'000;
    alice.vtb.account_usd = 0;
    alice.vtb.consumer_credit.is_active = false;
    alice.vtb.mortgage.is_active = true;
    alice.vtb.mortgage.body_debt = 8'000'000;
    alice.vtb.mortgage.monthly_payment = 90'000;
    alice.vtb.mortgage.interest_rate = 0.08;

    alice.crypto_account.balance = 0.0;
    alice.crypto_account.exchange_rate_usd = 65000.0;

    alice.car.value = 2'500'000;
    alice.car.gas = 12'000;

    alice.home.value = 15'000'000;
    alice.home.rent = 0;

    alice.monthly_food_cost = 25'000;
    alice.monthly_lifestyle_cost = 30'000;

    alice.health = { 85, 90, 80, true };
    alice.family = { false, true, 0 };

    // Bogdan
    bogdan.salary = 300'000;
    bogdan.vtb.account_rub = 50'000;
    bogdan.vtb.account_usd = 10'000;
    bogdan.vtb.consumer_credit.is_active = false;
    bogdan.vtb.mortgage.is_active = true;

    bogdan.crypto_account.balance = 1.5;
    bogdan.crypto_account.exchange_rate_usd = 65000.0;

    bogdan.car.value = 0;
    bogdan.car.gas = 0;

    bogdan.home.value = 0;
    bogdan.home.rent = 50'000;

    bogdan.monthly_food_cost = 60'000;
    bogdan.monthly_lifestyle_cost = 100'000;

    bogdan.health = { 60, 95, 80, true };
    bogdan.family = { false, true, 0 };
}

double get_random(double min, double max) {
    return min + (double)(rand()) / ((double)(RAND_MAX / (max - min)));
}

void alice_expenses(const int month, const int year, const Economy rus_economy)
{
    if (month == 12) alice.vtb.account_rub -= 2000;  // christmas party

    alice.monthly_food_cost += alice.monthly_food_cost * (rus_economy.inflation / 100.);

    alice.vtb.account_rub -= alice.monthly_food_cost;
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

void bogdan_salary(const int month, const int year)
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
    capital += alice.vtb.account_usd * russia.rate_usd_rub;
    capital += alice.car.value;
    capital += alice.home.value;
    printf("Capital = %lld", capital);
}


void alice_car(const int month)
{
    alice.vtb.account_rub -= alice.car.gas;
    if (month == 2) alice.vtb.account_rub -= alice.car.yearly_tax;
}

void world_events() 
{

}


void simulation()
{
    int year = 2026;
    int month = 2;

    while (alice.health.is_alive && bogdan.health.is_alive) {
        // World
        world_events();

        // Alice
        if (alice.health.is_alive) {
            alice_salary(month, year);
            alice_car(month);
            // my_cat();
            // my_trip();
            // my_rent();
            // my_mortgage();
            alice_expenses(month, year, russia);
        }

        //Bogdan
        if (bogdan.health.is_alive) {
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