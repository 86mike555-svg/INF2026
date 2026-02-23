#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <array>
#include <typeinfo>

using Percent = float;

using RUB = long long int;
using USD = long long int;
using BTC = double;

const std::array<double, 20> BTC_RATES = {
    65000.0, 58000.0, 45000.0, 30000.0, 35000.0, 50000.0, 69000.0, 80000.0,
    75000.0, 60000.0, 40000.0, 20000.0, 25000.0, 40000.0, 90000.0, 120000.0,
    100000.0, 85000.0, 70000.0, 150000.0
};

struct Economy {
    Percent inflation;
    double rate_usd_rub;
    int avg_salary;
    USD life_last_cost;

    bool crisis;
};

struct StockPortfolio {
    double russian_stocks;
    double us_stocks;
    double bonds;
    double index_fund;
};

struct StockMarket {
    double russian_index;
    double sp500;
    double bond_yield;
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
    int missed_payments;
};

struct Bank {
    RUB account_rub;
    USD account_usd;

    Loan mortgage;
    Loan consumer_credit;
    short credit_score;
};

struct Housing {
    RUB value;
    RUB rent;
    RUB monthly_utilities;
};

struct Health {
    RUB medicine_expenses;
    short happiness;
    short physical_health;
    short age;
    short max_age;
    short stress;
    bool is_alive;
};

struct Education {
    short degree_level;
    bool is_studying;
    RUB tuition_fee;
    int months_remaining;
    bool higher_education;
    short skill_level;
};

struct Family
{
    bool has_partner;
    bool has_parents;
    short children_amount;
    RUB child_expences;
};

struct Person {
    Bank vtb;
    Crypto crypto_account;
    StockPortfolio portfolio;

    Car car;
    Housing home;

    RUB salary;
    RUB monthly_food_cost;
    RUB monthly_lifestyle_cost;

    Education education;
    Health health;
    Family family;

};

struct Economy russia;
struct StockMarket market = { 3000.0, 4500.0, 8.0 };

struct Person alice;
struct Person bogdan;

int year = 2026;
int month = 2;
int simulation_month_counter = 0;

int current_event_type = 0;
int event_duration = 0;
int event_months_active = 0;
double event_severity = 0.0;
bool event_is_active = false;

const int MAX_CREDIT_SCORE = 850;
const int MIN_CREDIT_SCORE = 300;
const int MAX_MISSED_PAYMENTS_BEFORE_BANKRUPTCY = 3;


void init()
{
    srand(time(NULL));
    // Global
    russia.rate_usd_rub = 76.75;
    russia.inflation = 5.59;
    russia.avg_salary = 96'772;
    russia.life_last_cost = 100'000.0;
    russia.crisis = false;

    current_event_type = 0;
    event_is_active = false;
    event_duration = 0;
    event_months_active = 0;
    event_severity = 0.0;

    // Alice
    alice.salary = 200'000;
    alice.vtb.account_rub = 150'000;
    alice.vtb.account_usd = 0;
    alice.vtb.consumer_credit.is_active = false;
    alice.vtb.consumer_credit.missed_payments = 0;
    alice.vtb.consumer_credit.body_debt = 0;
    alice.vtb.consumer_credit.monthly_payment = 0;
    alice.vtb.consumer_credit.interest_rate = 0;

    alice.vtb.mortgage.is_active = true;
    alice.vtb.mortgage.body_debt = 8'000'000;
    alice.vtb.mortgage.monthly_payment = 90'000;
    alice.vtb.mortgage.interest_rate = 8.0;
    alice.vtb.mortgage.missed_payments = 0;

    alice.vtb.credit_score = 700;

    alice.portfolio.russian_stocks = 0;
    alice.portfolio.us_stocks = 0;
    alice.portfolio.bonds = 0;
    alice.portfolio.index_fund = 0;

    alice.crypto_account.balance = 0.0;
    alice.crypto_account.exchange_rate_usd = BTC_RATES[0];

    alice.car.value = 2'500'000;
    alice.car.gas = 12'000;
    alice.car.yearly_tax = 4'000;

    alice.home.value = 15'000'000;
    alice.home.rent = 0;
    alice.home.monthly_utilities = 4'000;

    alice.monthly_food_cost = 25'000;
    alice.monthly_lifestyle_cost = 30'000;

    alice.education.degree_level = 1;
    alice.education.is_studying = true;
    alice.education.tuition_fee = 0;
    alice.education.months_remaining = 30;
    alice.education.skill_level = 10;
    alice.education.higher_education = true;

    alice.health.medicine_expenses = 20'000;
    alice.health.happiness = 85;
    alice.health.physical_health = 90;
    alice.health.age = 20;
    alice.health.max_age = 80;
    alice.health.stress = 10;
    alice.health.is_alive = true;
    alice.family = { false, true, 0, 30'000 };

    // Bogdan
    bogdan.salary = 300'000;
    bogdan.vtb.account_rub = 50'000;
    bogdan.vtb.account_usd = 10'000;
    bogdan.vtb.consumer_credit.is_active = false;
    bogdan.vtb.consumer_credit.missed_payments = 0;
    bogdan.vtb.consumer_credit.body_debt = 0;
    bogdan.vtb.consumer_credit.monthly_payment = 0;
    bogdan.vtb.consumer_credit.interest_rate = 0;

    bogdan.vtb.mortgage.is_active = false;

    bogdan.vtb.credit_score = 650;

    bogdan.portfolio.russian_stocks = 0;
    bogdan.portfolio.us_stocks = 0;
    bogdan.portfolio.bonds = 0;
    bogdan.portfolio.index_fund = 0;

    bogdan.crypto_account.balance = 1.5;
    bogdan.crypto_account.exchange_rate_usd = BTC_RATES[0];

    bogdan.car.value = 0;
    bogdan.car.gas = 0;

    bogdan.home.value = 0;
    bogdan.home.rent = 50'000;
    bogdan.home.monthly_utilities = 5'000;

    bogdan.monthly_food_cost = 60'000; //healthy food
    bogdan.monthly_lifestyle_cost = 20'000;

    bogdan.education.degree_level = 1;
    bogdan.education.is_studying = true;
    bogdan.education.tuition_fee = 0;
    bogdan.education.months_remaining = 30;
    bogdan.education.skill_level = 20;
    bogdan.education.higher_education = true;

    bogdan.health.medicine_expenses = 30'000;
    bogdan.health.happiness = 70;
    bogdan.health.physical_health = 95;
    bogdan.health.age = 20;
    bogdan.health.max_age = 80;
    bogdan.health.stress = 20;
    bogdan.health.is_alive = true;
    bogdan.family = { false, true, 0, 40'000 };

}


double get_random(double min, double max)
{
    return min + (double)(rand()) / ((double)(RAND_MAX / (max - min)));
}


void crypto_rates_update()
{
    int index = simulation_month_counter % BTC_RATES.size();
    double current_rate = BTC_RATES[index];
    double noise = get_random(-2000.0, 2000.0);

    alice.crypto_account.exchange_rate_usd = current_rate + noise;
    bogdan.crypto_account.exchange_rate_usd = current_rate + noise;
}


void stock_market_update() {
    double ru_change = get_random(-5.0, 5.0);
    double us_change = get_random(-3.0, 3.0);

    if (event_is_active) {
        if (current_event_type == 1 || current_event_type == 8 || current_event_type == 13) {
            // Crisis events
            ru_change -= 10.0 * event_severity;
            us_change -= 8.0 * event_severity;
        }
        else if (current_event_type == 4 || current_event_type == 17) {
            // Growth events
            ru_change += 5.0 * event_severity;
            us_change += 7.0 * event_severity;
        }
        else if (current_event_type == 11) {
            // Sanctions
            ru_change -= 15.0 * event_severity;
        }
    }

    market.russian_index *= (1.0 + ru_change / 100.0);
    market.sp500 *= (1.0 + us_change / 100.0);

    market.russian_index = fmax(500.0, fmin(10000.0, market.russian_index));
    market.sp500 = fmax(1000.0, fmin(15000.0, market.sp500));

    if (russia.crisis) {
        market.bond_yield = 15.0 + get_random(0, 5);
    }
    else {
        market.bond_yield = 7.0 + get_random(-1, 3);
    }
}


void invest_in_stocks(Person& person, const char* name) {
    RUB monthly_investment = 0;

    if (person.vtb.account_rub > person.salary * 3) {
        monthly_investment = person.vtb.account_rub - person.salary * 2;
        monthly_investment = fmin(monthly_investment, person.salary * 0.3);
    }

    if (monthly_investment <= 0) return;

    person.vtb.account_rub -= monthly_investment;

    person.portfolio.russian_stocks += monthly_investment * 0.4;
    person.portfolio.us_stocks += (monthly_investment * 0.3) / russia.rate_usd_rub;
    person.portfolio.bonds += monthly_investment * 0.2;
    person.portfolio.index_fund += monthly_investment * 0.1;
}


void update_portfolio_value(Person& person) {
    double ru_return = (market.russian_index / 3000.0 - 1.0) * 0.1;
    double us_return = (market.sp500 / 4500.0 - 1.0) * 0.08;
    double bond_return = market.bond_yield / 100.0 / 12.0;

    person.portfolio.russian_stocks *= (1.0 + ru_return);
    person.portfolio.us_stocks *= (1.0 + us_return);
    person.portfolio.bonds *= (1.0 + bond_return);
    person.portfolio.index_fund *= (1.0 + (ru_return + us_return) / 2);
}


RUB get_total_portfolio_value(Person& person) {
    return (RUB)(person.portfolio.russian_stocks +
        person.portfolio.us_stocks * russia.rate_usd_rub +
        person.portfolio.bonds +
        person.portfolio.index_fund);
}


RUB calculate_max_loan_amount(Person& person)
{
    if (person.vtb.credit_score < 400) return 0;

    double credit_multiplier = (double)(person.vtb.credit_score - 300) / 550.0;
    RUB max_loan = (RUB)(person.salary * 12 * credit_multiplier);

    if (person.vtb.consumer_credit.is_active) {
        max_loan -= person.vtb.consumer_credit.body_debt;
    }
    if (person.vtb.mortgage.is_active) {
        max_loan -= person.vtb.mortgage.body_debt / 5;
    }

    return fmax(0, max_loan);
}


Percent calculate_loan_interest_rate(Person& person)
{
    Percent base_rate = russia.crisis ? 25.0f : 15.0f;

    Percent credit_adjustment = (750.0f - person.vtb.credit_score) / 50.0f;

    return fmax(10.0f, fmin(40.0f, base_rate + credit_adjustment));
}


bool take_consumer_credit(Person& person, RUB amount)
{
    if (person.vtb.consumer_credit.is_active) {

        RUB total_debt = person.vtb.consumer_credit.body_debt + amount;
        RUB max_allowed = calculate_max_loan_amount(person) + person.vtb.consumer_credit.body_debt;

        if (total_debt > max_allowed) {
            return false;
        }

        person.vtb.consumer_credit.body_debt = total_debt;
        person.vtb.consumer_credit.interest_rate = calculate_loan_interest_rate(person);

        double monthly_rate = person.vtb.consumer_credit.interest_rate / 1200.0;
        double annuity_coef = (monthly_rate * pow(1 + monthly_rate, 36)) /
            (pow(1 + monthly_rate, 36) - 1);
        person.vtb.consumer_credit.monthly_payment = (RUB)(total_debt * annuity_coef);
    }
    else {
        RUB max_loan = calculate_max_loan_amount(person);

        if (amount > max_loan) {
            return false;
        }

        person.vtb.consumer_credit.is_active = true;
        person.vtb.consumer_credit.body_debt = amount;
        person.vtb.consumer_credit.interest_rate = calculate_loan_interest_rate(person);
        person.vtb.consumer_credit.missed_payments = 0;

        double monthly_rate = person.vtb.consumer_credit.interest_rate / 1200.0;
        double annuity_coef = (monthly_rate * pow(1 + monthly_rate, 36)) /
            (pow(1 + monthly_rate, 36) - 1);
        person.vtb.consumer_credit.monthly_payment = (RUB)(amount * annuity_coef);

    }

    person.vtb.account_rub += amount;
    person.vtb.credit_score -= 10;
    person.health.stress += 15;

    return true;
}


void process_credit_payment(Person& person)
{
    if (!person.vtb.consumer_credit.is_active) return;

    RUB payment = person.vtb.consumer_credit.monthly_payment;

    if (person.vtb.account_rub >= payment) {
        person.vtb.account_rub -= payment;

        double interest_part = person.vtb.consumer_credit.body_debt *
            (person.vtb.consumer_credit.interest_rate / 1200.0);
        double principal_part = payment - interest_part;

        person.vtb.consumer_credit.body_debt -= (RUB)principal_part;

        if (person.vtb.credit_score < MAX_CREDIT_SCORE) {
            person.vtb.credit_score += 1;
        }

        if (person.vtb.consumer_credit.missed_payments > 0) {
            person.vtb.consumer_credit.missed_payments = 0;
        }

        // The loan is repaid
        if (person.vtb.consumer_credit.body_debt <= 0) {
            person.vtb.consumer_credit.is_active = false;
            person.vtb.consumer_credit.body_debt = 0;
            person.vtb.consumer_credit.monthly_payment = 0;
            person.vtb.credit_score += 20;
            person.health.stress -= 10;
        }
    }
    else {
        person.vtb.consumer_credit.missed_payments++;
        person.vtb.credit_score -= 30;
        person.health.stress += 25;

        person.vtb.consumer_credit.body_debt = (RUB)(
            person.vtb.consumer_credit.body_debt * 1.02
            );

    }
}


bool check_bankruptcy(Person& person)
{
    if (person.vtb.consumer_credit.missed_payments >= MAX_MISSED_PAYMENTS_BEFORE_BANKRUPTCY ||
        person.vtb.mortgage.missed_payments >= MAX_MISSED_PAYMENTS_BEFORE_BANKRUPTCY) {

        person.home.value = 0;
        person.car.value = 0;
        person.car.gas = 0;
        person.vtb.account_rub = 0;
        person.vtb.account_usd = 0;
        person.crypto_account.balance = 0;
        person.portfolio = { 0, 0, 0, 0 };

        person.vtb.consumer_credit.is_active = false;
        person.vtb.mortgage.is_active = false;

        person.vtb.credit_score = MIN_CREDIT_SCORE;
        person.health.stress = 100;
        person.health.happiness = 0;

        if (person.health.physical_health < 30 || person.health.age > 60) {
            person.health.is_alive = false;
            return true;
        }

        person.home.rent = 30000;

        return true;
    }
    return false;
}



bool try_spend(Person& person, RUB amount)
{
    if (amount <= 0) return true;

    if (person.vtb.account_rub >= amount) {
        person.vtb.account_rub -= amount;
        return true;
    }

    RUB deficit = amount - person.vtb.account_rub;

    if (person.vtb.account_usd > 0) {
        USD usd_needed = (USD)ceil((double)deficit / russia.rate_usd_rub);
        USD usd_to_use = fmin(usd_needed, person.vtb.account_usd);

        person.vtb.account_rub += (RUB)(usd_to_use * russia.rate_usd_rub);
        person.vtb.account_usd -= usd_to_use;

        if (person.vtb.account_rub >= amount) {
            person.vtb.account_rub -= amount;
            return true;
        }
    }

    deficit = amount - person.vtb.account_rub;

    if (person.crypto_account.balance > 0.0001) {
        double crypto_rub_value = person.crypto_account.balance *
            person.crypto_account.exchange_rate_usd *
            russia.rate_usd_rub;

        if (crypto_rub_value >= deficit) {
            double btc_to_sell = deficit / (person.crypto_account.exchange_rate_usd *
                russia.rate_usd_rub);
            person.crypto_account.balance -= btc_to_sell;
            person.vtb.account_rub += deficit;
        }
        else {
            person.vtb.account_rub += (RUB)crypto_rub_value;
            person.crypto_account.balance = 0;
        }

        if (person.vtb.account_rub >= amount) {
            person.vtb.account_rub -= amount;
            return true;
        }
    }

    deficit = amount - person.vtb.account_rub;
    RUB portfolio_value = get_total_portfolio_value(person);

    if (portfolio_value > 0) {
        double sell_ratio = fmin(1.0, (double)deficit / portfolio_value);

        person.vtb.account_rub += (RUB)(person.portfolio.russian_stocks * sell_ratio);
        person.vtb.account_rub += (RUB)(person.portfolio.us_stocks * russia.rate_usd_rub * sell_ratio);
        person.vtb.account_rub += (RUB)(person.portfolio.bonds * sell_ratio);
        person.vtb.account_rub += (RUB)(person.portfolio.index_fund * sell_ratio);

        person.portfolio.russian_stocks *= (1.0 - sell_ratio);
        person.portfolio.us_stocks *= (1.0 - sell_ratio);
        person.portfolio.bonds *= (1.0 - sell_ratio);
        person.portfolio.index_fund *= (1.0 - sell_ratio);

        if (person.vtb.account_rub >= amount) {
            person.vtb.account_rub -= amount;
            return true;
        }
    }

    deficit = amount - person.vtb.account_rub;

    RUB credit_amount = (RUB)(deficit * 1.2);
    credit_amount = fmax(credit_amount, 50000);

    if (take_consumer_credit(person, credit_amount)) {
        if (person.vtb.account_rub >= amount) {
            person.vtb.account_rub -= amount;
            return true;
        }
    }

    person.vtb.account_rub = 0;
    person.health.stress += 40;

    return false;
}


void alice_food_expences(const int month)
{
    try_spend(alice, alice.monthly_food_cost);
    if (month == 12) {
        alice.monthly_food_cost += (RUB)alice.monthly_food_cost * (russia.inflation / 100.);
    }
}



void alice_lifestyle_expences(const int month)
{
    try_spend(alice, alice.monthly_lifestyle_cost);
    if (month == 12) {
        alice.monthly_lifestyle_cost *= (1.0 + russia.inflation / 100.0);
    }
}


void alice_home_expences(const int month)
{
    try_spend(alice, alice.home.monthly_utilities);
    if (month == 12) {
        alice.home.monthly_utilities *= (1.0 + russia.inflation / 100.0);
    }
}


void alice_children_expences(const int month)
{
    RUB children_cost = alice.family.children_amount * alice.family.child_expences;

    try_spend(alice, children_cost);
    if (month == 12) {
        alice.family.child_expences *= (1.0 + russia.inflation / 100.0);
    }
}


void bogdan_food_expences(const int month)
{
    try_spend(bogdan, bogdan.monthly_food_cost);
    if (month == 12) {
        bogdan.monthly_food_cost += bogdan.monthly_food_cost * (russia.inflation / 100.);
    }
}


void bogdan_lifestyle_expences(const int month)
{
    try_spend(bogdan, bogdan.monthly_lifestyle_cost);
    if (month == 12) {
        bogdan.monthly_lifestyle_cost *= (1.0 + russia.inflation / 100.0);
    }
}


void bogdan_home_expences(const int month)
{
    try_spend(bogdan, bogdan.home.monthly_utilities);
    try_spend(bogdan, bogdan.home.rent);
    if (month == 12) {
        bogdan.home.monthly_utilities *= (1.0 + russia.inflation / 100.0);
        bogdan.home.rent *= (1.0 + russia.inflation / 100.0);
    }
}


void bogdan_children_expences(const int month)
{
    RUB children_cost = bogdan.family.children_amount * bogdan.family.child_expences;

    try_spend(bogdan, children_cost);
    if (month == 12) {
        bogdan.family.child_expences *= (1.0 + russia.inflation / 100.0);
    }
}


void do_russian_inflation()
{
    if (month == 1) {
        russia.avg_salary *= (russia.inflation / 100.) + 1;
    }
}


void alice_salary(const int month, const int year)
{
    if (month == 1) {
        alice.salary *= 1.05; //indexation
        alice.health.happiness += 5;
    }

    if (month == 2 && year == 2026) {
        alice.vtb.account_rub += 5000;  // bonus
        alice.health.happiness += 8;
    }

    alice.vtb.account_rub += alice.salary;
}


void bogdan_salary(const int month, const int year)
{
    if (get_random(0, 100) < 15) {
        // Job change
        double raise = get_random(1.10, 1.30);
        bogdan.salary = (RUB)(bogdan.salary * raise);

        // Job change stress
        bogdan.health.stress += (short)get_random(10, 25);
        if (bogdan.health.stress > 100) bogdan.health.stress = 100;
    }

    bogdan.vtb.account_rub += bogdan.salary;
    bogdan.health.happiness += 15;
}


void bogdan_life_prolongation(const int month)
{
    if (month == 1) {
        russia.life_last_cost *= (1.0 + russia.inflation / 100.0);
        RUB cost = (RUB)(russia.life_last_cost * russia.rate_usd_rub);

        if (bogdan.health.max_age >= 120) return;

        if (bogdan.health.max_age - bogdan.health.age > 3) return;

        double total_wealth = bogdan.vtb.account_rub +
            (bogdan.vtb.account_usd * russia.rate_usd_rub) +
            (bogdan.crypto_account.balance * bogdan.crypto_account.exchange_rate_usd * russia.rate_usd_rub);

        if (total_wealth >= cost) {
            if (try_spend(bogdan, cost)) {
                bogdan.health.max_age += 2;
                alice.health.happiness += 10;
            }
        }
    }
}


void apply_seasonal_events()
{
    if (month == 12) {
        alice.monthly_lifestyle_cost *= 1.5;
        bogdan.monthly_lifestyle_cost *= 1.5;
        alice.health.happiness += 5;
        bogdan.health.happiness += 5;
    }

    if (month == 1 && year > 2026) {
        alice.monthly_lifestyle_cost /= 1.5;
        bogdan.monthly_lifestyle_cost /= 1.5;
    }

    if (month >= 6 && month <= 8) {
        alice.health.stress = fmax(0, alice.health.stress - 2);
        bogdan.health.stress = fmax(0, bogdan.health.stress - 2);
    }

    if (month >= 9 && month <= 11) {
        if (get_random(0, 100) < 5) {
            alice.health.physical_health -= 5;
            alice.health.medicine_expenses += 5000;
        }
        if (get_random(0, 100) < 5) {
            bogdan.health.physical_health -= 5;
            bogdan.health.medicine_expenses += 5000;
        }
    }
}


void print_results()
{
    printf("\n\n############## FINAL RESULTS ##############\n\n");

    long long int capital_alice = alice.car.value +
        alice.crypto_account.balance * alice.crypto_account.exchange_rate_usd * russia.rate_usd_rub +
        alice.home.value + alice.vtb.account_rub + alice.vtb.account_usd * russia.rate_usd_rub +
        get_total_portfolio_value(alice);

    long long int capital_bogdan = bogdan.car.value +
        bogdan.crypto_account.balance * bogdan.crypto_account.exchange_rate_usd * russia.rate_usd_rub +
        bogdan.home.value + bogdan.vtb.account_rub + bogdan.vtb.account_usd * russia.rate_usd_rub +
        get_total_portfolio_value(bogdan);

    printf("Simulation ended in year %d\n", year);
    printf("Alice died at age %d | Bogdan died at age %d\n\n",
        alice.health.age, bogdan.health.age);

    printf("=== FINANCIAL ===\n");
    printf("Alice final capital: %lld RUB\n", capital_alice);
    printf("Bogdan final capital: %lld RUB\n", capital_bogdan);
    printf("Alice final salary: %lld | Bogdan: %lld\n\n", alice.salary, bogdan.salary);

    printf("=== FAMILY ===\n");
    printf("Alice had %d children\n", alice.family.children_amount);
    printf("Bogdan had %d children\n\n", bogdan.family.children_amount);

    printf("=== LIFE QUALITY ===\n");
    printf("Alice happinesss: %d | Bogdan: %d\n", alice.health.happiness, bogdan.health.happiness);

}


void alice_car(const int month)
{
    try_spend(alice, alice.car.gas);
    if (month == 2) try_spend(alice, alice.car.yearly_tax);
    if (month == 1) {
        alice.car.yearly_tax *= (1.0 + russia.inflation / 100.0);
        alice.car.gas *= (1.0 + russia.inflation / 100.0);
    }
}


void apply_economic_crisis()
{
    russia.inflation += 0.5 * event_severity;
    russia.rate_usd_rub += 2.0 * event_severity;
    russia.crisis = true;
}


void apply_pandemic(Person& person)
{
    person.health.physical_health -= (short)(3 * event_severity);
    person.health.medicine_expenses *= (1.0 + 0.3 * event_severity);
    person.monthly_lifestyle_cost *= 0.7;  // Lockdown
    person.car.gas *= 0.5;

    if (get_random(0, 100) < 5 * event_severity) {
        person.health.physical_health -= 20;
        person.health.stress += 30;
    }
}


void apply_war_conflict(Person& person)
{
    russia.inflation += 1.0 * event_severity;
    russia.rate_usd_rub += 5.0 * event_severity;
    russia.crisis = true;

    person.health.stress += (15 * event_severity);
    person.health.happiness -= (10 * event_severity);
    person.monthly_food_cost *= (1.0 + 0.1 * event_severity);
}


void apply_tech_boom(Person& person)
{
    if (person.education.skill_level > 15) {
        person.salary *= (1.0 + 0.03 * event_severity);
    }
    person.crypto_account.exchange_rate_usd *= (1.0 + 0.05 * event_severity);
    person.health.happiness += (3 * event_severity);
    russia.avg_salary *= (1.0 + 0.01 * event_severity);
}


void apply_oil_crisis(Person& person)
{
    russia.rate_usd_rub -= 2.0 * event_severity;
    person.car.gas *= (1.0 + 0.2 * event_severity);
    russia.avg_salary *= (1.0 + 0.005 * event_severity);
}


void apply_natural_disaster(Person& person)
{
    if (get_random(0, 100) < 5 * event_severity) {
        RUB damage = (RUB)(person.home.value * 0.1 * event_severity);
        person.home.value -= damage;
        person.vtb.account_rub -= damage;
        person.health.stress += 30;
    }
}


void apply_political_instability(Person& person)
{
    russia.rate_usd_rub += 3.0 * event_severity;
    person.health.stress += (10 * event_severity);

    if (get_random(0, 1000) < 5) {
        RUB frozen = person.vtb.account_rub * 0.1;
        person.vtb.account_rub -= frozen;
    }
}


void apply_global_recession(Person& person)
{
    russia.inflation -= 0.2 * event_severity;
    russia.avg_salary *= (1.0 - 0.01 * event_severity);
    person.home.value *= (1.0 - 0.005 * event_severity);
    person.health.stress += (5 * event_severity);
}


void apply_crypto_crash(Person& person)
{
    person.crypto_account.exchange_rate_usd *= (1.0 - 0.1 * event_severity);

    if (person.crypto_account.balance > 0.1) {
        person.health.stress += (20 * event_severity);
        person.health.happiness -= (15 * event_severity);
    }
}


void apply_crypto_boom(Person& person)
{
    person.crypto_account.exchange_rate_usd *= (1.0 + 0.15 * event_severity);

    if (person.crypto_account.balance > 0.1) {
        person.health.happiness += (15 * event_severity);
    }
}


void apply_sanctions(Person& person)
{
    russia.rate_usd_rub += 6.0 * event_severity;
    russia.inflation += 1.5 * event_severity;
    person.monthly_food_cost *= (1.0 + 0.1 * event_severity);
    person.health.stress += (10 * event_severity);

    if (person.vtb.account_usd > 1000 && get_random(0, 100) < 10) {
    }
}


void apply_real_estate_crash(Person& person)
{
    person.home.value *= (1.0 - 0.1 * event_severity);

    if (person.vtb.mortgage.is_active) {
        person.health.stress += (25 * event_severity);
    }
}


void apply_stock_crash(Person& person)
{
    russia.crisis = true;
    russia.avg_salary *= (1.0 - 0.02 * event_severity);
    person.health.stress += (8 * event_severity);
}


void apply_hyperinflation(Person& person)
{
    russia.inflation += 3.0 * event_severity;
    person.monthly_food_cost *= (1.0 + 0.15 * event_severity);
    person.vtb.account_rub *= (1.0 - 0.05 * event_severity);
    person.health.stress += (20 * event_severity);

}


void apply_currency_reform(Person& person)
{
    person.health.stress += (15 * event_severity);
}


void apply_mass_layoffs(Person& person, const char* name)
{
    if (get_random(0, 100) < 10 * event_severity) {
        if (person.salary > 0) {
            person.salary = 0;
            person.health.stress += 50;
            person.health.happiness -= 30;
        }
    }
    person.health.stress += (5 * event_severity);
}


void apply_economic_growth(Person& person)
{
    russia.avg_salary *= (1.0 + 0.02 * event_severity);
    person.salary *= (1.0 + 0.01 * event_severity);
    person.home.value *= (1.0 + 0.02 * event_severity);
    person.health.happiness += (5 * event_severity);
    person.health.stress -= (short)(3 * event_severity);

    if (russia.inflation > 4.0) {
        russia.inflation -= 0.3;
    }
}



void end_event()
{

    current_event_type = 0;
    event_is_active = false;
    russia.crisis = false;

    if (russia.inflation > 10.0) russia.inflation -= 2.0;
    if (russia.rate_usd_rub > 100.0) russia.rate_usd_rub -= 5.0;
}


void apply_event_to_person(Person& person, const char* name)
{
    if (!event_is_active) return;

    switch (current_event_type) {
    case 1:  apply_economic_crisis(); break;
    case 2:  apply_pandemic(person); break;
    case 3:  apply_war_conflict(person); break;
    case 4:  apply_tech_boom(person); break;
    case 5:  apply_oil_crisis(person); break;
    case 6:  apply_natural_disaster(person); break;
    case 7:  apply_political_instability(person); break;
    case 8:  apply_global_recession(person); break;
    case 9:  apply_crypto_crash(person); break;
    case 10: apply_crypto_boom(person); break;
    case 11: apply_sanctions(person); break;
    case 12: apply_real_estate_crash(person); break;
    case 13: apply_stock_crash(person); break;
    case 14: apply_hyperinflation(person); break;
    case 15: apply_currency_reform(person); break;
    case 16: apply_mass_layoffs(person, name); break;
    case 17: apply_economic_growth(person); break;
    }

    if (current_event_type != 4 && current_event_type != 10 && current_event_type != 17) {
        person.health.stress += (2 * event_severity);
    }
}


void start_random_event()
{
    if (event_is_active) return;

    if (get_random(0, 100) < 3) {
        current_event_type = (int)get_random(1, 17);
        event_severity = get_random(0.3, 1.0);
        event_duration = (int)get_random(6, 36);
        event_months_active = 0;
        event_is_active = true;

    }
}


void world_events()
{
    start_random_event();

    if (event_is_active) {
        event_months_active++;

        if (alice.health.is_alive) {
            apply_event_to_person(alice, "Alice");
        }
        if (bogdan.health.is_alive) {
            apply_event_to_person(bogdan, "Bogdan");
        }

        if (event_months_active >= event_duration) {
            end_event();
        }
    }

    apply_seasonal_events();
}


void random_events(Person& person)
{
    if (person.family.has_parents && get_random(0, 100) < 5) {
        RUB help_amount = 50'000;
        try_spend(person, help_amount);
    }

    if (get_random(0, 1000) < 1) {
        RUB inheritance = (RUB)get_random(1'000'000, 5'000'000);
        person.vtb.account_rub += inheritance;
        person.family.has_parents = false;
        person.health.stress += get_random(40, 60);
        person.health.happiness -= (short)get_random(20, 40);
    }
}


void alice_mortgage()
{
    if (alice.vtb.mortgage.is_active) {
        double interest_part = alice.vtb.mortgage.body_debt * (alice.vtb.mortgage.interest_rate / 1200.0);
        double debt_part = alice.vtb.mortgage.monthly_payment - interest_part;
        try_spend(alice, alice.vtb.mortgage.monthly_payment);
        alice.vtb.mortgage.body_debt -= debt_part;

        if (alice.vtb.mortgage.body_debt < 0) {
            alice.vtb.mortgage.body_debt = 0;
            alice.vtb.mortgage.is_active = false;
            alice.health.stress -= (short)get_random(10, 25);
            alice.health.happiness += (short)get_random(10, 20);
        }
    }
}


void alice_try_find_partner(const short age, const int salary)
{
    if (!alice.family.has_partner and alice.health.stress < 50) {
        double p = (salary / russia.avg_salary - 1.0) * 10.0;
        short salary_bonus = (p < 0) ? 0 : (p > 6 ? 6 : p);
        short age_penalty = age - 20;
        alice.family.has_partner = get_random(1, 100) + salary_bonus - age_penalty > 95;
        if (alice.family.has_partner) printf("Alice found a partner at %d!\n", alice.health.age);
        alice.health.happiness += (short)get_random(10, 20);
    }
}


void bogdan_try_find_partner(const short age, const int salary)
{
    if (!bogdan.family.has_partner and bogdan.health.stress < 50) {
        double p = (salary / russia.avg_salary - 1.0) * 10.0;
        short salary_bonus = (p < 0) ? 0 : (p > 6 ? 6 : p);
        short age_penalty = age - 20;
        bogdan.family.has_partner = get_random(1, 100) + salary_bonus - age_penalty > 95;
        if (bogdan.family.has_partner) printf("Bogdan found a partner at %d!\n", bogdan.health.age);
        bogdan.health.happiness += (short)get_random(10, 20);
    }
}


void check_family_expansion(Person& person, int year)
{
    if (person.family.has_partner && person.health.age > 25 && person.health.age < 45) {
        int chance = 99;
        if (person.family.children_amount == 0) chance = 98;

        if (get_random(1, 100) > chance) {
            person.family.children_amount++;
            person.health.stress += get_random(10, 25);
        }
    }
}


void alice_age(const int month)
{
    if (month == 12) {
        if (alice.health.is_alive)  ++alice.health.age;

    }
    if (alice.health.age >= alice.health.max_age) alice.health.is_alive = false;
}


void bogdan_age(const int month)
{
    if (month == 12) {
        if (bogdan.health.is_alive)  ++bogdan.health.age;

    }
    if (bogdan.health.age >= bogdan.health.max_age) bogdan.health.is_alive = false;
}

void alice_medecine_expences(const int month)
{
    if (alice.health.physical_health < 50) {
        try_spend(alice, alice.health.medicine_expenses);
    }
    if (alice.health.physical_health <= 0) {
        alice.health.is_alive = false;
    }
    if (month == 1) {
        alice.health.medicine_expenses *= (1.0 + russia.inflation / 100.0);
    }
}


void alice_stress()
{
    if (alice.health.stress > 90) {
        alice.health.physical_health -= 5;
    }
    if (alice.health.stress > 50) {
        alice.health.stress -= 5;
    }

}


void alice_trip()
{
    if (simulation_month_counter % 24 == 0) {
        try_spend(alice, alice.salary * 0.6);
    }
}


void alice_study()
{
    if (alice.education.is_studying) {
        try_spend(alice, alice.education.tuition_fee);
        --alice.education.months_remaining;
        if (alice.education.months_remaining == 0) {
            if (alice.education.higher_education) {
                ++alice.education.degree_level;
            }
            else {
                alice.education.skill_level += 10;
            }
            alice.education.is_studying = false;
        }
    }
    else {
        if (get_random(1, 6) == 3) {
            alice.education.is_studying = true;
            if (alice.education.degree_level < 4) {
                if (get_random(1, 2) == 2) {
                    alice.education.higher_education = true;
                }
                else {
                    alice.education.higher_education = false;
                    alice.education.tuition_fee = 50'000;
                }
            }
            else
            {
                alice.education.higher_education = false;
            }
        }
    }
}


void bogdan_medecine_expences(const int month)
{
    if (bogdan.health.physical_health < 50) {
        try_spend(bogdan, bogdan.health.medicine_expenses);
    }
    if (bogdan.health.physical_health <= 0) {
        bogdan.health.is_alive = false;
    }
    if (month == 1) {
        bogdan.health.medicine_expenses *= (1.0 + russia.inflation / 100.0);
    }
}


void bogdan_stress()
{
    if (bogdan.health.stress > 90) {
        bogdan.health.physical_health -= 5;
    }
    if (bogdan.health.stress > 50) {
        bogdan.health.stress -= 5;
    }

}


void bogdan_trip()
{
    if (simulation_month_counter % 24 == 0) {
        try_spend(bogdan, bogdan.salary * 0.6);
    }
}


void bogdan_study()
{
    if (bogdan.education.is_studying) {
        try_spend(bogdan, bogdan.education.tuition_fee);
        --bogdan.education.months_remaining;
        if (bogdan.education.months_remaining == 0) {
            if (bogdan.education.higher_education) {
                ++bogdan.education.degree_level;
            }
            else {
                bogdan.education.skill_level += 10;
            }
        }
    }
    else {
        if (get_random(1, 6) == 3) {
            bogdan.education.is_studying = true;
            if (bogdan.education.degree_level < 4) {
                if (get_random(1, 2) == 2) {
                    bogdan.education.higher_education = true;
                }
                else {
                    bogdan.education.higher_education = false;
                }
            }
            else
            {
                bogdan.education.higher_education = false;
            }
        }
    }
}


void alice_happiness()
{
    if (alice.health.stress <= 10) {
        alice.health.happiness += 10;
    }
    else if (alice.health.stress >= 80) {
        alice.health.happiness -= 10;
    }
}


void bogdan_happiness()
{
    if (bogdan.health.stress <= 10) {
        bogdan.health.happiness += 10;
    }
    else if (bogdan.health.stress >= 80) {
        bogdan.health.happiness -= 10;
    }
}


void simulation()
{
    while (alice.health.is_alive || bogdan.health.is_alive) {
        // World
        world_events();
        crypto_rates_update();
        stock_market_update();
        do_russian_inflation();

        // Alice
        if (alice.health.is_alive) {
            alice_salary(month, year);
            update_portfolio_value(alice);
            random_events(alice);
            alice_car(month);
            alice_age(month);
            alice_medecine_expences(month);
            alice_stress();
            alice_trip();
            alice_study();
            alice_mortgage();
            alice_food_expences(month);
            alice_children_expences(month);
            alice_home_expences(month);
            alice_lifestyle_expences(month);
            process_credit_payment(alice);
            check_bankruptcy(alice);
            alice_try_find_partner(alice.health.age, alice.salary);
            check_family_expansion(alice, year);
            alice_happiness();
            invest_in_stocks(alice, "Alice");
        }

        //Bogdan
        if (bogdan.health.is_alive) {
            bogdan_salary(month, year);
            update_portfolio_value(bogdan);
            random_events(bogdan);
            bogdan_food_expences(month);
            bogdan_children_expences(month);
            bogdan_home_expences(month);
            bogdan_lifestyle_expences(month);
            bogdan_age(month);
            bogdan_life_prolongation(month);
            bogdan_medecine_expences(month);
            bogdan_stress();
            bogdan_trip();
            bogdan_study();
            process_credit_payment(bogdan);
            check_bankruptcy(bogdan);
            bogdan_try_find_partner(bogdan.health.age, bogdan.salary);
            check_family_expansion(bogdan, year);
            invest_in_stocks(bogdan, "Bogdan");
            bogdan_happiness();
        }

        ++simulation_month_counter;

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