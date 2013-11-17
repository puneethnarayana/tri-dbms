/*
 * IndexCatalog.h
 *
 *  Created on: Nov 9, 2013
 *      Author: ravin
 */

#ifndef INDEXCATALOG_H_
#define INDEXCATALOG_H_

class IndexCatalog {
public:
	IndexCatalog();
	virtual ~IndexCatalog();
	int createIndexCatalogPage(int pageNumber,char *pageData);
};

#endif /* INDEXCATALOG_H_ */
