#include <stdio.h>


using RUB = long long int;
using USD = long long int;

using Percent = float;


struct Bank {
    RUB account;
    RUB deposite;
    Percent interest;

    USD account_usd;
    float rate_usd_rub;
};


struct Car {
    RUB gas;
    RUB value;
};


struct Luxery {
    RUB nogti;
};


struct Kvartira {
    RUB rent;
};


struct Person {
    Kvartira kvartira;
    Luxery luxery;
    Bank vtb;
    Car car;
    RUB salary;
    RUB food;
};

struct Person eva;
struct Person danil;

void eva_init()
{
    eva.vtb.account = 0;
    eva.vtb.deposite = 1'000'000;
    eva.vtb.interest = 14.5;
    eva.salary = 180'000;

    eva.vtb.account_usd = 1'000;
    eva.vtb.rate_usd_rub = 78.5;

    eva.food = 20'000;

    eva.car.value = 2'400'000;
    eva.car.gas = 15'000;

    eva.luxery.nogti = 3000;
}

void danil_init()
{
    danil.vtb.account = 0;
    danil.vtb.deposite = 1'000'000;
    danil.vtb.interest = 14.5;
    danil.salary = 180'000;

    danil.vtb.account_usd = 1'000;
    danil.vtb.rate_usd_rub = 78.5;

    danil.food = 20'000;

    danil.car.value = 2'400'000;
    danil.car.gas = 15'000;
}


void eva_salary(const int month, const int year)
{
    if (month == 12) {
        eva.vtb.account += eva.salary;  // 13th salary
    }

    if (month == 1 and year == 2027) {
        eva.salary *= 1.5;  // promotion
    }

    eva.vtb.account += eva.salary;
}


void danil_salary(const int month, const int year)
{
    if (month == 12) {
        danil.vtb.account += danil.salary;  // 13th salary
    }

    if (month == 1 and year == 2027) {
        danil.salary *= 1.5;  // promotion
    }

    danil.vtb.account += danil.salary;
}


void eva_kvartira()
{
    eva.vtb.account -= eva.kvartira.rent;
}


void eva_luxery()
{
    eva.vtb.account -= eva.luxery.nogti;
}


void eva_food()
{
    eva.vtb.account -= eva.food;
    danil.vtb.account -= danil.food;
}


void eva_car()
{
    eva.vtb.account -= eva.car.gas;
}


void danil_car()
{
    eva.vtb.account -= eva.car.gas;
}


void eva_deposite(const int month, const int year)
{
    if (year == 2026) eva.vtb.interest = 14.5;
    if (year == 2027) eva.vtb.interest = 13.5;
    if (year == 2028) eva.vtb.interest = 12.5;
    if (year == 2029) eva.vtb.interest = 11.5;

    eva.vtb.deposite += eva.vtb.deposite * (eva.vtb.interest / 12.0 / 100.0);

    eva.vtb.deposite += eva.vtb.account;
    eva.vtb.account = 0;
}


void eva_freelance(const int month, const int year)
{
    if (month == 3 and year == 2027) {
        eva.vtb.account_usd += 3'000;
    }
}


void danil_freelance(const int month, const int year)
{
    if (month == 3 and year == 2027) {
        eva.vtb.account_usd += 3'000;
    }
}


void print_results()
{
    printf("Salary = %lld\n", eva.salary);

    RUB capital = 0;
    capital += eva.vtb.account;
    capital += eva.car.value;
    capital += eva.vtb.deposite;
    capital += eva.vtb.account_usd * eva.vtb.rate_usd_rub;
    printf("Capital = %lld", capital);

    printf("Salary = %lld\n", danil.salary);

    RUB capital = 0;
    capital += danil.vtb.account;
    capital += danil.car.value;
    capital += danil.vtb.deposite;
    capital += danil.vtb.account_usd * danil.vtb.rate_usd_rub;
    printf("Capital = %lld", capital);
}





void simulation()
{
    int month = 2;
    int year = 2026;

    while (not (month == 3 and year == 2028)) {
        eva_salary(month, year);
        eva_freelance(month, year);
        eva_car();
        eva_food();
        eva_luxery();
        eva_kvartira();
        // my_cat();
        // my_medine();
        // my_home();
        eva_deposite(month, year);


        danil_salary(month, year);
        danil_freelance(month, year);
        danil_car();


        ++month;
        if (month == 13) {
            ++year;
            month = 1;
        }
    }
}


int main()
{
    eva_init();

    danil_init();

    simulation();

    print_results();
}
