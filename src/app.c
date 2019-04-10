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
#include "app.h"

//****************************************************************************
//                           Defines and typedefs
//****************************************************************************
#define PROJECT_TITLE     "Cli for Baremetal Embedded System"
#define FIRMWARE_VERSION  "0.0.1"

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
uint8_t app_ShowInfo(const char **ppcParams,
                     uint8_t ucParamCount,
                     char *pcResult)
{
    uint16_t usLengthInBytes = 0;

    usLengthInBytes += sprintf(pcResult + usLengthInBytes, "\r\n");
    usLengthInBytes += sprintf(pcResult + usLengthInBytes,
                               "\tPROJECT.. [ %s ]\r\n",
                               PROJECT_TITLE);
    usLengthInBytes += sprintf(pcResult + usLengthInBytes,
                               "\tVERSION.. [ %s ]\r\n",
                               FIRMWARE_VERSION);
    usLengthInBytes += sprintf(pcResult + usLengthInBytes,
                               "\tDATE..... [ %s %s]\r\n",
                               __DATE__, __TIME__);

    return true;
}//end AppShowInfo

uint8_t app_Exit(const char **ppcParams,
                 uint8_t ucParamCount,
                 char *pcResult)
{
    exit(0);
    return true;
}//end AppExit

uint8_t app_Sum(const char **ppcParams, uint8_t ucParamCount, char *pcResult)
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
}//end AppSum

//****************************************************************************
//                           L O C A L  F U N C T I O N S
//****************************************************************************

//****************************************************************************
//                             End of file
//****************************************************************************
//! @}
