#include <stdio.h>
#include <string.h>
int main()
{
    struct date {
	int year;
	int month;
	int day;
    };
    struct person {
	char name[32]; 
	struct date birthday;
	struct date inauguration;
    };
    struct person friend;

    strcpy(friend.name, "George Washington"); 
    friend.birthday.year = 1732;
    friend.birthday.month = 2;
    friend.birthday.day = 22;

    printf("My friend %s was born on %d/%d/%d\n",friend.name, friend.birthday.day,friend.birthday.month, friend.birthday.year);

    return(0);
}
