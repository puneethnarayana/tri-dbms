/*
 * DataPage.h
 *
 *  Created on: Nov 9, 2013
 *      Author: ravin
 */

#ifndef DATAPAGE_H_
#define DATAPAGE_H_
#include "../Global/globalStructures.h"
#include "../BufferManagement/BufferManager.h"
class DataPage {
public:
	DataPage(int fd,int pageNumber);
	virtual ~DataPage();
	int createDataPageHeaderStruct(int pageNumber,char *pageData);

	int getPageNumber();
	int getPageType();
	int getnextPageNumber();
	int getNoOfRecords();
	static int getDataPageSize();

	void setPageNumber(int pageNumber);
	void setPageType(int pageType);
	void setNextPageNumber(int nextPageNumber);
	void setNoOfRecords(int noOfRecords);

private:
	typedef struct{
		GenPageHeaderStruct genPageHeader_;
		int noOfRecords_;
	}DataPageHeaderStruct;
	DataPageHeaderStruct dataPageHeader_;
	BufferManager *buffManager_;
	int fd_;
	int pageNumber_;
	char *pageData_;
	bool isDataPageChanged_;
};

#endif /* DATAPAGE_H_ */
