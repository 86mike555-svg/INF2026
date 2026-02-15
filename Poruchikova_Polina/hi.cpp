#include <stdio.h>

//typedef int RUB; // C
using RUB = long long int; // C++


struct Car {
    RUB value;
    RUB gas;
};

struct kitty {
    RUB petfood;
    RUB vet;
    RUB filler;
};

struct Person {
    RUB salary;
    RUB capital;
    RUB food;
    struct Car kamaz; //создает переменную с данными которые в стракт машина (цена, бензин)
    struct kitty Barsik;
};


struct Person Alice; //создает переменную с данными которые в стракт персон (зп, еда и тд)

float pp = 14.5;


void alice_innit(){ //изначальные данные
    Alice.capital = 0;
    Alice.salary = 180'000;
    Alice.food = 20'000;
    Alice.kamaz.value = 2'400'000;
    Alice.kamaz.gas = 15'000;
    Alice.Barsik.vet = 5'000;
    Alice.Barsik.filler = 1'500;
    Alice.Barsik.petfood = 750;
}

void alice_salary(const int month,const int year){
    if ( (month == 8) && (year == 2026)) { 
        Alice.salary *= 1.5; //повышение зп
    }
    Alice.capital += Alice.salary; //capital = capital + salary;
}

void alice_pet(){
    Alice.capital -= Alice.Barsik.filler;
    Alice.capital -= Alice.Barsik.petfood;
    Alice.capital -= Alice.Barsik.vet;
}

void alice_bank_interest(){
    Alice.capital += Alice.capital * (pp / 12.0 / 100.0); //банковские проценты
}

void alice_food(){
    Alice.capital -= Alice.food;
}

void alice_car(){
    Alice.capital -= Alice.kamaz.gas; //стракт персон -> стракт машина -> бензин
}

void simulation(){  //условия подсчета, счет и смена месяцев
    int month = 2;
    int year = 2026;

    //for(int month = 1; month < 19; ++month) { //++month month++ month = month + 1
    //while ((month != 3) || (year != 2027))
    while ( !((month == 3) && (year == 2127)) ) { //подсчитывает все что есть в цикле
        alice_pet();
        alice_food();
        alice_bank_interest();
        alice_salary(month, year);

        ++month;
        if (month == 13) {
            month = 1;
            ++year;
        }
    }
}

void print_results(){ //печает результаты но запускается через мейн
    printf("salary = %lld\n", Alice.salary);
    printf("capital = %lld", Alice.capital);
}


int main(){ //выполняет войды
    alice_innit();

    simulation();

    print_results();
}
