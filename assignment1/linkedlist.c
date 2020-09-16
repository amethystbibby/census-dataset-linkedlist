/*  --------------------------------------------------------------------
    linkedlist.c 
    Created by Amethyst Bibby (arbibby@student.unimelb.edu.au) 27/08/20 
    
    Contains functions for creating/freeing a linked list, creating 
    nodes and adding/deleting them from a linked list, and searching
    for/retrieving a specific node by key.
    --------------------------------------------------------------------
*/

#include "linkedlist.h"

// allocates and initialises a new node
node_ptr
create_node(data_t *record) {
    // allocate space for node
    node_ptr newnode = malloc(sizeof(node_t)); 
    assert(newnode != NULL);
    
    // initialise members
    newnode->record = record; 
    newnode->next = NULL;
    
    return newnode;
} 

// creates a linked list and initialises list head and size
list_t
*create_list() {   
    // create linked list to store records
    list_t *list;
    list = (list_t*)malloc(sizeof(list_t));
    assert(list != NULL);
    
    // initialise head values
    node_ptr head = NULL;
    list->head = head;
    
    list->size = 0;
    
    return list;
}

// adds a node to a linked list
list_t
*add_node(list_t *list, data_t *data) {
    // create new node
    node_ptr new_node;
    new_node = create_node(data);
    
    assert(list!= NULL && new_node != NULL);

    // create first node in list
    if(list->head == NULL) {
        new_node->next = list->head;
        list->head = new_node;
    } else {
        // finds last node to add new node at the end of the list
        node_ptr temp = list->head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        // allocate next node and change head to new node
        new_node->next = NULL;
        temp->next = new_node;
    }
    list->size++;
    
    return list;
}


// checks whether or not a key exists in the linked list, returns a boolean
int
search(list_t *list, field_t key) {
    assert(list != NULL && list->head != NULL);
    
    // initialise current node to head node
    node_ptr current = list->head;
   
    // iterates through list until key node is found
    while(current != NULL) {        
        if (strcmp(current->record->trading_name, key) == 0) {
            return TRUE;
        }
        current = current->next;
    }
    return FALSE;
} 

// retrieves data associated with a node
data_t
*get_node(list_t *list, field_t key) {
    assert(list != NULL && list->head != NULL);
    
    // iterate through list until key node is found
    node_ptr current = list->head;
    while(current != NULL) {
        if (strcmp(current->record->trading_name, key) == 0) {
            return (current->record);
        }
        current = current->next;
    }
    
    return NULL;
}

// deletes a node from a linked list with a specific key
void
delete_node(list_t *list, field_t key) {
    assert(list != NULL && list->head != NULL);
    
    node_ptr to_delete = list->head, temp;
    
    // if head node contains key
    if (strcmp(to_delete->record->trading_name, key) == 0) {
        // unlink and free node
        list->head = to_delete->next;
        free(to_delete);
        return;
    }
    
    // iterate through linked list until key node is found
    while (to_delete != NULL) {
        if (strcmp(to_delete->record->trading_name, key) == 0) {
            // unlink and free node
            temp->next = to_delete->next;
            free(to_delete);
            return;
        }
        temp = to_delete;
        to_delete = to_delete->next;   
    }
    return;
}

// frees linked list and all nodes within it
void
free_list(list_t *list) {
    node_ptr current = list->head;
    
    // iterate over each node
    while(current) {
        // change to next node and free current node
        node_ptr to_free = current;
        current = current->next;
        free(to_free->record);
        free(to_free);
    }
    
    // free empty list
    free(list);
    return;
}
