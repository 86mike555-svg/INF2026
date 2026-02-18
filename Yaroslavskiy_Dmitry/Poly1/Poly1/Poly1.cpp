#include <stdio.h>


//ТИПЫ ДАННЫХ

using RUB = long long int;      //тип данных для операций в рублях
using USD = long long int;      //тип данных для операций в долларах

using Percent = float;          //тип данных для процентов (1-100%)


struct Bank {                   //структура банка
    RUB account;
    RUB deposite;
    USD account_usd;
    float rate_usd_rub;

    Percent interest;
   
};


struct Car {                    //структура автомобиля
    RUB gas;
    RUB value;
};


struct Business {               //структура бизнеса
    RUB investment;      // инвестиции в бизнес 
    RUB monthly_profit;  // текущая прибыль (за месяц) (+/-)
    float risk_factor;   // риски (0.0 - 1.0)
};

struct Loan {                   //структура кредита
    RUB body;            // тело кредита
    Percent interest;    // процент по кредиту
    int months_left;     // сколько месяцев осталось платить
};


struct Person {                 //структура Персонажа (главная!!!)
    Bank zoobank;
    Car car;
    RUB salary;
    RUB food;
};

struct NickPerson {      // отдельная структура для Персонажа Ник (главная!!!)
    Bank zoobank;
    Car car;             
    Business nikizza;   // бизнес пиццы "никицца"
    Loan credit;         // долги банку/Джуди
    RUB food;
    RUB fines;           // штрафы от полиции 
};
struct Person judy;             //Создание Персонажа Джуди;
struct NickPerson nick;             //Создание Персонажа Ник;


//ФУНКЦИИ
float key_rate(const int month, const int year);    //чтобы писать функции в любом порядке
float delta(const int month, const int year);


void judy_init()                            //функция инициализации Джуди
{
    //банковские счета
    judy.zoobank.account = 0;
    judy.zoobank.deposite = 1'000'000;
    judy.zoobank.interest=12.0;
    judy.salary = 180'000;

    judy.zoobank.account_usd = 1'000;
    judy.zoobank.rate_usd_rub = 78.5;

    //расходы на еду
    judy.food = 20'000;

    //машина (хорошая)
    judy.car.value = 2'400'000;
    judy.car.gas = 15'000;
}


void nick_init()
{
    //банковские счета
    nick.zoobank.account = 50'000;
    nick.zoobank.deposite = 0;
    nick.zoobank.interest = 0;

    nick.zoobank.rate_usd_rub = 78.5;

    //машина (старая развалюха)
    nick.car.value = 400'000;
    nick.car.gas = 10'000;

    //расходы на еду
    nick.food = 15'000;

    //бизнес "Никицца"
    nick.nikizza.investment = 200'000;
    nick.nikizza.monthly_profit = 40'000;       //базовая прибыль
    nick.nikizza.risk_factor = 0.3;             //30% шанс на неудачу

    //кредит (на бизнес)
    nick.credit.body = 300'000;
    nick.credit.interest = 18.0;         //высокий процент по кредиту (18%)
    nick.credit.months_left = 36;        //кредит на 3 года
}


void nick_business_logic(const int month, const int year)         //Ник зарабатывает на пицце
{
    // можно добавить rand() для изменения прибыли
    nick.zoobank.account += nick.nikizza.monthly_profit;
}

void nick_loan_payment()
{
    if (nick.credit.months_left > 0) {
        RUB monthly_payment = (nick.credit.body / 36) + (RUB)(nick.credit.body * (nick.credit.interest / 100 / 12));    //ежемесячный платеж

        nick.zoobank.account -= monthly_payment;
        nick.credit.months_left--;

        //усли денег не хватило, банк начисляет штраф, а долг растет
        if (nick.zoobank.account < 0) {
            nick.credit.body += 5000;
            printf("WARNING: Nick missed a loan payment in month %d!\n", nick.credit.months_left);
        }
    }
}

void nick_expenses()
{
    nick.zoobank.account -= nick.food;
    nick.zoobank.account -= nick.car.gas;
}


void inflation(const int month, const int year)        //функция инфляции
{
    //индексация в первом месяце года
    if (month == 1) {
        float rate = key_rate(month, year);
        float multiplier = (rate + 100.0) / 100.0;

        judy.salary = (RUB)(judy.salary * multiplier);          //увеличение зарплаты на ставку (индексация)
        judy.food = (RUB)(judy.food * multiplier);
        judy.car.gas = (RUB)(judy.car.gas * multiplier);

        judy.car.value = (RUB)(judy.car.value * 0.95);          //уменьшение стоимости машины Джуди


        nick.food = (RUB)(nick.food * multiplier);
        nick.car.gas = (RUB)(nick.car.gas * multiplier);
        nick.nikizza.monthly_profit = (RUB)(nick.nikizza.monthly_profit * multiplier);      //цены на пиццу растут со временем
        nick.car.value = (RUB)(nick.car.value * 0.90);          //уменьшение стоимости машины Ника (стареет быстрее чем у Джуди)
    }
}



void judy_salary(const int month, const int year)           //функция зарплаты Джуди
{
    if (month == 12) {
        judy.zoobank.account += judy.salary;  // 13th salary
    }

    judy.zoobank.account += judy.salary;
}


void judy_food()                            //функция еды Джуди
{
    judy.zoobank.account -= judy.food;
}


void judy_car()                             //функция машины Джуди
{
    judy.zoobank.account -= judy.car.gas;
}


// Вспомогательные функции для будущего расширения 
void judy_medine();
void judy_home();

float key_rate(const int month, const int year)              //функция ключевой ставки
{
    Percent percents_rate;
    if (year == 2026) percents_rate = 14.5;
    if (year == 2027) percents_rate = 12.5;
    if (year == 2028) percents_rate = 10;
    if (year == 2029) percents_rate = 7.5;
    if (year == 2030) percents_rate = 4;
    if (year == 2031) percents_rate = 4.5;
    return (percents_rate);
}

float delta(const int month, const int year)              //функция (ставка - % по депозиту или предложение по кредиту - ставка, 2026-2030гг)
{
    Percent percents_delta;
    if (year == 2026) percents_delta = 2.5;
    if (year == 2027) percents_delta = 2.5;
    if (year == 2028) percents_delta = 2;
    if (year == 2029) percents_delta = 1.5;
    if (year == 2030) percents_delta = 1;
    if (year == 2031) percents_delta = 1.5;
    return (percents_delta);
}


void judy_deposite(const int month, const int year)         //функция депозита Джуди в банке
{
    judy.zoobank.interest = key_rate(month, year) - delta(month, year);     //ключевая ставка - дельта ("комиссия" банка)

    judy.zoobank.deposite += (RUB)(judy.zoobank.deposite * (judy.zoobank.interest / 12.0 / 100.0));    //сложный процент

    judy.zoobank.deposite += judy.zoobank.account;
    judy.zoobank.account = 0;
}


void judy_freelance(const int month, const int year)            //функция подработки Джуди
{
    if (month == 3 and year == 2027) {
        judy.zoobank.account_usd += 3'000;
    }
}


/*void print_results(RUB deposit_at_start)                            //функция вывода результатов
{
    RUB capital = 0;
    RUB profit = judy.zoobank.deposite - deposit_at_start;
    capital += judy.zoobank.account;
    capital += judy.car.value;
    capital += judy.zoobank.deposite;
    capital += judy.zoobank.account_usd * judy.zoobank.rate_usd_rub;
    printf("Capital = %lld\n", capital);
    printf("Salary = %lld \n", judy.salary);
    printf("Deposit = %lld  ", judy.zoobank.deposite);
    printf("Interest on deposit = %.1f\n", judy.zoobank.interest);
    printf("Profit for the year = %lld \n", profit); // Вывод прибыли за год
    printf("Food expenses = %lld\n", judy.food);
}
*/


void print_judy_report(int month, int year, RUB deposit_at_start) {
    RUB profit = judy.zoobank.deposite - deposit_at_start;
    RUB total_assets = judy.zoobank.account + judy.zoobank.deposite +
        judy.car.value + (judy.zoobank.account_usd * judy.zoobank.rate_usd_rub);

    printf("\n.========================================================.\n");
    printf("|       OTCHET POLICII ZVEROPOLISA (OFFICER HOOPS)       |\n");
    printf("|--------------------------------------------------------|\n");
    printf("|   Mesyats: %02d, God: %d                               |\n", month-1, year);
    printf("|--------------------------------------------------------|\n");
    printf("| POKAZATEL'          | ZNACHENIE                        |\n");
    printf("|---------------------|----------------------------------|\n");
    printf("| Depozit (vklad)     | %15lld RUB              |\n", judy.zoobank.deposite);
    printf("| Valyuta ($)         | %15lld USD              |\n", judy.zoobank.account_usd);
    printf("|---------------------|----------------------------------|\n");
    printf("| Zarplata            | %15lld RUB              |\n", judy.salary);
    printf("| Produkty            | %15lld RUB              |\n", judy.food);
    printf("| Mashina (ocenka)    | %15lld RUB              |\n", judy.car.value);
    printf("|---------------------|----------------------------------|\n");
    printf("| PRIBIL' ZA GOD      | %15lld RUB              |\n", profit);
    printf("| ITOGO KAPITAL       | %15lld RUB              |\n", total_assets);
    printf("'========================================================'\n");
}


void print_nick_report(int month, int year) {
    printf("\n  _______________________________________________________  \n");
    printf(" /                                                       \\ \n");
    printf("|   DELISHKI NIKA UAYLDA (BUSINESS LOG)                   |\n");
    printf("|   Mesyats: %02d, God: %d                                |\n", month-1, year);
    printf("|  -----------------------------------------------------  |\n");
    printf("|   Nalichka v karmane:     %15lld RUB           |\n", nick.zoobank.account);
    printf("|   Pribil' s piccy:        %15lld RUB           |\n", nick.nikizza.monthly_profit);
    printf("|  -----------------------------------------------------  |\n");
    printf("|   DOLGI:                                                |\n");
    printf("|   Ostatok po kreditu:     %15lld RUB           |\n", nick.credit.body);
    printf("|   Mesyatsev platit':      %15d               |\n", nick.credit.months_left);
    printf("|  -----------------------------------------------------  |\n");
    printf("|   STATUS: %-30s                |\n", (nick.zoobank.account < 0 ? "VSE PLOHO (KOLLEKTORY!)" : "ZHIT' MOZHNO"));
    printf(" \\_______________________________________________________/ \n");
    printf("\n");
    printf("\n");
}


void simulation()                               //функция всей симуляции
{
    int month = 2;
    int year = 2026;
    RUB deposit_at_start_of_year = judy.zoobank.deposite;

    while (not (month == 3 and year == 2030)) {

        //--- Для Джуди ---//
        
        //повышение цен от инфляции и индексация зарплаты
        inflation(month, year);
        //получение зарплаты
        judy_salary(month, year);

        //judy_freelance(month, year);
        
        //вычитание расходов
        judy_food();
        judy_car();
        //
        // my_cat();
        // my_medine();
        // my_home();

        //проценты и перевод остатка на депозит
        judy_deposite(month, year);


        //--- Для Ника ---//
        nick_business_logic(month, year);
        nick_expenses();
        nick_loan_payment();

        ++month;
        if (month == 13) {
            printf("------------Year %d", year);
            printf(" Results:------------------------\n");
            printf("\n");
            printf("[JUDY STATUS]:\n");
            print_judy_report(month, year, deposit_at_start_of_year);
            printf("[NICK STATUS]:\n");
            print_nick_report(month, year);

            deposit_at_start_of_year = judy.zoobank.deposite;
            ++year;
            month = 1;
        }
    }
}


//ПРОГРАММА

int main()
{
    judy_init();

    nick_init();

    simulation();

}