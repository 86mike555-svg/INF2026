#include <stdio.h>

int salary = 200'001;
int capital = 0;
int food = 15'000;
int k=0;
// typedef int RUB;  // C
using RUB = long long int;  // C++

void my_salary(const int month);
struct storage {
    RUB price;
    RUB inc;
}  ;
struct child {
    RUB eat;
    RUB cloth;
    RUB xxx;
};
struct Dogs {
    RUB eat;
    RUB train;
};
struct Car {
    RUB value;
    RUB gas;
};
struct Jour {
    RUB road;
    RUB excurs;
    RUB hous;
};
struct Person {
    RUB salary;
    RUB capital;
    RUB food;
    Car car;
    Dogs dogs;
    Jour jour;
    storage storage;
    child child;

};

struct Person alice;

void alice_init()
{
    alice.capital = 0;
    alice.salary = 180'000;
    alice.food = 15'000;

    alice.car.value = 2'400'000;
    alice.car.gas = 12'000;

    alice.dogs.eat = 15'000;
    alice.dogs.train = 4'500;

    alice.jour.road = 10'000;
    alice.jour.excurs = 25'000;
    alice.jour.hous = 30'000;

    alice.storage.price=600'000;
    alice.storage.inc=60'000;

    alice.child.eat= 20'000;
    alice.child.cloth=15'000;
    alice.child.xxx=11'111;



}

float sberbank_interest(RUB sum, int month)
{
    if (month == 3) {
        // salary *= 1.5;
    }
    
    if (sum > 10'000 && sum < 3'000'000) {
        return 11.5;
    }

    if (sum >= 3'000'000) {
        return 12.5;
    }

    return 0.1;
}

float inf(int month)
{
    if (month == 12) {
        return 0.1;
    }
    else {
        return 0;
    }
}
float inft (int month)
{
  if (month == 12) {
        return 1.1;
    }
    else {
        return 1;
    }  
}
void alice_kladovka()
{
    if (k==0 && alice.capital>600'000){
        alice.capital-=alice.storage.price;
    }
    else {
         alice.capital-=alice.storage.inc;
    }
    if (k==1){
        alice.capital+=alice.storage.inc;

    }
}
void alice_salary(const int year, const int month)
{
    if (month == 3 ) {
        alice.salary *= 1.5;
    }
    if (month == 12) {
        alice.salary -= alice.salary * inf(month);
    }
    
    alice.capital += alice.salary;
}
void alice_children(int month){
    if (month%3==0){
        alice.capital-=alice.child.cloth;

    }
    alice.capital-=alice.child.eat;
    alice.capital-=alice.child.xxx;
}
void alice_food()
{
    alice.capital -= alice.food;
}

void print_results()
{
    printf("Salary = %lld\n", alice.salary);
    printf("Capital = %lld\n", alice.capital);
}

void alice_car()
{
    alice.capital -= alice.car.gas;
}

void alice_dogs()
{
    alice.capital -= alice.dogs.eat;
    alice.capital -= alice.dogs.train;
}

void alice_rest(int month) 
{
    if (alice.capital > 1'000'000 && month == 6) {
        alice.capital -= alice.jour.hous;
        alice.capital -= alice.jour.excurs;
        alice.capital -= alice.jour.road;
    }
}




void alice_bank_interest(int month)
{
    float pp;
    float dcp;
    pp = sberbank_interest(alice.capital, month);
    dcp = inf(month);
    alice.capital += alice.capital * (pp / 12.0 / 100.0);
    alice.capital -= alice.capital * dcp;
}

void alice_simulation()
{
    int year = 2026;
    int month = 2;

    while (!(year == 2031 && month == 2)) {
        alice_salary(year, month);
        alice_kladovka();
        alice_food();
        alice_car();
        alice_dogs();
        alice_rest(month);  
        alice_children(month);
        alice_bank_interest(month);
        

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
    
    alice_simulation();

    printf("Global Salary = %d\n", salary);
    printf("Global Capital = %d\n", capital);
    print_results();
    
    return 0;
}
