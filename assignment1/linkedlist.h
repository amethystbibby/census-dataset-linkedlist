/*  --------------------------------------------------------------------
    linkedlist.h 
    Created by Amethyst Bibby (arbibby@student.unimelb.edu.au) 27/08/20 
    
    Contains #include directives, type defs and function prototypes
    for linkedlist.c  
    --------------------------------------------------------------------
*/

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "dict.h"

typedef struct node {
    data_t *record;
    struct node *next;
} node_t;

typedef node_t* node_ptr;

typedef struct {
    node_ptr head;
    size_t size;
} list_t;

list_t *create_list();
node_ptr create_node(data_t *record);
list_t *add_node(list_t *list, data_t *data);

int search(list_t *list, field_t key);
data_t *get_node(list_t *list, field_t key);
void delete_node(list_t *list, field_t key);
void free_list(list_t *list);

#endif
