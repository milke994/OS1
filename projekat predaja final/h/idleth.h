/*
 * idleth.h
 *
 *  Created on: May 16, 2017
 *      Author: OS1
 */

#ifndef H_IDLETH_H_
#define H_IDLETH_H_
#include "thread.h"

class IddleThread : public Thread{
public:
	IddleThread();
	virtual void run();
	void start();
};


#endif /* H_IDLETH_H_ */
