#include <iostream>

int main()
{
	int year = 2026;
	int mounth = 2;
	int salary = 100000;
	int capital = 0;

	while(!(year == 2027 && mounth==2))
	{
		if(mounth==3)
		{
			salary *= 1.5;
		}
		capital += salary;

		++mounth;
		if(mounth == 13)
		{
			++year;
			mounth = 1;
		}
	}

	printf("salary = %d\n", salary);
	printf("capital = %d", capital);
}
