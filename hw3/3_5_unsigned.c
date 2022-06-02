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

/* unsigned long long power_with_mod(unsigned long long number, unsigned long long times, unsigned long long q) {    
    unsigned long long result = 1;
    
    for (unsigned long long i = 0; i < times; i++) {        
        result = (result * number) % q;    
    }    
    return result;
} */


void Rabin_Karp(char *target_string, unsigned long long string_num, unsigned long long l, unsigned long long q, NODE *value_table, unsigned long long *RK_table) {                  
    
    //P is used to save the real KP_value    
    unsigned long long p = 0;
    unsigned long long temp = 0;
    
    //Calculate RK_value
    for (unsigned long long j = 0; j < l; j++) {                
        p = ((CHARACTER_SET * p)%q + (target_string[j]-'!' + 1)) % q;                                
    }

    value_table[string_num].index = string_num;
    value_table[string_num].value = p;

    //printf("Final value is %llu\n", value_table[string_num].value);
    

    unsigned long long to_subtract;
    unsigned long long to_power = 1;
    //Calculate RK_value with the present value hidden
    for (unsigned long long j = 0; j < l; j++) {        
                
        //Actually it's not necessary to use power_with_mod since it's super time-consuming
        //to_subtract =(target_string[l - 1 - j]- '!' + 1) * power_with_mod(CHARACTER_SET, j, q);
        to_subtract =((target_string[l - 1 - j]- '!' + 1) * to_power)%q;                
        if (p >= to_subtract) {
            RK_table[string_num * l + j] = p - to_subtract;
        }
        else {
            RK_table[string_num * l + j] = p + q - to_subtract;
        }                
        //printf("RK_value is %llu\n", temp);
        to_power = to_power * CHARACTER_SET % q;
    }

//Back up of above
/*         to_subtract =(target_string[l - 1 - j]- '!' + 1) * to_power;                
        if (temp > to_subtract) {
            temp = temp - to_subtract;
        }
        else {
            temp = temp + q - to_subtract;
        }
        //Store the value to the Rk_table
        RK_table[string_num * l + j] = temp;
        //printf("RK_value is %llu\n", temp);
        to_power = to_power * CHARACTER_SET % q; */
}

void fill_tables(unsigned long long k, unsigned long long l, unsigned long long flag, unsigned long long q, NODE *value_table, unsigned long long *RK_table) {
         
    char *the_string = (char *)malloc((l+1) * sizeof(char));
    
    //i stands for number the string
    for (unsigned long long i = 0; i < k; i++) {
        scanf("%s", the_string);
        
/*         char ch;
        unsigned long long i = 0;
        while((ch = getchar_unlocked()) != '\n') {    
            the_string[i] = ch;
            i++;
        } */

        Rabin_Karp(the_string, i, l, q, value_table, RK_table);
        //printf("The value is %llu\n",value_table[i].value);
        //printf("from %llu\n",value_table[i].index);
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

int comparator(const void *p, const void *q) 
{
    unsigned long long l = ((NODE *)p)->value;
    unsigned long long r = ((NODE *)q)->value;
    if (l > r) {
        return 1;
    }
    
    else {
        return -1;
    }            
}


int main (void) {

/*     for (int i = 0;i < 5; i++) {
        printf("%lld\n",power_with_mod(2, i, 10000000000));
    } */
    unsigned long long max = (unsigned long long)2 << 62;
    max = max + max -1;

    //Calculate value of q, which is the max number used in Rabin Karp
    //unsigned long long q = max/CHARACTER_SET;
    unsigned long long q = (unsigned long long)1000000000000;
    //printf("%llu\n", max); 
    //printf("%llu\n", q);

    
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

    //Fill value_table and Rk_table with getting k set of string
    fill_tables(k, l, flag, q, value_table, RK_table);
    //printf("\n");

    qsort(value_table, k, sizeof(NODE), comparator);
    unsigned long long i = 0;
    while (i < k-1) {
        if (value_table[i].value== value_table[i+1].value) {
            printf("Yes\n");
            printf("%llu %llu\n", value_table[i].index, value_table[i+1].index);
            return 1;
            //return 1
        }
        else {
            i++;
        }
    }

    //Refresh the value_table
    for (unsigned long long i = 0; i < l; i++) {
        for (unsigned long long j = 0; j < k; j++) {
            value_table[j].value = RK_table[j * l + i];
            value_table[j].index = j;
        }

        qsort(value_table, k, sizeof(NODE), comparator);
        
        unsigned long long z = 0;    
        while (z < k-1) {
            if (value_table[z].value== value_table[z+1].value) {
                printf("Yes\n");
                printf("%llu %llu\n", value_table[z].index, value_table[z+1].index);
                return 1;
                //return 1
            }
            else {
                z++;
            }
        }
    }
    printf("No\n");            

    //Check result of q_sort
/*     for (int i = 0; i < k; i ++) {
        printf("%d\n", value_table[i].index);
        printf("%d\n", value_table[i].value);
    }

    qsort(value_table, k, sizeof(NODE), comparator);
    printf("\n");
        
    for (int i = 0; i < k; i ++) {
        printf("%d\n", value_table[i].index);
        printf("%d\n", value_table[i].value);
    } */

    
/*     for (int i = 0; i < k; i ++) {
        printf("%d\n", value_table[i].index);
        printf("%d\n", value_table[i].value);
    }
    printf("\n");

    for (int i = 0; i < k; i ++) {
        for (int j = 0; j < l; j ++) {
            printf("%d\n", RK_table[i * l + j]);
        }
    }  */
}
