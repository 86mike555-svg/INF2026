#include <cstdio>

using RUB = long long;

struct Cat {
    RUB value;
    RUB food;
};

struct Car {
    RUB value; 
	RUB gas;   
};

struct Bank {
	RUB checking; 
	RUB deposit;  
	double deposit_apr; 
};


struct Person {
    RUB salary; 
    RUB food;   
	Car car;    
	Cat cat;    
	Bank bank;  
};

Person Alice;

const double inflation_apr = 5.0; // Годовая инфляция 5%
const RUB checking_buffer = 250'000; // Минимальная сумма, которая должна оставаться на расчетном счете для покрытия расходов

double inflation_month = (inflation_apr / 100.0 / 12.0); // Месячная инфляция
double deposit_month = (Alice.bank.deposit_apr / 100.0 / 12.0); // Месячные проценты по вкладу

void alice_init() // Инициализация данных Алисы
{
	Alice.salary = 100'000; 

	Alice.food = 20'000; 

	Alice.car.value = 2'400'000; 
	Alice.car.gas = 15'000; 

	Alice.cat.value = 25'000; 
	Alice.cat.food = 5'000; 

	Alice.bank.checking = 0; 
	Alice.bank.deposit = 0; 
	Alice.bank.deposit_apr = 14.5; 
}

void alice_inflation_tick() // Инфляция повышает цены на все товары и услуги
{
	Alice.food *= (1.0 + inflation_month); 
	Alice.car.gas *= (1.0 + inflation_month); 
	Alice.car.value *= (1.0 + inflation_month); 

	Alice.cat.food *= (1.0 + inflation_month); 
	Alice.cat.value *= (1.0 + inflation_month); 
}

void alice_deposit_interest() // Алиса получает проценты по вкладу
{
	Alice.bank.deposit += Alice.bank.deposit * deposit_month; 
}

void alice_salary(int month, int year) // Алиса получает зарплату
{
	if ((month == 8) && (year == 2026)) 
	{
		Alice.salary *= 1.5; 
	}

	Alice.bank.checking += Alice.salary;
}

void alice_expenses_monthly() // Алиса оплачивает ежемесячные расходы
{
	if (Alice.bank.checking >= Alice.food)
	{
		Alice.bank.checking -= Alice.food;
	}
	else
	{
		Alice.bank.checking = 0;
	}

	if (Alice.bank.checking >= Alice.car.gas)
	{
		Alice.bank.checking -= Alice.car.gas;
	}
	else
	{
		Alice.bank.checking = 0;
	}

	if (Alice.bank.checking >= Alice.cat.food)
	{
		Alice.bank.checking -= Alice.cat.food;
	}
	else
	{
		Alice.bank.checking = 0;
	}
}

void alice_move_money_to_deposit() // Алиса переводит избыточные средства с расчетного счета на вклад
{
	if (Alice.bank.checking > checking_buffer) 
	{
		RUB amount = Alice.bank.checking - checking_buffer;
		Alice.bank.checking -= amount;
		Alice.bank.deposit += amount;
	}
}

void print_results() // Вывод результатов после моделирования
{
	printf("Salary = %lld\n", Alice.salary); 
	printf("Checking (bank) = %lld\n", Alice.bank.checking);
	printf("Deposit = %lld\n", Alice.bank.deposit); 
	printf("Total = %lld\n", (Alice.bank.checking + Alice.bank.deposit)); 

	printf("Food = %lld\n", Alice.food); 
	printf("Gas = %lld\n", Alice.car.gas); 
	printf("Cat food = %lld\n", Alice.cat.food); 

	printf("Car value = %lld\n", Alice.car.value); 
	printf("Cat value = %lld\n", Alice.cat.value); 
}

void simulation() // Моделирование финансовой жизни Алисы с февраля 2026 по март 2027
{
	int month = 2;
	int year = 2026;

	while (!((month == 3) && (year == 2027)))
	{
		alice_inflation_tick();
		alice_deposit_interest();
		alice_salary(month, year);
		alice_expenses_monthly();
		alice_move_money_to_deposit();

		++month;
		if (month == 13) {
			month = 1;
			++year;
		}
	}
}

int main() 
{
	alice_init();
	simulation(); 
	print_results(); 
}