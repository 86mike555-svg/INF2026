#include <stdio.h>

using Percent = float;
using Value = float;

using RUB = long long int;
using USD = long long int;

struct Car
{
    RUB value;
    RUB gas;
};

struct Bank
{
    RUB account_rub;
    USD account_usd;
    USD investment_portfolio;
    float rate_usd_rub;
};

struct Person
{
    Bank vtb;
    RUB food;
    RUB salary_rub;
    USD salary_usd;
    Car car;
    RUB lunch_cost;
    RUB home;
    Value health_problem_threshold;
    RUB health;
    Value luck;
};
struct Person alice;

void alice_food_cost(const int month, const int year)
{
    if (month == 12)
        alice.food += 2000; // party

    alice.food += alice.lunch_cost * 21; // 21 - average number of working days in a month
    Percent inflation = 12.0;
    switch (year)
    {
    case 2026:
        inflation = 12.5;
        break;
    case 2027:
        inflation = 14.0;
        break;
    case 2028:
        inflation = 13.0;
        break;
    case 2029:
        inflation = 11.5;
        break;
    }

    alice.food += alice.food * (inflation / 100. / 12.); 

    alice.vtb.account_rub -= alice.food;
}

void count_health_problem_threshold(Person person)
{
    if (person.vtb.account_rub < 0)
        person.health_problem_threshold += 0.2; // stress

    if (person.vtb.account_rub > 5000 || person.vtb.account_usd > 1000)
        person.health_problem_threshold -= 0.2; // financial stability => recovery

    if (person.luck > 0)
        person.health_problem_threshold -= 0.1; // minimize risk of health problems 
}

void reset_health_problem_threshold(Person person)
{
    person.health_problem_threshold = 0;
}

void reset_luck(Person person)
{
    person.luck = 0;
}

void alice_first_job(const int month, const int year)
{
    if (month == 2 && year == 2026 && alice.luck > 0.3)
        alice.vtb.account_rub += 5000; // bonus

    if (month == 3 && alice.luck > 0.3)
        alice.salary_rub *= 1.5;           // promotion
        alice.health_problem_threshold += 0.1; // responsibility stress

    alice.vtb.account_rub += alice.salary_rub;
    alice.health_problem_threshold += 0.2; // work stress
}

void alice_second_job(const int month, const int year)
{
    if (month == 5 && year == 2027 && alice.luck > 0.2)
        alice.vtb.account_usd += 3000; // bonus

    alice.vtb.account_usd += alice.salary_usd;
    alice.health_problem_threshold += 0.2; // work stress
}

void alice_car()
{
    alice.vtb.account_rub -= alice.car.gas;
    alice.health_problem_threshold += 0.2; // unactive lifestyle
}

void alice_trip()
{
    if (alice.vtb.account_usd > 6000)
        alice.vtb.account_usd -= 6000; // trip to Maldives

    alice.health_problem_threshold -= 0.3; // relaxation
}

void alice_cat(const int month, const int year)
{
    if (month == 12 && year == 2027)
        alice.vtb.account_usd -= 1000; // start-up costs

    if (month == 1)
        alice.vtb.account_rub -= 3000; // veterinary costs

    alice.vtb.account_rub -= 2000;         // food
    alice.vtb.account_rub -= 500;          // litter
    alice.health_problem_threshold -= 0.2; // cat's love
    alice.luck += 0.2; // cat brings luck
}

void alice_rent(const int month, const int year)
{
    if (alice.vtb.account_rub < 0)
    {
        alice.home += 5000;         // penalty
        alice.health_problem_threshold += 0.1; // stress
        alice.luck -= 0.2; // bad luck
    }
    else
    {
        alice.health_problem_threshold -= 0.1; // stability
    }

    Percent inflation = 8.3;
    switch (year)
    {
    case 2026:
        inflation = 6.1;
        break;
    case 2027:
        inflation = 9.4;
        break;
    case 2028:
        inflation = 8.4;
        break;
    case 2029:
        inflation = 8.0;
        break;
    }

    alice.home += alice.home * (inflation / 100. / 12.);

    alice.vtb.account_rub -= alice.home;
}

void alice_health(const int month, const int year)
{
    alice.health = 1000 * (alice.health_problem_threshold); // health depends on health problem threshold   

    if (month == 10)
        alice.health += 10000; // regular check-up
        alice.health_problem_threshold -= 0.1; // health awareness
        alice.luck += 0.1; // good health brings luck

    Percent inflation = 5.8;
    switch (year)
    {
    case 2026:
        inflation = 4.5;
        break;
    case 2027:
        inflation = 4.0;
        break;
    case 2028:
        inflation = 4.0;
        break;
    case 2029:
        inflation = 4.0;
        break;
    }

    alice.health += alice.health * (inflation / 100. / 12.);

    alice.vtb.account_rub -= alice.health;
}

void alice_investment_portfolio()
{
    if (alice.vtb.account_usd > 5000)
        alice.vtb.investment_portfolio += 5000; // invest in stocks
        alice.vtb.account_usd -= 5000;

    Percent return_rate = 10.0 * alice.luck; // return rate depends on luck
    alice.vtb.investment_portfolio = alice.vtb.investment_portfolio * (1.0 + return_rate / 100.);
}   

void print_results()
{
    printf("Capital_usd = %lld\n", alice.vtb.account_usd);
    printf("Capital_rub = %lld\n", alice.vtb.account_rub);
    printf("Capital_investment_portfolio = %lld\n", alice.vtb.investment_portfolio);
}

void RIP()
{
    printf("The person died due to health problems. Final capital:\n");
}

void alice_simulation()
{
    int year = 2026;
    int month = 2;

    while (!(year == 2028 && month == 8))
    {
        reset_health_problem_threshold(alice);
        reset_luck(alice);

        alice_food_cost(month, year);
        alice_first_job(month, year);
        alice_second_job(month, year);
        alice_car();
        alice_cat(month, year);
        alice_trip();
        alice_rent(month, year);
        alice_investment_portfolio();

        count_health_problem_threshold(alice);
        alice_health(month, year);

        if (alice.health_problem_threshold > 1)
        {
            RIP();
            return;
        }

        ++month;
        if (month == 13)
        {
            ++year;
            month = 1;
        }
    }
}


void alice_init()
{
    alice.vtb.rate_usd_rub = 78.76;
    alice.vtb.account_rub = 0;
    alice.vtb.account_usd = 10000;

    alice.lunch_cost = 5;
    alice.salary_rub = 180000;
    alice.salary_usd = 1500;
    alice.food = 1000;
    alice.home = 50000;

    alice.car.value = 2400000;
    alice.car.gas = 15000;
}

int main()
{
    alice_init();
    alice_simulation();
    print_results();
}
