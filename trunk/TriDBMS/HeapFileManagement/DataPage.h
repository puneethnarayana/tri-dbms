/*
 * DataPage.h
 *
 *  Created on: Nov 9, 2013
 *      Author: ravin
 */

#ifndef DATAPAGE_H_
#define DATAPAGE_H_

class DataPage {
public:
	DataPage();
	virtual ~DataPage();
private:
	typedef struct{
		GenPageHeaderStruct genPageHeader_;
		int noOfRecords_;
	}DataPageHeaderStruct;
	DataPageHeaderStruct dataPageHeader_;
};

#endif /* DATAPAGE_H_ */
