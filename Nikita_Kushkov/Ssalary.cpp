#include <stdio.h>
#include <random>
#include <time.h>



// typedef int RUB;  // C
using RUB = long long int;  // C++



struct Friends {
    RUB rest;
};



struct Car {
    RUB value;
    RUB gas;
};



struct Cat {
    RUB Proplan;
};



struct tax_servise {
    RUB salary_tax;
};



struct House {
    RUB fixed_costs;
};



struct Person {
    RUB salary;
    RUB capital;
    RUB food;
    RUB gambling;
    RUB savings;
    RUB salary_tax;
    Cat cat;
    Car car;
    RUB fixed_costs;
    RUB rest;
};
struct Person alice;



void alice_init()
{
    alice.capital = 500'000;
    alice.salary = 380'000;
    alice.food = 15'000;
    alice.gambling = 5'000;
    alice.savings = 0;
    alice.salary_tax = 68'400;
    alice.car.value = 2'400'000;
    alice.car.gas = 12'000;

    alice.cat.Proplan = 60;
    alice.fixed_costs = 7'000;
    alice.rest = 10'000;
}



float sberbank_interest(RUB sum)
{
    if (sum > 10'000 and sum < 3'000'000) {
        return 11.5;
    }

    if (sum >= 3'000'000) {
        return 12.5;  
    }

    return 0.1;
}



void alice_salary(const int year, const int month) // Зп 
{
    RUB old_salary = alice.salary;
    if (month == 3 and year == 2026) {
        alice.salary *= 1.5;
         printf("Повышение зарплаты! Было: %lld, стало: %lld\n", old_salary, alice.salary);
    }
        
    alice.capital += alice.salary;
     printf("Месяц %d.%d: + Зарплата: %lld руб. (капитал: %lld руб.)\n", month, year, alice.salary, alice.capital);
}



void alice_taxes(const int month) // Подоходный налог
{
     alice.capital -= alice.salary_tax;
       printf("Месяц %d: - Налог: %lld руб. (капитал: %lld руб.)\n", month, alice.salary_tax, alice.capital);
}



void alice_fixed_costs(const int month) // Плата за жилье
{
    alice.capital -= alice.fixed_costs;
    printf("Месяц %d: - Коммунальные: %lld руб. (капитал: %lld руб.)\n", month, alice.fixed_costs, alice.capital);
}



void alice_food() // Расходы на еду
{
    alice.capital -= alice.food;
    printf("- Еда: %lld руб. (капитал: %lld руб.)\n", alice.food, alice.capital);
}



void alice_cat() // Расходы на кота
{
    alice.capital -= alice.cat.Proplan;
    printf("- Корм для кота: %lld руб. (капитал: %lld руб.)\n", alice.cat.Proplan, alice.capital);
}



void alice_car() // Расходы на машину
{
    alice.capital -= alice.car.gas;
     printf("- Бензин: %lld руб. (капитал: %lld руб.)\n", alice.car.gas, alice.capital);
}



void Friends_rest(const int month) // Расходы на встречи с друзьями
{
    
    int chance = rand() % 100 + 1; // Случайный шанс от 1 до 100
    
    if (chance <= 75) { // 75% шанс пойти с друзьями
        alice.capital -= alice.rest;
        printf("Месяц %d: - Встреча с друзьями (шанс %d%%): %lld руб. (капитал: %lld руб.)\n", 
               month, chance, alice.rest, alice.capital);
    } else {
        printf("Месяц %d: Встреча с друзьями отменяется (шанс %d%%)\n", month, chance);
    }
}



void alice_gambling(const int month) // Игровая зависимость
{
    alice.capital -= alice.gambling;
    printf("Месяц %d: - Лотереи: %lld руб. (капитал: %lld руб.)\n", month, alice.gambling, alice.capital);
}



void alice_bank_interest(const int month) // Вклад в банке
{
    float pp = sberbank_interest(alice.capital);
    RUB interest = alice.capital * (pp / 12.0 / 100.0);
    alice.capital += interest;
    printf("Месяц %d: + Банковский процент (%.1f%%): %lld руб. (капитал: %lld руб.)\n", 
           month, pp, interest, alice.capital);
}



void alice_savings(const int month) // Сбережения
{
    RUB saved = alice.salary * 0.1;
    alice.savings += saved;
    printf("Месяц %d: Отложено в сбережения: %lld руб. (всего сбережений: %lld руб.)\n", 
           month, saved, alice.savings);
}



void alice_trip(const int year, const int month) { // Путешествие
    static RUB trip_savings = 0; 
    trip_savings += 5000;
    printf("Месяц %d.%d: Накопление на путешествие: +5000 руб. (всего: %lld руб.)\n", 
           month, year, trip_savings);
    
    if(trip_savings >= 200'000) {
        alice.capital -= 200'000;
        printf("***** ПУТЕШЕСТВИЕ! Потрачено 200,000 руб. (капитал: %lld руб.) *****\n", alice.capital);
        trip_savings = 0;
    }
}

void alice_casino(const int month) // Казино
{ 
    // Начало игры только если есть деньги
    if (alice.capital <= 0) return;
    
    // Максимальное и минимальное значение ставки
    RUB max_bet = (alice.capital > 5000) ? 5000 : alice.capital / 10;
    RUB min_bet = (alice.capital > 1000) ? 1000 : 100;
    
    if (max_bet < min_bet) return; // Недостаточно денег для игры
    
    // Рандомное значение ставки
    RUB bet = min_bet + (rand() % (max_bet - min_bet + 1));
    
    // Рандомное число от 1 до 10 для игры
    int alice_number = rand() % 10 + 1;
    
    // Рандомное число приводящее к выйгрышу
    int winning_number = rand() % 10 + 1;
    
    printf("Month %d - Casino: Bet = %lld RUB, Alice's number = %d, ", month, bet, alice_number);
    
    if (alice_number == winning_number) {
        RUB win_amount = bet * 5;
        alice.capital += win_amount;
        printf("WIN! +%lld RUB (winning number was %d)\n", win_amount, winning_number);
    } else {
        alice.capital -= bet;
        printf("LOSE! -%lld RUB (winning number was %d)\n", bet, winning_number);
    }
}



void alice_simulation()
{
    int year = 2026;
    int month = 2;
    


    while ( not (year == 2027 and month == 2) ) {

        alice_savings(month);
        alice_casino(month);
        alice_trip(year, month);
        alice_food();
        alice_car();
        alice_cat();
        alice_gambling(month);
        alice_taxes(month);
        alice_bank_interest(month);
        alice_salary(year, month);
        alice_fixed_costs(month);
        Friends_rest(month);
        
        ++month;
        if (month == 13) {
            ++year;
            month = 1;
        }
    }
}



void print_results()
{
    printf("Salary = %lld\n", alice.salary);
    printf("Capital = %lld", alice.capital);
    printf("Savings = %lld" , alice.savings);
}



void print_spending_summary() 
{
    printf("\n\n========== ИТОГИ ПО ТРАТАМ АЛИСЫ (Февраль 2026 - Февраль 2027) ==========\n");
    printf("========================================================================\n");
    
    // Расчеты на основе исходных данных
    int total_months = 13; // Фев 2026 - Фев 2027 (13 месяцев)
    
    long long int total_food = alice.food * total_months;
    long long int total_gambling = alice.gambling * total_months;
    long long int total_tax = alice.salary_tax * total_months;
    long long int total_fixed_costs = alice.fixed_costs * total_months;
    long long int total_car_gas = alice.car.gas * total_months;
    long long int total_cat_food = alice.cat.Proplan * total_months;
    long long int total_rest = alice.rest * 10; // 75% шанс, примерно 10 месяцев из 13
    
    // Расчет зарплаты (с учетом повышения в марте 2026)
    long long int total_salary = 0;
    for (int i = 0; i < total_months; i++) {
        if (i == 1) // Март 2026 (второй месяц)
            total_salary += alice.salary * 1.5;
        else
            total_salary += alice.salary;
    }
    
    // Расчет банковских процентов (приблизительно)
    long long int total_interest = alice.capital * 0.115; // ~11.5% годовых
    
    printf("================== РАСХОДЫ ==================\n");
    printf("Категория            | Сумма (руб.) | %% от всех расходов\n");
    printf("--------------------|--------------|-------------------\n");
    printf("Продукты питания     | %'12lld | %.1f%%\n", total_food, (total_food * 100.0) / (total_food + total_gambling + total_tax + total_fixed_costs + total_car_gas + total_cat_food + total_rest));
    printf("Игровая зависимость  | %'12lld | %.1f%%\n", total_gambling, (total_gambling * 100.0) / (total_food + total_gambling + total_tax + total_fixed_costs + total_car_gas + total_cat_food + total_rest));
    printf("Налоги               | %'12lld | %.1f%%\n", total_tax, (total_tax * 100.0) / (total_food + total_gambling + total_tax + total_fixed_costs + total_car_gas + total_cat_food + total_rest));
    printf("Коммунальные платежи | %'12lld | %.1f%%\n", total_fixed_costs, (total_fixed_costs * 100.0) / (total_food + total_gambling + total_tax + total_fixed_costs + total_car_gas + total_cat_food + total_rest));
    printf("Бензин               | %'12lld | %.1f%%\n", total_car_gas, (total_car_gas * 100.0) / (total_food + total_gambling + total_tax + total_fixed_costs + total_car_gas + total_cat_food + total_rest));
    printf("Корм для кота        | %'12lld | %.1f%%\n", total_cat_food, (total_cat_food * 100.0) / (total_food + total_gambling + total_tax + total_fixed_costs + total_car_gas + total_cat_food + total_rest));
    printf("Встречи с друзьями   | %'12lld | %.1f%%\n", total_rest, (total_rest * 100.0) / (total_food + total_gambling + total_tax + total_fixed_costs + total_car_gas + total_cat_food + total_rest));
    printf("--------------------|--------------|-------------------\n");
    
    long long int total_expenses = total_food + total_gambling + total_tax + total_fixed_costs + total_car_gas + total_cat_food + total_rest;
    printf("ВСЕГО РАСХОДОВ      | %'12lld | 100.0%%\n", total_expenses);
    
    printf("\n================== ДОХОДЫ ==================\n");
    printf("Категория            | Сумма (руб.)\n");
    printf("--------------------|--------------\n");
    printf("Зарплата (с учетом повышения) | %'12lld\n", total_salary);
    printf("Банковские проценты (примерно) | %'12lld\n", total_interest);
    printf("--------------------|--------------\n");
    printf("ВСЕГО ДОХОДОВ       | %'12lld\n", total_salary + total_interest);
    
    printf("\n================== ФИНАЛЬНЫЙ БАЛАНС ==================\n");
    printf("Начальный капитал: %'lld руб.\n", 500000);
    printf("Всего доходов:     %'lld руб.\n", total_salary + total_interest);
    printf("Всего расходов:    %'lld руб.\n", total_expenses);
    printf("------------------------------------------------\n");
    printf("Ожидаемый капитал: %'lld руб.\n", 500000 + (total_salary + total_interest) - total_expenses);
    printf("Фактический капитал из программы: %'lld руб.\n", alice.capital);
    printf("Разница (из-за казино и случайностей): %+'lld руб.\n", alice.capital - (500000 + (total_salary + total_interest) - total_expenses));
    
    printf("\n================== РАСХОДЫ ПО МЕСЯЦАМ ==================\n");
    printf("Месяц       | Еда     | Налоги  | Коммун. | Бензин  | Кот     | Казино  | Друзья  | Всего\n");
    printf("------------|---------|---------|---------|---------|---------|---------|---------|--------\n");
    
    for (int m = 0; m < total_months; m++) {
        char month_name[10];
        int month_num = (2 + m) % 12;
        if (month_num == 0) month_num = 12;
        
        const char* months[] = {"Янв", "Фев", "Мар", "Апр", "Май", "Июн", "Июл", "Авг", "Сен", "Окт", "Ноя", "Дек"};
        
        long long int month_food = alice.food;
        long long int month_tax = alice.salary_tax;
        long long int month_fixed = alice.fixed_costs;
        long long int month_gas = alice.car.gas;
        long long int month_cat = alice.cat.Proplan;
        long long int month_gambling = alice.gambling;
        long long int month_rest = (rand() % 100 < 75) ? alice.rest : 0; // 75% шанс
        
        printf("%s %d     | %'6lld | %'6lld | %'6lld | %'6lld | %'6lld | %'6lld | %'6lld | %'6lld\n",
               months[month_num-1], 2026 + (m/12), 
               month_food, month_tax, month_fixed, month_gas, month_cat, month_gambling, month_rest,
               month_food + month_tax + month_fixed + month_gas + month_cat + month_gambling + month_rest);
    }
}



int main()
{
    alice_init();

    srand(time(NULL));
    
    alice_simulation();
    
    print_results();

    print_spending_summary();

    return 0;
}