//! @addtogroup Application
//! @brief Application for cli testing
//! @{
//
//****************************************************************************
//! @file app.c
//! @brief Implement application functions
//! @author Savindra Kumar(savindran1989@gmail.com)
//! @bug No known bugs.
//
//****************************************************************************
//****************************************************************************
//                           Includes
//****************************************************************************
//standard header files
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
//user defined header files
#include "projectinfo.h"
#include "app.h"

//****************************************************************************
//                           Defines and typedefs
//****************************************************************************

//****************************************************************************
//                           external variables
//****************************************************************************

//****************************************************************************
//                           Private variables
//****************************************************************************

//****************************************************************************
//                           Private Functions
//****************************************************************************

//****************************************************************************
//                    G L O B A L  F U N C T I O N S
//****************************************************************************
//
//! @brief Display Project Information
//! @param[in]  ppcParams    Pointer to parameters string
//! @param[in]  ucParamCount Number of Parameters
//! @param[out] pcResult     Pointer to result buffer
//! @return     uint8_t      true -Command executed successfully
//!                          false-Command not executed
//
uint8_t AppShowInfo(char **ppcParams, uint8_t ucParamCount, char *pcResult)
{
    uint16_t usLengthInBytes = 0;

    usLengthInBytes += sprintf(pcResult + usLengthInBytes, "\r\n");
    usLengthInBytes += sprintf(pcResult + usLengthInBytes, "................................................................\r\n");
    usLengthInBytes += sprintf(pcResult + usLengthInBytes, "\tPROJECT.. [ %s ]\r\n", PROJECT_TITLE);
    usLengthInBytes += sprintf(pcResult + usLengthInBytes, "\tVERSION.. [ %s ]\r\n", FIRMWARE_VERSION);
    usLengthInBytes += sprintf(pcResult + usLengthInBytes, "\tDATE..... [ %s %s]\r\n", __DATE__, __TIME__);
    usLengthInBytes += sprintf(pcResult + usLengthInBytes, "................................................................\r\n");

    return true;
}//end AppShowInfo

//
//! @brief Exit from application
//! @param[in]  ppcParams    Pointer to parameters string
//! @param[in]  ucParamCount Number of Parameters
//! @param[out] pcResult     Pointer to result buffer
//! @return     uint8_t      true -Command executed successfully,
//!                          false-Command not executed
//
uint8_t AppExit(char **ppcParams, uint8_t ucParamCount, char *pcResult)
{
    exit(0);
    return true;
}//end AppExit

//
//! @brief Sum of two numbers
//! @param[in]  ppcParams    Pointer to parameters string
//! @param[in]  ucParamCount Number of Parameters
//! @param[out] pcResult     Pointer to result buffer
//! @return     uint8_t      true -Command executed successfully,
//!                          false-Command not executed
//
uint8_t AppSum(char **ppcParams, uint8_t ucParamCount, char *pcResult)
{
    uint16_t usLengthInBytes = 0;
    int32_t  iNum1           = 0;
    int32_t  iNum2           = 0;
    int32_t  iSum            = 0;

    iNum1 = atoi(ppcParams[0]);
    iNum2 = atoi(ppcParams[1]);

    iSum = iNum1 + iNum2;

    usLengthInBytes += sprintf(pcResult + usLengthInBytes, "\r\n");
    usLengthInBytes += sprintf(pcResult + usLengthInBytes, "Sum = %d", iSum);
    usLengthInBytes += sprintf(pcResult + usLengthInBytes, "\r\n");

    return true;
} //end AppSum

//****************************************************************************
//                           L O C A L  F U N C T I O N S
//****************************************************************************

//****************************************************************************
//                             End of file
//****************************************************************************
//! @}
