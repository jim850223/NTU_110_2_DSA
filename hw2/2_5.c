#include <stdio.h>
#include <stdlib.h>
#include "price.h"

//Index of root = 1

//To record the stock of the k point
typedef struct {
    long long unsigned value;
    int stock;
}K_POINT;

void print_elements(K_POINT *output, int Q);
unsigned long long *get_output (int Q, int s1);
int *create_Brians_favorites(int A);
K_POINT *make_Brians_favorites_to_a_min_heap (int *bStocks, int A, int N);
void get_prices_store_into_the_array(int *bStocks, K_POINT *min_heap, int A, int N);
void heapify(K_POINT *group_of_nodes, int index, int range);
void build_the_heap (K_POINT *group_of_nodes, int range);
K_POINT *heap_sort(K_POINT *heap, int range);


int main(void) {

    int A, Q, N;

    scanf("%d", &A); //A denotes the number of Brian's favorite stocks
    scanf("%d", &Q); //Q denotes the number of questions
    scanf("%d", &N); //N defines how long each stock is guranted to increase its price, as mentioned above
    
    //Create an array to store Brian's favorite stocks
    int * bStocks = create_Brians_favorites(A);

    
    //Build a min heap which is comprised of A * n nodes from Brian's A favorites stocks


    //Declare an 10^6 array to store the result of the heap sort with a given heap and add new elements into the array at the same time
    
            
    //Testing section for heap_sort
    K_POINT *min_heap = (K_POINT *)malloc(A * N * sizeof(K_POINT));
    get_prices_store_into_the_array(bStocks, min_heap, A, N);
    print_elements(min_heap, A * N);
    printf("\n\n");
    build_the_heap (min_heap, A * N);
    print_elements(min_heap, A * N);
    printf("\n\n");
    K_POINT *result = heap_sort(min_heap, A * N);
    print_elements(result, A * N);

    

    
    //Testing section for heapifu
/*     K_POINT *min_heap = (K_POINT *)malloc(8* sizeof(K_POINT));
    K_POINT a1;
    a1.value = 4;
    K_POINT a2;
    a2.value = 2;
    K_POINT a3;
    a3.value = 7;
    K_POINT a4;
    a4.value = 1;
    K_POINT a5;
    a5.value = 6;
    K_POINT a6;
    a6.value = 3;
    K_POINT a7;
    a7.value = 5;
    min_heap[1] = a1;
    min_heap[2] = a2;
    min_heap[3] = a3;
    min_heap[4] = a4;
    min_heap[5] = a5;
    min_heap[6] = a6;
    min_heap[7] = a7;   
    print_elements(min_heap, 7);
    build_the_heap (min_heap, 7);
    //heapify(min_heap, 3, 7);
    //heapify(min_heap, 2, 7);
    //heapify(min_heap, 1, 7);
    printf("\n\n");
    print_elements(min_heap, 7); */

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

//Print elements of an unsigned long long array
//Checked
void print_elements(K_POINT *output, int Q) {
    for (int i = 1; i <= Q; i++) {
        printf("%llu\n", output[i].value);        
        //printf("%d\n", output[i].stock);
    }
}


//Create an array to store Brian's favorite stocks
//Checked
int *create_Brians_favorites(int A) {
        int As;//To store Brian's favorite stocks
    
        int *bStocks = (int *)malloc(A * sizeof(int));        
        for (int i = 0; i < A; i++) {
            scanf("%d", &As);        
            bStocks[i] = As;
    }
    return bStocks;
}

//Build a min heap which is comprised of A * n nodes from Brian's A favorites stocks
/* K_POINT *make_Brians_favorites_to_a_min_heap (int *bStocks, int A, int N) {
    
    //declare an array with malloc to store prices of the stocks
    K_POINT *min_heap = (K_POINT *)malloc(A * N * sizeof(K_POINT));
    //Get n prices from stocks and store them into an array
    get_prices_store_into_the_array(bStocks, min_heap, A, N);
    
    //Sort the given array such that prices are monotonic
    //void sorts_prices()
    
    return heap
}
 */
//Checked
void get_prices_store_into_the_array(int *bStocks, K_POINT *min_heap, int A, int N) {
    //To record the index of the array
    int count = 1;
    //To determine which stock to choose
    for (int i = 0; i < A; i++) {
        //To determin which day to choose from 1
        for (int j = 1; j <= N; j++) {
            //Store the prices into the heap
            min_heap[count].value = price(bStocks[i], j);
            min_heap[count].stock = bStocks[i];
            count++;
        }
    }
}

void heapify(K_POINT *group_of_nodes, int index, int range) {
    int small = 2 * index;
    if (small <= range) {
        if (small + 1 <= range) {
            if (group_of_nodes[small].value >= group_of_nodes[small+1].value) {
                small = small + 1;
        }
        if (group_of_nodes[small].value < group_of_nodes[index].value) {
            unsigned long long tmp = group_of_nodes[small].value;
            group_of_nodes[small].value = group_of_nodes[index].value;
            group_of_nodes[index].value = tmp;
            heapify(group_of_nodes, small, range);
        }
    }
    }
}

void build_the_heap (K_POINT *group_of_nodes, int range) {
    for (int i = range/2; i > 0; i-- ) {
        heapify(group_of_nodes, i, range);
    }
}

K_POINT *heap_sort(K_POINT *heap, int range) {
    K_POINT *sortted_array = (K_POINT *)malloc(range * (sizeof(int)) + 1);
    for (int i = 1; i <= range; i++) {
        sortted_array[i].value = heap[1].value;
        heap[1].value = heap[range+1-i].value;
        heapify(heap, 1, range+1-i);
    }
    return sortted_array;
}

/* void heapify_elements_of_array(unsigned long long *min_heap, int arrayLength){
    //heapify the elements from the last parent node
    
} */

/* void heap_sort {
    
} */