/*  -------------------------------------------------------------------- 
    dict.h 
    Created by Amethyst Bibby (arbibby@student.unimelb.edu.au) 27/08/20 
    
    Contains #include directives, type defs and function prototypes
    for dict.c
    --------------------------------------------------------------------
*/

#ifndef DICT_H
#define DICT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_FIELD_LENGTH 128
#define MAX_LINE_LENGTH 512

#define QUOTE '\"'
#define COMMA ','

#define TRUE 1
#define FALSE 0

// stores a line of max length from csv file
typedef char line_t[MAX_LINE_LENGTH + 1]; 
// stores a field of max length from line
typedef char field_t[MAX_FIELD_LENGTH + 1];

// field data from a line
// all fields are stored as strings
typedef struct {
    field_t census_year; // Census year
    field_t blockID; // Block ID
    field_t propertyID; // Property ID
    field_t base_propertyID; // Base property ID
    field_t clue; // Clue small area
    field_t trading_name; // Trading name (used as key)
    field_t code; // Industry (ANZSIC4) code
    field_t description; // Industry (ANZSIC4) description
    field_t x; // x coordinate
    field_t y; // y coordinate
    field_t location; // Location coordinates
} data_t; 

void parse_line(line_t line, data_t *record);
void classify_field(field_t field, data_t *line_data, int field_count);
void print_data(data_t *record);
void fprint_data(field_t key, data_t *record, FILE *fp);

#endif
