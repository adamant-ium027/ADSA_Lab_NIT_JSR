// Create a linked list and perform all the operations: insertion, deletion, searching and traversing.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node{
    int info;
    struct Node *next;
};

struct Node *insertion(struct Node *, int);
struct Node *deletion(struct Node *, int);
bool searching(struct Node *, int);
void traverse(struct Node *);


int main(void){
    struct Node *single_ll = NULL;

    int key;
    int insert_value;
    int del_value;
    int search_value;

    printf("Enter 1 for insertion:\n");
    printf("Enter 2 for deletion:\n");
    printf("Enter 3 for searching:\n");
    printf("Enter 4 for traversing:\n");
    printf("Enter 5 to quit:\n\n");

    do{
        printf("Enter: ");
        scanf("%d", &key);

        switch(key){
            case 1:
                printf("Enter number to be inserted: ");
                scanf("%d", &insert_value);
                printf("\n");
                single_ll = insertion(single_ll, insert_value);
                break;

            case 2:
                printf("Enter value to be deleted: ");
                scanf("%d", &del_value);
                printf("\n");
                single_ll = deletion(single_ll, del_value);
                break;
            
            case 3:
                printf("Enter element to be searched: ");
                scanf("%d", &search_value);
                if(searching(single_ll, search_value)) printf("It belongs to the linked list.\n\n");
                else printf("It does not belongs to the linked list\n\n");
                break;

            case 4:
                printf("The current linked list looks like:\n");
                traverse(single_ll);
                break;

            default:
                exit(1);
        }
    }while(true);



    return 0;
}

struct Node *insertion(struct Node *single_ll, int insert_value){
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    temp->info  = insert_value;
    temp->next = NULL;

    if(single_ll == NULL){
        return temp;
    }
    else{
        struct Node *ptr = single_ll;
        while(ptr->next != NULL){
            ptr = ptr->next;
        }
        ptr->next = temp;
        return single_ll;
    }
}

struct Node *deletion(struct Node *single_ll, int del_value){
    if(!searching(single_ll, del_value) || single_ll == NULL) return single_ll;

    struct Node *ptr, *temp_ptr;

    // delete at begining
    if(single_ll->info == del_value){
        temp_ptr = single_ll->next;
        free(single_ll);
        return temp_ptr;
    }
    
    // delete at elsewhere
    ptr = single_ll;
    while(ptr->next->info != del_value && ptr->next->next != NULL){
        ptr = ptr->next;
    }
    temp_ptr = ptr->next->next;
    free(ptr->next);
    ptr->next = temp_ptr;

    return single_ll;
}

bool searching(struct Node *single_ll, int search_value){
    struct Node *ptr = single_ll;

    while(ptr != NULL && ptr->info != search_value){
        ptr = ptr->next;
    }

    if(ptr != NULL) return true; // if the req. value is present in the linked list then the 'ptr' can never contain NULL.
    return false;
}


void traverse(struct Node *single_ll){
    if(single_ll == NULL){
        printf("The current linked list is empty.\n\n");
        return;
    }

    struct Node *ptr =  single_ll;
    while(ptr){
        printf("%d ", ptr->info);
        ptr = ptr->next;
    }
    
    printf("\n\n");
}