#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INFLATION_POINT 0.03
#define SALARY_POINT 0.02
#define SAVING_POINT 0.10
using RUB = long long int;  // C++

enum months
{
    January = 1,
    February,
    March,
    April,
    May,
    June,
    July,
    August,
    September,
    October,
    November,
    December
};

typedef struct
{
    RUB savings;   // сбережения на счете
    int percent;   // накопительный процент

} savings_account; 

typedef struct 
{
   // float inflation;
    RUB capital; // ----------------------------- кол-во денег в свободном доступе человека
    savings_account personal_saving_account; // - сберегательный счет

} bank_account;

typedef struct
{
    RUB food;
    RUB gas;

} monthly_expenses;


typedef struct
{
    RUB market_value;
    RUB gas_cost;

} car;


typedef struct  
{
    char name[10];
    RUB person_salary;
    bank_account personal_bank_account;
    car personal_car;
    monthly_expenses personal_expenses;

} person;


void init_person(person* curr_person)
{
    
    memset(curr_person, 0, sizeof(curr_person));

    puts("Input next start personal options splited by SPACE: name, salary, capital, savings, savings percent,\n\
market value of car (0 if haven't it), gas cost, food cost:");

    char name[10] = { 0 };
    scanf("%s %lld %lld %lld %d %lld %lld %lld", name, &(curr_person->person_salary),&(curr_person->personal_bank_account.capital),
        &(curr_person->personal_bank_account.personal_saving_account.savings), &(curr_person->personal_bank_account.personal_saving_account.percent),
        &(curr_person->personal_car.market_value), &(curr_person->personal_car.gas_cost), &(curr_person->personal_expenses.food));

    //curr_person->personal_expenses.gas = curr_person->personal_car.gas_cost;
    strcpy(curr_person->name, name);

}

void inflation_update(person* curr_person, float inflation)
{
    //*inflation += 0.03;
    curr_person->personal_expenses.food *= inflation;
    curr_person->personal_car.gas_cost *= inflation;
    curr_person->personal_car.market_value *= (2 - inflation);
}

void expension(person* curr_person)
{
    curr_person->personal_expenses.gas = curr_person->personal_car.gas_cost;
    curr_person->personal_bank_account.capital -= (curr_person->personal_expenses.food + curr_person->personal_expenses.gas);
}

void get_salary(person* curr_person, int month)
{
    if (month == September || month == February)
    {
        curr_person->person_salary *= (1 + SALARY_POINT);
    }
    curr_person->personal_bank_account.capital += curr_person->person_salary;
}

void savings_action(person* curr_person)
{
    RUB saving_value = curr_person->personal_bank_account.capital * SAVING_POINT;
    curr_person->personal_bank_account.personal_saving_account.savings += saving_value;
    curr_person->personal_bank_account.capital -= saving_value;
}

void savings_update(person* curr_person)
{
    RUB get_savings = curr_person->personal_bank_account.personal_saving_account.savings *
        curr_person->personal_bank_account.personal_saving_account.percent / 1200;
    curr_person->personal_bank_account.personal_saving_account.savings += get_savings;
}

void simulation(int first_month, int last_month, int first_year, int last_year, person* list_of_persons, int number_of_persons)
{
    int curr_month = first_month;
    int curr_year = first_year;

    float inflation = 1.0;
    while (!(curr_year == last_year && curr_month == last_month)) 
    {
        for (int i = 0; i < number_of_persons; i++)
        {
            get_salary(list_of_persons + i, curr_month);
            // bank_account action
            expension(list_of_persons + i);
            savings_update(list_of_persons + i);
            savings_action(list_of_persons + i);
           
        }
        curr_month++;
        if (curr_month > December)
        {
            curr_month = January;
            curr_year += 1;
            inflation += INFLATION_POINT;
            for (int i = 0; i < number_of_persons; i++) inflation_update(list_of_persons + i, inflation);
        }
    }
}


int main()
{
    puts("Input number of persons:");
    int number_of_persons;
    scanf("%d", &number_of_persons);

    person* list_of_persons = (person*)malloc(sizeof(person) * number_of_persons);
    for (int i = 0; i < number_of_persons; i++)
    {
        init_person(list_of_persons + i);
    }

    return EXIT_SUCCESS;
}