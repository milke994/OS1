/*
 * lock.h
 *
 *  Created on: May 30, 2017
 *      Author: OS1
 */

#ifndef H_LOCK_H_
#define H_LOCK_H_

#define unlock if(System::running->val == 1 && System::flag == 1){\
	System::flag = 0;\
	System::dispatch();\
}\
System::running->val--;
#define lock System::running->val++;



#endif /* H_LOCK_H_ */
