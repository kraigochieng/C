#include <stdio.h>

void display_menu()
{
    printf("Please choose an instruction:\n");
    printf("1. Even or Odd number Checker\n");
    printf("2. Positive or Negative number Checker\n");
    printf("3. Number of Digits Checker\n");
    printf("4. Exit Program\n\n");
    printf("Type in the number of the option you would like:\n");
}

int check;

int isEven(int value)
{
    check = value % 2;
    if (check == 0)
    {
        printf("\n%d is an even number.\n", value);
    }
    else
    {
        printf("\n%d is an odd number.\n", value);
    }
}

int isPos(int value)
{
    check = value - 0;
    if (check > 0)
    {
        printf("\n%d is a positive number.\n", value);
    }
    else if (check < 0)
    {
        printf("\n%d is a negative number.\n", value);
    }
    else
    {
        printf("\n%d is neither a positive or a negative number.\n", value);
    }
}

int NumDigit(int value)
{
    check = value/10;
    int count = 1;
    while(check!=0)
    {
        count++;
        check = check/10;
    }
    printf("\n%d has %d digit(s)\n",value,count);
}

int get_input(int choice, int value)
{
    switch (choice)
    {
        case 1:
            isEven(value);
        break;

        case 2:
            isPos(value);
        break;

        case 3:
            NumDigit(value);
        break;

    }
}
main()
{
    static choice = 0;// To make the do...while loop work
    do
    {
        display_menu();
        int choice;
        scanf("%d",&choice);
        if (choice == 4)
        {
            printf("\nProgram Closed!\n");
            break;
        }
        else
        {
            while (choice>4)
            {
                printf("\nInvalid option. Choose a number from the menu above.\n");
                printf("Retry:\n");
                scanf("%d",&choice);
                if (choice == 4)
                {
                printf("\nProgram Closed!\n");
                break;
                }
            }
        int value;
        printf("\nEnter number to be evaluated:\n");
        scanf("%d",&value);
        get_input(choice,value);
        printf("\n\n");
        }
    }
    while(choice<4);
}


