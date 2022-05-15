#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define STRING_LENGTH 10000001

char *get_string() {
    char *the_string = (char *)malloc(STRING_LENGTH * sizeof(char));        
    char ch;
    unsigned long i = 0;
    while((ch = getchar_unlocked()) != '\n') {    
       the_string[i] = ch;
       i++;
    }
  the_string[i] = '\0';
  return the_string;
}

void print_the_content(char *test_for_string) {
    for (unsigned long i = 0; i < 10; i++) {
        printf("%c\n", test_for_string[i]);
    }
}


/* unsigned long get_length_of_prefix_of_string(char *string_to_detect, unsigned long string_length) {
    //Init an array to store the information of the LPS, which is Longest Proper Suffix
    //and double the size to concatenate the reverse version of the string to the back of the original string
    //e.g. the original string = 'abbcc', and the information to store if for 'abbccccbba'
    unsigned long *the_string = (unsigned long *)malloc(string_length * 2 * sizeof(unsigned long));
       
} */

unsigned long computeLPSArray(char *string_to_detect, unsigned long string_length)
{
    
    unsigned long *lps = (unsigned long *)malloc((string_length * 2 + 1) * sizeof(unsigned long));
    
    //Duplicate the original array with the reversal replica concaatenate to the end of the original array
    char *the_string_with_reverse_replica = (char *)malloc((string_length * 2 + 1) * sizeof(char));
    
    for (unsigned long  i = 0; i < string_length; i++) {
        the_string_with_reverse_replica[i] = string_to_detect[i];
    }

    the_string_with_reverse_replica[string_length] = '$';
        
    for (unsigned long  i = string_length + 1; i < string_length * 2 + 1; i++) {
        the_string_with_reverse_replica[i] = string_to_detect[string_length * 2 - i];
    }
        
    

    unsigned long len = 0;
    lps[0] = 0; // lps[0] is always 0
 
    // the loop calculates lps[i] for i = 1 to M-1
    unsigned long i = 1;
    unsigned long M = string_length * 2 + 1;

    while (i < M)
    {
        if (the_string_with_reverse_replica[i] == the_string_with_reverse_replica[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else // (the_string_with_reverse_replica[i] != the_string_with_reverse_replica[len])
        {                                    
            if (len != 0)
            {
                len = lps[len-1];                                
            }
            else // if (len == 0)
            {
                lps[i] = 0;
                i++;
            }
        }
    }
    
    return string_length - lps[string_length * 2];
}

unsigned long computeLPSArray_inverse(char *string_to_detect, unsigned long string_length)
{
    
    unsigned long *lps = (unsigned long *)malloc((string_length * 2 + 1) * sizeof(unsigned long));
    
    //Duplicate the original array with the reversal replica concaatenate to the end of the original array
    char *the_string_with_reverse_replica = (char *)malloc((string_length * 2 + 1) * sizeof(char));
    
    for (unsigned long  i = 0; i < string_length; i++) {
        the_string_with_reverse_replica[i + string_length + 1] = string_to_detect[i];
    }

    the_string_with_reverse_replica[string_length] = '$';
        
    for (unsigned long  i = string_length + 1; i < string_length * 2 + 1; i++) {
        the_string_with_reverse_replica[i - string_length - 1] = string_to_detect[string_length * 2 - i];
    }
        
    

    unsigned long len = 0;
    lps[0] = 0; // lps[0] is always 0
 
    // the loop calculates lps[i] for i = 1 to M-1
    unsigned long i = 1;
    unsigned long M = string_length * 2 + 1;

    while (i < M)
    {
        if (the_string_with_reverse_replica[i] == the_string_with_reverse_replica[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else // (the_string_with_reverse_replica[i] != the_string_with_reverse_replica[len])
        {                                    
            if (len != 0)
            {
                len = lps[len-1];                                
            }
            else // if (len == 0)
            {
                lps[i] = 0;
                i++;
            }
        }
    }
    
    return string_length - lps[string_length * 2];
}

int main()
{
    //Store the input into the array
    char * string_to_detect =get_string();
    
    unsigned long string_length = strlen(string_to_detect);    

    unsigned long result_normal_way = computeLPSArray(string_to_detect, string_length);
    
    unsigned long result_reversal_way = computeLPSArray_inverse(string_to_detect, string_length);
    
    
    if (result_normal_way < result_reversal_way) {
        printf("%lu\n", result_normal_way);
        
        for (unsigned long i = 0; i < result_normal_way; i++) {
            //printf("%c", string_to_detect[string_length - 1 - i]);
            putchar_unlocked(string_to_detect[string_length - 1 - i]);
        }        
        
        for (unsigned long i = 0; i < string_length; i++) {
            //printf("%c", string_to_detect[i]);
            putchar_unlocked(string_to_detect[i]);
        }
        printf("\n");
    }

    else if (result_normal_way == 0 ||result_reversal_way == 0) {
        printf("0\n");
        for (unsigned long i = 0; i < string_length; i++) {
            //printf("%c", string_to_detect[i]);
            putchar_unlocked(string_to_detect[i]);
        }
        printf("\n");
    }
           
    else if (result_normal_way == result_reversal_way) {
        
        printf("%lu\n", result_reversal_way);

        for (unsigned long i = 0; i < result_normal_way; i++) {
            //printf("%c", string_to_detect[string_length - 1 - i]);
            putchar_unlocked(string_to_detect[string_length - 1 - i]);
        }        
        
        for (unsigned long i = 0; i < string_length; i++) {
            //printf("%c", string_to_detect[i]);
            putchar_unlocked(string_to_detect[i]);
        }                    
        
        printf("\n");

        for (unsigned long i = 0; i < result_reversal_way; i++) {
            //printf("%c", string_to_detect[i]);
            putchar_unlocked(string_to_detect[i]);
        }
        
        for (unsigned long i = 0; i < string_length; i++) {
        //printf("%c", string_to_detect[string_length - 1 -i]);
        putchar_unlocked(string_to_detect[string_length - 1 - i]);
        }                            
        printf("\n");            
    }
    
    else {
        printf("%lu\n", result_reversal_way);
        
        for (unsigned long i = 0; i < result_reversal_way; i++) {
            //printf("%c", string_to_detect[i]);
            putchar_unlocked(string_to_detect[i]);
        }
        
        for (unsigned long i = 0; i < string_length; i++) {
            //printf("%c", string_to_detect[string_length - 1 -i]);
            putchar_unlocked(string_to_detect[string_length - 1 - i]);
        }
        
        printf("\n");        
    }
}