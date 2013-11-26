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
#include <vector>
#include <string>
using namespace std;
class DataPage {
public:
	DataPage(int fd,int pageNumber);
	virtual ~DataPage();
	int createDataPageHeaderStruct(int pageNumber);
	int deleteDataPage();

	int getPageNumber();
	int getPageType();
	int getnextPageNumber();
	int getNoOfRecords();
	int getHeaderOffset();
	int getContinuousFreeSpaceOffset();
	int getContinuousFreeSpaceAvailable();

	static int getDataPageSize();
	static int getDataSlotEntrySize();
	void setPageNumber(int pageNumber);
	void setPageType(int pageType);
	void setNextPageNumber(int nextPageNumber);
	void setNoOfRecords(int noOfRecords);
	void setContinuousFreeSpaceOffset(int offset);
	void setContinuousFreeSpaceAvailable(int freeSpace);

	int insertRecord(char *record,int recordLength);
	vector<string> getAllRecords();
	int getRecord(int slotEntryNumber,char *&record,int *recordLen);
	int getOffsetForRecord(int recordLength); 	/*checks for the slot directory which can hold record of "recordLength".
	 	 	 	 	 	 	 	 	 	 	 	 * Returns -1 if there isn't any such slot.
	 	 	 	 	 	 	 	 	 	 	 	 */
	int getSlotNoForOffset(int offset);
	int getSlotNoForRecord(int recordLength);
	int addSlotDirectoyEntry(int recordLength);
	int addSlotDirectoyEntry(int offset,int recordLength);
	int updateSlotDirectoryEntry(int slotNumber,int recordLength);
	int freeSlotDirectoryEntry(int slotNumber);

private:
	typedef struct{
		GenPageHeaderStruct genPageHeader_;
		int noOfRecords_; // It's actually number of slots in slotDirectory.
		int headerOffset_;
		int continuousFreeSpaceOffset_;
		int continuousFreeSpaceAvailable_;
		int directoryPageBackPtr;
		int directoryEntryBackPtr;
	}DataPageHeaderStruct;
	DataPageHeaderStruct dataPageHeader_;

	typedef struct{
		int recordOffset;
		int recordLength;
	}SlotDirectoryEntry;

	SlotDirectoryEntry getSlotDirectoryEntry(int slotNumber);

	BufferManager *buffManager_;
	int fd_;
	int pageNumber_;
	char *pageData_;
	bool isDataPageChanged_;
};

#endif /* DATAPAGE_H_ */
