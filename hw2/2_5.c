#include <stdio.h>
#include <stdlib.h>
#include "price.h"

//Index of root = 1

//To record the stock of the k point
typedef struct {
    long long unsigned value;
    int stock;
    int where;
}K_POINT;

typedef struct {
    int t;
    int stock;
}STOCK_INFO;

void print_elements(unsigned long long *output, int Q);
unsigned long long *get_output (int Q, int s1);
STOCK_INFO *create_Brians_favorites(int A, int N);
K_POINT *make_Brians_favorites_to_a_min_heap (STOCK_INFO *bStocks, int A, int N);
void get_prices_store_into_the_array(STOCK_INFO *bStocks, K_POINT *min_heap, int A, int N);
void heapify(K_POINT *group_of_nodes, int index, int range);
void build_the_heap (K_POINT *group_of_nodes, int range);
K_POINT *heap_sort(K_POINT *heap, int range);
K_POINT *heap_sort_with_new_value(K_POINT *heap, int range, STOCK_INFO *bStocks);
unsigned long long *save_query(K_POINT *sorted_array, int Q);


int main(void) {

    int A, Q, N;

    scanf("%d", &A); //A denotes the number of Brian's favorite stocks
    scanf("%d", &Q); //Q denotes the number of questions
    scanf("%d", &N); //N defines how long each stock is guranted to increase its price, as mentioned above
    
    //Create an array to store Brian's favorite stocks
    STOCK_INFO *bStocks = create_Brians_favorites(A, N);

    
    //Build a min heap which is comprised of A * n nodes from Brian's A favorites stocks


    //Declare an 10^6 array to store the result of the heap sort with a given heap and add new elements into the array at the same time
    
            
    //Testing section for heap_sort
    K_POINT *min_heap = (K_POINT *)malloc(A * N * sizeof(K_POINT));
    get_prices_store_into_the_array(bStocks, min_heap, A, N);
    //print_elements(min_heap, A * N);    
    //printf("\n\n");
    
    build_the_heap (min_heap, A * N);
    
    //print_elements(min_heap, A * N);
    //printf("\n\n");
    //K_POINT *result = heap_sort(min_heap, A * N);

    K_POINT * result = heap_sort_with_new_value(min_heap, A * N, bStocks);

    unsigned long long * final_result = save_query(result, Q);
    print_elements(final_result, Q);
    
    //print_elements(result, 100);
    
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
void print_elements(unsigned long long *output, int Q) {
    for (int i = 1; i <= Q; i++) {
        printf("%llu\n", output[i]);        
        //printf("%d\n", output[i].stock);
    }
}


//Create an array to store Brian's favorite stocks
//Checked
STOCK_INFO *create_Brians_favorites(int A, int N) {
        int As;//To store Brian's favorite stocks
    
        STOCK_INFO *bStocks = (STOCK_INFO *)malloc(A * sizeof(STOCK_INFO));        
        for (int i = 0; i < A; i++) {
            scanf("%d", &As);        
            bStocks[i].stock = As;
            bStocks[i].t = N;
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
void get_prices_store_into_the_array(STOCK_INFO *bStocks, K_POINT *min_heap, int A, int N) {
    //To record the index of the array
    int count = 1;
    //To determine which stock to choose
    for (int i = 0; i < A; i++) {
        //To determin which day to choose from 1
        for (int j = 1; j <= N; j++) {
            //Store the prices into the heap
            min_heap[count].value = price(bStocks[i].stock, j);
            min_heap[count].stock = bStocks[i].stock;
            min_heap[count].where = i;
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
            int tmp_stock = group_of_nodes[small].stock;
            int tmp_where = group_of_nodes[small].where;

            group_of_nodes[small].value = group_of_nodes[index].value;
            group_of_nodes[small].stock = group_of_nodes[index].stock;    
            group_of_nodes[small].where = group_of_nodes[index].where;    
            
            group_of_nodes[index].value = tmp;
            group_of_nodes[index].stock = tmp_stock;
            group_of_nodes[index].where = tmp_where;

            heapify(group_of_nodes, small, range);
        }
    }
    }
}

void build_the_heap(K_POINT *group_of_nodes, int range) {
    for (int i = range/2; i > 0; i-- ) {
        heapify(group_of_nodes, i, range);
    }
}

K_POINT *heap_sort(K_POINT *heap, int range) {
    K_POINT *sortted_array = (K_POINT *)malloc(range * (sizeof(sortted_array)) + 1);
    for (int i = 1; i <= range; i++) {
        
        sortted_array[i].value = heap[1].value;
        
        heap[1].value = heap[range+1-i].value;
        
        heapify(heap, 1, range+1-i);
    }
    return sortted_array;
}

 K_POINT *heap_sort_with_new_value(K_POINT *heap, int range, STOCK_INFO *bStocks) {
    
    K_POINT *sortted_array = (K_POINT *)malloc(1000001 * (sizeof(K_POINT)));
    
    for (int i = 1; i <= 1000000; i++) {
        //printf("%llu\n", heap[1].value);
        sortted_array[i].value = heap[1].value;
        bStocks[heap[1].where].t++;
        
        //Which stock to predict and which t to choose
        heap[1].value = price(heap[1].stock, bStocks[heap[1].where].t);        
        //printf("%llu\n", heap[1].value);
        heapify(heap, 1, range);
    }

    return sortted_array;
}

unsigned long long *save_query(K_POINT *sorted_array, int Q) {
    int x;
    int k;
    unsigned long long *result = (unsigned long long *)malloc((Q+1) * sizeof(unsigned long long));
    for (int i = 1; i <= Q; i++) {
        scanf("%d", &x);
        scanf("%d", &k);
        result[i] = sorted_array[k].value;
    }
    return result;
}




