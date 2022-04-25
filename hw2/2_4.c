#include <stdio.h>
#include <stdlib.h>


typedef struct node{
    int final_point;
    int on_the_main_road;
    struct node *next;
    int index;
} NODE;

void add_node(int index, int index_2, NODE *adj_list);
NODE *adj_list_init(int N);
void print_node(NODE *adj_list, int N);

//1 + N-1 + Q lines of input

int main(void) {
    int N, Q, S, R;

    scanf("%d", &N); // Number of cities  10^6
    //a, b, c, s,S, R <= N
    scanf("%d", &Q); // Number of queries 10^6
    scanf("%d", &S); // Capital city 
    scanf("%d", &R); // Resort City

    //Set adjencency list
    ///NODE *adj_list = (NODE *)malloc((N+1) * sizeof(NODE));
    NODE *adj_list = adj_list_init(N);

    print_node(adj_list, N);

    //Adjacency initialization
    
    
    //malloc test
    //printf("%p\n", adj_list[999999].next);

    

    //To find the stack of the main_road
    //main_road = DFS(capital, prev, 0) Use 0 to set final_point. Use prev to prevent double visting
    
    //To set elements inside main_road to itself
    //void set_itself(main_road)

    //for elements inside main_road
    //  DFS(element, element.value) //if the adjencnecy nodes of the nodes.main_road = 0, then do dfs
    
    //final_point = check final point(adjencency_list)
    
    //print_elements(final_point)
        
}


NODE *adj_list_init(int N) {
    NODE *adj_list = (NODE *)malloc((N+1) * sizeof(NODE));
    //To record nodes
    for (int i = 0; i < N-1; i++) {
        int a1, a2;
        
        scanf("%d",&a1);
        scanf("%d",&a2);
        
        //Add adjencency nodes to the specific node
        
        add_node(a1, a2, adj_list);
        
        add_node(a2, a1, adj_list);                
    }
    return adj_list;
}

void add_node(int index, int index_2, NODE *adj_list) {
    NODE *tmp = adj_list+index;
     while (tmp->next != NULL) {
        tmp = tmp -> next;
    }
    
    tmp->next = (NODE *)malloc(sizeof(NODE));
    tmp->next->final_point = 0;
    tmp->next->next = NULL;
    tmp->next->on_the_main_road = 0;    
    tmp->next->index = index_2;
}

void print_node(NODE *adj_list, int N) {
    
    for (int i = 1; 1 <= N; i++) {
        NODE *tmp = (adj_list+i)->next;        
        while (tmp != NULL) {
            printf("%d\n", tmp->index);
            tmp = tmp->next;
        }
    //printf("\n\n");
    }
        //printf("n");
}