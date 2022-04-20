#include <stdio.h>
#include <stdlib.h>
#include "price.h"
void print_output(unsigned long long *output, int Q);
unsigned long long *get_output (int Q, int s1);

int main(void) {

    int A, Q, N, s1;
    scanf("%d", &A);
    scanf("%d", &Q);
    scanf("%d", &N);

    scanf("%d", &s1);

    //get s_set

    
    //use for loop to put input into an array
    unsigned long long *output = get_output (Q, s1);        

    print_output(output, Q);    
    
    

/*     unsigned long long a = price(1,i);
    printf("%llu\n", a); */
    
}


unsigned long long *get_output (int Q, int s1){
    
    //Create an array to save outputs
    //unsigned long long output[Q];
    
    unsigned long long *output = (unsigned long long *)malloc(Q * sizeof(unsigned long long));
    
    int extre_stock, sweet_point;
    for (int i = 0; i < Q; i++) {
        
        scanf("%d", &extre_stock);
        scanf("%d", &sweet_point);

        output[i] = price(s1, sweet_point);        
    }    

    return output;
}

void print_output(unsigned long long *output, int Q) {
    for (int i = 0; i < Q; i++) {
        printf("%llu\n", output[i]);
    }
}

/* get_the_k() {
    
} */


/* get_s() {
    
} */