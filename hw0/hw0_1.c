#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stdbool.h>

/*int main(void)
{
    int n;
    int m;
    printf("請輸入第一個整數");
    scanf("%d", &n);
    printf("請輸入第二個整數");
    scanf("%d", &m);
    int ans = 1;
    int tmp;
    while (n != 0 && m != 0){
        if (n%2 == 0 && m%2 == 0){
            ans = ans * 2;
            n = n/2;
            m = m/2;
        }
        else if (n%2 == 0){
            n = n/2;
        }
        else if (m%2 == 0){
            m = m/2;
        }
        if (n > m){
            tmp = n;
            n = m;
            m = tmp;
        }
        m = m - n;
    }
    printf("%d\n", n * ans); 
}  
*/

int comparator(int *, int *);
int *strToInt(char *);
void print_the_number(int *);
void swap(int **, int **);
/*
void strToInt(char toDo[], int arr_len, int result[])

both of the ways are allowed, check out the difference
you can whether put the arguments name or not
szince char is different to char array, you should type char* instead of char in the first fashion

*/


int main(void){
    char num1[256];
    char num2[256];
    printf("Please type in number 1\n");
    scanf("%s", num1);
    printf("Please type in numebr 2\n");
    scanf("%s", num2);
    
    int *num1_transform = strToInt(num1);  
    int *num2_transform = strToInt(num2);  
        
    //print_the_number(num1_transform);
    printf("%d\n", comparator(num1_transform, num2_transform));
}

int comparator(int *num1, int *num2)
//not finished yet, you can only compare the length
{
    if (num1[0] > num2[0])
        return true;
    else{
        if (num1[0] < num2[0])
            return false;
        else{
            //compare every number of them
            for (int i = num1[0]; i > 0; i--){
                if (num1[i] > num2[i]){
                    return true;
                }
                else if (num1[i] < num2[i]){
                    return false;
                }
            }
            return 2;
            //return 2 if they are equl
        }    
    }
}

void swap(int **num1, int **num2)
{
    int **tmp = num1;
    num1 = num2;
    num2 = tmp;
}


//substractor
//divisor
//multiplier


/* void strToInt(char toDo[], int arr_len, int result[]){
    //int result[arr_len];
    for (int i = 0; i < arr_len; i++){
        result[i] = (int)(toDo[i] - '0');
        //printf("%d", result[i]);
    //the problem is that it will save til the end of the string
    }
} */

//make the above function in an oppsite direction
int *strToInt(char toDo[])
{
    int arr_len = strlen(toDo);
    //store the length of the long integer in the first element of the array
    int * result = (int *) malloc((arr_len + 1) * sizeof(int));
    result[0] = arr_len;
    for (int i = 0; i < arr_len; i++){
        result[arr_len - i] = (int)(toDo[i] - '0');
    }
    return result;
}

void print_the_number(int toDo[])
{   
    int num_len = toDo[0];
    for (int i = 0; i < num_len; i++)
        printf("%d", toDo[num_len - i]);
    printf("\n");
}