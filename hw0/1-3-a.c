#include <stdio.h>
#include <stdlib.h>

/* #define MINN -50 // inclusive 
#define MAXN 50 // inclusive
int main(){
int storage[MAXN - MINN + 1]={0}; 
int *ary = (int *)malloc(sizeof(int[101]));
for (int i=MINN; i<=MAXN; i++) ary[i] = i;
for (int i=MINN; i<=MAXN; i++) printf("%d ", ary[i]);
return 0; } */

int main() {

int fake_a[] = {1, 3}; 
int fake_b[] = {2, 4}; 
int *real_a = fake_a;
int *real_b = fake_b;

for (int i = 0; i < 2; i++)
    printf("%d ", *(real_a + i));

for (int i = 0; i < 2; i++)
    printf("%d ", *(real_b + i));

int *tmp = real_a; 
real_a = real_b;
real_b = tmp;

for (int i=0; i<2; i++)
    printf("%d ", *(real_a + i));


for (int i=0; i<2; i++)
    printf("%d ", *(real_b + i));

}
