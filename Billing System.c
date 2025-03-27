#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//STRUCTURE FOR STORING ITEM DETAILS.
typedef struct
{
    char  NAME[30];
    int   QUANTITY;
    float UNIT_PRICE;
    float ITEM_TOTAL;
} item;

//CLEAR MY SCREEN.
void CLEAR_SCREEN()
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif   
}

//DECLARING FUNCTION TO PRINT THE BILL IN TERMINAL.
void PRINT_BILL_TERMINAL(item ar[], int x, float S_T, float V, float V_A, float T_A_V);

//DECLARING FUNCTION TO PRINT THE BILL IN .CSV FILE.
void PRINT_BILL_CSV(item ar[], int x, float S_T, float V, float V_A, float T_A_V);

//DECLARING FUNCTION TO PRITNT A SPERATOR BETWEEN BILL DETAILS.
void DIVIDER (void);

int main()
{
    //CLEAR SCREEN BEFORE STARTING PROGRAM.
    CLEAR_SCREEN();

    //DECLARING AN ARRAY OF "ITEMS" WITH LENGTH OF "LENGTH".
    int LENGTH;
         printf("HOW MANY ITEMS IN YOUR BILL : ");
        scanf("%i", &LENGTH);
    item array[LENGTH];

    //DECLARING A FLOAT TO INTILIZE IT LATER FOR THE SUBTOTAL.
    float Sub_Total = 0;

    //SCANNING VALUES.    
        for(int i = 0; i < LENGTH; i++)
        {
        //PROMPT USER FOR ITEM NAME.
             printf("ITEM -NAME- : ");
            scanf("%s" ,&array[i].NAME);

        //PROMPT USER FOR ITEM QUANTITY.
             printf("ITEM -QUANTITY- : ");
            scanf("%i" ,&array[i].QUANTITY);

        //PROMPT USER FOR ITEM UNIT_PRICE.
             printf("UNIT -PRICE- : ");
            scanf("%f" ,&array[i].UNIT_PRICE);

        //CALCULATING EACH ITEM_TOTAL.  
            array[i].ITEM_TOTAL = array[i].QUANTITY * array[i].UNIT_PRICE;

        //CALCULATING SUB_TOTAL BEFORE -VAT- FOR THE WHOLE BILL. 
            Sub_Total += array[i].ITEM_TOTAL;
        }

    ///SCANNING -VAT- PERCENTAGE.
    float VAT_PERCENTAGE;  
        printf("VAT_PERCENTAGE : ");
        scanf("%f", &VAT_PERCENTAGE);

    //SUBTOTAL AFTER VAT.
    float VAT_AMOUNT = (VAT_PERCENTAGE/ 100)* Sub_Total;

    //CALCULATING NET TOTAL.
    float TOTAL = Sub_Total + VAT_AMOUNT;

        PRINT_BILL_TERMINAL(array , LENGTH , Sub_Total , VAT_PERCENTAGE , VAT_AMOUNT ,TOTAL);
        PRINT_BILL_CSV(array , LENGTH , Sub_Total , VAT_PERCENTAGE , VAT_AMOUNT ,TOTAL);
    //------------------------------------------------------------------------
    int close;
    printf("\nDO YOU WAN TO CALCULATE ANOTHER BILL ?\nPRESS 1 FOR ""YES"" ""ENTER TO EXIT"" ");
    scanf("%i", &close);

        if(close == 1)
        {
            main();
        }
        else
        {
            return 0;
        }
    }

void PRINT_BILL_TERMINAL(item ar[], int x, float S_T, float V, float V_A, float T_A_V)
    {
        CLEAR_SCREEN();

        DIVIDER();
        printf("| %-15s | %5s | %8s | %8s |\n", "ITEM", "QTY", "U_PRICE", "TOTAL");
        DIVIDER();
        for(int j = 0; j < x; j++)
        {
            printf("| %-15s | %5d | %8.2f | %8.2f |\n",
            ar[j].NAME, ar[j].QUANTITY, ar[j].UNIT_PRICE, ar[j].ITEM_TOTAL);
        }
        DIVIDER();
        printf("SUBTOTAL : %.2f\nVAT %.1f%% : %.2f \nTOTAL : %.2f\n",
        S_T , V ,V_A, T_A_V);
    }

void PRINT_BILL_CSV(item ar[], int x, float S_T, float V, float V_A, float T_A_V)
    {
        //OPENFILE IN WRITING MODE
        FILE *his = fopen("BILL_HIS.CSV" , "w");
        if(his == NULL)
        {
            printf("CANNOT OPEN FILE");
            return ;
        }

        //PRINT THE HEADER ROW IN .CSV FILE.
        fprintf(his , "ITEM NAME,QUANTITY,UNIT_PRICE,TOTAL");

        //PRINT THE BILL ITEMS (NAMES , QUANTITIES , U_PRICE) IN ROWS.
        for(int z = 0; z < x; z++)
        {
            fprintf(his,"%s,%i,%.2f,%.2f\n",ar[z].NAME,ar[z].QUANTITY,ar[z].UNIT_PRICE,ar[z].ITEM_TOTAL);
        }
        //PRINT THE SUBTOTAL FOR THE TOTALS OF ITEMS.
        fprintf(his,"SUBTOTAL,,,%.2f\n",S_T);

        //PRINT THE VAT PERCENTAGE AND AMOUNT.
        fprintf(his,"VAT_PERCENTAGE%.1f%%,,,%.2f\n", V , V_A);
        
        //PRINT THE TOTAL AFTER THE VAT.
        fprintf(his,"TOTAL,,,%.2f", T_A_V);

        //SAFELY CLOSING THE FILE FOR NON-EXPECTED BEHAVIORS.
        fclose(his);
    }

void DIVIDER (void)
{
    printf("-------------------------------------------------\n");
}