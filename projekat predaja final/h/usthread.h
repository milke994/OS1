/*
 * usthread.h
 *
 *  Created on: May 16, 2017
 *      Author: OS1
 */

#ifndef H_USTHREAD_H_
#define H_USTHREAD_H_
#include "thread.h"

extern int userMain(int argc, char *argv[]);

class UserThread : public Thread{
protected:
	void run();
public:
	UserThread(int argc, char *argv[]);
	char **argv;
	int argc, retValue;
};


#endif /* H_USTHREAD_H_ */
