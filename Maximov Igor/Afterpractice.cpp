#include <stdio.h>

using RUB = long long int; // C++


struct Car {
  RUB value;
  RUB gas;
};

struct Person
{
    RUB salary; 
    RUB account; // текущий банковский счет
    RUB deposit; // вклад
    RUB food;
    RUB hamster;
    struct Car car;
};
struct Person Alice;


float pp = 14.5;


void alice_salary(const int month, const int year) {
    if ((month == 8) && (year == 2026)) { // премия
        Alice.salary *= 1.5;
    }

    Alice.account += Alice.salary;

}
void print_result(){
  printf("\n=== Счета ===\n");
  printf("Account = %lld\n", Alice.account);
  printf("Deposit = %lld\n", Alice.deposit);
  printf("Total capital = %lld\n", Alice.account + Alice.deposit + Alice.car.value);
}

void price_2026(){
    printf("\n=== Start prices (2026):\n");
    printf("Salary = %lld\n", Alice.salary);
    printf("Food = %lld\n", Alice.food);
    printf("Car gas = %lld\n", Alice.car.gas);
    printf("Car value = %lld\n", Alice.car.value);
}

void price_2037(){
    printf("\n=== Final prices (2037):\n");
    printf("Salary = %lld\n", Alice.salary);
    printf("Food = %lld\n", Alice.food);
    printf("Car gas = %lld\n", Alice.car.gas);
    printf("Car value = %lld\n", Alice.car.value);
}

void alice_bank_interest(){
  RUB interest = Alice.deposit * (pp / 12.0 / 100.0);
  Alice.account += interest;
}

void alice_food(){
  Alice.account -= Alice.food;
}

void alice_car(){
  Alice.account -= Alice.car.gas;
}

void alice_hamster(){
    Alice.account -= Alice.hamster;
}

void alice_transfer_to_deposit(){
    Alice.deposit += Alice.account;
    Alice.account = 0;
}

void apply_inflation(){
    Alice.salary = Alice.salary * 106 / 100;
    Alice.food = Alice.food * 106 / 100;
    Alice.car.gas = Alice.car.gas * 106 / 100;
    Alice.car.value = Alice.car.value * 106 / 100;
    Alice.hamster = Alice.hamster * 106 / 100;
}

void Alice_init() {
  Alice.account = 0;
  Alice.deposit = 0;
  Alice.salary = 100'000;
  Alice.food = 20'000;
  Alice.car.value = 2'400'000;
  Alice.car.gas = 15'000;
  Alice.hamster = 5'000;
}



void simulation(){
  

    int month = 2;
    int year = 2026; 

  

    while (!(( month == 3) && (year == 2037)) ) {
      alice_bank_interest();
      alice_salary(month, year);
      alice_food();  
      alice_car();
      alice_hamster();
      alice_transfer_to_deposit();

      ++month;
      if (month == 13) {
         month = 1;
         ++year;

         apply_inflation();
    }
  }
}




int main()
{
    Alice_init();

    price_2026();

    simulation();

    price_2037();

    print_result();
}