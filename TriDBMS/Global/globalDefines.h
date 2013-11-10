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
#define DB_PAGE 6

#define DEFAULT_PAGE_SIZE 4096
#define MAX_FILE_NAME_LENGTH 128
#define SUCCESS 1

#define INT_SIZE 4
#define BOOL_SIZE 1
#define CHAR_SIZE 1
#define DATE_SIZE 3

#define MAX_QUERY_LENGTH 256
#endif /* GLOBALDEFINES_H_ */
