#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct member {
    int id;
    struct member *next;
    //struct member *prev;
}MEMBER;

typedef struct {
    MEMBER *head;
    MEMBER *end;
    //int reverse;
}MEMBER_QUEUE;

typedef struct group {
    //If you want to declare the struct you define in the struct itself, you have to declare it with struct group
    int group_num;
    struct group *next;
    //struct group *prev;
    MEMBER_QUEUE *member_queue;
}GROUP;

typedef struct {
    GROUP *head;
    GROUP *end;    
    //int reverse;
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
void print_every_bathrooms(int bathrooms_quantity, BATHROOM_INFO *bathroom_in_store);
void print_the_bathroom_queue(int bathroom_num, BATHROOM_INFO *bathroom_in_store);
void print_the_member_queue(GROUP *group);
void connect_group_to_group_queue(GROUP *group_pointer, int bathroom_num, BATHROOM_INFO *bathroom_in_store);
GROUP *find_the_second_last_group(GROUP_QUEUE *group_queue);
MEMBER *find_the_second_last_member(MEMBER_QUEUE *member_queue);
void leave(int bathroom_num, BATHROOM_INFO *bathroom_in_store);
void mission_to_do(char *mission, int group, int id, int bathroom, BATHROOM_INFO *bathroom_in_store);

int main(void) {


    printf("Please enter the criteria (i.e. bathrooms, situations, group):\n");
    int bathrooms_quantity, situations, groups;
    scanf("%d", &bathrooms_quantity);
    scanf("%d", &situations);
    scanf("%d", &groups);

    BATHROOM_INFO bathroom_in_store[bathrooms_quantity];
    bathroom_init(bathroom_in_store, bathrooms_quantity);
    
    char *mission = (char *)malloc(6*sizeof(char));
    int group, member_id, bathroom, i = 0;
    while (i++ < situations) {
        printf("Please enter the instructions (i.e. mission, group, id, bathroom):\n");
        scanf(" %s",mission);    
        mission_to_do(mission, group, member_id, bathroom, bathroom_in_store);        

    }
    
    print_every_bathrooms(bathrooms_quantity, bathroom_in_store);
}
/* 
    
    print_the_bathroom_queue(1,bathroom_in_store); */

    
/*     group_num = 1;
    while (group_num != 0) {
        scanf("%d", &bathroom_num);
        leave(bathroom_num, bathroom_in_store);
        scanf("%d", &group_num);
    } */



    //leave(1, bathroom_in_store);
    //print_the_bathroom_queue(1,bathroom_in_store);
    



    //GROUP *tmp = find_the_second_last_group(bathroom_in_store[1].group_queue);
    //printf("\n");
    //print_the_member_queue(tmp);
    //printf("\n");
    //MEMBER *tmp_2 = find_the_second_last_member(tmp->member_queue);
    //printf("%d", tmp_2->id);

    //print_the_bathroom_queue(2,bathroom_in_store);


//Initialize every element of th array
void bathroom_init(BATHROOM_INFO *bathroom_in_store, int bathrooms_quantity) {
    for (int i = 0; i < bathrooms_quantity; i++) {
        //It can be simplified with only one variable declared
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
    new_group->next = NULL;    
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

void print_every_bathrooms(int bathrooms_quantity, BATHROOM_INFO *bathroom_in_store) {
    for (int i = 0; i < bathrooms_quantity; i++) {
        print_the_bathroom_queue(i, bathroom_in_store);
    }
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

void leave(int bathroom_num, BATHROOM_INFO *bathroom_in_store) {
    
    GROUP_QUEUE *group_queue = bathroom_in_store[bathroom_num].group_queue;
    //Means that there is only one group left in the group_queue
    if (group_queue->end == group_queue->head) {
        
        //If there is only 1 member left
        if (group_queue->end->member_queue->end == group_queue->end->member_queue->head) {
            //free(group_queue->head->member_queue->head);
            //free(group_queue->head->member_queue);
            group_queue->end->member_queue->end = NULL;
            group_queue->end->member_queue->head = NULL; 


            //Only need to do once since the head and the last point to the same address
            //free(group_queue->head);

            group_queue->end->member_queue = NULL;
            
            group_queue->head = NULL;
            group_queue->end = NULL;                                                            
        }

        //Otherwise, there are more than 1 members left
        else {
            MEMBER *new_last_member = find_the_second_last_member(group_queue->head->member_queue);
            //Free the last member of the queue
            //free(group_queue->end->member_queue->end);            
            new_last_member->next = NULL;
            group_queue->end->member_queue->end = new_last_member;                                    
        }                         
    }
    //Otherwise, there is more than one group in the group_queue
    else {
        //If there is only 1 member left
        if (group_queue->end->member_queue->end == group_queue->end->member_queue->head) {
            //free(group_queue->head->member_queue->head);
            //free(group_queue->head->member_queue);
            GROUP *new_last_group = find_the_second_last_group(group_queue);
            //free(group_queue->end);
            new_last_group->next = NULL;
            group_queue->end = new_last_group;            
        }
        //If there are more than 1 members left
        else {
            MEMBER *new_last_member = find_the_second_last_member(group_queue->end->member_queue);
            //Free the last member of the queue
            //free(group_queue->end->member_queue->end);            
            new_last_member->next = NULL;
            group_queue->end->member_queue->end = new_last_member;                                    
        } 
    }                        
}

void mission_to_do(char *mission, int group, int member_id, int bathroom, BATHROOM_INFO *bathroom_in_store) {        
    if (strcmp("enter", mission) == 0) {
        scanf("%d",&member_id);
        scanf("%d",&group);
        scanf("%d",&bathroom);
        enter(member_id, group, bathroom, bathroom_in_store);

        print_the_bathroom_queue(bathroom, bathroom_in_store);
        //printf("%s, %d, %d, %d!\n",mission, group, id, bathroom);
    }
    else if (strcmp("leave", mission) == 0) {
        scanf("%d",&bathroom);
        leave(bathroom, bathroom_in_store);
        //printf("leave\n");
        print_the_bathroom_queue(bathroom, bathroom_in_store);
    }
    else if (strcmp("go", mission) == 0){
    }
    else {
        printf("please follow the rule bro!\n");
    }
}


GROUP *find_the_second_last_group(GROUP_QUEUE *group_queue) {
    GROUP *tmp = group_queue->head;
    while (tmp->next != group_queue->end) {
        tmp = tmp->next;
    }
    return tmp;
}

MEMBER *find_the_second_last_member(MEMBER_QUEUE *member_queue) {
    MEMBER *tmp = member_queue->head;
    while (tmp->next != member_queue->end) {
        tmp = tmp->next;
    }
    return tmp;
}

void go() {    
}

void close() {
}