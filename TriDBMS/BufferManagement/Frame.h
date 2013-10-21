/*
 * Frame.h
 *
 *  Created on: Oct 19, 2013
 *      Author: ravin
 */

#ifndef FRAME_H_
#define FRAME_H_

class Frame {
public:
	Frame();
	virtual ~Frame();
	bool dirtyFlag_;
	int pinCount_;
	unsigned long priority_;
	int pageNumber_;
	char *pageData_;
};

#endif /* FRAME_H_ */
