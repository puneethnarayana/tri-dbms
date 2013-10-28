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

#define PAGE_SIZE 4096

#endif /* GLOBALDEFINES_H_ */
