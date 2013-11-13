/*
 * globalDefines.h
 *
 *  Created on: Oct 23, 2013
 *      Author: ravin
 */

#ifndef GLOBALDEFINES_H_
#define GLOBALDEFINES_H_


/*page types, saved in page header, for priority check in page replacement*/
#define DB_MAIN_HEADER_PAGE 0
#define SYS_TABLES_PAGE 1
#define SYS_COLUMNS_PAGE 2
#define INDEX_CATALOG_PAGE 3
#define DIRECTORY_HEADER_PAGE 4
#define DIRECTORY_PAGE 5
#define INDEX_ROOT_PAGE 6
#define INDEX_INTERNAL_PAGE 7
#define INDEX_LEAF_PAGE 8
#define DATA_PAGE 9


#define DEFAULT_PAGE_SIZE 4096
#define DEFAULT_DB_SIZE 10
#define MAX_FILE_NAME_LENGTH 128
#define MAX_DATABASES 50
#define SUCCESS 1

#define INT_SIZE 4
#define BOOL_SIZE 1
#define CHAR_SIZE 1
#define DATE_SIZE 3

//Pour l'index
#define COL_INTEGER 1
#define COL_FLOAT 2
#define COL_DOUBLE 3
#define COL_VARCHAR 4
#define COL_LONG 5

#define EQUAL_TO 1
#define GREATER_THAN 2
#define GREATER_THAN_OR_EQUAL_TO 3
#define LESS_THAN 4
#define LESS_THAN_OR_EQUAL_TO 5

#define MAX_QUERY_LENGTH 256
#endif /* GLOBALDEFINES_H_ */
