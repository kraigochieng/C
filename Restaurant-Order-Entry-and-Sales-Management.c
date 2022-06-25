/*

The program is an order entry and sales management app for a restaurant. It has the following structure:
1. Add order
2. Manage Sales

The "Add order" choice does the following:
1. Item choice
2. Price calculation
3. Receipt printing

The "Manage Sales" choice has the following choices:
1. Total sales - will display the total sales of the restaurant
2. Sales By Food Item - allows one to determine the total sales for a particular item based on their preferred food item
3. Sales By Payment Type - allows one to determine the total sales made by a particular payment type based on their preferred payment type

The program is meant to stay open for a whole day. In order to close it, a password by the admin is required.

PASSWORD: @K13andA

The file "totals.txt" stores the data for the day and to be manually transferred to the books

*/

#include <stdio.h>
#include <time.h>

#define FOOD_ITEMS 7 // NUMBER OF FOOD ITEMS ON LIST
#define CUSTOMER_SIZE 100 // MAXIMUM NUMBER OF CUSTOMERS POSSIBL
#define PAYMENT_TYPE 3 // NUMBER OF TYPES OF PAYMENT

int i; // Count variable
int oc=0; // Order count
int foc; // File order count
int ic=0; // Item count
int mm_ch, cm_ch, fm_ch, sm_ch; // Menu options
int yn; // Yes/No questions
char password[8] = "@K13andA"; // To keep system live until kept by admin
char pass_entry[15];
float sum_of_totals, sum_of_food_total, sum_of_payment_total; // Total sum for all orders

int ft_no, pt_no;

struct items
{
    int no;
    float unit_price;
    float price;
    int quantity;
};

struct orders
{
    struct items item[CUSTOMER_SIZE];
    float total_price;
    int payment_no;
    int payment_price;
    int payment_balance;
    float vat;
    float ctl;
} order[CUSTOMER_SIZE];

// Incase of any changes in the items, modify here
char item_name[FOOD_ITEMS][15]={"Chapati", "Ndengu", "Rice plain", "Pilau", "Beef stew", "Chicken", "Cabbage"}; // Food list
int item_price[FOOD_ITEMS]={10,30, 50, 60, 50, 60, 10}; // Food prices
char payment_arr[PAYMENT_TYPE][10]={"Cash","Mpesa","Card"};

FILE *tt;

void pass();
void payment_total_menu();
void payment_total_choice();
void food_total_menu();
void food_total_choice();
void total_total();
void sales_menu();
void sales_menu_choice();
void food_menu();
void food_menu_choice();
void main_menu();
void main_menu_choice();
void payment();
void payment_choice();
void payment_figure();
void receipt();

void main()
{
    main_menu();
}
void pass()
{
    printf("ENTER PASSWORD: ");
    scanf("%s",pass_entry);
    if(pass_entry==password)
    {
        printf("\nPROGRAM CLOSED\n");
    }
    else
    {
        printf("\nINVALID PASSWORD\n");
        pass();
    }
}

void payment_total_choice()
{
    sum_of_payment_total = 0;// it has to be reset since it to keep prevent accumulation
    printf("\nEnter choice no.: ");
    scanf("%d", &pt_no);
    if (pt_no>PAYMENT_TYPE)
    {
        printf("\nINVALID CHOICE\n");
        payment_total_choice();
    }
    else
    {
        for(i=0;i<(oc+1);i++) // To loop through the orders only since the
        {
            if(order[i].payment_no==pt_no)
            {
                sum_of_payment_total += order[i].total_price;
            }
        }
        printf("\n...........................\n");
        printf("%s(TOTAL): Kshs. %.2f", payment_arr[(pt_no-1)], sum_of_payment_total);
        printf("\n...........................\n");
        sales_menu();
    }

}
void payment_total_menu()
{
    printf("\nPayment Type\n");
    printf("------------\n");
    for(i=0;i<PAYMENT_TYPE;i++)
    {
        printf("%d. %s\n",i+1,payment_arr[i]);
    }
    payment_total_choice();
}

void food_total_choice()
{
    int k; // this count variable is for the nested for loop
    sum_of_food_total = 0;
    printf("\nEnter choice no.: ");
    scanf("%d", &ft_no);
    if(ft_no>FOOD_ITEMS)
    {
        printf("\nINVALID CHOICE\n");
        food_total_choice();
    }
    else
    {
        for(i=0;i<(oc+1);i++) // To loop through the orders
        {
            for(k=0;k<(ic+1);k++)  // To loop through the items
            {
                if(order[i].item[k].no==ft_no)
                {
                    sum_of_food_total += order[i].item[k].price;
                }
            }
        }
        printf("\n...........................\n");
        printf("\n%s(TOTAL): Kshs. %.2f", item_name[(ft_no-1)], sum_of_food_total);
        printf("\n...........................\n");
        sales_menu();
    }
}

void food_total_menu()
{
    printf("\nSALES BY FOOD ITEM\n");
    printf("------------------------------------------------------------\n");
    printf("   NAME\n");
    for(i=0; i<FOOD_ITEMS; i++)
    {
        printf("%d. %s\n", i+1,item_name[i]);
    }
    food_total_choice();
}

void total_total()
{
    printf("\nTOTAL SALES: Kshs. %.2f\n",sum_of_totals);
    sales_menu();
}
void sales_menu_choice()
{
    printf("\nEnter choice no.: ");
    scanf("%d", &sm_ch);
    switch(sm_ch)
    {
        case 0:
            main_menu();
            break;
        case 1:
            total_total();
            break;
        case 2:
            food_total_menu();
            break;
        case 3:
            payment_total_menu();
            break;
        default:
            printf("\nINVALID CHOICE\n");
            sales_menu_choice();
            break;
    }
}

void sales_menu()
{
    printf("\nSALES MENU\n");
    printf("------------------------------------------------------------\n");
    printf("1. Total Sales\n");
    printf("2. Sales by Food Item\n");
    printf("3. Sales by Payment Type\n");
    printf("0. Back to Main Menu\n");
    sales_menu_choice();
}
void receipt()
{
    printf("\nRECEIPT\n");
    printf("------------------------------------------------------------\n");
    time_t t =time(0);
    char *now = ctime(&t);
    printf("\nDATE AND TIME: %s\n", now);
    printf("..................................................................\n");
    printf("NO\tITEM NAME    UNIT PRICE    QUANTITY    TOTAL PRICE\n");
    printf("..................................................................\n");
    for(i=0;i<(ic+1);i++)
    {
        printf("%d\t%-17s%-14.2f%-12d%.1f0\n", i+1,item_name[(order[oc].item[i].no)-1], 0.82 * order[oc].item[i].unit_price, order[oc].item[i].quantity, 0.82 * order[oc].item[i].price);
    }
    printf("           ............................................\n");
    printf("                        SUBTOTAL: Kshs. %.1f0\n", 0.82 * order[oc].total_price);
    printf("            VALUE ADDED TAX(16%%): Kshs. %.1f0\n",order[oc].vat);
    printf("               CATERING LEVY(2%%): Kshs. %.1f0\n",order[oc].ctl);
    printf("           ............................................\n");
    printf("                     TOTAL PRICE: Kshs. %.1f0\n", order[oc].total_price);
    printf("           ............................................\n");
    printf("                         PAID BY: %s\n",payment_arr[(order[oc].payment_no)-1]);
    printf("                     AMOUNT PAID: Kshs. %d\n", order[oc].payment_price);
    printf("                         BALANCE: Kshs. %d\n", order[oc].payment_balance);
    printf("           ............................................\n");
    printf("              Email: vrkibandaski@gmail.com\n");
    printf("                 Telephone: +25412345678\n");
    printf(".......................................................................\n\n");
    printf("       THANK YOU FOR EATING AT VILLA ROSA KIBANDASKI\n\n");
}

void payment_figure()
{
    printf("\nEnter amount paid: ");
    scanf("%d",&order[oc].payment_price);
    if (order[oc].payment_price <  order[oc].total_price)
    {
        printf("\nINSUFFICIENT PAYMENT, total is %f\n", order[oc].total_price);
        payment_figure();
    }
    else
    {
        order[oc].payment_balance = order[oc].payment_price - order[oc].total_price;
    }


}
void payment_choice()
{
    printf("\nEnter choice no.: ");
    scanf("%d",&order[oc].payment_no);

    if (order[oc].payment_no>PAYMENT_TYPE)
    {
        printf("\nINVALID CHOICE\n");
        payment_choice();
    }
    else
    {
        payment_figure();
    }

}
void payment()
{
    printf("\nPayment Type\n");
    printf("------------\n");
    for(i=0;i<PAYMENT_TYPE;i++)
    {
        printf("%d. %s\n",i+1,payment_arr[i]);
    }
    payment_choice();
}

void add_item()
{
    printf("Add item? 1 for YES, 2 for NO\n");
    scanf("%d", &yn);
    switch(yn)
    {
        case 1:
            ic++; // For next item of same order

            food_menu_choice();
            break;
        case 2:

            // Calculation of totals of totals
            sum_of_totals += order[oc].total_price;

            // To store all total prices in a file
            tt = fopen("totals.txt" ,"a");
            fprintf(tt,"\n%d %.2f",oc+1,order[oc].total_price);
            fclose(tt);
            payment();
            receipt();
            oc++;
            ic = 0; // To reset item count to 0 for the new order
            printf("\nORDER COMPLETE!\n");
            main_menu();
            break;
        default:
            printf("\nINVALID CHOICE\n");
            add_item();
            break;
    }
}

void food_menu_choice()
{

    printf("\nEnter item no.: ");
    scanf("%d",&order[oc].item[ic].no); // number on menu

    if (order[oc].item[ic].no>FOOD_ITEMS) // To ensure that a number that is input is on the menu
    {
        food_menu_choice();
    }
    else
    {
        printf("\nEnter quantity.: ");
        scanf("%d",&order[oc].item[ic].quantity); // quantity

        order[oc].item[ic].unit_price = item_price[(order[oc].item[ic].no)-1];

        order[oc].item[ic].price = order[oc].item[ic].unit_price * order[oc].item[ic].quantity; // price

        order[oc].total_price += order[oc].item[ic].price; //t.price

        order[oc].vat = 0.16 * order[oc].total_price;
        order[oc].ctl = 0.02 * order[oc].total_price;

        add_item(); // add item
    }


}

void food_menu()
{
    printf("\nFOOD MENU\n");
    printf("------------------------------------------------------------\n");
    printf("   NAME        PRICE\n");
    for(i=0; i<FOOD_ITEMS; i++)
    {
        printf("%d. %s\t%d\n", i+1,item_name[i],item_price[i]);
    }
    food_menu_choice();
}

void main_menu_choice()
{
    printf("\nEnter choice no.: ");
    scanf("%d",&mm_ch);
    switch(mm_ch)
    {
        case 0:
            pass();
            break;
        case 1:
            food_menu();
            break;
        case 2:
            sales_menu();
            break;
        default:
            printf("INVALID CHOICE\n");
            main_menu_choice();
            break;
    }

}

void main_menu()
{
    printf("\nMAIN MENU\n");
    printf("------------------------------------------------------------\n");
    printf("1. Add order\n");
    printf("2. Manage sales\n");
    printf("0. Exit program\n");
    main_menu_choice();
}
