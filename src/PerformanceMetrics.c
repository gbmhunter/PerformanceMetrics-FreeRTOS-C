//!
//! @file 		PerformanceMetrics.c
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @date 		16/10/2011
//! @brief 		See PerformanceMetrics.h
//! @details
//!		<b>Last Modified:			</b> 07/11/2012					\n
//!		<b>Version:					</b> v2.0.1						\n
//!		<b>Company:					</b> CladLabs					\n
//!		<b>Project:					</b> Free Code Modules			\n
//!		<b>Language:				</b> C							\n
//!		<b>Compiler:				</b> GCC						\n
//! 	<b>uC Model:				</b> PSoC5						\n
//!		<b>Computer Architecture:	</b> ARM						\n
//! 	<b>Operating System:		</b> FreeRTOS v7.2.0			\n
//!		<b>Documentation Format:	</b> Doxygen					\n
//!		<b>License:					</b> GPLv3						\n
//!	
//!		See the Doxygen documentation or PerformanceMetrics.h for a detailed description on this module.
//!


//===============================================================================================//
//========================================= INCLUDES ============================================//
//===============================================================================================//

#include "Include.h"

//===============================================================================================//
//============================================ GUARDS ===========================================//
//===============================================================================================//

#ifdef __cplusplus
	extern "C" {
#endif

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

//! Holds the task handle of PerformanceMetrics_Task(), once task has been created with
//! PerformanceMetrics_Start()
static xTaskHandle taskHandle = 0;

//! @brief 		Main parameters structure. 
//! @details	Used to create a variable which holds
//! 				modifiable main parameters (which can be updated).
static struct{
	uint32 debugPrintTimeMs;
} performanceMetricsParameters =
{
	.debugPrintTimeMs = configPERFORMANCE_METRICS_PRINT_PERIOD_SEC*1000
};


//===============================================================================================//
//================================== PRIVATE FUNCTION PROTOTYPES ================================//
//===============================================================================================//


void PerformanceMetrics_Task(void *pvParameters);

#if(configPRINT_DEBUG_PERFORMANCE_METRICS == 1)
	void PerformanceMetrics_SendDebugMsg(char* msgDebug);
#endif

//===============================================================================================//
//===================================== PUBLIC FUNCTIONS ========================================//
//===============================================================================================//

// See the Doxygen documentation or the function declarations in PerformanceMetrics.h for more information

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
//! @private
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

// none

//===============================================================================================//
//========================================= GRAVEYARD ===========================================//
//===============================================================================================//

#ifdef __cplusplus
	} // extern "C" {
#endif

// EOF
