#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stdbool.h>
#define MAX_LENGTH 256


int comparator(int *, int *);
int *strToInt(char *);
void print_the_number(int *);
void swap(int **, int **);
void substractor(int **num1, int **num2);
char *get_num_in_str();
void divisor(int **);
/*
void strToInt(char toDo[], int arr_len, int result[])

both of the ways are allowed, check out the difference
you can whether put the arguments name or not
szince char is different to char array, you should type char* instead of char in the first fashion

*/


int main(void){
    
    char *num1 = get_num_in_str();    
    char *num2 = get_num_in_str();    
    
    int *num1_transform = strToInt(num1);
    int *num2_transform = strToInt(num2);      

    printf("%d\n", comparator(num1_transform, num2_transform));
    substractor(&num1_transform, &num2_transform);
    
    
}


void swap(int **num1, int **num2)
{
    int **tmp = num1;
    num1 = num2;
    num2 = tmp;
}


void substractor(int **num1, int **num2)
{
    int num1_len = num1[0][0];
    int num2_len = num2[0][0];
    //printf("%d\n", num1_len);
    for (int i = 1; i <= num2_len; i++) {
    /* You can't use num1_len as a boundary since you have no idea about the element of 
    num2[num1_len] if their's length are not equal. It might result in a segmentation fault.*/
        if (num1[0][i] >= num2[0][i]) {
            num1[0][i] = (num1[0][i]) - (num2[0][i]);
        }
        else {
            num1[0][i] = (num1[0][i]) + 10;
            int j = i;
            while (num1[0][j+1] == 0) {
                j++;
                num1[0][j] = 9;
            }
            (num1[0][j+1])--;                    
            num1[0][i] = (num1[0][i])- (num2[0][i]);
        }
    }
    //Check if the length of num1 is still the same.
    while (num1[0][num1_len] == 0){
        num1[0][0] = (num1[0][0]) - 1;
        num1_len--;
    }
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
            //return 2 if they are equal
        }    
    }
}


void divisor(int **num) {
    int num_length = num[0][0];
    for (int i = num_length; i > 0; i-- ) {
        if (num[0][i] == 1) {
            num[0][i] = 0;
            num[0][i-1] = num[0][i-1] + 10;
        }
        else if (num[0][i] % 2 == 1) {
            num[0][i] = num[0][i] / 2;
            num[0][i-1] = num[0][i-1] + 10;
        }
        else {
            num[0][i] = num[0][i] / 2;
        }        
    }
}

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

char *get_num_in_str(void) {
    char * str_num = (char *) malloc((MAX_LENGTH + 1) * sizeof(char));
    printf("Please type in number \n");
    scanf("%s", str_num);
    return str_num;
}

void print_the_number(int toDo[])
{   
    int num_len = toDo[0];
    for (int i = 0; i < num_len; i++)
        printf("%d", toDo[num_len - i]);
    printf("\n");
}