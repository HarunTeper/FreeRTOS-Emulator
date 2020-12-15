#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL_scancode.h>

#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include "task.h"




void controlTask(void *pParam)
{
	portTickType xLastWakeTime;
	const portTickType xFrequency = 10;
	xLastWakeTime=xTaskGetTickCount();
	
	printf("-----Starting control task------\n");	

	for( ;; )
	{	
		int i;

		for(;;) {
		}
		
		//vTaskDelayUntil(&xLastWakeTime, xFrequency);
	}
}

void timingTask(void *pParam)
{	
	portTickType xLastWakeTime;
	const portTickType xFrequency = 150;
	xLastWakeTime=xTaskGetTickCount();

	
	
	printf("-----Starting timing task------\n");

		
	for( ;; )
	{	
		int i;

		for(i=0; i<10; i++) {
			printf("Interrupt\n");
		}

		printf("-----Change Prio------\n");


		vTaskDelayUntil(&xLastWakeTime, xFrequency);
	}	
}


#define PRINT_TASK_ERROR(task) PRINT_ERROR("Failed to print task ##task");

int main(int argc, char *argv[])
{
    printf("-----Creating tasks------\n");
			
	xTaskCreate(timingTask, "Timing Task", 128, NULL, 5, NULL);
	xTaskCreate(controlTask, "Control Task", 128, NULL, 3, NULL);
	
	printf("-----Starting scheduler------\n");
	
	/* Start the scheduler to start the tasks executing. */
	vTaskStartScheduler();

	/* The following line should never be reached because vTaskStartScheduler() 
	will only return if there was not enough FreeRTOS heap memory available to
	create the Idle and (if configured) Timer tasks.  Heap management, and
	techniques for trapping heap exhaustion, are described in the book text. */
	for( ;; );
	return 0;
}


// cppcheck-suppress unusedFunction
__attribute__((unused)) void vMainQueueSendPassed(void)
{
    /* This is just an example implementation of the "queue send" trace hook. */
}

// cppcheck-suppress unusedFunction
__attribute__((unused)) void vApplicationIdleHook(void)
{
#ifdef __GCC_POSIX__
    struct timespec xTimeToSleep, xTimeSlept;
    /* Makes the process more agreeable when using the Posix simulator. */
    xTimeToSleep.tv_sec = 1;
    xTimeToSleep.tv_nsec = 0;
    nanosleep(&xTimeToSleep, &xTimeSlept);
#endif
}
