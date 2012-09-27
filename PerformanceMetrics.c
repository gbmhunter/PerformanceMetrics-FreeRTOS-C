//!
//! @file 		PerformanceMetrics.c
//! @author 	Geoffrey Hunter (gbmhunter@gmail.com)
//! @date 		16/10/2011
//! @brief 		
//! @details
//!		<b>Last Modified:			</b> 27/09/2011			\n
//!		<b>Version:					</b> v2.0				\n
//!		<b>Company:					</b> CladLabs			\n
//!		<b>Project:					</b> Template Code		\n
//!		<b>Computer Architecture:	</b> ARM				\n
//!		<b>Compiler:				</b> GCC				\n
//! 	<b>uC Model:				</b> PSoC5				\n
//!		<b>Documentation Format:	</b> Doxygen			\n
//!


//===============================================================================================//
//========================================= INCLUDES ============================================//
//===============================================================================================//

#include "Include.h"

//===============================================================================================//
//================================== PRECOMPILER CHECKS =========================================//
//===============================================================================================//

#ifndef configENABLE_TASK_PERFORMANCE_METRICS
	#error Please define the switch configENABLE_TASK_PERFORMANCE_METRICS
#endif 

#ifndef configPRINT_DEBUG_PERFORMANCE_METRICS
	#error Please define the switch configPRINT_DEBUG_PERFORMANCE_METRICS
#endif

//===============================================================================================//
//=================================== PRIVATE TYPEDEFS ==========================================//
//===============================================================================================//

// none

//===============================================================================================//
//==================================== PRIVATE DEFINES ==========================================//
//===============================================================================================//

// none

//===============================================================================================//
//================================== PRIVATE VARIABLES ==========================================//
//===============================================================================================//

static xTaskHandle taskHandle = 0;

//! @brief 		Main parameters structure. 
//! @details	Used to create a variable which holds
// 				modifiable main parameters (which can be updated).
static struct{
	uint32 debugPrintTimeMs;
} performanceMetricsParameters =
{
	.debugPrintTimeMs = configPERFORMANCE_METRICS_PRINT_PERIOD_SEC*1000
};


//===============================================================================================//
//================================== PRIVATE FUNCTION PROTOTYPES ================================//
//===============================================================================================//

// Task Functions
void PerformanceMetrics_Task(void *pvParameters);

#if(configPRINT_DEBUG_PERFORMANCE_METRICS == 1)
	void PerformanceMetrics_SendDebugMsg(char* msgDebug);
#endif

//===============================================================================================//
//===================================== PUBLIC FUNCTIONS ========================================//
//===============================================================================================//

//! @breif 		Start-up function for power management
//! @details 	Creates power management task, creates commmand queue, starts the ADC
//!				creates interrupt sync semaphore, calls PowerMgmt_SetInitialParameters()
//!	@note		Not thread-safe. Do not call from any tasks, but call from main() before 
//!				scheduler is started.
//! @public
void PerformanceMetrics_Start(uint32 taskStackSize, uint8 taskPriority)
{	

	#if(configENABLE_TASK_PERFORMANCE_METRICS == 1)
		// Create the main task manager task
		xTaskCreate(	&PerformanceMetrics_Task,
						(signed portCHAR *) "Performance Metrics Task",
						taskStackSize,
						NULL,
						taskPriority,
						&taskHandle);
	#endif
	
}

xTaskHandle PerformanceMetrics_ReturnTaskHandle(void)
{
	return taskHandle;
}

//===============================================================================================//
//==================================== PRIVATE FUNCTIONS ========================================//
//===============================================================================================//

//! @brief 		Main power management task
//! @param		*pvParameters Void pointer (not used)
//! @note		Not thread-safe. Do not call from any task, this function is a task that
//!				is called by the FreeRTOS kernel
//! @public
void PerformanceMetrics_Task(void *pvParameters)
{
	#if(configPRINT_DEBUG_PERFORMANCE_METRICS == 1)
		PerformanceMetrics_SendDebugMsg("PER_MET: Performance metrics task started.\r\n");
	#endif
	
	static char taskMetricsStringBuff[configTASK_METRICS_STRING_BUFF_SIZE];

	static char freeHeapSpaceString[configFREE_HEAP_SPACE_STRING_BUFF_SIZE];
	
	// Infinite task loop
	for(;;)
	{
		
		vTaskDelay(performanceMetricsParameters.debugPrintTimeMs/portTICK_RATE_MS);
		// Get task information
		vTaskList((signed char*)taskMetricsStringBuff);
		snprintf(freeHeapSpaceString, 50, "\r\nTick = %u\r\nFree Heap Space = %u\r\n\r\n", (uint32) xTaskGetTickCount(), (uint32) xPortGetFreeHeapSize());
		strlcat(taskMetricsStringBuff, freeHeapSpaceString, sizeof(taskMetricsStringBuff));
		// Print task information
		#if(configPRINT_DEBUG_PERFORMANCE_METRICS == 1)
			PerformanceMetrics_SendDebugMsg(taskMetricsStringBuff);
		#endif
	}
}

#if(configPRINT_DEBUG_PERFORMANCE_METRICS == 1)
	//! @brief		Sends a message to the debug message queue.
	//! @param		Pointer to the null-terminated string to send.
	//! @note		Thread-safe
	//! @private
	void PerformanceMetrics_SendDebugMsg(char* msgDebug)
	{
		UartDebug_PutString(msgDebug);
	}
#endif

//===============================================================================================//
//======================================== ISR's ================================================//
//===============================================================================================//


//===============================================================================================//
//========================================= GRAVEYARD ===========================================//
//===============================================================================================//

// EOF