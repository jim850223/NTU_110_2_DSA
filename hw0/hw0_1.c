#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stdbool.h>
#define MAX_LENGTH 256

int comparator(int *, int *);
void print_the_number(int *);
void swap(int **, int **);
void substractor(int **num1, int **num2);
char *get_num_in_str();
void divisor(int **);
void adder_to_itself_with_digit_control(int **num1, int **num2, int digit);
int *one_digit_multiplier(int *, int);
void self_multiplier(int **num1, int **num2);

/*
void strToInt(char toDo[])
both of the ways are allowed, check out the difference
you can whether put the arguments name or not
szince char is different to char array, you should type char* instead of char in the first fashion
*/

int *strToInt(char *);

//int main(int argc, char *argv[]) {
int main() {
    //char *num1 = get_num_in_str();    
    //char *num2 = get_num_in_str();    
    
    char * num1 = (char *) malloc((MAX_LENGTH + 1) * sizeof(char));
    char * num2 = (char *) malloc((MAX_LENGTH + 1) * sizeof(char));
    
    scanf("%s%s",num1,num2);
    
    int *num1_transform = strToInt(num1);
    int *num2_transform = strToInt(num2);
    //int n = comparator(num1_transform, num2_transform);
    //printf("%d\n", n);

/*     swap(&num1_transform, &num2_transform);
    print_the_number(num1_transform);
    print_the_number(num2_transform); */

    //substractor(&num1_transform, &num2_transform);
    //print_the_number(num1_transform);
    //printf("%d\n", num1_transform[0]);
                    
    int *ans = (int *) malloc((MAX_LENGTH + 1) * sizeof(int));
    ans[0] = 1;
    ans[1] = 1;

    int *two = (int *) malloc((MAX_LENGTH + 1) * sizeof(int));
    two[0] = 1;
    two[1] = 2;

    while (num1_transform[0] != 0 && num2_transform[0] != 0) {
        if ((num1_transform[1]%2 == 0) && (num2_transform[1]%2 == 0)) {
            self_multiplier(&ans, &two);
            divisor(&num1_transform);
            divisor(&num2_transform);
        }
        else if (num1_transform[1]%2 == 0){
            divisor(&num1_transform);
        }
        else if (num2_transform[1]%2 == 0){
            divisor(&num2_transform);
        }
        if (comparator(num1_transform, num2_transform) == 1) {
            swap(&num1_transform, &num2_transform);
        }
        substractor(&num2_transform, &num1_transform);
        //printf("calculating!!\n");
    }
    self_multiplier(&num1_transform, &ans);    
    print_the_number(num1_transform);
    
}


void swap(int **num1, int **num2)
{
    int *tmp = *num1;
    *num1 = *num2;
    *num2 = tmp;
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
/*         else {
            num1[0][i] = (num1[0][i]) + 10;
            int j = i;
            while (num1[0][j+1] == 0) {
                j++;
                num1[0][j] = 9;
            }
            (num1[0][j+1])--;                    
            num1[0][i] = (num1[0][i])- (num2[0][i]);
        } */
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
    //Check the length of num1.
    
    for (int i = 0; i < num1_len; i++) {
        if (num1[0][num1_len - i] == 0) {
            num1[0][0] = num1[0][0] - 1;
        }
        else break;
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
    if (num[0][num_length] == 0) {
        num[0][0] -= 1;
    }
}


void adder_to_itself_with_digit_control(int **num1, int **num2, int digit) {
    
    /* if you wnat to add the number to the second digit, you just need to move the number to the left with 1 movement, which
    is digit - 1 */
    digit -= 1;

    int long_length = (num1[0][0] >= num2[0][0]) ? num1[0][0] : num2[0][0];    
    //to check if the final result is longer than long_length

    int final_length = (digit + num2[0][0] >= long_length) ? digit + num2[0][0] : long_length;
    
    
    /* You need to run til the end of the number since the number you've got might be more than 10 on every digit which you have
    to dealing with the i+1 digit */
    for (int i = digit + 1; i <= final_length; i++) {

        if ((num1[0][i] + num2[0][i-digit]) >= 10) {            
            num1[0][i+1] += 1;
            //it's add 1 but not 10, bad mistake

            num1[0][i] = (num1[0][i] + num2[0][i-digit]) % 10;
    
        }
        else {
            num1[0][i] += num2[0][i-digit];
        }
    }
    //if the number of the last digit is more than 10, you have to add 1 to i+1 digit
    if (num1[0][final_length + 1]) {
        num1[0][0] = final_length + 1;
    }
    else {
        num1[0][0] = final_length;
    }
}

int *one_digit_multiplier(int *multiplier, int multiplicand) {
    
    //int *result = (int *) malloc((multiplier[0] + 2) * sizeof(int));
    int *result = (int *) malloc((MAX_LENGTH + 1) * sizeof(int));
    
    //to check if the length of the result is more than multipler's
    int over = 0;
    int tmp = 0;
    for (int i = 1; i <= multiplier[0]; i++) {
        tmp = multiplier[i] * multiplicand;
        //be careful, you need to add the temp to the number which was there to have % or /
        if (tmp + result[i] >= 10) {
            result[i+1] = (tmp +result[i]) / 10;
            result[i] = (tmp +result[i]) % 10;
            over = 1;
        }
        else {
            result[i] += tmp;
            over = 0;
        }
    }
        
    result[0] = multiplier[0];
    if (over == 1) {
        result[0] += 1;
    }
    return result;
}


 //the result will be like num1 = num1 * num2
void self_multiplier(int **num1, int **num2) {
    int *result = (int *) malloc((MAX_LENGTH + 1) * sizeof(int));
    result[0] = 0;

    for (int i = 1; i <= num2[0][0]; i++) {
        //get the result of i digit of num2 multiple num1
        int *tmp = one_digit_multiplier(* num1, num2[0][i]);
        //print_the_number(tmp);
        adder_to_itself_with_digit_control(&result, &tmp, i);                
    }
    *num1 = result;
    //print_the_number(result);
} 


int *strToInt(char toDo[])
{   

    //store the length of the long integer in the first element of the array
    int arr_len = strlen(toDo);

    //the reason why the the result of linux and mac are different is because I malloc arr_length+1 instead of MAX_LENGTH+1 in the beginning
    int * result = (int *) malloc((MAX_LENGTH + 1) * sizeof(int));
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