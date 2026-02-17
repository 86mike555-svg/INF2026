#include <stdio.h>

using RUB = long long int;
using USD = long long int;

//расходы на авто
struct Car { 
    RUB value;
    RUB gas;
};

struct Bank {
    RUB account_rub;
    USD account_usd;
    float rate_usd_rub;
};

struct Sub {
    RUB yandex_music;
    RUB vpn;
    RUB boosty;
};

struct Person {
    Bank vtb;
    RUB capital;
    RUB salary;
    RUB food;
    Car car;
    Sub sub;
};
struct Person alice;


void alice_init()
{
    alice.vtb.rate_usd_rub = 78.76;
    alice.vtb.account_rub = 0;
    alice.vtb.account_usd = 0;

    alice.salary = 180'000;
    alice.food = 3'000;

    alice.car.value = 2'400'000;
    alice.car.gas = 15'000;

    alice.sub.yandex_music = 450;
    alice.sub.vpn = 100;
    alice.sub.boosty = 150;
}


void alice_subs()
{
    alice.vtb.account_rub -= alice.sub.yandex_music;
    alice.vtb.account_rub -= alice.sub.vpn;
    alice.vtb.account_rub -= alice.sub.boosty;
}


void alice_food(const int month)
{
    if (month == 12) {
        alice.capital -= 2000;
    }
    alice.capital -= alice.food;
}


void alice_car()
{
    alice.vtb.account_rub -= alice.car.gas;
}


void alice_salary(const int month, const int year)
{
    if (month == 3){
        alice.salary = (alice.salary * 1.5);
    }
    if (year == 2027 && month == 2){
        alice.vtb.account_rub += 5000;
    }
    alice.vtb.account_rub += alice.salary;
}


void simulation()
{
    int year = 2026;
    int month = 2;
    while ( !(year == 2027 && month == 2)) {
        alice_salary(month, year);
        alice_food(month);
        alice_car();
        alice_subs();

        ++month;
        if (month == 13){
            ++year;
            month = 1;
        }
    }  
}


void print_resullts()
{
    printf("Salary = %lld\n", alice.salary);
    printf("Capital = %lld", alice.vtb.account_rub);
}


int main(){
   alice_init();
   simulation();
   print_resullts();
}
