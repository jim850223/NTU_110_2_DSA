#include <stdio.h>
#include <stdlib.h>

typedef struct member {
    int id;
    struct member *next;
}MEMBER;

typedef struct {
    MEMBER *head;
    MEMBER *end;
}MEMBER_QUEUE;

typedef struct group {
    //If you want to declare the struct you define in the struct itself, you have to declare it with struct group
    int group_num;
    struct group *next;
    MEMBER_QUEUE *member_queue;
}GROUP;

typedef struct {
    GROUP *head;
    GROUP *end;    
}GROUP_QUEUE;


typedef struct {
    //Close is used to record whether the toilet is closed or not
    int close;
    GROUP_QUEUE *group_queue; 
}BATHROOM_INFO;

void bathroom_init(BATHROOM_INFO *bathroom_in_store, int bathrooms_num);
GROUP *group_init(int group_num, int member_id);
GROUP *find_group(int group_num, int bathroom_num, BATHROOM_INFO *bathroom_in_store);
void join_group(int id, GROUP *group_pointer, int bathroom_num, BATHROOM_INFO *bathroom_in_store);
void enter(int member_id, int group_num, int bathroom_num, BATHROOM_INFO *bathroom_in_store);
void print_the_bathroom_queue(int bathroom_num, BATHROOM_INFO *bathroom_in_store);
void print_the_member_queue(GROUP *group);
void connect_group_to_group_queue(GROUP *group_pointer, int bathroom_num, BATHROOM_INFO *bathroom_in_store);

int main(void) {    
    int bathrooms_quantity, situations, groups;
    scanf("%d", &bathrooms_quantity);
    scanf("%d", &situations);
    scanf("%d", &groups);
    
    BATHROOM_INFO bathroom_in_store[bathrooms_quantity];
    bathroom_init(bathroom_in_store, bathrooms_quantity);        
    
    //Make group_num = 1 to enter the while loop
    int member_id, group_num = 1, bathroom_num;
    
    //Ask for the member info
    while (group_num != 0) {
        scanf("%d", &member_id);    
        scanf("%d", &group_num);
        scanf("%d", &bathroom_num);
        enter(member_id, group_num, bathroom_num, bathroom_in_store);
    }

    print_the_bathroom_queue(1,bathroom_in_store);
    print_the_bathroom_queue(2,bathroom_in_store);
}

//Initialize every element of th array
void bathroom_init(BATHROOM_INFO *bathroom_in_store, int bathrooms_quantity) {
    for (int i = 0; i < bathrooms_quantity; i++) {
        GROUP_QUEUE *group_queue = (GROUP_QUEUE *) malloc(sizeof(GROUP_QUEUE));
        group_queue->head = NULL;
        group_queue->end = NULL;
        bathroom_in_store[i].close = 0;
        bathroom_in_store[i].group_queue = group_queue;
    }
}

//Initiate a group with a given group_num and given member_id which can be used to initiate a member_queue
GROUP *group_init(int group_num, int member_id) {
    //Started from the minimum part of thw group, a.k.a. first member of the group
    MEMBER *first_member = (MEMBER *) malloc(sizeof(MEMBER));
    first_member->id = member_id;
    first_member->next = NULL;
    MEMBER_QUEUE *new_member_queue = (MEMBER_QUEUE *) malloc(sizeof(MEMBER_QUEUE));
    new_member_queue->head = first_member;
    new_member_queue->end = first_member;
    GROUP *new_group = (GROUP *) malloc(sizeof(GROUP));
    new_group->group_num = group_num;
    new_group->member_queue = new_member_queue;
    return new_group;
}


//Find the pointer of the group, or return NULL
GROUP *find_group(int group_num, int bathroom_num, BATHROOM_INFO *bathroom_in_store) {
    //Use tmp to save the current position of the group which you are checking
    GROUP *tmp = bathroom_in_store[bathroom_num].group_queue->head;
    while (tmp != NULL) {
        if (tmp->group_num == group_num) {
            return tmp;
        }
        else {
            tmp = tmp->next;
        }
    }
    return tmp;
}

//Put the member into the group
void join_group(int id, GROUP *group_pointer, int bathroom_num, BATHROOM_INFO *bathroom_in_store) {
    MEMBER *new_member = (MEMBER *) malloc(sizeof(MEMBER));
    new_member->id = id;
    new_member->next = NULL;
    
    MEMBER_QUEUE *target_member_queue = group_pointer->member_queue;
    target_member_queue->end->next = new_member;
    target_member_queue->end = new_member;    
}


void enter(int member_id, int group_num, int bathroom_num, BATHROOM_INFO *bathroom_in_store) {
    //choose the correct bathroom
    //while the i bathroom is closed, go to the i-1 bathroom.if the 0 bathroom is closed then go to the bathroom[bathroom_quantity-1]
    
    if (bathroom_in_store[bathroom_num].group_queue->head == NULL) {
        GROUP *new_group = group_init(group_num, member_id);
        bathroom_in_store[bathroom_num].group_queue->head = new_group;
        bathroom_in_store[bathroom_num].group_queue->end = new_group;
    }
    else {        
        GROUP *group_pointer = find_group(group_num, bathroom_num, bathroom_in_store);
        if (group_pointer != NULL) {            
            join_group(member_id, group_pointer, bathroom_num, bathroom_in_store);
            
        }
        else {
            GROUP *new_group = group_init(group_num, member_id);        
            bathroom_in_store[bathroom_num].group_queue->end->next = new_group;        
            bathroom_in_store[bathroom_num].group_queue->end = new_group;        
        }
    }
}

//Used to connect the group to the group_queue which has no group inside it 
void connect_group_to_group_queue(GROUP *group_pointer, int bathroom_num, BATHROOM_INFO *bathroom_in_store) {
    bathroom_in_store[bathroom_num].group_queue->head = group_pointer;
    bathroom_in_store[bathroom_num].group_queue->end = group_pointer;
}

void print_the_bathroom_queue(int bathroom_num, BATHROOM_INFO *bathroom_in_store) {
    GROUP *tmp = bathroom_in_store[bathroom_num].group_queue->head;
    while(tmp != NULL) {
        print_the_member_queue(tmp);
        tmp = tmp->next;
    }
    printf("\n");
}

void print_the_member_queue(GROUP *group) {
    MEMBER *tmp = group->member_queue->head;
    while(tmp != NULL) {
        printf("%d ", tmp->id);
        tmp = tmp->next;
        }
}

void leave() {
}

void go() {    
}

void close() {
}