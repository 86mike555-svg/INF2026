#include <stdio.h>

using RUB = long long int;

struct Car {
  RUB value;
  RUB gas;
};

struct Pet {
  RUB food;
};

struct Bank {
  RUB account;   
  RUB deposit;   
};

struct Person {
  RUB salary;
  RUB capital;   
  RUB food;

  Car car;
  Pet pet;
  Bank bank;
};

struct Person Alice;

float bank_percent = 14.5;      
float inflation = 8.0;          

void alice_salary(const int month, const int year) {

  if ((month == 8) && (year == 2026)) { 
    Alice.salary = Alice.salary * 1.5;
  }

  
  Alice.bank.account += Alice.salary;
}

void alice_food() {
  Alice.bank.account -= Alice.food;
}

void alice_car() {
  Alice.bank.account -= Alice.car.gas;
}

void alice_pet() {
  Alice.bank.account -= Alice.pet.food;
}

void alice_deposit_percent() {
  
  Alice.bank.deposit += Alice.bank.deposit * (bank_percent / 12.0 / 100.0);
}

void alice_transfer_to_deposit() {
  
  if (Alice.bank.account > 100000) {
    RUB sum = Alice.bank.account - 100000;
    Alice.bank.deposit += sum;
    Alice.bank.account -= sum;
  }
}

void alice_inflation(int month) {

  
  if (month == 1) {
    Alice.food += Alice.food * (inflation / 100.0);
    Alice.car.gas += Alice.car.gas * (inflation / 100.0);
    Alice.pet.food += Alice.pet.food * (inflation / 100.0);
    Alice.car.value += Alice.car.value * (inflation / 100.0);
  }
}

void print_results() {

  printf("Salary = %lld\n", Alice.salary);
  printf("Bank account = %lld\n", Alice.bank.account);
  printf("Deposit = %lld\n", Alice.bank.deposit);
  printf("Car price = %lld\n", Alice.car.value);
}

void simulation()
{
  int month = 2;
  int year = 2026;

  while (!((month == 3) && (year == 2127))) {

    alice_inflation(month);

    alice_deposit_percent();

    alice_food();
    alice_car();
    alice_pet();

    alice_salary(month, year);

    alice_transfer_to_deposit();

    ++month;
    if (month == 13) {
      month = 1;
      ++year;
    }
  }
}

void alice_init()
{
  Alice.salary = 180000;
  Alice.capital = 0;

  Alice.food = 20000;

  Alice.car.value = 2400000;
  Alice.car.gas = 15000;

  Alice.pet.food = 5000;

  Alice.bank.account = 0;
  Alice.bank.deposit = 0;
}

int main()
{
  alice_init();
  simulation();
  print_results();
}
