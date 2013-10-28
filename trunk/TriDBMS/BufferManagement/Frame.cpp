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
Frame::Frame() {
	// TODO Auto-generated constructor stub
	pageNumber_=-1;
	dirtyFlag_=false;
	pinCount_=-1;
	priority_=0;
	pageData_=new char[4096];//page size=4KB

}

Frame::~Frame() {
	// TODO Auto-generated destructor stub
}

