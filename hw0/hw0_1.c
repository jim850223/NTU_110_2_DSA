#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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


void strToInt(char*, int, int*);
/*
void strToInt(char toDo[], int arr_len, int result[])

both of the ways are allowed, check out the difference
you can whether put the arguments name or not
szince char is different to char array, you should type char* instead of char in the first fashion

*/


int main(void){
    char num1[512];
    char num2[512];
    printf("Please type in number 1\n");
    scanf("%s", num1);
    //int len = (int)sizeof(trans_num) / sizeof(trans_num[0]);
    int len1 = strlen(num1);
    //get the length of the input
    printf("Please type in numebr 2\n");
    scanf("%s", num2);
    int len2 = strlen(num2);

    int num1_transform[len1];
    strToInt(num1, len1, num1_transform);  
    //trnsform the string to integer array
    int num2_transform[len2];
    strToInt(num2, len2, num2_transform); 
        
    for (int i = 0; i < len1; i++){
        printf("%d", num1_transform[i]);
    }
    printf("\n");
    
}



/* void strToInt(char toDo[], int arr_len, int result[]){
    //int result[arr_len];
    for (int i = 0; i < arr_len; i++){
        result[i] = (int)(toDo[i] - '0');
        //printf("%d", result[i]);
    //the problem is that it will save til the end of the string
    }
} */

//make the above function in an oppsite direction
void strToInt(char toDo[], int arr_len, int result[]){
    for (int i = 0; i < arr_len; i++){
        result[arr_len -1 - i] = (int)(toDo[i] - '0');    
    //you have to delete 1 to make the position correct
    }
}