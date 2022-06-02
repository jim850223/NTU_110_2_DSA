#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h> 


int main (void) {

    long long test = (long long)2 << 62;
    long long test2 = (long long)2 << 60;
    printf("%d\n", test>test2);
    printf("%lld\n", test);
    

}