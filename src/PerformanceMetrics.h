//!
//! @file 		PerformanceMetrics.h
//! @author 	Geoffrey Hunter (gbmhunter@gmail.com)
//! @date 		27/09/2011
//! @brief 		Header file for PerformanceMetrics.c
//! @details
//!		<b>Last Modified:			</b> 27/09/2011					\n
//!		<b>Version:					</b> v2.0						\n
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
//!		See the Doxygen documentation or PerformanceMetrics.c for a detailed description on this module.
//!		

//===============================================================================================//
//======================================== HEADER GUARD =========================================//
//===============================================================================================//

#ifndef _PERFORMANCE_METRICS_H
#define _PERFORMANCE_METRICS_H

//===============================================================================================//
//=================================== PUBLIC FUNCTION PROTOTYPES ================================//
//===============================================================================================//

void PerformanceMetrics_Start(uint32 taskStackSize, uint8 taskPriority);
xTaskHandle PerformanceMetrics_ReturnTaskHandle(void);

// End of header guard
#endif

// EOF