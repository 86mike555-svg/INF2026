#include <stdio.h>


using RUB = float;
using EUR = float;
using Percent = float;
bool newflat_own = false;

struct Bank {
    RUB account;
    RUB deposite;
    Percent interest;

    EUR account_eur;
    float rate_eur_rub;
};


struct Car {
    RUB gas;
    RUB value;
};


struct Сar_service {
    RUB service;
};


struct Girlfriend {
    RUB date;
    RUB flowers;
};


struct Flat {
    RUB rent;
    RUB HCS; // housing and communal services
};


struct Friends {
    RUB beer;
};


struct Gym {
    RUB subscription;
    RUB protein;
};


struct Cat {
    RUB eatforcat;
    RUB toiletforcat;
};


struct Cosmetic {
    RUB pomade;
    RUB mascara;
    RUB foundation;
    RUB summ;
};


struct Gifts
{
    RUB gifts;
};


struct Person {

    Bank tb;
    Car car;
    Gym gym;
    Flat flat;
    Girlfriend girlfriend;
    Friends friends;
    Сar_service cs;
    Cat cat;
    Cosmetic cosmetic;
    Gifts gifts;


    RUB boyfriend;
    RUB holiday;
    RUB salary;
    RUB food;

};


struct Person davis;
struct Person lisa;


void pair_init()
{
    davis.tb.account = 0;
    davis.tb.deposite = 10'000;
    davis.tb.interest = 14.5;
    davis.salary = 150'000;

    davis.tb.account_eur = 5000;
    davis.tb.rate_eur_rub = 90.45;

    davis.food = 25'000;

    davis.car.value = 1'800'000;
    davis.car.gas = 15'000;
    lisa.car.value = 0;

    davis.cs.service = 10'000;

    davis.girlfriend.date = 10'000;
    davis.girlfriend.flowers = 2'000;

    davis.gym.subscription = 1'600;
    davis.gym.protein = 1'000;

    davis.flat.rent = 60'000;
    davis.flat.HCS = 5'000;
    lisa.flat.rent = 10'000;

    davis.cat.eatforcat = 1'000;
    davis.cat.toiletforcat = 500;

    davis.friends.beer = 2'000;

    lisa.tb.account = 0;
    lisa.tb.deposite = 5'000;
    lisa.tb.interest = 14.5;
    lisa.salary = 30'000;

    lisa.boyfriend = 15'000;

    lisa.tb.account_eur = 5000;
    lisa.tb.rate_eur_rub = 90.45;

    lisa.food = 15'000;

    lisa.cosmetic.pomade = 3'000;
    lisa.cosmetic.mascara = 2'500;
    lisa.cosmetic.foundation = 4'000;
    lisa.cosmetic.summ = 0;

    davis.gifts.gifts = 15'000;
    lisa.gifts.gifts = 10'000;

    davis.holiday = lisa.holiday = 10'000;
}


void lisa_salary(const int month, const int year)
{
    if (month == 12) {
        lisa.tb.account += lisa.salary;
    }

    if (month == 1 and year == 2029) {
        lisa.salary *= 1.2;
    }

    if (month == 1 and year == 2032) {
        lisa.salary *= 1.25;
    }

    lisa.tb.account += lisa.salary;

    lisa.tb.account += lisa.boyfriend;
}


static void lisa_deposite(const int month, const int year)
{
    if (year == 2026) {
        lisa.tb.interest = 14.5;
    }

    if (year == 2027) {
        lisa.tb.interest = 13.5;
    }

    if (year == 2028) {
        lisa.tb.interest = 12.5;
    }

    if (year == 2029) {
        lisa.tb.interest = 11.5;
    }

    lisa.tb.deposite += lisa.tb.deposite * (lisa.tb.interest / 12.0 / 100.0);

    lisa.tb.deposite += lisa.tb.account;
    lisa.tb.account = 0;
}


void lisa_cosmetic(const int month, const int year)
{


    if (month == 4 or month == 9) {
        lisa.tb.account -= lisa.cosmetic.pomade;
    }


    if (month == 2 or month == 7) {
        lisa.tb.account -= lisa.cosmetic.mascara;
    }


    if (month == 3 or month == 8) {
        lisa.tb.account -= lisa.cosmetic.foundation;
    }

}


void davis_salary(const int month, const int year)
{

    if (month == 12) {
        davis.tb.account += davis.salary;
    }


    if (month == 1 and year == 2028) {
        davis.salary *= 1.5;
    }


    if (month == 6 and year == 2030) {
        davis.salary *= 1.3;
    }


    if (month == 1 and year == 2033) {
        davis.salary *= 1.5;
    }


    davis.tb.account += davis.salary;
}


void davis_inflation(const int month, const int year)
{
    float inflation = 9.4f / 100.0f; // 9.4% per year
    davis.food += davis.food * inflation / 12;

    davis.car.gas += davis.car.gas * inflation / 12;
    davis.cs.service += davis.cs.service * inflation / 12;

    davis.girlfriend.date += davis.girlfriend.date * inflation / 12;
    davis.girlfriend.flowers += davis.girlfriend.flowers * inflation / 12;

    davis.gym.subscription += davis.gym.subscription * inflation / 12;
    davis.gym.protein += davis.gym.protein * inflation / 12;

    davis.flat.HCS += davis.flat.HCS * inflation / 12;

    davis.friends.beer += davis.friends.beer * inflation / 12;

    davis.cat.eatforcat += davis.cat.eatforcat * inflation / 12;
    davis.cat.toiletforcat += davis.cat.toiletforcat * inflation / 12;


    lisa.food += lisa.food * inflation / 12;
    lisa.cosmetic.pomade += lisa.cosmetic.pomade * inflation / 12;
    lisa.cosmetic.mascara += lisa.cosmetic.mascara * inflation / 12;
    lisa.cosmetic.foundation += lisa.cosmetic.foundation * inflation / 12;
    

    if (newflat_own == false) {
        lisa.flat.rent += lisa.flat.rent * inflation / 12;
        davis.flat.rent += davis.flat.rent * inflation / 12;
    }


	if (month == 1) {
        inflation += 0.5 / 100; // дополнительная инфляция в январе
    }

}


void davis_cat()
{
    davis.tb.account -= davis.cat.eatforcat;
    davis.tb.account -= davis.cat.toiletforcat;
}


void davis_food()
{
    davis.tb.account -= davis.food;
    lisa.tb.account -= lisa.food;
}


void davis_car()
{
    davis.tb.account -= davis.car.gas;
}


void davis_girlfriend()
{
    davis.tb.account -= davis.girlfriend.date;
    davis.tb.account -= davis.girlfriend.flowers;

    davis.tb.account -= lisa.boyfriend;
}


void davis_gym()
{
    davis.tb.account -= davis.gym.protein;
    davis.tb.account -= davis.gym.subscription;

    lisa.tb.account -= davis.gym.subscription;
}

void davis_flat(const int month, const int year)
{
    

    if (newflat_own == false) {
        davis.tb.account -= davis.flat.rent;
        davis.tb.account -= davis.flat.HCS;
        davis.tb.account += lisa.flat.rent;
        lisa.tb.account -= lisa.flat.rent;
    }

}


void davis_cs(const int month, const int year)
{

    if (month == 6) {
        davis.tb.account -= davis.cs.service;
    }


    if (month == 1 and year == 2030) {
        davis.tb.account -= (davis.cs.service * 10);
    }

}


void davis_deposite(const int month, const int year)
{
    if (year == 2026) {
        davis.tb.interest = 14.5;
    }

    if (year == 2027) {
        davis.tb.interest = 13.5;
    }

    if (year == 2028) {
        davis.tb.interest = 12.5;
    }

    if (year == 2029) {
        davis.tb.interest = 11.5;
    }

    if (year >= 2030) {
        davis.tb.interest = 9.5;
    }

    davis.tb.deposite += davis.tb.deposite * (davis.tb.interest / 12.0 / 100.0);

    // добавление остатка со счёта на вклад
    davis.tb.deposite += davis.tb.account;

    davis.tb.account = 0;

}

void pair_medicine(const int month, const int year)
{
    if (month == 2 or month == 11) {
        davis.tb.account -= 2'000;
    }

    if (month == 3 or month == 10) {
        lisa.tb.account -= 2'000;
    }

}


void pair_gifts(const int month, const int year)
{
    if (month == 1) {
        davis.tb.account -= davis.gifts.gifts;
        lisa.tb.account -= lisa.gifts.gifts;
    }

    if (month == 2) {
        davis.tb.account -= davis.gifts.gifts * 0.5;
        lisa.tb.account -= lisa.gifts.gifts * 0.5;
    }

    if (month == 10) {
        davis.tb.account -= davis.gifts.gifts;
        lisa.tb.account -= lisa.gifts.gifts;
    }

    if (month == 11) {
        lisa.tb.account -= lisa.gifts.gifts * 1.5;
    }

    if (month == 12) {
        davis.tb.account -= davis.gifts.gifts * 1.5;
    }

}


void pair_holiday(const int month, const int year)
{
    if (month == 6) {
        davis.tb.account -= davis.holiday * 5;
        lisa.tb.account -= lisa.holiday * 2;
    }

    if (month == 1 and year == 2028) {
        davis.tb.account -= davis.holiday * 3;
        lisa.tb.account -= lisa.holiday * 1.5;
    }

}


void pair_newcar(const int month, const int year)
{

    if (month == 12) {
        davis.car.value -= davis.car.value * 0.15;
        lisa.car.value -= lisa.car.value * 0.15;
    }

    if (davis.tb.deposite > 8'000'000) {
        davis.tb.deposite -= 4'000'000;
        davis.car.value += 4'000'000;
    }


    if (year == 2039) {
        davis.tb.deposite -= 4'000'000;
        lisa.car.value += 4'000'000;
    }

}


void pair_marriage(const int month, const int year)
{

    if (month == 7 and year == 2035) {
        davis.tb.account -= 1'500'000;
        lisa.tb.account -= 1'000'000;
    }


}

void pair_ownflat(const int month, const int year)
{
    
    RUB newflat = 15'000'000;

    if (month == 1 and year == 2032) {

        newflat_own = true;
        davis.tb.account -= newflat / 12 / 15 * 1.22;
        davis.flat.rent = 0;
        lisa.flat.rent = 0;

    }


    if (newflat_own == true) {

        if (newflat > 0) {
            davis.tb.account -= newflat / 12 / 15 * 1.22;
        }

        else {
            davis.tb.account -= 0;
        }
    }
}


void print_results()
{
    printf("Salary davis = %.2f\n", davis.salary);

    RUB capitaldavise = 0;

    capitaldavise += davis.car.value;
    capitaldavise += davis.tb.deposite;
    capitaldavise += davis.tb.account_eur * davis.tb.rate_eur_rub;

    printf("Capital davis = %.2f\n", capitaldavise);
    printf("Bank davis = %.2f\n", davis.tb.deposite);
    printf("Car davis = %.2f\n", davis.car.value);


    printf("Salary lisa = %.2f\n", lisa.salary);

    RUB capitallisa = 0;

    capitallisa += lisa.tb.account;
    capitallisa += lisa.tb.deposite;
    capitallisa += lisa.tb.account_eur * lisa.tb.rate_eur_rub;

    printf("Capital lisa = %.2f\n", capitallisa);
	printf("Bank lisa = %.2f\n", lisa.tb.deposite);
	printf("Car lisa = %.2f\n", lisa.car.value);

    RUB totalcapital = capitaldavise + capitallisa;
    printf("Total capital = %.2f\n", totalcapital);

}


void simulation()
{
    int month = 2;
    int year = 2026;

    while (not (month == 3 and year == 2036
        )) {

        davis_salary(month, year);
        davis_food();
        davis_car();
        davis_gym();
        davis_girlfriend();
        davis_flat(month, year);
        davis_cs(month, year);
        davis_inflation(month, year);
        davis_cat();

        lisa_salary(month, year);
        lisa_cosmetic(month, year);

        pair_medicine(month, year);
        pair_gifts(month, year);
        pair_holiday(month, year);
        pair_newcar(month, year);
        pair_marriage(month, year);
        pair_ownflat(month, year);

        davis_deposite(month, year);
        lisa_deposite(month, year);


        ++month;
        if (month == 13) {
            ++year;
            month = 1;
        }

    }
}



int main()
{

    pair_init();

    simulation();

    print_results();

}