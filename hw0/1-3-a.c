#include <stdio.h>
#include <stdlib.h>

#define MINN -50 // inclusive 
#define MAXN 50 // inclusive
int main(){
int storage[MAXN - MINN + 1]={0}; 
int *ary = (int *)malloc(sizeof(int[101]));
for (int i=MINN; i<=MAXN; i++) ary[i] = i;
for (int i=MINN; i<=MAXN; i++) printf("%d ", ary[i]);
return 0; }