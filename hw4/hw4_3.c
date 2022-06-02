#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef struct disjointSet{
    // TODO: Determine fields to use by your method
    long long rank;
    long long parent;
} DisjointSet;

void makeset(long long shops, DisjointSet *ds){
    // TODO: Initialize a set with hash value
    //int i = hash(s);
    for (long long i = 1; i <= shops; i++) {
        ds[i].parent = i;
        ds[i].rank = 0;
    }
}

int find_set(long long index, DisjointSet *ds) {        
    if (ds[index].parent != index)
        ds[index].parent = find_set(ds[index].parent, ds);
        //ds[i].rank = ds[ds[i].parent].rank;
    return ds[index].parent;
}

bool same_set(long long index_1, long long index_2, DisjointSet *ds) {    
    int a = find_set(index_1, ds), b = find_set(index_2, ds);
    if (a == b) {
        return true;
    }    
    else {
        return false;
    }
}

void group(long long index_1, long long index_2, DisjointSet *ds) {    
    int a = find_set(index_1, ds), b = find_set(index_2, ds);
    // TODO: Implement your union algorithm here
    //Attach smaller rank tree uder root of high rank tree(Union by rank)
    if (ds[a].rank > ds[b].rank) {
        ds[b].parent = a;
    }
    else if (ds[a].rank < ds[b].rank) {
        ds[a].parent = b;
    }
    //If ranks are same, then make one as root and 
    //increase its rank by one
    else {
        ds[b].parent = a;
        ds[a].rank++;
    }
}

int main(void) {
    //shops is used to count the shops left
    long long shops;    
    long long collections;
    scanf("%lld", &shops);
    scanf("%lld", &collections);
    //total_shops is used to record the number of shops at the begining
    long long total_shops = shops;
    DisjointSet ds[total_shops+1];
    long long times_of_querys = 0;

    char *job = (char *)malloc(sizeof(char) * 6);    
    long long *answer = (long long*)malloc(sizeof(long long) * collections);
    long long data_1;
    long long data_2;
    //jump_to is used to record the value of boom
    long long jump_to;
    DisjointSet *history_for_boom = (DisjointSet*)malloc(sizeof(DisjointSet) * (collections+1) * (total_shops+1));
    makeset(total_shops, ds);
    //Initialize for the first row of the history
    //Use rank to store the number of store
    history_for_boom[0].rank = shops;
    for (long long i = 1; i <= shops; i++) {
        history_for_boom[i].parent = i;
        history_for_boom[i].rank = 0;
    }
    
    for (long long i = 1; i <= collections; i++) {
        scanf("%s", job);
        if (!strcmp(job, "query")) {
            times_of_querys++;            
            //printf("%llu\n", shops);
            answer[times_of_querys-1] = shops;
            
            history_for_boom[i * (total_shops+1)].rank = shops;
            for (long long j = 1; j <= total_shops; j++) {
                history_for_boom[i * (total_shops+1)+j].parent = ds[j].parent;
                history_for_boom[i * (total_shops+1)+j].rank = ds[j].rank;
            }
        }
        else if (!strcmp(job, "merge")) {        
            scanf("%lld", &data_1);
            scanf("%lld", &data_2);
            if (!same_set(data_1, data_2, ds)) {
                group(data_1, data_2, ds);                
                shops--;
            }
            //Shops left in each round
            history_for_boom[i * (total_shops+1)].rank = shops;
            for (long long j = 1; j <= total_shops; j++) {
                history_for_boom[i * (total_shops+1)+j].parent = ds[j].parent;
                history_for_boom[i * (total_shops+1)+j].rank = ds[j].rank;
            }
        }
        else {
            scanf("%lld", &jump_to);
            for (long long j = 1; j <= total_shops; j++) {
                ds[j].parent = history_for_boom[jump_to * (total_shops+1)+j].parent;                
                ds[j].rank = history_for_boom[jump_to * (total_shops+1)+j].rank;                
                shops = history_for_boom[jump_to * (total_shops+1)].rank;
                //printf("%lld\n\n", ds[j].parent);
                //printf("%lld\n\n", ds[j].rank);
                //printf("%lld\n\n", shops);
                history_for_boom[i * (total_shops+1)].rank = shops;
                history_for_boom[i * (total_shops+1)+j].parent = ds[j].parent;
                history_for_boom[i * (total_shops+1)+j].rank = ds[j].rank;
            }
        }
    }        
    
    for (long long i = 0; i < times_of_querys; i++) {
        printf("%lld\n", answer[i]);
    }
}

/* 4 7
query
merge 1 2
query
merge 3 4
query
merge 1 3
query */

