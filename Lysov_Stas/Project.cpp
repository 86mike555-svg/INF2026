#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>
using namespace std;

// typedef int RUB;  // C
using RUB = long long int;  // C++
using BUB = long double;

struct Expenses {
    string name;
    RUB value;
    string date;
};

struct Income {
    string name;
    RUB value;
    string date;
};

struct Wallet {
    vector<Income> income;
    vector<Expenses> expenses;
    BUB balance;
	BUB salary;
};

struct Car {
    RUB value;
};

struct Person {
    RUB capital;
    Wallet wallet;
    Car car;
    RUB house_value;
};
struct Person alice;

void alice_init()
{
    alice.wallet.balance = 180'000;
	alice.wallet.salary = 150'000;

	alice.car.value = 2'000'000;
    alice.house_value = 4'000'000;

    alice.capital = alice.wallet.balance + alice.car.value + alice.house_value;
}

void expenses_init(string name, RUB value, string date)
{
    Expenses exp{ name, value, date };
    alice.wallet.expenses.push_back(exp);
    alice.wallet.balance -= value;

    cout << "Expense added!\n";
}

void income_init(string name, RUB value, string date)
{
    Income inc{ name, value, date };
    alice.wallet.income.push_back(inc);
    alice.wallet.balance += value;
    cout << "Income added!\n";
}

void alice_salary()
{
    alice.wallet.balance += alice.wallet.salary;
}

float sberbank_interest(RUB sum)   // Сделать sum 
 {
     if (sum > 10'000 and sum < 3'000'000) {
         return 11.5;
     }

     if (sum >= 3'000'000) {
         return 12.5;  //  125 -1 +
     }

     return 0.1;
 }

 void alice_bank_interest()
 {
     float pp;
     pp = sberbank_interest(alice.capital);
     alice.capital += alice.capital * (pp / 12.0 / 100.0);
 }

 void alice_simulation()
 {
     int year = 2026;
     int month = 2;

     while ( not (year == 2027 and month == 2) ) {
         // my_cat();
         // my_trip();
         alice_bank_interest();
         alice_salary();

         ++month;
         if (month == 13) {
             ++year;
             month = 1;
         }
     }
 }

 void financial_report()
 {
     cout << "\n_________ FINANCIAL REPORT _________\n";
     cout << "Wallet balance: " << alice.wallet.balance << endl;
     cout << "Bank capital: " << alice.capital << endl;
     cout << "Car value: " << alice.car.value << endl;
     cout << "House value: " << alice.house_value << endl;

     cout << "Total net worth: "
         << alice.wallet.balance
         + alice.capital
         + alice.car.value
         + alice.house_value
         << endl;
 }


int main()
{
    alice_init();
    int sizexp = 0;
    cout << "Capital: " << alice.wallet.balance + alice.car.value + alice.house_value << endl;

    while (true)
    {
        string operations;
        cout << "Enter operations (Add_expense, Add_income, Check_balance, Report): ";
        cin >> operations;

        if (operations == "Add_expense") {
            string name_expense;
            cout << "Name of expense: ";
            cin >> name_expense;

            RUB value_expense;
            cout << "Value of expense: ";
            cin >> value_expense;

            string date_expense;
            cout << "Date of expense: ";
            cin >> date_expense;

           
         

            expenses_init(name_expense, value_expense, date_expense);
            cout << "Expense added! ";

        }
        else if (operations == "Add_income") {
            string name_income;
            cout << "Name of income: ";
            cin >> name_income;

            RUB value_income;
            cout << "Value of income: ";
            cin >> value_income;

            string date_income;
            cout << "Date of income: ";
            cin >> date_income;

            income_init(name_income, value_income, date_income);
            cout << "Income added! ";
        }
        else if (operations == "Check_balance") {
            cout << "Current balance: "
                << alice.wallet.balance
                << endl;
		}
        else if (operations == "Report") {
            financial_report();
        }
        
        else {
            cout << "Invalid operation!" << endl;
        }
    }

}



//bool create_csv_if_not_exists(const std::string& filename) {
 //    ifstream check(filename);
 //    if (check.good()) {
 //        check.close();
 //        return false; // файл уже есть
 //    }

 //    ofstream file(filename);
 //    if (!file.is_open()) {
 //        throw std::runtime_error("не удалось создать файл: " + filename);
 //    }

 //     //заголовок csv (по желанию)
 //    file << "name,value,date\n";
 //    return true; // файл создан
 //}
 //void create_csv(const string& namef, const string& data)
 //{
 //    if (namef.empty()) return;

 //    ofstream file(namef, ios::app); // append, чтобы не затирать файл
 //    if (file.is_open()) {
 //        file << data;
 //    }
 //}
// Узнать, как сделать файл для хранения данных, и как его использовать для сохранения данных о доходах и расходах.
