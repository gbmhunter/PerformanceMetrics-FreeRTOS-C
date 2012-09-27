//!
//! @file 		PerformanceMetrics.h
//! @author 	Geoffrey Hunter (gbmhunter@gmail.com)
//! @date 		27/09/2011
//! @brief 		Header file for PerformanceMetrics.c
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
//======================================== HEADER GUARD =========================================//
//===============================================================================================//

#ifndef _PERFORMANCE_METRICS_H
#define _PERFORMANCE_METRICS_H

//==================================================================================================//
//=================================== PUBLIC FUNCTION PROTOTYPES ===================================//
//==================================================================================================//

void PerformanceMetrics_Start(uint32 taskStackSize, uint8 taskPriority);
xTaskHandle PerformanceMetrics_ReturnTaskHandle(void);

// End of header guard
#endif

// EOF