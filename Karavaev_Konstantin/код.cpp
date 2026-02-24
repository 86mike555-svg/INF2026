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


struct Company {
    RUB income;
    RUB expenses;
    RUB capital;
    int employees;
};


struct Cat {
    RUB food;
    RUB vet;
    RUB grooming;
    char name[20];
};


struct Mortgage {
    RUB loan_amount;  // сумма кредита
    RUB monthly_payment;  
    RUB debt;  // оставток долга
    Percent rate;  // ставка
    int years;
    RUB property_value;
};


struct Car {
    RUB gas;
    RUB value;
    RUB maintenance;  // ТО
    RUB wash;         // мойка
    RUB parking;      // парковка
    RUB tuning;       // тюнинг
    RUB insurance;    // страховка
    RUB tires;        // шины
};


struct Person {
    Bank vtb;
    Car car;
    Cat cat;
    Mortgage mortgage;
    RUB salary;
    RUB food;
};

struct PersonBob {
    Bank vtb;
    Company sport_nutrition;
    Cat cat;
    Car BMW;
    RUB salary;
    RUB food;
    RUB business_income;
};


struct Person alice;
struct PersonBob bob;


void alice_init()
{
    alice.vtb.account = 0;
    alice.vtb.deposite = 1'000'000;
    alice.vtb.interest = 14.5;
    alice.salary = 180'000;

    alice.vtb.account_usd = 1'000;
    alice.vtb.rate_usd_rub = 78.5;

    alice.food = 20'000;

    alice.car.value = 2'400'000;
    alice.car.gas = 15'000;

    alice.cat.food = 2'500;
    alice.cat.vet = 1'200;
    alice.cat.grooming = 2'000;
    const char* alice_cat_name = "Snowball";
    for (int i = 0; i < 20 && alice_cat_name[i] != '\0'; i++) {
        alice.cat.name[i] = alice_cat_name[i];
    }

    alice.mortgage.loan_amount = 7'000'000;
    alice.mortgage.monthly_payment = 65'000;
    alice.mortgage.debt = 6'800'000;
    alice.mortgage.rate = 11.0;
    alice.mortgage.years = 15;
    alice.mortgage.property_value = 8'500'000;

    alice.car.maintenance = 8'000;   // ТО
    alice.car.wash = 1'500;           // мойка
    alice.car.parking = 4'000;        // парковка
    alice.car.tuning = 0;              // Алиса не делает тюнинг
    alice.car.insurance = 25'000;      // страховка в год
    alice.car.tires = 12'000;          // шины
}


void bob_init()
{
    bob.vtb.account = 5'000'000;  // банковские счета
    bob.vtb.deposite = 500'000;
    bob.vtb.interest = 16.0;
    bob.vtb.account_usd = 20'000;
    bob.vtb.rate_usd_rub = 78.5;


    bob.sport_nutrition.income = 1'000'000;  //  Компания спорт. питания
    bob.sport_nutrition.expenses = 200'000;
    bob.sport_nutrition.capital = 3'000'000;
    bob.sport_nutrition.employees = 6;


    bob.cat.food = 3'000;  //  Кот Дарт Вейдер
    bob.cat.vet = 1'000;
    bob.cat.grooming = 10'000;
    const char* cat_name = "Darth Vader";  // имя кота
    for (int i = 0; i < 20 && cat_name[i] != '\0'; i++) {
        bob.cat.name[i] = cat_name[i];
    }


    bob.BMW.value = 8'000'000;  //  Машина
    bob.BMW.gas = 30'000;
    bob.BMW.maintenance = 25'000;      // ТО BMW
    bob.BMW.wash = 3'500;               // мойка
    bob.BMW.parking = 10'000;           // парковка
    bob.BMW.tuning = 150'000;           // тюнинг
    bob.BMW.insurance = 120'000;        // страховка
    bob.BMW.tires = 30'000;             // шины

    bob.salary = 800'000;  //  Личные финансы Боба
    bob.food = 50'000;
    bob.business_income = 800'000;

}


void alice_salary(const int month, const int year)
{
    if (month == 12) {
        alice.vtb.account += alice.salary;  // 13th salary
    }

    if (month == 1 and year == 2027) {
        alice.salary *= 1.5;  // promotion
    }

    alice.vtb.account += alice.salary;
}

void alice_mortgage_payment(int month, int year)
{
    alice.vtb.account -= alice.mortgage.monthly_payment;  // платеж

    RUB principal = alice.mortgage.monthly_payment * 30 / 100;  // часть долга уменьшается
    alice.mortgage.debt -= principal;

    if (alice.mortgage.debt <= 0) {
        alice.mortgage.debt = 0;
    }

    if (month == 12) {
        alice.mortgage.property_value = alice.mortgage.property_value * 105 / 100;
    }
}


void bob_salary(const int month, const int year)
{
    bob.vtb.account += bob.salary;  // обычная зп

    bob.vtb.account += bob.business_income;  // доходы от бизнеса

    if (month == 12) {
        bob.vtb.account += bob.business_income;  // бонус в декабре
    }

    if (month == 1 and year == 2027) {
        bob.salary = bob.salary * 130 / 100;
        bob.business_income = bob.business_income * 120 / 100;
    }

}


void bob_business(int month, int year)
{
    int profit = bob.sport_nutrition.income - bob.sport_nutrition.expenses;

    if (profit > 0) {
        bob.vtb.account += profit;  // если доход есть - зачисляем на счет бобика

        bob.sport_nutrition.capital += profit * 15 / 100;  // увеличение капитала компании
    }

    if (month == 6 and year == 2026) {
        bob.sport_nutrition.income += 500'000;
    }

    if (month == 9 and year == 2026) {
        bob.sport_nutrition.income += 500'000;
        bob.sport_nutrition.employees += 2;
    }

}


void bob_bonus_from_company(int month, int year)
{
    // Если у компании хорошая прибыль - бонус Бобу
    int profit = bob.sport_nutrition.income - bob.sport_nutrition.expenses;
    if (profit > 400'000) {
        RUB bonus = profit * 10 / 100;  // 10% от прибыли
        bob.vtb.account += bonus;
    }
}


void bob_investment_dividends()
{
    RUB dividends = bob.vtb.deposite * 1 / 100;  // 2% от депозита
    bob.vtb.account += dividends;
}


void bob_cat()
{
    bob.vtb.account -= bob.cat.food;
    bob.vtb.account -= bob.cat.grooming;
    bob.vtb.account -= bob.cat.vet;
}




void bob_car_tires()
{
    bob.vtb.account -= bob.BMW.tires;
}


void bob_car_maintenance()
{
    RUB maintenance = bob.BMW.value * 5 / 1000;  // 0.5% от стоимости BMW
    bob.vtb.account -= maintenance;
}


void bob_car_wash()
{
    RUB wash = 3'000;  // премиум мойка
    bob.vtb.account -= wash;
}


void bob_car_parking()
{
    RUB parking = 8'000;  // парковка в центре
    bob.vtb.account -= parking;
}


void bob_car_tuning()
{
    RUB tuning = 150'000;
    bob.vtb.account -= tuning;
    bob.BMW.value += 200'000;  // машина дорожает после тюнинга
}


void bob_car_insurance()
{
    RUB insurance = bob.BMW.value * 7 / 100;  // 7% страховка в год
    bob.vtb.account -= insurance;
}


void bob_random_events(int month, int year)
{
    if (month == 4 and year == 2026) {
        bob.sport_nutrition.capital -= 500'000;  // убыток из-за сломанного оборудования
        bob.vtb.account -= 350'000;  // доплата за доп оборудование
    }

    if (month == 8 and year == 2026) {
        bob.vtb.account -= 15'000;  // прививки для кота
    }

    if (month == 11 and year == 2026) {
        bob.sport_nutrition.income += 500'000;  // рост дохода 
    }

    if (month == 2 and year == 2027) {
        bob.vtb.account -= 50'000;  // коту нужна операция
    }
}


void bob_deposite(const int month, const int year)
{
    if (year == 2026) bob.vtb.interest = 11.0;
    if (year == 2027) bob.vtb.interest = 10.0;
    if (year == 2028) bob.vtb.interest = 9.0;
    if (year == 2029) bob.vtb.interest = 8.0;
    bob.vtb.deposite += bob.vtb.deposite * (bob.vtb.interest / 12.0 / 100.0);

    bob.vtb.deposite += bob.vtb.account;
    bob.vtb.account = 0;
}


void alice_food()
{
    alice.vtb.account -= alice.food;
}


void alice_car()
{
    alice.vtb.account -= alice.car.gas;
}


void alice_car_maintenance()
{
    alice.vtb.account -= alice.car.maintenance;
}

void alice_car_wash()
{
    alice.vtb.account -= alice.car.wash;
}

void alice_car_parking()
{
    alice.vtb.account -= alice.car.parking;
}

void alice_car_insurance()
{
    alice.vtb.account -= alice.car.insurance;
}

void alice_car_tires()
{
    alice.vtb.account -= alice.car.tires;
}


void alice_cat()
{
    alice.vtb.account -= alice.cat.food;
    alice.vtb.account -= alice.cat.vet;
    alice.vtb.account -= alice.cat.grooming;
}


void alice_car_fine()
{
    RUB fine = 2'500;
    alice.vtb.account -= fine;
}


void alice_deposite(const int month, const int year)
{
    if (year == 2026) alice.vtb.interest = 14.5;
    if (year == 2027) alice.vtb.interest = 13.5;
    if (year == 2028) alice.vtb.interest = 12.5;
    if (year == 2029) alice.vtb.interest = 11.5;

    alice.vtb.deposite += alice.vtb.deposite * (alice.vtb.interest / 12.0 / 100.0);

    alice.vtb.deposite += alice.vtb.account;
    alice.vtb.account = 0;
}


void alice_freelance(const int month, const int year)
{
    if (month == 3 and year == 2027) {
        alice.vtb.account_usd += 3'000;
    }
}


void print_results()
{
    printf("Salary = %lld\n", alice.salary);

    RUB capital = 0;
    capital += alice.vtb.account;
    capital += alice.car.value;
    capital += alice.vtb.deposite;
    capital += alice.vtb.account_usd * alice.vtb.rate_usd_rub;
    capital += alice.mortgage.property_value;

    printf("Capital = %lld\n", capital);
    printf("-------------------\n");
}


void print_bob_results()
{
    printf("Bob Salary = %lld\n", bob.salary);

    RUB bob_capital = 0;
    bob_capital += bob.vtb.account;
    bob_capital += bob.BMW.value;
    bob_capital += bob.vtb.deposite;
    bob_capital += bob.vtb.account_usd * bob.vtb.rate_usd_rub;
    bob_capital += bob.sport_nutrition.capital;

    printf("Bob Capital = %lld\n", bob_capital);
}

void simulation()
{
    int month = 2;
    int year = 2026;

    while (not (month == 3 and year == 2028)) {

        alice_salary(month, year);
        alice_freelance(month, year);
        alice_food();
        alice_car();  // бензин
 
        alice_car_maintenance();
        alice_car_wash();
        alice_car_parking();
        if (month == 11) alice_car_tires();      // шины в ноябре
        if (month == 1) alice_car_insurance();    // страховка в январе

        alice_deposite(month, year);

        bob_salary(month, year);
        bob_business(month, year);

        bob_car_maintenance();
        bob_car_wash();
        bob_car_parking();
        if (month == 8) bob_car_tuning();         // тюнинг в августе
        if (month == 1) bob_car_insurance();      // страховка в январе
        if (month == 10) bob_car_tires();         // шины в октябре

        bob_cat();
        bob_random_events(month, year);
        bob_deposite(month, year);

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
    bob_init();

    simulation();

    print_results();
    print_bob_results();

    return 0;
}