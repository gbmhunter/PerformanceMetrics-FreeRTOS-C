//!
//! @file 		PerformanceMetrics.h
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @date 		16/10/2011
//! @brief 		Performance measuring task for the FreeRTOS operating system.
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
//!		CHANGELOG:
//!			v2.0.1 -> Added C++ guards. Moved documentation into .h file.
//!				Added a few more comments to functions.
//!		

//===============================================================================================//
//============================================ GUARDS ===========================================//
//===============================================================================================//

#ifndef PERFORMANCE_METRICS_H
#define PERFORMANCE_METRICS_H

#ifdef __cplusplus
	extern "C" {
#endif

//===============================================================================================//
//=================================== PUBLIC FUNCTION PROTOTYPES ================================//
//===============================================================================================//

//! @brief 		Start-up function for power management
//! @details 	Creates power management task, creates commmand queue, starts the ADC
//!				creates interrupt sync semaphore, calls PowerMgmt_SetInitialParameters()
//!	@note		Not thread-safe. Do not call from any tasks, but call from main() before 
//!				scheduler is started.
//! @public
void PerformanceMetrics_Start(uint32 taskStackSize, uint8 taskPriority);

//! @brief		Returns the task handle for PerformanceMetrics_Task()
//! @public
xTaskHandle PerformanceMetrics_ReturnTaskHandle(void);

#ifdef __cplusplus
	} // extern "C" {
#endif

#endif // #ifndef PERFORMANCE_METRICS_H

// EOF
