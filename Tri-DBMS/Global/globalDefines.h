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

#define MAX_QUERY_LENGTH 256
#endif /* GLOBALDEFINES_H_ */
