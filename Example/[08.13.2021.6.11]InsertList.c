

/* Standard includes. */
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

/*workspace start*/

/*workspace ending*/

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"

/* This project provides two demo applications.  A simple blinky style demo
application, and a more comprehensive test and demo application.  The
mainCREATE_SIMPLE_BLINKY_DEMO_ONLY setting is used to select between the two.

If mainCREATE_SIMPLE_BLINKY_DEMO_ONLY is 1 then the blinky demo will be built.
The blinky demo is implemented and described in main_blinky.c.

If mainCREATE_SIMPLE_BLINKY_DEMO_ONLY is not 1 then the comprehensive test and
demo application will be built.  The comprehensive test and demo application is
implemented and described in main_full.c. */
#define mainCREATE_SIMPLE_BLINKY_DEMO_ONLY	1

/* This demo uses heap_5.c, and these constants define the sizes of the regions
that make up the total heap.  heap_5 is only used for test and example purposes
as this demo could easily create one large heap region instead of multiple
smaller heap regions - in which case heap_4.c would be the more appropriate
choice.  See http://www.freertos.org/a00111.html for an explanation. */
#define mainREGION_1_SIZE	7001
#define mainREGION_2_SIZE	18105
#define mainREGION_3_SIZE	2807

/*-----------------------------------------------------------*/
/*
 * main_blinky() is used when mainCREATE_SIMPLE_BLINKY_DEMO_ONLY is set to 1.
 * main_full() is used when mainCREATE_SIMPLE_BLINKY_DEMO_ONLY is set to 0.
 */
extern void main_blinky( void );
extern void main_full( void );

/*
 * Only the comprehensive demo uses application hook (callback) functions.  See
 * http://www.freertos.org/a00016.html for more information.
 */
void vFullDemoTickHookFunction( void );
void vFullDemoIdleFunction( void );

/*
 * This demo uses heap_5.c, so start by defining some heap regions.  It is not
 * necessary for this demo to use heap_5, as it could define one large heap
 * region.  Heap_5 is only used for test and example purposes.  See
 * http://www.freertos.org/a00111.html for an explanation.
 */
static void  prvInitialiseHeap( void );

/*
 * Prototypes for the standard FreeRTOS application hook (callback) functions
 * implemented within this file.  See http://www.freertos.org/a00016.html .
 */
void vApplicationMallocFailedHook( void );
void vApplicationIdleHook( void );
void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName );
void vApplicationTickHook( void );
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize );

/*
 * Writes trace data to a disk file when the trace recording is stopped.
 * This function will simply overwrite any trace files that already exist.
 */
static void prvSaveTraceFile( void );

/*-----------------------------------------------------------*/

/* When configSUPPORT_STATIC_ALLOCATION is set to 1 the application writer can
use a callback function to optionally provide the memory required by the idle
and timer tasks.  This is the stack that will be used by the timer task.  It is
declared here, as a global, so it can be checked by a test that is implemented
in a different file. */
StackType_t uxTimerTaskStack[ configTIMER_TASK_STACK_DEPTH ];

/* The user trace event posted to the trace recording on each tick interrupt.
Note:  This project runs under Windows, and Windows will not be executing the
RTOS threads continuously.  Therefore tick events will not appear with a regular
interval within the trace recording. */
traceLabel xTickTraceUserEvent;
static portBASE_TYPE xTraceRunning = pdTRUE;

/*-----------------------------------------------------------*/


/*----------------------------workspace start-------------------------------*/
//任务初始化任务
void TaskInit(void* pv);
#define TaskInitStackInit 50
UBaseType_t TaskPriority = 1;
TaskHandle_t TaskInitHandle;
//任务1
void Task1(void* pv);
#define Task1StackInit 50
UBaseType_t Task1Priority = 2;
TaskHandle_t Task1Handle;

//任务2
void Task2(void* pv);
#define Task2StackInit 50
UBaseType_t Task2Priority = 3;
TaskHandle_t Task2Handle;

//任务3
void Task3(void* pv);
#define Task3StackInit 50
UBaseType_t Task3Priority = 4;
TaskHandle_t Task3Handle;


/*----------------------------workspace end-------------------------------*/


int main( void )
{
	prvInitialiseHeap();
	vTraceInitTraceData();
	xTickTraceUserEvent = xTraceOpenLabel( "tick" );
	//workspace start
	//任务初始化任务
	BaseType_t TaskInitParam = xTaskCreate((TaskFunction_t)TaskInit,
											(const char *)"TaskInit",
											(uint16_t)TaskInitStackInit,
											(void *)NULL,
											(UBaseType_t)TaskPriority,
											(TaskHandle_t *)&TaskInitHandle);
	
	//init task 3
	BaseType_t Task3Param = xTaskCreate((TaskFunction_t)Task3,
		(const char *)"Task3",
		(uint16_t)Task3StackInit,
		(void *)NULL,
		(UBaseType_t)Task3Priority,
		(TaskHandle_t *)&Task3Handle);

//init task 1
	BaseType_t Task1Param = xTaskCreate((TaskFunction_t)Task1,
		(const char *)"Task1",
		(uint16_t)Task1StackInit,
		(void *)NULL,
		(UBaseType_t)Task1Priority,
		(TaskHandle_t *)&Task1Handle);
	//init task 2
	BaseType_t Task2Param = xTaskCreate((TaskFunction_t)Task2,
		(const char *)"Task2",
		(uint16_t)Task2StackInit,
		(void *)NULL,
		(UBaseType_t)Task2Priority,
		(TaskHandle_t *)&Task2Handle);



		vTaskStartScheduler();
		
		
	//workspace end
	return 0;
}
/*-----------------------------------------------------------*/



/*----------------------------workspace start-------------------------------*/
void TaskInit(void* pv)
{
	List_t ListTotal;
	ListItem_t listitem1;
	ListItem_t listitem2;
	ListItem_t listitem3;

	vListInitialise(&ListTotal);		//初始化列表
	vListInitialiseItem(&listitem1);	//初始化列表项1
	vListInitialiseItem(&listitem2);	//初始化列表项2
	vListInitialiseItem(&listitem3);	//初始化列表项3

	listitem1.xItemValue = 40;			//列表项1 赋值 40
	listitem2.xItemValue = 50;			//列表项2 赋值 60
	listitem3.xItemValue = 60;			//列表项3 赋值 50

										//print list address.
	printf("<-----------------print list and listitem address--------------------->\r\n");
	printf("Project                     address                       \r\n");
	printf("ListTotal address           0x%x\r\n", (&ListTotal) );			//list address
	printf("ListTotal index             %x\r\n",	ListTotal.pxIndex);		//list index
	printf("ListTotal xlistend          %x\r\n",    ListTotal.xListEnd);	//list end
	printf("ListTotal NumberOfItems     %x\r\n",	ListTotal.uxNumberOfItems);	//list 中存储的项目数
	printf("Listitem1 address           0x%x\r\n", (&listitem1));			//listitem1 address
	printf("Listitem2 address           0x%x\r\n", (&listitem2));			//listitem2 address
	printf("Listitem3 address           0x%x\r\n", (&listitem3));			//listitem3 address
	printf("<-----------------print ending--------------------->\r\n");

	vListInsertEnd(&ListTotal, &listitem1);													//insert list item1 to list
	printf("<-----------------insert listitem1 to list--------------------->\r\n");		
	printf("Project                              address                       \r\n");
	printf("ListTotal index                      %x\r\n", ListTotal.pxIndex);						//list index
	printf("ListTotal.xListEnd.pxNext            %x\r\n", ListTotal.xListEnd.pxNext);	
	printf("listitem1.pxNext                     %x\r\n", listitem1.pxNext);

	printf("ListTotal.xListEnd.pxPrevious        %x\r\n", ListTotal.xListEnd.pxPrevious);	
	printf("listitem1.pxPrevious                 %x\r\n", listitem1.pxPrevious);

	printf("ListTotal NumberOfItems              %x\r\n", ListTotal.uxNumberOfItems);	//list 中存储的项目数
	printf("Listitem1 address                    0x%x\r\n", (&listitem1));			    //listitem1 address
	printf("<-----------------print ending--------------------->\r\n");		//

	vListInsertEnd(&ListTotal, &listitem2);										//insert list item2 to list
	printf("<-----------------insert listitem2  to list--------------------->\r\n");
	printf("Project                              address                       \r\n");
	printf("ListTotal index                      %x\r\n", ListTotal.pxIndex);						//list index
	printf("ListTotal.xListEnd.pxNext            %x\r\n", ListTotal.xListEnd.pxNext);
	printf("listitem1.pxNext                     %x\r\n", listitem1.pxNext);

	printf("ListTotal.xListEnd.pxPrevious        %x\r\n", ListTotal.xListEnd.pxPrevious);
	printf("listitem1.pxPrevious                 %x\r\n", listitem1.pxPrevious);
	printf("ListTotal NumberOfItems              %x\r\n", ListTotal.uxNumberOfItems);	//list 中存储的项目数
	printf("Listitem1 address                    0x%x\r\n", (&listitem1));			    //listitem1 address

	printf("listitem2.pxPrevious                 %x\r\n", listitem2.pxPrevious);
	printf("listitem2.pvContainer                %x\r\n", listitem2.pvContainer);
	printf("listitem2.pvOwner                    %x\r\n", listitem2.pvOwner);
	printf("listitem2.pxNext                     %x\r\n", listitem2.pxNext);
	printf("listitem2.xItemValue                 %d\r\n", listitem2.xItemValue);
	printf("Listitem2 address                    0x%x\r\n", (&listitem2));			    //listitem2 address
	printf("<-----------------print ending--------------------->\r\n");		//
										

	//vListInsert(&ListTotal, &listitem3);            //insert list item3 to list
	vListInsertEnd(&ListTotal, &listitem3);
	printf("<-----------------insert listitem3 to list--------------------->\r\n");
	printf("Project                              address                       \r\n");

	printf("listitem1.pxPrevious                 %x\r\n", listitem1.pxPrevious);
	printf("listitem1.pvContainer                %x\r\n", listitem1.pvContainer);
	printf("listitem1.pvOwner                    %x\r\n", listitem1.pvOwner);
	printf("listitem1.pxNext                     %x\r\n", listitem1.pxNext);
	printf("listitem1.xItemValue                 %d\r\n", listitem1.xItemValue);
	printf("Listitem1 address                    0x%x\r\n", (&listitem1));			    //listitem1 address

	printf("listitem2.pxPrevious                 %x\r\n", listitem2.pxPrevious);
	printf("listitem2.pvContainer                %x\r\n", listitem2.pvContainer);
	printf("listitem2.pvOwner                    %x\r\n", listitem2.pvOwner);
	printf("listitem2.pxNext                     %x\r\n", listitem2.pxNext);
	printf("listitem2.xItemValue                 %d\r\n", listitem2.xItemValue);
	printf("Listitem2 address                    0x%x\r\n", (&listitem2));			    //listitem2 address

	printf("listitem3.pxPrevious                 %x\r\n", listitem3.pxPrevious);
	printf("listitem3.pvContainer                %x\r\n", listitem3.pvContainer);
	printf("listitem3.pvOwner                    %x\r\n", listitem3.pvOwner);
	printf("listitem3.pxNext                     %x\r\n", listitem3.pxNext);
	printf("listitem3.xItemValue                 %d\r\n", listitem3.xItemValue);
	printf("Listitem3 address                    0x%x\r\n", (&listitem3) );
	printf("<-----------------print ending--------------------->\r\n");		//


	while (1)
	{
		printf("Finsh Task Init\r\n");
		Sleep(100);
	}
	
	
}

void Task1(void* pv)
{
	unsigned int count1 = 0;
	while (1) 
	{
		count1++;
		printf("this task1 count1 = %d\r\n", count1);
		Sleep(10);
		if (count1 == 10)
		{
			vTaskSuspend(Task1Handle);
			vTaskResume(Task2Handle);
			vTaskStartScheduler();
		}
	}
}

void Task2(void* pv)
{
	unsigned int count2 = 0;
	while (1)
	{
		count2++;
		printf("this task2 count2 = %d\r\n", count2);
		Sleep(10);
		if (count2 == 10)
		{
			vTaskSuspend(Task2Handle);
			count2 = 0;
		}
	}
}
void Task3(void* pv)
{
	unsigned int count3 = 0;
	while (1)
	{
		count3++;
		printf("this task3 count3 = %d\r\n", count3);
		Sleep(10);
		if (count3 == 10)
		{
			vTaskSuspend(Task3Handle);
		}

	}
}
/*----------------------------workspace ending-------------------------------*/
void vApplicationMallocFailedHook( void )
{
	/* vApplicationMallocFailedHook() will only be called if
	configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h.  It is a hook
	function that will get called if a call to pvPortMalloc() fails.
	pvPortMalloc() is called internally by the kernel whenever a task, queue,
	timer or semaphore is created.  It is also called by various parts of the
	demo application.  If heap_1.c, heap_2.c or heap_4.c is being used, then the
	size of the	heap available to pvPortMalloc() is defined by
	configTOTAL_HEAP_SIZE in FreeRTOSConfig.h, and the xPortGetFreeHeapSize()
	API function can be used to query the size of free heap space that remains
	(although it does not provide information on how the remaining heap might be
	fragmented).  See http://www.freertos.org/a00111.html for more
	information. */
	vAssertCalled( __LINE__, __FILE__ );
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
	/* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
	to 1 in FreeRTOSConfig.h.  It will be called on each iteration of the idle
	task.  It is essential that code added to this hook function never attempts
	to block in any way (for example, call xQueueReceive() with a block time
	specified, or call vTaskDelay()).  If application tasks make use of the
	vTaskDelete() API function to delete themselves then it is also important
	that vApplicationIdleHook() is permitted to return to its calling function,
	because it is the responsibility of the idle task to clean up memory
	allocated by the kernel to any task that has since deleted itself. */

	/* Uncomment the following code to allow the trace to be stopped with any
	key press.  The code is commented out by default as the kbhit() function
	interferes with the run time behaviour. */
	/*
		if( _kbhit() != pdFALSE )
		{
			if( xTraceRunning == pdTRUE )
			{
				vTraceStop();
				prvSaveTraceFile();
				xTraceRunning = pdFALSE;
			}
		}
	*/

	#if ( mainCREATE_SIMPLE_BLINKY_DEMO_ONLY != 1 )
	{
		/* Call the idle task processing used by the full demo.  The simple
		blinky demo does not use the idle task hook. */
		vFullDemoIdleFunction();
	}
	#endif
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
{
	( void ) pcTaskName;
	( void ) pxTask;

	/* Run time stack overflow checking is performed if
	configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
	function is called if a stack overflow is detected.  This function is
	provided as an example only as stack overflow checking does not function
	when running the FreeRTOS Windows port. */
	vAssertCalled( __LINE__, __FILE__ );
}
/*-----------------------------------------------------------*/

void vApplicationTickHook( void )
{
	/* This function will be called by each tick interrupt if
	configUSE_TICK_HOOK is set to 1 in FreeRTOSConfig.h.  User code can be
	added here, but the tick hook is called from an interrupt context, so
	code must not attempt to block, and only the interrupt safe FreeRTOS API
	functions can be used (those that end in FromISR()). */

	#if ( mainCREATE_SIMPLE_BLINKY_DEMO_ONLY != 1 )
	{
		vFullDemoTickHookFunction();
	}
	#endif /* mainCREATE_SIMPLE_BLINKY_DEMO_ONLY */

	/* Write a user event to the trace log.  Note:  This project runs under
	Windows, and Windows will not be executing the RTOS threads continuously.
	Therefore tick events will not appear with a regular interval within the the
	trace recording. */
	vTraceUserEvent( xTickTraceUserEvent );
}
/*-----------------------------------------------------------*/

void vApplicationDaemonTaskStartupHook( void )
{
	/* This function will be called once only, when the daemon task starts to
	execute	(sometimes called the timer task).  This is useful if the
	application includes initialisation code that would benefit from executing
	after the scheduler has been started. */
}
/*-----------------------------------------------------------*/

void vAssertCalled( unsigned long ulLine, const char * const pcFileName )
{
static portBASE_TYPE xPrinted = pdFALSE;
volatile uint32_t ulSetToNonZeroInDebuggerToContinue = 0;

	/* Called if an assertion passed to configASSERT() fails.  See
	http://www.freertos.org/a00110.html#configASSERT for more information. */

	/* Parameters are not used. */
	( void ) ulLine;
	( void ) pcFileName;

	printf( "ASSERT! Line %d, file %s, GetLastError() %d\r\n", ulLine, pcFileName, GetLastError() );

 	taskENTER_CRITICAL();
	{
		/* Stop the trace recording. */
		if( xPrinted == pdFALSE )
		{
			xPrinted = pdTRUE;
			if( xTraceRunning == pdTRUE )
			{
				vTraceStop();
				prvSaveTraceFile();
			}
		}

		/* You can step out of this function to debug the assertion by using
		the debugger to set ulSetToNonZeroInDebuggerToContinue to a non-zero
		value. */
		while( ulSetToNonZeroInDebuggerToContinue == 0 )
		{
			__asm{ NOP };
			__asm{ NOP };
		}
	}
	taskEXIT_CRITICAL();
}
/*-----------------------------------------------------------*/

static void prvSaveTraceFile( void )
{
FILE* pxOutputFile;

	fopen_s( &pxOutputFile, "Trace.dump", "wb");

	if( pxOutputFile != NULL )
	{
		fwrite( RecorderDataPtr, sizeof( RecorderDataType ), 1, pxOutputFile );
		fclose( pxOutputFile );
		printf( "\r\nTrace output saved to Trace.dump\r\n" );
	}
	else
	{
		printf( "\r\nFailed to create trace dump file\r\n" );
	}
}
/*-----------------------------------------------------------*/

static void  prvInitialiseHeap( void )
{
/* The Windows demo could create one large heap region, in which case it would
be appropriate to use heap_4.  However, purely for demonstration purposes,
heap_5 is used instead, so start by defining some heap regions.  No
initialisation is required when any other heap implementation is used.  See
http://www.freertos.org/a00111.html for more information.

The xHeapRegions structure requires the regions to be defined in start address
order, so this just creates one big array, then populates the structure with
offsets into the array - with gaps in between and messy alignment just for test
purposes. */
static uint8_t ucHeap[ configTOTAL_HEAP_SIZE ];
volatile uint32_t ulAdditionalOffset = 19; /* Just to prevent 'condition is always true' warnings in configASSERT(). */
const HeapRegion_t xHeapRegions[] =
{
	/* Start address with dummy offsets						Size */
	{ ucHeap + 1,											mainREGION_1_SIZE },
	{ ucHeap + 15 + mainREGION_1_SIZE,						mainREGION_2_SIZE },
	{ ucHeap + 19 + mainREGION_1_SIZE + mainREGION_2_SIZE,	mainREGION_3_SIZE },
	{ NULL, 0 }
};

	/* Sanity check that the sizes and offsets defined actually fit into the
	array. */
	configASSERT( ( ulAdditionalOffset + mainREGION_1_SIZE + mainREGION_2_SIZE + mainREGION_3_SIZE ) < configTOTAL_HEAP_SIZE );

	/* Prevent compiler warnings when configASSERT() is not defined. */
	( void ) ulAdditionalOffset;

	vPortDefineHeapRegions( xHeapRegions );
}
/*-----------------------------------------------------------*/

/* configUSE_STATIC_ALLOCATION is set to 1, so the application must provide an
implementation of vApplicationGetIdleTaskMemory() to provide the memory that is
used by the Idle task. */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
/* If the buffers to be provided to the Idle task are declared inside this
function then they must be declared static - otherwise they will be allocated on
the stack and so not exists after this function exits. */
static StaticTask_t xIdleTaskTCB;
static StackType_t uxIdleTaskStack[ configMINIMAL_STACK_SIZE ];

	/* Pass out a pointer to the StaticTask_t structure in which the Idle task's
	state will be stored. */
	*ppxIdleTaskTCBBuffer = &xIdleTaskTCB;

	/* Pass out the array that will be used as the Idle task's stack. */
	*ppxIdleTaskStackBuffer = uxIdleTaskStack;

	/* Pass out the size of the array pointed to by *ppxIdleTaskStackBuffer.
	Note that, as the array is necessarily of type StackType_t,
	configMINIMAL_STACK_SIZE is specified in words, not bytes. */
	*pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}
/*-----------------------------------------------------------*/

/* configUSE_STATIC_ALLOCATION and configUSE_TIMERS are both set to 1, so the
application must provide an implementation of vApplicationGetTimerTaskMemory()
to provide the memory that is used by the Timer service task. */
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize )
{
/* If the buffers to be provided to the Timer task are declared inside this
function then they must be declared static - otherwise they will be allocated on
the stack and so not exists after this function exits. */
static StaticTask_t xTimerTaskTCB;

	/* Pass out a pointer to the StaticTask_t structure in which the Timer
	task's state will be stored. */
	*ppxTimerTaskTCBBuffer = &xTimerTaskTCB;

	/* Pass out the array that will be used as the Timer task's stack. */
	*ppxTimerTaskStackBuffer = uxTimerTaskStack;

	/* Pass out the size of the array pointed to by *ppxTimerTaskStackBuffer.
	Note that, as the array is necessarily of type StackType_t,
	configMINIMAL_STACK_SIZE is specified in words, not bytes. */
	*pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}

