#include <stdio.h>

int main() {
    int test[5];

    int count = 0;
    for (int i = 0; i < 5; i++) {
        char ch;
        ch = getchar();        
        putchar(ch);
        count++;
        putchar('\n');
        //printf("%d\n", test[i]);
    }
    printf("%d\n", count);
}