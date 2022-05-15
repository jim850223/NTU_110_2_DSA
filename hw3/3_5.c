#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define NUMBER_OF_MAGIC 1000001 //k 10^6
#define LENGTH_OF_MAGIC 1000001 //l 10^6
#define CHARACTER_SET (94) //From 0X21 to 0X7E + extra 1 to add an element
                             //to store the value where we hide a bit from other bits
                             //Remember to put parentheses around number
#include <math.h> 

//flag = 0 output either of multiple pairs, (i, j), where the i-th magic is similar to j-th 

//flag = 1 print out one integer, indicaating the number of similar pairs
//Having got to deal with the situations where many pairs show up

typedef struct node {
    unsigned long long value;
    unsigned long long index;
} NODE;

unsigned long long power_with_mod(unsigned long long number, unsigned long long times, unsigned long long max_number) {    
    unsigned long long result = 1;
    
    for (unsigned long long i = 0; i < times; i++) {        
        result = (result * number) % max_number;    
    }    
    return result;
}


void Rabin_Karp(char *target_string, unsigned long long string_num, unsigned long long l, unsigned long long max_number, NODE *value_table, unsigned long long *RK_table) {                  
    
    
    //P is used to save the real KP_value    
    unsigned long long p = 0;
    unsigned long long temp;
    
    //Calculate RK_value
    for (unsigned long long j = 0; j < l; j++) {                
        p = (CHARACTER_SET * p + target_string[j]) % max_number;                                
    }   
    value_table[string_num].index = string_num;
    value_table[string_num].value = p;

    printf("%llu\n", value_table[string_num].value);
    
    //Calculate RK_value with the present value hidden
    for (unsigned long long j = 0; j < l; j++) {        
        //Copy value from p to temp to calculate RK_value with the present value hidden
        temp = p;
        temp = 
            temp - target_string[l - 1 - j] * power_with_mod(CHARACTER_SET, j, max_number);
        //Store the value into the Rk_table
        RK_table[0 * l + j] = temp;
        printf("%llu\n", temp);
    }
/* 
    for (unsigned long long i = 0; i < l; i++) {
        printf("%llu\n", RK_table[0 * l + i]);        
    } */
}

void get_table(unsigned long long k, unsigned long long l, unsigned long long flag, unsigned long long max_number, NODE *value_table, unsigned long long *RK_table) {
         
    char *the_string = (char *)malloc(l * sizeof(char));
        
    for (unsigned i = 0; i < k; i++) {
        scanf("%s", the_string);
        Rabin_Karp(the_string, i, l, max_number, value_table, RK_table);
        printf("The value is %llu\n",value_table[i].value);
        printf("from %llu\n",value_table[i].index);
    }    
    



//Figure how to use getchar() it after finish the question
/*     while((ch = getchar_unlocked()) != '\n') {           
       //Since we store ch in ascii code, we can manipulat codes in form of decimal
       //or char as you want       
       the_string[i] = ch;
       //The result of i is the length of the string
       i++;       
    } */

//Print the content of the string
/*     for (unsigned long long j = 0; j < l; j++) {        
        //printf("%c\n", the_string[j]);
        putchar_unlocked(the_string[j]);
    }
    putchar('\n'); */
    
            
/*     //Get string content    
    calculate_RK_value();
    
    for (unsigned long long i = 0; i < k; i++) {        
        for (unsigned long long j = 0; j < l; j++) {
            
        }

    } */
    
}


int main (void) {
    
    
    unsigned long long bigValue = ((unsigned long long)2 <<62);
    bigValue = bigValue + bigValue - 1;    
    
    //Calculate value of q, which is the max number used in Rabin Karp
    unsigned long long max_number = (bigValue/CHARACTER_SET);        

    
    //Set  k, l, flag
    unsigned long long k, l, flag;
    scanf("%llu", &k);
    scanf("%llu", &l);
    scanf("%llu", &flag);

    //value_table is used to store final RK_value and it's index
    NODE *value_table = (NODE *)malloc(sizeof(NODE) * k);

    //Init a table to store RK_values
    unsigned long long *RK_table = 
        (unsigned long long*)malloc(k * l * sizeof(unsigned long long));

    //Get table that stores RK_value in every step
    get_table(k, l, flag, max_number, value_table, RK_table);
        
    
    
        
}