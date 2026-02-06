#include <stdio.h>  // <stdio.h> - библиотека .  #include - включить/добавить

int main()
{
    int year = 2026;
    int month = 2;

    int salary = 100'000;
    int capital = 0;

    //for (int month = 1; month < 13; ++month){ //++moth ;(=) moth++ ;(=) month = month + 1
    //while (year != 2027 || month != 2 ) { // || = or

    while ( ! (year == 2027 && month == 2 )) { //&& - and
    
        if (month==3){
            salary=(salary*1.5);
        }

        capital+=salary;

        ++month; // == month = month + 1

        if (month == 13) {
            ++year;
            month=1;
        }
    }
    //capital = 12* salary;

    printf("Salary = %d\n",salary); //\n- на новой строке
    printf("Capital = %d",capital); //%d

}