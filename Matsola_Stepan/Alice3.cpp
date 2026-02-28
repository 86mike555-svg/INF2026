#include <stdio.h>
#include <stdbool.h>

using RUB = long long int;
using INFLATION = double;
using PERCENT = double;

struct Bank {
    char name[50];
    PERCENT deposit_rate;
    RUB min_deposit;
    int term_months;
    bool is_reliable;
};

struct BankAccount {
    RUB deposit;
    RUB checking;
    PERCENT deposit_rate;
    int deposit_term;
    int months_passed;
    struct Bank* bank;
};

struct Car {
    RUB value;
    RUB gas;
    RUB maintenance;
    INFLATION gas_inflation;
    INFLATION maintenance_inflation;
};

struct Dog {
    RUB value;
    RUB food;
    RUB vet;
    INFLATION food_inflation;
    INFLATION vet_inflation;
};

struct Hamster {
    RUB value;
    RUB food;
    RUB bedding;
    INFLATION food_inflation;
    INFLATION bedding_inflation;
};

struct Child {
    RUB monthly_expenses;
    RUB education_fund;
    RUB clothes;
    INFLATION expenses_inflation;
    INFLATION education_inflation;
    int age;
};

struct Spouse {
    RUB salary;
    RUB personal_expenses;
    RUB savings;
    INFLATION salary_indexation;
    INFLATION expenses_inflation;
};

struct Family {
    RUB common_fund;
    RUB emergency_fund;
    RUB monthly_savings_target;
    RUB total_expenses;
    RUB total_income;
};

struct Person {
    RUB salary;
    RUB food;
    RUB utilities;
    RUB entertainment;
    RUB health_insurance;

    INFLATION food_inflation;
    INFLATION utilities_inflation;
    INFLATION entertainment_inflation;
    INFLATION health_inflation;
    INFLATION salary_indexation;

    struct Car car;
    struct Dog dog;
    struct Hamster hamster;
    struct BankAccount bank;
    RUB fathers_money;

    struct Spouse husband;
    struct Child child;
    struct Family family;
};

struct Person Alice;

struct Bank sberbank = { "Sberbank", 12.5, 100000, 12, true };
struct Bank vtb = { "VTB", 13.0, 150000, 9, true };
struct Bank gazprombank = { "Gazprombank", 13.5, 200000, 6, true };
struct Bank tinkoff = { "Tinkoff", 14.0, 50000, 3, true };
struct Bank alfabank = { "Alfa-Bank", 13.8, 100000, 6, true };
struct Bank otkritie = { "Otkritie", 12.0, 50000, 12, true };
struct Bank sovcombank = { "Sovcombank", 11.5, 30000, 3, false };
struct Bank rosselkhoz = { "Rosselkhoz", 12.8, 100000, 12, true };
struct Bank mkb = { "MKB", 13.2, 150000, 6, true };
struct Bank uralsib = { "Uralsib", 11.0, 50000, 3, false };

struct Bank* available_banks[] = {
    &sberbank, &vtb, &gazprombank, &tinkoff, &alfabank,
    &otkritie, &sovcombank, &rosselkhoz, &mkb, &uralsib
};
int banks_count = 10;

struct Bank* choose_best_bank(RUB deposit_amount, int months_to_keep) {
    struct Bank* best_bank = NULL;
    PERCENT best_rate = 0;

    for (int i = 0; i < banks_count; i++) {
        struct Bank* bank = available_banks[i];

        if (deposit_amount >= bank->min_deposit &&
            months_to_keep >= bank->term_months) {

            if (bank->deposit_rate > best_rate && bank->is_reliable) {
                best_rate = bank->deposit_rate;
                best_bank = bank;
            }
        }
    }

    if (best_bank == NULL && deposit_amount >= sberbank.min_deposit) {
        best_bank = &sberbank;
    }

    return best_bank;
}

void open_new_deposit(RUB amount) {
    if (amount <= 0) return;

    struct Bank* chosen_bank = choose_best_bank(amount, 12);

    if (chosen_bank != NULL) {
        if (Alice.bank.deposit == 0) {
            Alice.bank.bank = chosen_bank;
            Alice.bank.deposit_rate = chosen_bank->deposit_rate;
            Alice.bank.deposit_term = chosen_bank->term_months;
            Alice.bank.months_passed = 0;
        }
        else {
            if (chosen_bank->deposit_rate > Alice.bank.deposit_rate) {
                Alice.bank.bank = chosen_bank;
                Alice.bank.deposit_rate = chosen_bank->deposit_rate;
                Alice.bank.deposit_term = chosen_bank->term_months;
                Alice.bank.months_passed = 0;
            }
        }

        Alice.bank.deposit += amount;
    }
}

void bank_interest() {
    if (Alice.bank.checking > 0) {
        RUB to_deposit = Alice.bank.checking - 50000;
        if (to_deposit > 0) {
            Alice.bank.deposit += to_deposit;
            Alice.bank.checking = 50000;
        }
    }

    if (Alice.bank.deposit > 0) {
        Alice.bank.months_passed++;

        if (Alice.bank.months_passed >= Alice.bank.deposit_term) {
            RUB interest = Alice.bank.deposit * Alice.bank.deposit_rate / 100;
            Alice.bank.deposit += interest;

            struct Bank* new_bank = choose_best_bank(Alice.bank.deposit, 12);
            if (new_bank != NULL && new_bank->deposit_rate > Alice.bank.deposit_rate) {
                Alice.bank.bank = new_bank;
                Alice.bank.deposit_rate = new_bank->deposit_rate;
                Alice.bank.deposit_term = new_bank->term_months;
            }

            Alice.bank.months_passed = 0;
        }
        else {
            RUB monthly_interest = Alice.bank.deposit * Alice.bank.deposit_rate / 100 / 12;
            Alice.bank.deposit += monthly_interest;
        }
    }
}

void husband_salary(int month, int year) {
    if (month == 1 && year > 2026) {
        Alice.husband.salary = Alice.husband.salary *
            (100 + Alice.husband.salary_indexation) / 100;
    }

    Alice.family.common_fund += Alice.husband.salary;
    Alice.family.total_income += Alice.husband.salary;

    RUB husband_expenses = Alice.husband.personal_expenses;
    Alice.family.common_fund -= husband_expenses;
    Alice.family.total_expenses += husband_expenses;

    Alice.husband.savings += Alice.husband.salary * 0.1;
}

void child_expenses() {
    RUB child_total = Alice.child.monthly_expenses + Alice.child.clothes;
    Alice.family.common_fund -= child_total;
    Alice.family.total_expenses += child_total;

    RUB education_contribution = Alice.family.common_fund * 0.05;
    if (education_contribution > 10000) {
        Alice.child.education_fund += education_contribution;
        Alice.family.common_fund -= education_contribution;
    }

    static int last_year = 0;
    if (last_year != 2037) {
        Alice.child.monthly_expenses = Alice.child.monthly_expenses *
            (100 + Alice.child.expenses_inflation) / 100;
        Alice.child.clothes = Alice.child.clothes *
            (100 + Alice.child.expenses_inflation) / 100;
        last_year = 2037;
    }
}

void alice_salary(const int month, const int year) {
    if (month == 1 && year > 2026) {
        Alice.salary = Alice.salary * (100 + Alice.salary_indexation) / 100;
    }

    if ((month == 8) && (year == 2026)) {
        RUB bonus = Alice.salary * 0.5;
        Alice.family.common_fund += bonus;
        Alice.family.total_income += bonus;
    }

    Alice.family.common_fund += Alice.salary;
    Alice.family.total_income += Alice.salary;
}

void alice_food() {
    RUB food_cost = Alice.food;
    Alice.family.common_fund -= food_cost;
    Alice.family.total_expenses += food_cost;
}

void alice_car() {
    RUB gas_cost = Alice.car.gas;
    RUB maint_cost = Alice.car.maintenance;
    RUB total_car_cost = gas_cost + maint_cost;

    Alice.family.common_fund -= total_car_cost;
    Alice.family.total_expenses += total_car_cost;
}

void alice_dog() {
    RUB dog_food = Alice.dog.food;
    RUB dog_vet = Alice.dog.vet;
    RUB total_dog_cost = dog_food + dog_vet;

    Alice.family.common_fund -= total_dog_cost;
    Alice.family.total_expenses += total_dog_cost;
}

void alice_hamster() {
    RUB hamster_food = Alice.hamster.food;
    RUB hamster_bedding = Alice.hamster.bedding;
    RUB total_hamster_cost = hamster_food + hamster_bedding;

    Alice.family.common_fund -= total_hamster_cost;
    Alice.family.total_expenses += total_hamster_cost;
}

void alice_utilities() {
    RUB utilities_cost = Alice.utilities;
    Alice.family.common_fund -= utilities_cost;
    Alice.family.total_expenses += utilities_cost;
}

void alice_entertainment() {
    RUB entertainment_cost = Alice.entertainment;
    Alice.family.common_fund -= entertainment_cost;
    Alice.family.total_expenses += entertainment_cost;
}

void alice_health_insurance() {
    RUB insurance_cost = Alice.health_insurance;
    Alice.family.common_fund -= insurance_cost;
    Alice.family.total_expenses += insurance_cost;
}

void apply_all_inflations() {
    Alice.car.gas = Alice.car.gas * (100 + Alice.car.gas_inflation) / 100;
    Alice.car.maintenance = Alice.car.maintenance *
        (100 + Alice.car.maintenance_inflation) / 100;

    Alice.dog.food = Alice.dog.food * (100 + Alice.dog.food_inflation) / 100;
    Alice.dog.vet = Alice.dog.vet * (100 + Alice.dog.vet_inflation) / 100;

    Alice.hamster.food = Alice.hamster.food *
        (100 + Alice.hamster.food_inflation) / 100;
    Alice.hamster.bedding = Alice.hamster.bedding *
        (100 + Alice.hamster.bedding_inflation) / 100;

    Alice.food = Alice.food * (100 + Alice.food_inflation) / 100;
    Alice.utilities = Alice.utilities * (100 + Alice.utilities_inflation) / 100;
    Alice.entertainment = Alice.entertainment *
        (100 + Alice.entertainment_inflation) / 100;
    Alice.health_insurance = Alice.health_insurance *
        (100 + Alice.health_inflation) / 100;

    Alice.husband.personal_expenses = Alice.husband.personal_expenses *
        (100 + Alice.husband.expenses_inflation) / 100;
}

void manage_family_budget() {
    if (Alice.family.common_fund > Alice.family.emergency_fund * 2) {
        RUB to_emergency = Alice.family.common_fund * 0.1;
        Alice.family.emergency_fund += to_emergency;
        Alice.family.common_fund -= to_emergency;
    }

    if (Alice.family.common_fund > Alice.family.monthly_savings_target) {
        RUB excess = Alice.family.common_fund - Alice.family.monthly_savings_target;

        if (excess > 50000) {
            open_new_deposit(excess);
            Alice.family.common_fund -= excess;
        }
    }

    if (Alice.family.common_fund > 100000) {
        RUB to_bank = Alice.family.common_fund - 100000;
        Alice.bank.checking += to_bank;
        Alice.family.common_fund -= to_bank;
    }
}

void alice_init() {
    Alice.bank.deposit = 50000;
    Alice.bank.checking = 0;
    Alice.bank.deposit_rate = 11.0;
    Alice.bank.deposit_term = 12;
    Alice.bank.months_passed = 0;
    Alice.bank.bank = &sberbank;

    Alice.fathers_money = 5000000;

    Alice.salary = 180000;
    Alice.salary_indexation = 2.0;
    Alice.food = 20000;
    Alice.food_inflation = 1.2;
    Alice.utilities = 15000;
    Alice.utilities_inflation = 1.5;
    Alice.entertainment = 10000;
    Alice.entertainment_inflation = 1.3;
    Alice.health_insurance = 8000;
    Alice.health_inflation = 2.0;

    Alice.car.value = 2400000;
    Alice.car.gas = 15000;
    Alice.car.maintenance = 5000;
    Alice.car.gas_inflation = 0.4;
    Alice.car.maintenance_inflation = 1.0;

    Alice.dog.value = 5000;
    Alice.dog.food = 3000;
    Alice.dog.vet = 1000;
    Alice.dog.food_inflation = 1.0;
    Alice.dog.vet_inflation = 2.0;

    Alice.hamster.value = 2000;
    Alice.hamster.food = 2000;
    Alice.hamster.bedding = 1000;
    Alice.hamster.food_inflation = 1.0;
    Alice.hamster.bedding_inflation = 1.5;

    Alice.husband.salary = 250000;
    Alice.husband.personal_expenses = 30000;
    Alice.husband.savings = 100000;
    Alice.husband.salary_indexation = 2.5;
    Alice.husband.expenses_inflation = 1.5;

    Alice.child.monthly_expenses = 25000;
    Alice.child.education_fund = 0;
    Alice.child.clothes = 10000;
    Alice.child.expenses_inflation = 1.8;
    Alice.child.education_inflation = 3.0;
    Alice.child.age = 3;

    Alice.family.common_fund = 0;
    Alice.family.emergency_fund = 0;
    Alice.family.monthly_savings_target = 50000;
    Alice.family.total_expenses = 0;
    Alice.family.total_income = 0;

    RUB initial_purchases = Alice.car.value + Alice.dog.value + Alice.hamster.value;
    Alice.bank.deposit -= initial_purchases;
}

void simulation() {
    int month = 2;
    int year = 2026;

    alice_salary(1, 2026);
    Alice.family.common_fund += Alice.fathers_money;
    Alice.family.common_fund -= (Alice.car.value + Alice.dog.value + Alice.hamster.value);

    while (!((month == 3) && (year == 2037))) {

        alice_salary(month, year);
        husband_salary(month, year);

        alice_dog();
        alice_hamster();
        alice_food();
        alice_car();
        alice_utilities();
        alice_entertainment();
        alice_health_insurance();
        child_expenses();

        manage_family_budget();

        ++month;
        if (month == 13) {
            month = 1;
            ++year;

            bank_interest();
            apply_all_inflations();

            printf("\n=== Year %d ===\n", year);
            printf("Family total income: %lld RUB\n", Alice.family.total_income);
            printf("Family total expenses: %lld RUB\n", Alice.family.total_expenses);
            printf("Emergency fund: %lld RUB\n", Alice.family.emergency_fund);
            printf("Bank deposit: %lld RUB (rate %.1f%% in %s)\n",
                Alice.bank.deposit, Alice.bank.deposit_rate, Alice.bank.bank->name);
            printf("Child education fund: %lld RUB\n",
                Alice.child.education_fund);
            printf("Husband personal savings: %lld RUB\n\n",
                Alice.husband.savings);

            Alice.family.total_expenses = 0;
            Alice.family.total_income = 0;
        }
    }
}

void print_results() {
    RUB total_capital = Alice.bank.deposit + Alice.bank.checking +
        Alice.family.emergency_fund + Alice.child.education_fund +
        Alice.husband.savings + Alice.family.common_fund;

    printf("\n========== FINAL RESULTS (March 2037) ==========\n\n");

    printf("=== Alice ===\n");
    printf("Salary: %lld RUB\n", Alice.salary);
    printf("Deposit: %lld RUB\n", Alice.bank.deposit);
    printf("Checking account: %lld RUB\n", Alice.bank.checking);
    printf("Bank: %s (rate %.1f%%)\n",
        Alice.bank.bank->name, Alice.bank.deposit_rate);

    printf("\n=== Family ===\n");
    printf("Common family fund: %lld RUB\n", Alice.family.common_fund);
    printf("Emergency fund: %lld RUB\n", Alice.family.emergency_fund);

    printf("\n=== Husband ===\n");
    printf("Husband salary: %lld RUB\n", Alice.husband.salary);
    printf("Husband personal savings: %lld RUB\n", Alice.husband.savings);

    printf("\n=== Child ===\n");
    printf("Child age: %d years\n", Alice.child.age);
    printf("Education fund: %lld RUB\n", Alice.child.education_fund);

    printf("\n=== ASSETS ===\n");
    printf("Car: %lld RUB\n", Alice.car.value);
    printf("Dog: %lld RUB\n", Alice.dog.value);
    printf("Hamster: %lld RUB\n", Alice.hamster.value);

    printf("\n=== TOTAL CAPITAL ===\n");
    printf("Total family capital: %lld RUB\n", total_capital);

    RUB initial_capital = 5000000 + 50000;
    RUB profit = total_capital - initial_capital;
    printf("Profit for the period: %lld RUB\n", profit);
    printf("Return: %.1f%%\n", (double)profit / initial_capital * 100);

    printf("\n================================================\n");
}

int main() {
    printf("=== FAMILY BUDGET SIMULATION ===\n");
    printf("Start: February 2026\n");
    printf("End: March 2037\n\n");

    alice_init();
    simulation();
    print_results();

}