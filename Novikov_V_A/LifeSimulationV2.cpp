#include <stdio.h>
#include <stdlib.h>
#include <time.h>


using RUB = long long int;
using USD = long long int;

using KM = long int;
using Years = int;

using Percent = float;


struct Bank {
    RUB account;
    RUB deposite;
    USD account_usd;
    float rate_usd_rub;

    Percent deposite_interest;
    Percent credit_interest;

    RUB credit;
    RUB credit_limit;
    RUB payment;

    RUB total_spent;
    RUB total_earned;
};


struct Car {
    RUB value;
    RUB credit;
    RUB credit_payment;
    Percent credit_interest;

    RUB gas_month;
    RUB gas_price;

    RUB winter_tires;
    RUB summer_tires;
    RUB tire_change;

    RUB season_service;
    RUB insurance;

    RUB random_repair_min;
    RUB random_repair_max;
    RUB accumulated_repair;

    Years age;
    KM mileage_year;
    int months_since_service;  //время с посл. ТО
};


struct Person {
    Bank tbank;
    Car bmw_x3;
    Car bmw_x5;
    RUB salary;
    RUB food;
};
struct Person rick;
//struct Person cliff;


void rick_init()
{
    rick.tbank.account = 0;
    rick.salary = 300'000;
    rick.tbank.account_usd = 0;

    rick.tbank.rate_usd_rub = 80.0;
    rick.tbank.deposite = 100'000;
    rick.tbank.deposite_interest = 8.0;
    rick.tbank.credit = 1'000'000;
    rick.tbank.credit_limit = 5'000'000;
    rick.tbank.credit_interest = 21.0;

    rick.tbank.total_spent = 0;
    rick.tbank.total_earned = 0;

    rick.food = 30'000;


    rick.bmw_x3.value = 4'500'000;
    rick.bmw_x3.credit = 0;
    rick.bmw_x3.credit_payment = 0;
    rick.bmw_x3.credit_interest = 0;

    rick.bmw_x3.gas_month = 18'000;
    rick.bmw_x3.gas_price = 55.0;

    rick.bmw_x3.winter_tires = 100'000;
    rick.bmw_x3.summer_tires = 90'000;
    rick.bmw_x3.tire_change = 5'000;

    rick.bmw_x3.season_service = 25'000;
    rick.bmw_x3.insurance = 90'000;

    rick.bmw_x3.random_repair_min = 5'000;
    rick.bmw_x3.random_repair_max = 60'000;
    rick.bmw_x3.accumulated_repair = 0;

    rick.bmw_x3.age = 4;
    rick.bmw_x3.mileage_year = 15'000;
    rick.bmw_x3.months_since_service = 0;


    rick.bmw_x5.value = 8'500'000;
    rick.bmw_x5.credit = 5'000'000;
    rick.bmw_x5.credit_payment = 95'000;
    rick.bmw_x5.credit_interest = 18.5;

    rick.bmw_x5.gas_month = 30'000;
    rick.bmw_x5.gas_price = 55.0;

    rick.bmw_x5.winter_tires = 200'000;
    rick.bmw_x5.summer_tires = 180'000;
    rick.bmw_x5.tire_change = 8'000;

    rick.bmw_x5.season_service = 50'000;
    rick.bmw_x5.insurance = 200'000;

    rick.bmw_x5.random_repair_min = 20'000;
    rick.bmw_x5.random_repair_max = 250'000;
    rick.bmw_x5.accumulated_repair = 0;

    rick.bmw_x5.age = 1;
    rick.bmw_x5.mileage_year = 25'000;
    rick.bmw_x5.months_since_service = 0;
}

void rick_salary(const int month, const int year)
{
    if (month == 12) {
        rick.tbank.account += rick.salary; // 13th salary
    }

    if (month == 1 and year == 2027) {
        rick.salary *= 1.5; //promotion
    }

    rick.tbank.account += rick.salary;
    rick.tbank.total_earned += rick.salary;
}

void rick_freelance(const int month, const int year)
{
    if (month == 3 and year == 2027) {
        rick.tbank.account_usd += 3'000;
    }
}

void rick_food()
{
    if (rick.tbank.account >= rick.food) {
        rick.tbank.account -= rick.food;
        rick.tbank.total_spent += rick.food;
    }
    else {
        rick.tbank.credit += rick.food - rick.tbank.account;
        rick.tbank.total_spent += rick.food;
        rick.tbank.account = 0;
    }
}

void rick_car_x3(const int month, const int year)
{
    if (rick.bmw_x3.credit > 0) {
        rick.bmw_x3.credit += rick.bmw_x3.credit * (rick.bmw_x3.credit_interest / 12.0 / 100.0);
        if (rick.tbank.account >= rick.bmw_x3.credit_payment) {
            rick.tbank.account -= rick.bmw_x3.credit_payment;
            rick.bmw_x3.credit -= rick.bmw_x3.credit_payment;
            rick.tbank.total_spent += rick.bmw_x3.credit_payment;
        }
        else {
            rick.tbank.account -= 10000;  //late payment
            rick.tbank.total_spent += 10000;
        }
    }

        RUB gas_cost = rick.bmw_x3.gas_month;
        if (rick.tbank.account >= gas_cost) {
            rick.tbank.account -= gas_cost;
            rick.tbank.total_spent += gas_cost;
        }
        else {
            rick.tbank.credit += gas_cost - rick.tbank.account;
            rick.tbank.total_spent += gas_cost;
            rick.tbank.account = 0;
        }

        if (month == 2) {
            if (rick.tbank.account >= rick.bmw_x3.insurance) {
                rick.tbank.account -= rick.bmw_x3.insurance;
                rick.tbank.total_spent += rick.bmw_x3.insurance;
            }
            else {
                rick.tbank.credit += rick.bmw_x3.insurance - rick.tbank.account;
                rick.tbank.total_spent += rick.bmw_x3.insurance;
                rick.tbank.account = 0;
            }
        }

        if (month == 10 or month == 4) {
            if (rick.tbank.account >= rick.bmw_x3.tire_change) {
                rick.tbank.account -= rick.bmw_x3.tire_change;
                rick.tbank.total_spent += rick.bmw_x3.tire_change;
            }
            else {
                rick.tbank.credit += rick.bmw_x3.tire_change - rick.tbank.account;
                rick.tbank.total_spent += rick.bmw_x3.tire_change;
                rick.tbank.account = 0;
            }
        }

        if (year % 3 == 0) {
            if (month == 10) {
                if (rick.tbank.account >= rick.bmw_x3.winter_tires) {
                    rick.tbank.account -= rick.bmw_x3.winter_tires;
                    rick.tbank.total_spent += rick.bmw_x3.winter_tires;
                }
                else {
                    rick.tbank.credit += rick.bmw_x3.winter_tires - rick.tbank.account;
                    rick.tbank.total_spent += rick.bmw_x3.winter_tires;
                    rick.tbank.account = 0;
                }
            }
            if (month == 4) {
                if (rick.tbank.account >= rick.bmw_x3.summer_tires) {
                    rick.tbank.account -= rick.bmw_x3.summer_tires;
                    rick.tbank.total_spent += rick.bmw_x3.summer_tires;
                }
                else {
                    rick.tbank.credit += rick.bmw_x3.summer_tires - rick.tbank.account;
                    rick.tbank.total_spent += rick.bmw_x3.summer_tires;
                    rick.tbank.account = 0;
                }
            }
        }

        rick.bmw_x3.months_since_service++;
        if (rick.bmw_x3.months_since_service >= 2) {
            RUB service_cost = rick.bmw_x3.season_service;
            if (rick.bmw_x3.age > 5) {  //после 5 лет
                service_cost = service_cost * 1.3;
            }
            if (rick.bmw_x3.age > 10) {  //после 10 лет
                service_cost = service_cost * 1.5;
            }
            if (rick.tbank.account >= service_cost) {
                rick.tbank.account -= service_cost;
                rick.tbank.total_spent += service_cost;
            }
            else {
                rick.tbank.credit += service_cost - rick.tbank.account;
                rick.tbank.total_spent += service_cost;
                rick.tbank.account = 0;
            }
            rick.bmw_x3.months_since_service = 0;
        }

        int random_chance = rand() % 100;
        int repair_chance = rick.bmw_x3.age * 3;  // 3% за каждый год

        if (random_chance < repair_chance) {
            RUB repair_cost = rick.bmw_x3.random_repair_min + (rand() % (rick.bmw_x3.random_repair_max - rick.bmw_x3.random_repair_min));
            if (rick.tbank.account >= repair_cost) {
                rick.tbank.account -= repair_cost;
                rick.tbank.total_spent += repair_cost;
                rick.bmw_x3.accumulated_repair += repair_cost;
            }
            else {
                rick.tbank.credit += repair_cost - rick.tbank.account;  //если денег на ремонт нет, то кредит
                rick.bmw_x3.accumulated_repair += repair_cost;
                rick.tbank.total_spent += repair_cost;
                rick.tbank.account = 0;
            }
        }

        if (month == 12) {
            rick.bmw_x3.age++;
            rick.bmw_x3.value = rick.bmw_x3.value * 0.90;  // reduction in cost because old
            rick.bmw_x3.mileage_year += 2000;
        }
}

void rick_car_x5(const int month, const int year)
{
    if (rick.bmw_x5.credit > 0) {
        rick.bmw_x5.credit += rick.bmw_x5.credit * (rick.bmw_x5.credit_interest / 12.0 / 100.0);
        if (rick.tbank.account >= rick.bmw_x5.credit_payment) {
            rick.tbank.account -= rick.bmw_x5.credit_payment;
            if (rick.bmw_x5.credit >= rick.bmw_x5.credit_payment) {
                rick.bmw_x5.credit -= rick.bmw_x5.credit_payment;
            }
            else {
                RUB overpayment = rick.bmw_x5.credit_payment - rick.bmw_x5.credit;  //возврат при долг < платеж
                rick.bmw_x5.credit = 0;
                rick.tbank.account += overpayment;
            }
            rick.tbank.total_spent += rick.bmw_x5.credit_payment;
        }
        else {
            rick.tbank.account -= 10000;  //late payment
            rick.tbank.total_spent += 10000;
        }
    }
        RUB gas_cost = rick.bmw_x5.gas_month;
        if (rick.tbank.account >= gas_cost) {
            rick.tbank.account -= gas_cost;
            rick.tbank.total_spent += gas_cost;
        }
        else {
            rick.tbank.credit += gas_cost - rick.tbank.account;
            rick.tbank.total_spent += gas_cost;
            rick.tbank.account = 0;
        }

        if (month == 2) {
            if (rick.tbank.account >= rick.bmw_x5.insurance) {
                rick.tbank.account -= rick.bmw_x5.insurance;
                rick.tbank.total_spent += rick.bmw_x5.insurance;
            }
            else {
                rick.tbank.credit += rick.bmw_x5.insurance - rick.tbank.account;
                rick.tbank.total_spent += rick.bmw_x5.insurance;
                rick.tbank.account = 0;
            }
        }

        if (month == 10 or month == 4) {
            if (rick.tbank.account >= rick.bmw_x5.tire_change) {
                rick.tbank.account -= rick.bmw_x5.tire_change;
                rick.tbank.total_spent += rick.bmw_x5.tire_change;
            }
            else {
                rick.tbank.credit += rick.bmw_x5.tire_change - rick.tbank.account;
                rick.tbank.total_spent += rick.bmw_x5.tire_change;
                rick.tbank.account = 0;
            }
        }

        if (year % 3 == 0) {
            if (month == 10) {
                if (rick.tbank.account >= rick.bmw_x5.winter_tires) {
                    rick.tbank.account -= rick.bmw_x5.winter_tires;
                    rick.tbank.total_spent += rick.bmw_x5.winter_tires;
                }
                else {
                    rick.tbank.credit += rick.bmw_x5.winter_tires - rick.tbank.account;
                    rick.tbank.total_spent += rick.bmw_x5.winter_tires;
                    rick.tbank.account = 0;
                }
            }
            if (month == 4) {
                if (rick.tbank.account >= rick.bmw_x5.summer_tires) {
                    rick.tbank.account -= rick.bmw_x5.summer_tires;
                    rick.tbank.total_spent += rick.bmw_x5.summer_tires;
                }
                else {
                    rick.tbank.credit += rick.bmw_x5.summer_tires - rick.tbank.account;
                    rick.tbank.total_spent += rick.bmw_x5.summer_tires;
                    rick.tbank.account = 0;
                }
            }
        }

        rick.bmw_x5.months_since_service++;
        if (rick.bmw_x5.months_since_service >= 2) {
            RUB service_cost = rick.bmw_x5.season_service;
            if (rick.bmw_x5.age > 5) {  //после 5 лет
                service_cost = service_cost * 1.2;
            }
            if (rick.bmw_x5.age > 10) {  //после 10 лет
                service_cost = service_cost * 1.4;
            }
            if (rick.tbank.account >= service_cost) {
                rick.tbank.account -= service_cost;
                rick.tbank.total_spent += service_cost;
            }
            else {
                rick.tbank.credit += service_cost - rick.tbank.account;
                rick.tbank.total_spent += service_cost;
                rick.tbank.account = 0;
            }
            rick.bmw_x5.months_since_service = 0;
        }

        int random_chance = rand() % 100;
        int repair_chance = rick.bmw_x5.age * 2;  // 2% за каждый год

        if (random_chance < repair_chance) {
            RUB repair_cost = rick.bmw_x5.random_repair_min +
                (rand() % (rick.bmw_x5.random_repair_max - rick.bmw_x5.random_repair_min));
            if (rick.tbank.account >= repair_cost) {
                rick.tbank.account -= repair_cost;
                rick.tbank.total_spent += repair_cost;
                rick.bmw_x5.accumulated_repair += repair_cost;
            }
            else {
                rick.tbank.credit += repair_cost - rick.tbank.account;  //если денег на ремонт нет, то кредит
                rick.bmw_x5.accumulated_repair += repair_cost;
                rick.tbank.total_spent += repair_cost;
                rick.tbank.account = 0;
            }
        }

        if (month == 12) {
            rick.bmw_x5.age++;
            rick.bmw_x5.value = rick.bmw_x5.value * 0.95;  // потеря в цене каждый год
        }
}

void rick_credit(const int month, const int year)
{
    if (rick.tbank.credit > 0) {
        if (year == 2026) rick.tbank.credit_interest = 21.0;
        if (year == 2027) rick.tbank.credit_interest = 20.5;
        if (year == 2028) rick.tbank.credit_interest = 19.5;
        if (year == 2029) rick.tbank.credit_interest = 18.5;
        if (year == 2030) rick.tbank.credit_interest = 18.0;
        if (year == 2031) rick.tbank.credit_interest = 17.5;
        if (year == 2032) rick.tbank.credit_interest = 17.0;
        if (year == 2033) rick.tbank.credit_interest = 16.5;
        if (year == 2034) rick.tbank.credit_interest = 16.0;
        if (year == 2035) rick.tbank.credit_interest = 15.5;
        if (year == 2036) rick.tbank.credit_interest = 15.0;
        if (year == 2037) rick.tbank.credit_interest = 14.5;
        if (year == 2038) rick.tbank.credit_interest = 14.0;
        if (year == 2039) rick.tbank.credit_interest = 13.5;
        if (year == 2040) rick.tbank.credit_interest = 13.0;
        if (year == 2041) rick.tbank.credit_interest = 12.5;
        if (year == 2042) rick.tbank.credit_interest = 12.0;
        if (year == 2043) rick.tbank.credit_interest = 11.5;
        if (year == 2044) rick.tbank.credit_interest = 11.0;
        if (year == 2045) rick.tbank.credit_interest = 10.5;
        if (year == 2046) rick.tbank.credit_interest = 10.0;
        if (year == 2047) rick.tbank.credit_interest = 9.5;
        if (year == 2048) rick.tbank.credit_interest = 9.0;
        if (year == 2049) rick.tbank.credit_interest = 8.5;
        if (year == 2050) rick.tbank.credit_interest = 8.0;

        rick.tbank.credit += rick.tbank.credit * (rick.tbank.credit_interest / 12.0 / 100.0);

        rick.tbank.payment = rick.tbank.credit * 0.05;
        if (rick.tbank.account >= rick.tbank.payment) {
            rick.tbank.account -= rick.tbank.payment;
            rick.tbank.credit -= rick.tbank.payment;
            rick.tbank.total_spent += rick.tbank.payment;
        }
        else {
            rick.tbank.account -= 1000;  //late payment
            rick.tbank.total_spent += 1000;
        }

        if (rick.tbank.credit > 0 && rick.tbank.credit < 5000) {  //проверка малости кредита
            if (rick.tbank.account >= rick.tbank.credit) {  //если хватает сразу
                rick.tbank.account -= rick.tbank.credit;
                rick.tbank.total_spent += rick.tbank.credit;
                rick.tbank.credit = 0;
            }
            else {
                rick.tbank.credit -= rick.tbank.account;  //хватает частично
                rick.tbank.total_spent += rick.tbank.account;
                rick.tbank.account = 0;
            }
        }
        if (rick.tbank.credit < 0) {
            rick.tbank.credit = 0;
        }
    }
}


void rick_deposite(const int month, const int year)
{
    if (year == 2026) rick.tbank.deposite_interest = 8.0;
    if (year == 2027) rick.tbank.deposite_interest = 7.8;
    if (year == 2028) rick.tbank.deposite_interest = 7.5;
    if (year == 2029) rick.tbank.deposite_interest = 7.2;
    if (year == 2030) rick.tbank.deposite_interest = 7.0;
    if (year == 2031) rick.tbank.deposite_interest = 6.8;
    if (year == 2032) rick.tbank.deposite_interest = 6.5;
    if (year == 2033) rick.tbank.deposite_interest = 6.2;
    if (year == 2034) rick.tbank.deposite_interest = 6.0;
    if (year == 2035) rick.tbank.deposite_interest = 5.8;
    if (year == 2036) rick.tbank.deposite_interest = 5.5;
    if (year == 2037) rick.tbank.deposite_interest = 5.2;
    if (year == 2038) rick.tbank.deposite_interest = 5.0;
    if (year == 2039) rick.tbank.deposite_interest = 4.8;
    if (year == 2040) rick.tbank.deposite_interest = 4.5;
    if (year == 2041) rick.tbank.deposite_interest = 4.2;
    if (year == 2042) rick.tbank.deposite_interest = 4.0;
    if (year == 2043) rick.tbank.deposite_interest = 3.8;
    if (year == 2044) rick.tbank.deposite_interest = 3.5;
    if (year == 2045) rick.tbank.deposite_interest = 3.2;
    if (year == 2046) rick.tbank.deposite_interest = 3.0;
    if (year == 2047) rick.tbank.deposite_interest = 2.8;
    if (year == 2048) rick.tbank.deposite_interest = 2.5;
    if (year == 2049) rick.tbank.deposite_interest = 2.2;
    if (year == 2050) rick.tbank.deposite_interest = 2.0;

    rick.tbank.deposite += rick.tbank.deposite * (rick.tbank.deposite_interest / 12.0 / 100.0);

    if (rick.tbank.account > 0) {
        rick.tbank.deposite += rick.tbank.account;
        rick.tbank.account = 0;
    }

    else if (rick.tbank.account < 0) {
        rick.tbank.credit += -rick.tbank.account;
        rick.tbank.account = 0;
    }
}

void print_results()
{
    printf("\n========== RICK'S LIFE FINANCIAL STATEMENT ==========\n");
    printf("Salary: %lld RUB.\n", rick.salary);

    RUB bank_capital = 0;
    bank_capital += rick.tbank.account;
    bank_capital += rick.tbank.deposite;
    bank_capital += rick.tbank.account_usd * rick.tbank.rate_usd_rub;
    RUB car_capital = 0;
    car_capital += rick.bmw_x3.value;
    car_capital += rick.bmw_x5.value;

    printf("\n--- Assets ---\n");
    printf("Bank: %lld RUB.\n", bank_capital);
    printf("BMW X3: %lld RUB.\n", rick.bmw_x3.value);
    printf("BMW X5: %lld RUB.\n", rick.bmw_x5.value);
    RUB total_capital = bank_capital + car_capital;

    printf("\n--- Debts ---\n");
    printf("Consumer credit: %lld RUB.\n", rick.tbank.credit);
    printf("Car credit: %lld RUB.\n", rick.bmw_x5.credit);
    RUB total_debt = rick.tbank.credit + rick.bmw_x5.credit;

    printf("\n--- Car statistics ---\n");
    printf("BMW X3 - total number of repairs: %lld RUB.\n", rick.bmw_x3.accumulated_repair);
    printf("BMW X5 - total number of repairs: %lld RUB.\n", rick.bmw_x5.accumulated_repair);
    printf("Total Repair Costs: %lld RUB.\n", rick.bmw_x3.accumulated_repair + rick.bmw_x5.accumulated_repair);

    RUB clean_capital = total_capital - total_debt;
    printf("\n--- RESULT ---\n");
    printf("Total capital: %lld RUB.\n", total_capital);
    printf("Total debt: %lld RUB.\n", total_debt);
    printf("Clean capital: %lld RUB.\n", clean_capital);
}


void simulation()
{
    int month = 2;
    int year = 2026;

    while (not (month == 3 and year == 2050)) {
        rick_salary(month, year);
        rick_freelance(month, year);
        rick_car_x3(month, year);
        rick_car_x5(month, year);
        rick_credit(month, year);
        rick_food();
        rick_deposite(month, year);
        // my_cat();
        // my_medine();
        // my_home();

        ++month;
        if (month == 13) {
            ++year;
            month = 1;
        }
    }
}


int main()
{
    srand(time(NULL));

    rick_init();

    simulation();

    print_results();

    return 0;
}