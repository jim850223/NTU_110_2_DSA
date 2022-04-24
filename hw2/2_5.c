#include <stdio.h>
#include <stdlib.h>
#include "price.h"
void print_elements(unsigned long long *output, int Q);
unsigned long long *get_output (int Q, int s1);
unsigned long long *create_Brians_favorites(int A);
unsigned long long *make_Brians_favorites_to_a_min_heap (unsigned long long *bStocks, int A, int N);
void get_prices_store_into_the_array(unsigned long long *bStocks, unsigned long long *min_heap, int A, int N);

int main(void) {

    int A, Q, N;

    scanf("%d", &A); //A denotes the number of Brian's favorite stocks
    scanf("%d", &Q); //Q denotes the number of questions
    scanf("%d", &N); //N defines how long each stock is guranted to increase its price, as mentioned above
    
    //Create an array to store Brian's favorite stocks
    unsigned long long * bStocks = create_Brians_favorites(A);

    
    //Build a min heap which is comprised of A * n nodes from Brian's A favorites stocks


    //Declare an 10^6 array to store the result of the heap sort with a given heap and add new elements into the array at the same time
    
    
        
    //Testing section for get_prices
    /* unsigned long long *min_heap = (unsigned long long *)malloc(A * N * sizeof(unsigned long long));
    get_prices_store_into_the_array(bStocks, min_heap, A, N);
    print_elements(min_heap, A * N); */
    
    
}


unsigned long long *get_output (int Q, int s1){
    
    //Create an array to save outputs    
    unsigned long long *output = (unsigned long long *)malloc(Q * sizeof(unsigned long long));
    
    int extre_stock, sweet_point;
    for (int i = 0; i < Q; i++) {
        
        scanf("%d", &extre_stock);
        scanf("%d", &sweet_point);

        output[i] = price(s1, sweet_point);        
    }

    return output;
}

//Print elements of an array
//Checked
void print_elements(unsigned long long *output, int Q) {
    for (int i = 0; i < Q; i++) {
        printf("%llu\n", output[i]);
    }
}


//Create an array to store Brian's favorite stocks
//Checked
unsigned long long *create_Brians_favorites(int A) {
        unsigned long long As;//To store Brian's favorite stocks
    
        unsigned long long *bStocks = (unsigned long long *)malloc(A * sizeof(unsigned long long));        
        for (int i = 0; i < A; i++) {
            scanf("%llu", &As);        
            bStocks[i] = As;
    }
    return bStocks;
}

//Build a min heap which is comprised of A * n nodes from Brian's A favorites stocks
unsigned long long *make_Brians_favorites_to_a_min_heap (unsigned long long *bStocks, int A, int N) {
    
    //declare an array with malloc to store prices of the stocks
    unsigned long long *min_heap = (unsigned long long *)malloc(A * N * sizeof(unsigned long long));
    //Get n prices from stocks and store them into an array
    get_prices_store_into_the_array(bStocks, min_heap A, N);
    
    //Sort the given array such that prices are monotonic
    //void sorts_prices()
    
    return heap
}

//Checked
void get_prices_store_into_the_array(unsigned long long *bStocks, unsigned long long *min_heap, int A, int N) {
    //To record the index of the array
    int count = 0;
    //To determine which stock to choose
    for (int i = 0; i < A; i++) {
        //To determin which day to choose from 1
        for (int j = 1; j <= N; j++) {
            //Store the prices into the heap
            min_heap[count] = price(bStocks[i], j);
            count++;            
        }
    }
}


void heapify() {
    
}


void heapify_elements_of_array(unsigned long long *min_heap, int arrayLength){
    //heapify the elements from the last parent node
    
}

void heap_sort {
    
}