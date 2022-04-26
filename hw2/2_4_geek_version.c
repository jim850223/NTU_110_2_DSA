#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Stack {
    int top;
    unsigned capacity;
    int* array;
}STACK;

// A structure to represent an adjacency list node
typedef struct AdjListNode {
    int final_point;
    int on_the_main_road;
    int index;
    struct AdjListNode* next;
}NODE;
 
// A structure to represent an adjacency list
typedef struct AdjList {
    NODE* head;
}ADJ_LIST;
 

typedef struct Graph {
    int V;
    ADJ_LIST* array;
}GRAPH;
 
NODE* newAdjListNode(int index);
struct Graph* createGraph(int V);
void addEdge(struct Graph* graph, int src, int index);
void printGraph(struct Graph* graph);
void adj_list_init(int N, GRAPH *graph);
STACK *createStack(unsigned capacity);
int isFull(struct Stack* stack);
int isEmpty(struct Stack* stack);
void push(struct Stack* stack, int item);
int pop(struct Stack* stack);
int dfs_capital_version(int prev_value, NODE *entry_point, GRAPH *graph, STACK *stack,int capital, int on_the_main_road);
 
// Driver program to test above functions
int main()
{

   int N, Q, S, R;

    scanf("%d", &N); // Number of cities  10^6
    //a, b, c, s,S, R <= N
    scanf("%d", &Q); // Number of queries 10^6
    scanf("%d", &S); // Capital city 
    scanf("%d", &R); // Resort City
    
    struct Graph* graph = createGraph(N+1);
    adj_list_init(N, graph);
    printGraph(graph);
    STACK *stack = createStack(N+1);
    NODE *tmp = graph->array[R].head;
    push(stack, R);
    while (tmp != NULL)  {
            push(stack, tmp->index);
            if (tmp->index == S) {
                //printf("aa\n");                            
                break;
            }
            else {        
                int result = dfs_capital_version(R, tmp, graph, stack, S, 0);
                if (result == 1){
                    break;
                }
                //printf("count%d\n", count);                            
                tmp = tmp->next;
                pop(stack);
            }
        }

    while (isEmpty(stack) != 1) {
        //printf("hello??\n");
        printf("%d\n", pop(stack));
        }
    //printf("%d\n", graph->array[1].head->index);
    //printf("%d\n", graph->array[1].head->next->index);
    //printf("%d\n", graph->array[1].head->next->next->index);
    
/*     while (isEmpty(stack) != 0) {
        printf("%d\n", pop(stack));
    } */

    

    

}


NODE* newAdjListNode(int index)
{
    NODE* newNode = (NODE*)malloc(sizeof(NODE));
    newNode->index = index;
    newNode->next = NULL;
    newNode->final_point = 0;
    newNode->on_the_main_road = 0;
    return newNode;
}
 
// A utility function that creates a graph of V vertices
struct Graph* createGraph(int V)
{
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
 
    // Create an array of adjacency lists.  Size of
    // array will be V
    graph->array = (ADJ_LIST*)malloc(V * sizeof(ADJ_LIST));
 
    // Initialize each adjacency list as empty by
    // making head as NULL
    int i;
    for (i = 0; i < V; ++i)
        graph->array[i].head = NULL;
    
    return graph;
}
 
// Adds an edge to an undirected graph
void addEdge(struct Graph* graph, int src, int dest)
{
    // Add an edge from src to dest.  A new node is
    // added to the adjacency list of src.  The node
    // is added at the beginning
    NODE* check = NULL;
    NODE* newNode = newAdjListNode(dest);
 
    if (graph->array[src].head == NULL) {
        //newNode->next = graph->array[src].head;
        graph->array[src].head = newNode;
    }
    else {
 
        check = graph->array[src].head;
        while (check->next != NULL) {
            check = check->next;
        }
        // graph->array[src].head = newNode;
        check->next = newNode;
    }
 
    // Since graph is undirected, add an edge from
    // dest to src also
    newNode = newAdjListNode(src);
    if (graph->array[dest].head == NULL) {
        //newNode->next = graph->array[dest].head;
        graph->array[dest].head = newNode;
    }
    else {
        check = graph->array[dest].head;
        while (check->next != NULL) {
            check = check->next;
        }
        check->next = newNode;
    }
 
    // newNode = newAdjListNode(src);
    // newNode->next = graph->array[dest].head;
    // graph->array[dest].head = newNode;
}
 
// A utility function to print the adjacency list
// representation of graph
void printGraph(struct Graph* graph)
{
    int v;
    for (v = 0; v < graph->V; ++v) {
        NODE * pCrawl = graph->array[v].head;
        printf("\n Adjacency list of vertex %d\n head ", v);
        while (pCrawl) {
            printf("-> %d", pCrawl->index);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
}

void adj_list_init(int N, GRAPH *graph) {
    for (int i = 0; i < N-1; i++) {
        int a1, a2;
        scanf("%d",&a1);
        scanf("%d",&a2);
        
        //Add adjencency nodes to the specific node
        addEdge(graph, a1, a2);                
    }
}

// function to create a stack of given capacity. It initializes size of
// stack as 0
STACK *createStack(unsigned capacity)
{
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}
 
// Stack is full when top is equal to the last index
int isFull(struct Stack* stack)
{
    return stack->top == stack->capacity - 1;
}
 
// Stack is empty when top is equal to -1
int isEmpty(struct Stack* stack)
{
    return stack->top == -1;
}
 
// Function to add an item to stack.  It increases top by 1
void push(struct Stack* stack, int item)
{
    if (isFull(stack))
        return;
    stack->array[++stack->top] = item;
    printf("%d pushed to stack\n", item);
}
 
// Function to remove an item from stack.  It decreases top by 1
int pop(struct Stack* stack)
{
    if (isEmpty(stack))
        return INT_MIN;
    return stack->array[stack->top--];
}

int dfs_capital_version(int prev_value, NODE *entry_point, GRAPH *graph, STACK *stack,int capital, int on_the_main_road) {
    //Use NODE * instead of int to set prev to prevent segmentation fault
    
    int present_v = entry_point->index;
    //NODE *adj_value = graph->array[tmp->index].head;
    NODE *adj_value = graph->array[entry_point->index].head;
    
    while (adj_value != NULL)  {
        

        if (adj_value->index != capital && adj_value->index != prev_value) {
            //printf("cc\n");
            push(stack, adj_value->index);
            //printf("check\n");
            //printf("%d\n", adj_value->index);
            //printf("%d\n", prev_value);            
            int result = dfs_capital_version(entry_point->index, adj_value, graph, stack, capital, 0);
            if (result == 1) {
                return 1;
            }
            //printf("finish\n");
            pop(stack);
            
            adj_value = adj_value->next;
        }
        else if (adj_value->index == capital) {
            //printf("aa\n");
            push(stack, adj_value->index);
            return 1;
        }        
        
        else if (adj_value->index == prev_value) {            
            //printf("bb\n");
            //printf("%d\n", adj_value->index);
            //printf("%d\n", prev_value);            
            adj_value = adj_value->next;                        
        }
    
    }
    return 0;
}
/* 
7 4 6 2
1 5 5 6 1 2 2 4 2 7 7 3
  */

/* //Backup
int dfs_capital_version(int value, NODE *entry_point, GRAPH *graph, STACK *stack,int capital, int on_the_main_road) {
    //Use NODE * instead of int to set prev to prevent segmentation fault
    
    NODE *tmp = entry_point;
    int adj_value = graph->array[tmp->index].head->index;
    int prev_tmp = value;
    while (tmp != NULL)  {
        
         if (prev == NULL && tmp->index != capital) {
            push(stack, tmp->index);
            dfs_capital_version(tmp, graph, stack, capital, prev_tmp, 0);
            pop(stack);
            prev_tmp = tmp;
            tmp = tmp->next;
        }
        else if (prev == NULL && tmp->index == capital) {
            push(stack, tmp->index);
            return 1;            
        } 
        

        if (tmp->index != capital && graph->array[tmp->index].head->index != prev_tmp) {
            printf("cc\n");
            push(stack, tmp->index);
            printf("%d\n", tmp->index);
            printf("%d\n", prev_tmp);
            printf("%d\n",graph->array[tmp->index].head->index );
            dfs_capital_version(tmp->index, graph->array[tmp->index].head, graph, stack, capital, 0);
            pop(stack);
            
            tmp = tmp->next;
        }
        else if (graph->array[tmp->index].head->index == prev_tmp) {            
            printf("bb\n");
            printf("%d\n", tmp->index);
            printf("%d\n", prev_tmp);
            printf("%d\n",graph->array[tmp->index].head->index );
            tmp = tmp->next;  
            printf("%d???\n", tmp->index);
            
        }
        
        else if (tmp->index == capital) {
            printf("aa\n");
            push(stack, tmp->index);
            return 1;
        }        
    }
    return 0;
} */