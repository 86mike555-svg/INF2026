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

struct StockMarket market = { 3000.0, 4500.0, 8.0 };

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
    RUB medicine_expences;
    short happines;
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


void init()
{
    srand(time(NULL));
    // Global
    russia.rate_usd_rub = 76.75;
    russia.inflation = 5.59;
    russia.avg_salary = 96'772;
    russia.life_last_cost = 100'000.0;
    russia.crisis = false;

    // Alice
    alice.salary = 200'000;
    alice.vtb.account_rub = 150'000;
    alice.vtb.account_usd = 0;
    alice.vtb.consumer_credit.is_active = false;
    alice.vtb.mortgage.is_active = true;
    alice.vtb.mortgage.body_debt = 8'000'000;
    alice.vtb.mortgage.monthly_payment = 90'000;
    alice.vtb.mortgage.interest_rate = 8.0;

    alice.crypto_account.balance = 0.0;
    alice.crypto_account.exchange_rate_usd = BTC_RATES[0];

    alice.car.value = 2'500'000;
    alice.car.gas = 12'000;

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

    alice.health.medicine_expences = 20'000;
    alice.health.happines = 85;
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
    bogdan.vtb.mortgage.is_active = true;

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

    bogdan.health.medicine_expences = 30'000;
    bogdan.health.happines = 70;
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
    // Случайное изменение индексов
    double ru_change = get_random(-5.0, 5.0);
    double us_change = get_random(-3.0, 3.0);

    // Влияние событий
    if (current_event.is_active) {
        switch (current_event.type) {
        case WorldEventType::ECONOMIC_CRISIS:
        case WorldEventType::GLOBAL_RECESSION:
        case WorldEventType::STOCK_MARKET_CRASH:
            ru_change -= 10.0 * current_event.severity;
            us_change -= 8.0 * current_event.severity;
            break;
        case WorldEventType::ECONOMIC_GROWTH:
        case WorldEventType::TECH_BOOM:
            ru_change += 5.0 * current_event.severity;
            us_change += 7.0 * current_event.severity;
            break;
        case WorldEventType::SANCTIONS:
            ru_change -= 15.0 * current_event.severity;
            break;
        default:
            break;
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


bool try_spend(Person& person, RUB amount)
{
    if (amount <= 0) return true;

    if (person.vtb.account_rub >= amount) {
        person.vtb.account_rub -= amount;
        return true;
    }

    RUB deficit = amount - person.vtb.account_rub;
    double usd_needed_dbl = (double)deficit / russia.rate_usd_rub;
    USD usd_needed = (USD)ceil(usd_needed_dbl);

    if (person.vtb.account_usd >= usd_needed) {
        person.vtb.account_usd -= usd_needed;
        person.vtb.account_rub += (RUB)(usd_needed * russia.rate_usd_rub);
        person.vtb.account_rub -= amount;
        return true;
    }
    else {
        if (person.vtb.account_usd > 0) {
            person.vtb.account_rub += (RUB)(person.vtb.account_usd * russia.rate_usd_rub);
            person.vtb.account_usd = 0;
        }
    }
    deficit = amount - person.vtb.account_rub;
    double crypto_rub_value = person.crypto_account.balance * person.crypto_account.exchange_rate_usd * russia.rate_usd_rub;

    if (crypto_rub_value >= deficit) {
        double btc_to_sell = deficit / (person.crypto_account.exchange_rate_usd * russia.rate_usd_rub);
        person.crypto_account.balance -= btc_to_sell;
        person.vtb.account_rub += deficit;
        person.vtb.account_rub -= amount;
        return true;
    }

    // Bankrupt
    person.vtb.account_rub -= amount;
    person.health.is_alive = false; // Died
    printf("%s went bankrupt and died at age %d\n", typeid(person).name(), person.health.age);
    return false;
}


void alice_food_expences(const int month)
{
    try_spend(alice, alice.monthly_food_cost);
    if (month == 12) {
        alice.monthly_food_cost += alice.monthly_food_cost * (russia.inflation / 100.);
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
    if (month == 12) {
        bogdan.home.monthly_utilities *= (1.0 + russia.inflation / 100.0);
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


void do_inflation()
{
    russia.avg_salary *= (russia.inflation / 100.) + 1;
}


void alice_salary(const int month, const int year)
{
    if (month == 1) {
        alice.salary *= 1.05; //indexation
        alice.health.happines += 5;
    }

    if (month == 2 && year == 2026) {
        alice.vtb.account_rub += 5000;  // bonus
        alice.health.happines += 8;
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
    alice.health.happines += 15;
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
                alice.health.happines += 10;
            }
        }
    }
}


void bogdan_investments()
{
    if (bogdan.vtb.account_rub > 100'000) {
        double investment_rub = 50'000.0;
        bogdan.vtb.account_rub -= (RUB)investment_rub;
        double investment_usd = investment_rub / russia.rate_usd_rub;
        bogdan.crypto_account.balance += investment_usd / bogdan.crypto_account.exchange_rate_usd;
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
        alice.health.max_age, bogdan.health.max_age);

    printf("=== FINANCIAL ===\n");
    printf("Alice final capital: %lld RUB\n", capital_alice);
    printf("Bogdan final capital: %lld RUB\n", capital_bogdan);
    printf("Alice final salary: %lld | Bogdan: %lld\n\n", alice.salary, bogdan.salary);

    printf("=== FAMILY ===\n");
    printf("Alice had %d children\n", alice.family.children_amount);
    printf("Bogdan had %d children\n\n", bogdan.family.children_amount);

    printf("=== LIFE QUALITY ===\n");
    printf("Alice happiness: %d | Bogdan: %d\n", alice.health.happines, bogdan.health.happines);
    printf("Alice emigrated: %s | Bogdan: %s\n",
        alice.emigration.has_emigrated ? alice.emigration.country : "No",
        bogdan.emigration.has_emigrated ? bogdan.emigration.country : "No");

    printf("\n=== WINNER ===\n");
    if (capital_alice > capital_bogdan && alice.health.happines > bogdan.health.happines) {
        printf("ALICE wins in both wealth and happiness!\n");
    }
    else if (capital_bogdan > capital_alice && bogdan.health.happines > alice.health.happines) {
        printf("BOGDAN wins in both wealth and happiness!\n");
    }
    else if (capital_alice > capital_bogdan) {
        printf("ALICE is wealthier, but BOGDAN is happier!\n");
    }
    else {
        printf("BOGDAN is wealthier, but ALICE is happier!\n");
    }

    printf("\n###########################################\n");
}


void alice_car(const int month)
{
    alice.vtb.account_rub -= alice.car.gas;
    if (month == 2) alice.vtb.account_rub -= alice.car.yearly_tax;
}


void world_events()
{
    russia.crisis = (get_random(1, 200) == 100);
    if (russia.crisis) {
        russia.inflation += 5.0;
        russia.rate_usd_rub += 20.0;
        printf("CRISIS HIT in %d!\n", year);
        alice.health.stress += (short)get_random(20, 40);
        bogdan.health.stress += (short)get_random(20, 40);
        alice.health.happines -= (short)get_random(10, 20);
        bogdan.health.happines -= (short)get_random(10, 20);
    }
    else {
        // Normalization
        if (russia.inflation > 5.59) {
            russia.inflation -= 0.1;
        }
    }
}


void random_events(Person& person)
{
    if (person.family.has_parents && get_random(0, 100) < 5) {
        RUB help_amount = 50'000;
        person.vtb.account_rub -= help_amount;
    }

    if (get_random(0, 1000) < 1) {
        RUB inheritance = (RUB)get_random(1'000'000, 5'000'000);
        person.vtb.account_rub += inheritance;
        person.family.has_parents = false;
        person.health.stress += (short)get_random(40, 60);
        person.health.happines -= (short)get_random(20, 40);
    }
}


void alice_mortgage()
{
    if (alice.vtb.mortgage.is_active) {
        double interest_part = alice.vtb.mortgage.body_debt * (alice.vtb.mortgage.interest_rate / 1200.0); // comment
        double debt_part = alice.vtb.mortgage.monthly_payment - interest_part;
        alice.vtb.account_rub -= alice.vtb.mortgage.monthly_payment;
        alice.vtb.mortgage.body_debt -= debt_part;

        if (alice.vtb.mortgage.body_debt < 0) {
            alice.vtb.mortgage.body_debt = 0;
            alice.vtb.mortgage.is_active = false;
            alice.health.stress -= (short)get_random(10, 25);
            alice.health.happines += (short)get_random(10, 20);
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
        alice.health.happines += (short)get_random(10, 20);
    }
}


void bogdan_try_find_partner(const short age, const int salary)
{ //split
    if (!bogdan.family.has_partner and bogdan.health.stress < 50) {
        double p = (salary / russia.avg_salary - 1.0) * 10.0;
        short salary_bonus = (p < 0) ? 0 : (p > 6 ? 6 : p);
        short age_penalty = age - 20;
        bogdan.family.has_partner = get_random(1, 100) + salary_bonus - age_penalty > 95;
        if (bogdan.family.has_partner) printf("Bogdan found a partner at %d!\n", bogdan.health.age);
        alice.health.happines += (short)get_random(10, 20);
    }
}


void check_family_expansion(Person& person, int year)
{
    if (person.family.has_partner && person.health.age > 25 && person.health.age < 45) {
        int chance = 99;
        if (person.family.children_amount == 0) chance = 98;

        if (get_random(1, 100) > chance) {
            person.family.children_amount++;
            person.health.stress += (short)get_random(10, 25);
            printf("New child born for someone at age %d!\n", person.health.age);
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
        try_spend(alice, alice.health.medicine_expences);
    }
    if (alice.health.physical_health <= 0) {
        alice.health.is_alive = false;
    }
    if (month == 1) {
        alice.health.medicine_expences *= (1.0 + russia.inflation / 100.0);
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
        }
    }
    else {
        if (get_random(1, 6) == 3) {
            alice.education.is_studying = true;
            if (alice.education.higher_education < 4) {
                if (get_random(1, 2) == 2) {
                    alice.education.higher_education = true;
                }
                else {
                    alice.education.higher_education = false;
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
        try_spend(bogdan, bogdan.health.medicine_expences);
    }
    if (bogdan.health.physical_health <= 0) {
        bogdan.health.is_alive = false;
    }
    if (month == 1) {
        bogdan.health.medicine_expences *= (1.0 + russia.inflation / 100.0);
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
            if (bogdan.education.higher_education < 4) {
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


void alice_happines()
{
    if (alice.health.stress <= 10) {
        alice.health.happines += 10;
    }
    else if (alice.health.stress >= 80) {
        alice.health.happines -= 10;
    }
}


void bogdan_happines()
{
    if (bogdan.health.stress <= 10) {
        bogdan.health.happines += 10;
    }
    else if (bogdan.health.stress >= 80) {
        bogdan.health.happines -= 10;
    }
}


void simulation()
{
    while (alice.health.is_alive || bogdan.health.is_alive) {
        // World
        world_events();
        crypto_rates_update();
        update_srock_market();
        do_inflation(); // russia mb + world events

        // Alice
        if (alice.health.is_alive) {
            alice_salary(month, year);
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
            alice_try_find_partner(alice.health.age, alice.salary);
            check_family_expansion(alice, year);
            alice_happines();
        }

        //Bogdan
        if (bogdan.health.is_alive) {
            bogdan_salary(month, year);
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
            bogdan_try_find_partner(bogdan.health.age, bogdan.salary);
            check_family_expansion(bogdan, year);
            bogdan_investments();
            bogdan_happines();
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