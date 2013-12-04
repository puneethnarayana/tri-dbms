/*
 * IndexUI.h
 *
 *  Created on: Dec 4, 2013
 *      Author: bill
 */

#ifndef INDEXUI_H_
#define INDEXUI_H_

#include "../BufferManagement/BufferManager.h"
#include "IndexHeader.h"
#include "BPlusTree.h"

class IndexUI {
public:
	IndexUI();
	virtual ~IndexUI();
	void CreateIndexDB(int fanout);
	void OpenIndexDB();


};

#endif /* INDEXUI_H_ */
