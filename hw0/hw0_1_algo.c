#include<stdio.h>
#include<stdlib.h>

int main(void)
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
    