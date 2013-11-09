/*
 * Frame.cpp
 *
 *  Created on: Oct 19, 2013
 *      Author: ravin
 */

#include "Frame.h"
#include "BufferManager.h"
#include "string.h"
#include "LRUPageReplacement.h"

#include "../Global/globalDefines.h"
#include "../Global/globalStructures.h"
#include "../Global/globalVariables.h"
Frame::Frame(int frameSize) {
	// TODO Auto-generated constructor stub
	//fd_=-1;
	pageNumber_=-1;
	dirtyFlag_=false;
	pinCount_=-1;
	priority_=0;
	priorityType_=new char[2];	/* main header page,dir page, index root, index leaf,
								* index intermediate, data page etc.,
								*/
	strcpy(priorityType_,"DATA_PAGE");
	pageData_=new char[frameSize];//page size=4KB

}

Frame::~Frame() {
	// TODO Auto-generated destructor stub
}

