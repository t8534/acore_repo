/*
* Configuration of module: Os (Tasks.c)
*
* Created by:              
* Copyright:               
*
* Configured for (MCU):    MPC551x
*
* Module vendor:           ArcCore
* Generator version:       2.0.34
*
* Generated by Arctic Studio (http://arccore.com) 
*           on Wed Jul 06 17:58:25 CEST 2011
*/

#include "Os.h"
#include "EcuM.h"

// #define USE_LDEBUG_PRINTF // Uncomment this to turn debug statements on.
#include "debug.h"


// Tasks
void Startup( void ) {

	EcuM_StartupTwo();

	TerminateTask();
}


void OsIdle( void ) {
	while(1);
}


// Hooks
#define ERROR_LOG_SIZE 20

struct LogBad_s {
	uint32_t param1;
	uint32_t param2;
	uint32_t param3;
	TaskType taskId;
	OsServiceIdType serviceId;
	StatusType error;
};

void ErrorHook ( StatusType Error ) {

	TaskType task;
	static struct LogBad_s LogBad[ERROR_LOG_SIZE];
	static uint8_t ErrorCount = 0;
	GetTaskID(&task);
	OsServiceIdType service = OSErrorGetServiceId();
	
	LDEBUG_PRINTF("## ErrorHook err=%d\n",Error);

	/* Log the errors in a buffer for later review */
	LogBad[ErrorCount].param1 = os_error.param1;
	LogBad[ErrorCount].param2 = os_error.param2;
	LogBad[ErrorCount].param3 = os_error.param3;
	LogBad[ErrorCount].serviceId = service;
	LogBad[ErrorCount].taskId = task;
	LogBad[ErrorCount].error = Error;

	ErrorCount++;

	// Stall if buffer is full.
	while(ErrorCount >= ERROR_LOG_SIZE);

}

void PostTaskHook ( void ) {
	TaskType task;
	GetTaskID(&task);
	LDEBUG_PRINTF("## PreTaskHook, taskid=%d\n",task);
}

void PreTaskHook ( void ) {
	TaskType task;
	GetTaskID(&task);
	LDEBUG_PRINTF("## PreTaskHook, taskid=%d\n",task);
}

void ShutdownHook ( StatusType Error ) {
	LDEBUG_PRINTF("## ShutdownHook\n");
	while(1);
}

void StartupHook ( void ) {
	LDEBUG_PRINTF("## StartupHook\n");
}
