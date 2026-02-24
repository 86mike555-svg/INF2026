#include <stdio.h>


//|--------------------ТИПЫ ДАННЫХ-----------------------|

using RUB = long long int;      //тип данных для операций в рублях
using USD = long long int;      //тип данных для операций в долларах

using Percent = float;          //тип данных для процентов (1-100%)


//|--------------------СТРУКТУРЫ-----------------------|

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


//|--------------------ФУНКЦИИ-----------------------|

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


//НИК

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


//ДЖУДИ

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


// ОГРОМНАЯ ФУНКЦИЯ ЖИЗНЕННЫХ СОБЫТИЙ НИКА УАЙЛДА (имитирует хаотичную жизнь в Зверополисе, события влияют на баланс, бизнес или текущие расходы)

void nick_life_events(int month, int year) {
    
    int event_id = (month * 17 + year * 3) % 40;    //просто формула для выбора события (без использования rand()), имитирует "случайные" события

    printf("  [NICK STORY]: ");

    switch (event_id) {
    case 0:
        printf("Nik prodal partiyu 'Lapo-ledentsov' slonam. +15000 RUB\n");
        nick.zoobank.account += 15000;
        break;
    case 1:
        printf("Vstretil Blica na pochte. Poteryal ves' den' v ocheredi. Business prostoial. -3000 RUB\n");
        nick.zoobank.account -= 3000;
        break;
    case 2:
        printf("Mister Big prigrozil za starye dolgi. Prishlos' otdat' 'protsent za uvazhenie'. -12000 RUB\n");
        nick.zoobank.account -= 12000;
        break;
    case 3:
        printf("Dzhudi pomogla zakryt' shtrafy Nika po staroy druzhbe. +5000 RUB\n");
        nick.zoobank.account += 5000;
        break;
    case 4:
        printf("Nik nashel skidku na syr dlya pitstsy. Pribyl' 'Nikiccy' rastet!\n");
        nick.nikizza.monthly_profit += 2000;
        break;
    case 5:
        printf("Furgon slomalsya pryamo posredi dorogi. Srochnyy remont dvigatelya. -25000 RUB\n");
        nick.zoobank.account -= 25000;
        break;
    case 6:
        printf("Nik pereprodal bilet v operu baranu-mafiose. +8500 RUB\n");
        nick.zoobank.account += 8500;
        break;
    case 7:
        printf("Nalogovaya inspektsiya proverila scheta 'Nikiccy'. Prishlos' zaplatit' nalog. -15000 RUB\n");
        nick.zoobank.account -= 15000;
        break;
    case 8:
        printf("Vypala nevidannaya udacha v ulichnuyu lotereyu 'Hvost Udachi'! +10000 RUB\n");
        nick.zoobank.account += 10000;
        break;
    case 9:
        printf("Nik kupil novyy dorogoy galstuk dlya vstrechi s investorami. -4500 RUB\n");
        nick.zoobank.account -= 4500;
        break;
    case 10:
        printf("doch' Mistera Biga stala postoyannym klientom. Pribyl' rastet! +5000 RUB\n");
        nick.nikizza.monthly_profit += 5000;
        break;
    case 11:
        printf("Nik reshil s'ekonomit' na nalogakh, no ego poimali. Shtraf! -20000 RUB\n");
        nick.zoobank.account -= 20000;
        break;
    case 12:
        printf("Vygodnyy obmen valyuty u podpol'nykh dilerov v ruyone Tundratown. +1000 USD\n");
        nick.zoobank.account_usd += 1000;
        break;
    case 13:
        printf("Nik kupil stil'nye ochki, chtoby vyglyadet' solidnee. -7000 RUB\n");
        nick.zoobank.account -= 7000;
        break;
    case 14:
        printf("Sosedi pozhalovalis' na shum ot pechi dlya pitstsy. Vzyatka inspektoru. -5000 RUB\n");
        nick.zoobank.account -= 5000;
        break;
    case 15:
        printf("Dzhudi zabyla obed, i Nik ugostil ee koronnoiy pitstsey. -1000 RUB.\n");
        nick.zoobank.account -= 1000;
        break;
    case 16:
        printf("Nik nashel novogo postavshchika muki. Zatraty snizilis'.\n");
        nick.nikizza.monthly_profit += 3000;
        break;
    case 17:
        printf("Vystavka malogo biznesa v Zveropolise. Nik poluchil pochetnyy grant! +40000 RUB\n");
        nick.zoobank.account += 40000;
        break;
    case 18:
        printf("Kto-to skrutil zerkala s furgona Nika noch'yu. -4000 RUB\n");
        nick.zoobank.account -= 4000;
        break;
    case 19:
        printf("Glavnyy povar 'Nikiccy' ushel v otpusk. Ubytki. -6000 RUB\n");
        nick.zoobank.account -= 6000;
        break;
    case 20:
        printf("Nik zaregistriroval novyy brend 'Wild Pizza'. Investitsii v marketing. -15000 RUB\n");
        nick.nikizza.investment += 15000;
        break;
    case 21:
        printf("Krysha garazha protekla vo vremya dozhdya. Nuzhen remont. -5000 RUB\n");
        nick.zoobank.account -= 5000;
        break;
    case 22:
        printf("Selfi Nika s pitstsey stalo virusnym v setyakh. Reklama! +10000 RUB\n");
        nick.zoobank.account += 10000;
        break;
    case 23:
        printf("Nik popal v probku iz-za lenivtsev. Opovzdal na vazhnuyu sdelku. -3000 RUB\n");
        nick.zoobank.account -= 3000;
        break;
    case 24:
        printf("Mister Big podaril Niku staryy antikvarnyy shkaf. Tam byl taynik! +25000 RUB\n");
        nick.zoobank.account += 25000;
        break;
    case 25:
        printf("Zabastovka fermerov. Produkty dlya lichnoy zhizni podorozhali. -4000 RUB\n");
        nick.food += 4000;
        break;
    case 26:
        printf("Nik vyigral v kosti u odnogo uprytogo barana. +15000 RUB\n");
        nick.zoobank.account += 15000;
        break;
    case 27:
        printf("Nochnoe ograblenie furgona! Vorishki vskryli seyf. -12000 RUB\n");
        nick.zoobank.account -= 12000;
        break;
    case 28:
        printf("Nik reshil stat' fut-blogerom i kupil doroguyu kameru. -30000 RUB\n");
        nick.zoobank.account -= 30000;
        break;
    case 29:
        printf("Bol'shoy zakaz dlya morskikh svinok. 100 mini-pitsts! +10000 RUB\n");
        nick.zoobank.account += 10000;
        break;
    case 30:
        printf("Nik nashel na svalke rariternuyu zapchast' i prodal ee kollektsioneru. +7000 RUB\n");
        nick.zoobank.account += 7000;
        break;
    case 31:
        printf("Odin iz kuryerov Nika poteryal sumku s den'gami. -5000 RUB\n");
        nick.zoobank.account -= 5000;
        break;
    case 32:
        printf("Nik organizoval ulichnyy kvest dlya turistov. +9000 RUB\n");
        nick.zoobank.account += 9000;
        break;
    case 33:
        printf("Kholodil'nik v 'Nikicce' vyshel iz stroya. Produkty isportilis'. -8000 RUB\n");
        nick.zoobank.account -= 8000;
        break;
    case 34:
        printf("Nik sluchayno pomog staromu slonu pereyti dorogu. Poluchil chaevye. +1000 RUB\n");
        nick.zoobank.account += 1000;
        break;
    default:
        printf("Obychnyy den' ulichnogo lisa. Nik prosto gulyal i dumal o budushchem.\n");
        break;
    }
}


void simulation()                               //функция всей симуляции
{
    int month = 2;
    int year = 2026;
    RUB deposit_at_start_of_year = judy.zoobank.deposite;

    while (not (month == 3 and year == 2031)) {

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
        nick_life_events(month, year);  //те рандомные события в жизни Ника
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
