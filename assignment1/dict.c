/*  -------------------------------------------------------------------- 
    dict.c 
    Created by Amethyst Bibby (arbibby@student.unimelb.edu.au) 27/08/20 
    
    Contains functions for parsing a line of csv input and extracting
    field data, classifying field data appropriately and printing out 
    data to a file. Main function manages file manipulation and 
    drives dictionary operations.
    --------------------------------------------------------------------
*/

#include "dict.h"
#include "linkedlist.h"

int
main(int argc, char *argv[]) {    
    // open input file
    FILE *input_fp = fopen(argv[1], "r");
    if (input_fp == NULL) {
        printf("Could not open input file\n");
        return 1;
    }
        
    // open output file
    FILE *output_fp = fopen(argv[2], "w");
    if (output_fp == NULL) {
        printf("Could not open output file\n");
        return 1;
    }    
    
    // create linked list to store records
    list_t *record_list = create_list();

    line_t line;
    // read file one record at a time
    while(fgets(line, MAX_LINE_LENGTH, input_fp) != NULL) {
        data_t *record = malloc(sizeof(data_t));
        assert(record != NULL);
        
        // store record in struct
        parse_line(line, record);
        
        // assign each record to a node in linked list
        *record_list = *add_node(record_list, record);
    }

    // output relevant record for each key read from stdin
    field_t key;
    while(fgets(key, MAX_FIELD_LENGTH, stdin)) {
        // remove trailing newline from key
        char *token;
        token = strtok(key, "\n");
        
        // check if key exists in list
        if (search(record_list, key) == FALSE) {
            fprintf(output_fp, "%s --> ", token);
            fprintf(output_fp, "NOT FOUND\n");
        } else {
            // find all occurences of key in list
            while (search(record_list, key) == TRUE) {
                // get record associated with key and print to output file
                data_t *key_record = get_node(record_list, token);
                fprint_data(token, key_record, output_fp);
                
                // delete occurence of key
                delete_node(record_list, token);
                free(key_record);
            }
        }
    } 
    
    // free linked list and close files used
    free_list(record_list);
    fclose(input_fp);
    fclose(output_fp);
    
    return 0;
}

// parses a line read from csv input and stores that record in a structure
void
parse_line(line_t line, data_t *record) {
    field_t field = "";
    int i = 0, field_count = 0, quotes_open = FALSE;
    
    // parse line to split up fields until end of line is reached
    while(line[i] != '\0' && line[i] != '\r' && line[i+1] != '\n') { 
        // ignore opening quotes and last closing quote of a field
        if ((line[i] == QUOTE && (!quotes_open || line[i+1] == COMMA ||
        line[i+1] == '\0' || line[i+1] == '\n' || line[i+1] == '\r'))) {
            // toggles boolean value (used to interpret escaping quotes)
            quotes_open = !quotes_open;  
            
        // keep closing quotes 
        } else if (line[i] == QUOTE) {
            quotes_open = !quotes_open;
            strncat(field, &line[i], 1);
        
        // get field when comma is reached (outside of quotes)
        } else if (line[i] == COMMA && quotes_open == FALSE) {
            classify_field(field, record, field_count);
            memset(field, 0, sizeof(field));
            field_count++;
        } else {
            strncat(field, &line[i], 1);
        }
        i++;
    }
    // get last field (location field)
    classify_field(field, record, field_count);
    memset(field, 0, sizeof(field));
    field_count++;
}



/* assigns a field to the appropriate structure element 
   (hardcoded as per assignment spec) */
void classify_field(field_t field, data_t *line_data, int field_count) {    
    if(field_count == 0) {
        strcpy(line_data->census_year, field);
    } else if(field_count == 1) {
        strcpy(line_data->blockID, field);
    } else if(field_count == 2) {
        strcpy(line_data->propertyID, field);
    } else if(field_count == 3) {
        strcpy(line_data->base_propertyID, field);
    } else if(field_count == 4) {
        strcpy(line_data->clue, field);
    } else if(field_count == 5) {
        strcpy(line_data->trading_name, field);
    } else if(field_count == 6) {
        strcpy(line_data->code, field);
    } else if(field_count == 7) {
        strcpy(line_data->description, field);
    } else if(field_count == 8) {
        strcpy(line_data->x, field);
    } else if(field_count == 9) {
        strcpy(line_data->y, field);
    } else if(field_count == 10) {
        strcpy(line_data->location, field);
    }
}

// prints a census record to a file (format as per assignment spec)
void 
fprint_data(field_t key, data_t *record, FILE *fp) {
    fprintf(fp, "%s --> ", key);
    fprintf(fp, "Census year: %s || ", record->census_year);
    fprintf(fp, "Block ID: %s || ", record->blockID);
    fprintf(fp, "Property ID: %s || ", record->propertyID);
    fprintf(fp, "Base property ID: %s || ", record->base_propertyID);
    fprintf(fp, "CLUE small area: %s || ", record->clue);
    fprintf(fp, "Industry (ANZSIC4) code: %s || ", record->code);
    fprintf(fp, "Industry (ANZSIC4) description: %s || ", record->description);
    fprintf(fp, "x coordinate: %s || ", record->x);
    fprintf(fp, "y coordinate: %s || ", record->y);
    fprintf(fp, "Location: %s || \n", record->location); 
}
