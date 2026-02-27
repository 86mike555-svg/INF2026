#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <math.h>
#include <cstdlib> // random
#include <vector>

// typedef int RUB;  // C
using RUB = long long int;  // C++
const RUB CASH_LIMIT = 100'000;


struct Car {
    RUB value;
    RUB gas;
};


struct Job {
    RUB salary;                // текущая зарплата
    double fire_probability;   // шанс увольнения в месяц (%)
    double raise_probability;  // шанс повышения в месяц (%)
    double annual_raise_percent; // повышение в год (%)
    int raise_month;           // месяц повышения
};


struct World {
    double inflation_rate;     // инфляция в %
};


struct Deposit {
    RUB amount;                // сумма на вкладе
    double annual_rate;        // годовая ставка %
    int months_left;           // срок до конца
    bool replenishable;        // можно ли пополнять
};


struct Credit {
    RUB sumcredit;
    RUB monthly_payment;
    double interest_rate; // ставка в %
    int months_left;      // срок до конца
};


struct Investment {
    RUB amount;
    double expected_return; // годовая доходность %
    double risk;            // риск %
};


struct YearlyReport {
    int year;
    RUB net_worth;
    RUB capital;
    RUB deposit;
    RUB car_value;
    RUB credit;
    RUB rent_paid; // для Боба
};

std::vector<YearlyReport> report_alice;
std::vector<YearlyReport> report_bob;

struct Person {
    RUB salary;
    RUB food;
    Car car;
    RUB capital;  // наличные
    Deposit deposit;
    Job job;
    Credit credit;
    Investment investment;
    RUB rent; 
};


Person alice;
Person bob;


void alice_init()
{
    alice.capital = 0;
    alice.salary = 500'000;
    alice.food = 20'000;

    alice.car.value = 2'400'000;
    alice.car.gas = 10'000;

    alice.deposit.amount = 0;
    alice.deposit.annual_rate = 11.5;
    alice.deposit.months_left = 12;
    alice.deposit.replenishable = true;

    alice.job.salary = 180'000;
    alice.job.fire_probability = 2.0;
    alice.job.raise_probability = 5.0;
    alice.job.annual_raise_percent = 7.5;
    alice.job.raise_month = 3;

    alice.credit.sumcredit = 2'400'000;
    alice.credit.monthly_payment = 30'000;
    alice.credit.interest_rate = 12.0;
    alice.credit.months_left = 48;

    alice.investment.amount = 0;
    alice.investment.expected_return = 15.0;
    alice.investment.risk = 5.0;
}


void bob_init()
{
    bob.capital = 0;
    bob.salary = 500'000;
    bob.food = 20'000;

    bob.car.value = 2'400'000;
    bob.car.gas = 10'000;

    bob.deposit.amount = 0;
    bob.deposit.annual_rate = 11.5;
    bob.deposit.months_left = 12;
    bob.deposit.replenishable = true;

    bob.job.salary = 180'000;
    bob.job.fire_probability = 2.0;
    bob.job.raise_probability = 5.0;
    bob.job.annual_raise_percent = 7.5;
    bob.job.raise_month = 3;

    bob.investment.amount = 0;
    bob.investment.expected_return = 15.0;
    bob.investment.risk = 5.0;
}


World world_init()
{
    World world;
    world.inflation_rate = 8.0; // 8% годовых
    return world;
}


void apply_inflation(Person& alice, const World& world)
{
    double monthly_inflation = world.inflation_rate / 12.0 / 100.0;

    alice.food = static_cast<RUB>(alice.food * (1 + monthly_inflation));
    alice.car.gas = static_cast<RUB>(alice.car.gas * (1 + monthly_inflation));
    alice.car.value = static_cast<RUB>(alice.car.value * (1 + monthly_inflation));
}


void salary_with_career(int year, int month, Person& person)
{
    if (month == person.job.raise_month)
    {
        person.salary = static_cast<RUB>(person.salary * (1 + person.job.annual_raise_percent / 100.0));
    }

    if ((rand() % 100) < person.job.raise_probability)
    {
        person.salary = static_cast<RUB>(person.salary * 1.1);
    }

    if ((rand() % 100) < person.job.fire_probability)
    {
        person.salary = 0;
    }

    person.capital += person.salary;
}



void deposit_interest(Person& alice)
{
    if (alice.deposit.amount <= 0) return;
    if (alice.deposit.months_left <= 0) return;

    RUB income = static_cast<RUB>(alice.deposit.amount * (alice.deposit.annual_rate / 12.0 / 100.0));
    alice.deposit.amount += income;
    alice.deposit.months_left--;
}


void replenish_deposit(Person& alice)
{
    if (!alice.deposit.replenishable) return;
    if (alice.capital <= CASH_LIMIT) return;
    if (alice.deposit.months_left <= 0) return;

    RUB excess = alice.capital - CASH_LIMIT;
    alice.capital -= excess;
    alice.deposit.amount += excess;
}


void person_food(Person& person, const World& world)
{
    double monthly_inflation = world.inflation_rate / 12.0 / 100.0;
    RUB adjusted_food = static_cast<RUB>(person.food * (1 + monthly_inflation));
    person.capital -= adjusted_food;
}


void person_car(Person& person, const World& world)
{
    double monthly_inflation = world.inflation_rate / 12.0 / 100.0;
    RUB adjusted_gas = static_cast<RUB>(person.car.gas * (1 + monthly_inflation));
    person.capital -= adjusted_gas;
}


void depreciate_car(Person& person)
{
    double depreciation_rate = 1.0 / 100.0; // 1% в месяц
    person.car.value = static_cast<RUB>(person.car.value * (1 - depreciation_rate));
}


void person_pay_rent(Person& person)
{
    if (person.rent <= 0) return;

    person.capital -= person.rent;
}


void pay_credit(Person& alice)
{
    if (alice.credit.months_left <= 0) return;

    RUB interest = static_cast<RUB>(alice.credit.sumcredit * (alice.credit.interest_rate / 12.0 / 100.0));
    RUB payment = alice.credit.monthly_payment + interest;

    if (alice.capital >= payment)
    {
        alice.capital -= payment;
        alice.credit.sumcredit -= alice.credit.monthly_payment;
        alice.credit.months_left--;
    }
    else
    {
        if (alice.capital >= interest)
        {
            RUB principal_payment = alice.capital - interest;
            alice.credit.sumcredit -= principal_payment;
            alice.capital = 0;
        }
        else
        {
            alice.credit.sumcredit += (interest - alice.capital);
            alice.capital = 0;
        }
    }

    if (alice.credit.sumcredit < 0) alice.credit.sumcredit = 0;
}


void person_pay_rent(Person& person, const World& world)
{
    if (person.rent <= 0) return;

    double monthly_inflation = world.inflation_rate / 12.0 / 100.0;
    RUB adjusted_rent = static_cast<RUB>(person.rent * (1 + monthly_inflation));

    person.capital -= adjusted_rent;
}


void person_simulation(Person& person, const World& world, std::vector<YearlyReport>& yearly_report_vector)
{
    int start_year = 2026;
    int simulation_years = 30;

    int year = start_year;
    int month = 1;

    while (year < start_year + simulation_years) 
    {
        salary_with_career(year, month, person);

        person_food(person, world);
        person_car(person, world);  
        depreciate_car(person);

        replenish_deposit(person);
        deposit_interest(person);

        pay_credit(person);

        person_pay_rent(person, world);

        if (month == 12)
        {
            YearlyReport yearly_report_entry;

            yearly_report_entry.year = year;
            yearly_report_entry.net_worth = calculate_net_worth(person);
            yearly_report_entry.capital = person.capital;
            yearly_report_entry.deposit = person.deposit.amount;
            yearly_report_entry.car_value = person.car.value;
            yearly_report_entry.credit = person.credit.sumcredit;
            yearly_report_entry.rent_paid = person.rent;

            yearly_report_vector.push_back(yearly_report_entry);
        }

        month++;

        if (month == 13)
        {
            month = 1;
            year++;
        }
    }
}


void compare_people(const Person& first, const Person& second)
{
    RUB first_net = calculate_net_worth(first);
    RUB second_net = calculate_net_worth(second);

    printf("\n======== COMPARISON ========\n");

    if (first_net > second_net)
        printf("First person is wealthier by %lld\n", first_net - second_net);
    else if (second_net > first_net)
        printf("Second person is wealthier by %lld\n", second_net - first_net);
    else
        printf("Both are equal in wealth\n");
}


RUB calculate_net_worth(const Person& person)
{
    RUB assets = 0;
    RUB liabilities = 0;

    assets += person.capital;
    assets += person.deposit.amount;
    assets += person.car.value;
    assets += person.investment.amount;

    liabilities += person.credit.sumcredit;

    return assets - liabilities;
}

void print_person_results(const Person& person, const std::string& name)
{
    printf("\n===== %s RESULT =====\n", name.c_str());
    printf("Final salary      = %lld\n", person.salary);
    printf("Final capital     = %lld\n", person.capital);
    printf("Deposit amount    = %lld\n", person.deposit.amount);
    printf("Car value         = %lld\n", person.car.value);
    printf("Credit debt       = %lld\n", person.credit.sumcredit);

    RUB net_worth = calculate_net_worth(person);
    printf("NET WORTH         = %lld\n", net_worth);
}


void print_yearly_report(const std::vector<YearlyReport>& report_vector, const std::string& name)
{
    printf("\n================ %s YEARLY REPORT ================\n", name.c_str());
    printf("Year | NetWorth | Capital | Deposit | CarValue | Credit | Rent\n");

    for (size_t index = 0; index < report_vector.size(); index++)
    {
        printf("%4d | %8lld | %7lld | %7lld | %8lld | %7lld | %7lld\n",
            report_vector[index].year,
            report_vector[index].net_worth,
            report_vector[index].capital,
            report_vector[index].deposit,
            report_vector[index].car_value,
            report_vector[index].credit,
            report_vector[index].rent_paid
        );
    }
}


int main()
{
    alice_init();
    bob_init();

    World world = world_init();

    person_simulation(alice, world, report_alice);
    person_simulation(bob, world, report_bob);

    print_person_results(alice, "ALICE");
    print_person_results(bob, "BOB");

    compare_people(alice, bob);
}
