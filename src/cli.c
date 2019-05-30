//! @addtogroup Cli
//! @brief Cli Interface
//! @{
//
//****************************************************************************
//! @file cli.c
//! @brief Cli interface
//! @author Savindra Kumar(savindran1989@gmail.com)
//! @bug No known bugs.
//
//****************************************************************************
//****************************************************************************
//                           Includes
//****************************************************************************
//standard header files
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
//user defined header files
#include "cli.h"
#include "app.h"

//****************************************************************************
//                           Defines and typedefs
//****************************************************************************
#define DELIMITER                  ' '
#define CMD_SIZE_IN_BYTES          (100u)
#define CMD_OFFSET                 (0u)
#define PARAM_OFFSET               (1u)
#define MAX_NUM_OF_PARAMS          (8u)

//****************************************************************************
//                           Private Functions
//****************************************************************************
//
//! @brief Handles Received characters from Cli
//! @param[in] pcData           Pointer to Received characters
//! @param[in] ucBytesRec       Number of character received
//! @return    uint8_t          true  - Command received
//!                             false - command not received yet
//
static uint8_t RxHandler (const char *pcData, uint8_t ucBytesReceived);

//
//! @brief Get Parameters from commands
//! @param[in] pcData     Pointer to command string
//! @param[in] ucLength   Size of command string
//! @param[in] cDelimiter Delimiter used to separate parameters
//! @param[in] pcParamBuf Pointer to number of parameters in command
//! @return    uint8_t    Number of parameters in command string
//
static uint8_t GetParameters (char *pcData,
                              uint8_t ucLength,
                              char cDelimiter,
                              char *pcParamBuf[]);

//
//! @brief Display available commands
//! @param[in]  ppcParams      Pointer to parameters string
//! @param[in]  ucParamCount   Number of Parameters
//! @param[out] pcResult       Pointer to result buffer
//! @return     uint8_t        true -Command executed successfully,
//!                            false-Command not executed
//
static uint8_t Help (const char **ppcParameters,
                     uint8_t ucParameterCount,
                     char *pcResult);

//****************************************************************************
//                           external variables
//****************************************************************************

//****************************************************************************
//                           Private variables
//****************************************************************************
static const CliCmdList_t m_CliCmdListBuf[] =
{
    { "help", Help, "Displays list of supported commands", 0 },
    { "info", app_ShowInfo, "Shows device info", 0 },
    { "exit", app_Exit, "Exit from program", 0 },
    { "sum", app_Sum, "Sum of two numbers", 2 }
};

static char    m_cCmdBuf[CMD_SIZE_IN_BYTES];
static uint8_t m_ucIndex = 0;

//****************************************************************************
//                    G L O B A L  F U N C T I O N S
//****************************************************************************
void cli_Init(char *pcResult)
{
    sprintf(pcResult, CLI_DEF_TEXT);
}//end CliInit

uint8_t cli_ProcessCmd(const char *pcData, uint8_t ucBytesRec, char *pcResult)
{
    char     *pcParamsBuf[MAX_NUM_OF_PARAMS] = {0};
    uint8_t  ucParamCount                    = 0;
    uint8_t  ucCount                         = 0;
    uint16_t usNumOfCmds                     = 0;
    bool     bIsCmdRec                       = false;
    bool     bIsCmdProcess                   = false;


    if (NULL != pcData)
    {
        bIsCmdRec = RxHandler(pcData, ucBytesRec);
    }

    if ( (true == bIsCmdRec) && (strlen(m_cCmdBuf) > 0) )
    {
        ucParamCount = GetParameters(m_cCmdBuf, strlen(m_cCmdBuf), DELIMITER, pcParamsBuf);
        usNumOfCmds  = sizeof(m_CliCmdListBuf) / sizeof(m_CliCmdListBuf[0]);

        for (ucCount = 0; ucCount < usNumOfCmds; ucCount++)
        {
            if (!strcmp(pcParamsBuf[CMD_OFFSET], m_CliCmdListBuf[ucCount].pcName))
            {
                uint8_t    ucParamsInCmd   = 0;
                const char **ppcCmdParams  = (const char**)&pcParamsBuf[PARAM_OFFSET];

                ucParamsInCmd = ucParamCount - 1;

                if (ucParamsInCmd == m_CliCmdListBuf[ucCount].ucExpectedNumOfParams)
                {
                    bIsCmdProcess = m_CliCmdListBuf[ucCount].CliExecuteCmd(ppcCmdParams,
                                                                           ucParamsInCmd,
                                                                           pcResult);
                }
                else
                {
                    strcpy(pcResult, "\nIncorrect Parameters\r\n");
                    bIsCmdProcess = true;
                }
                break;
            }//end if
        }//end for

        if (ucCount == usNumOfCmds)
        {
            strcpy(pcResult, "\nCommand not found\r\n");
            bIsCmdProcess = true;
        }//end if
    }//end if

    return bIsCmdProcess;
}//end CliProcessCommand

void cli_ResetBuffer (char *pcResult)
{
    m_ucIndex = 0;
    memset(m_cCmdBuf, 0, sizeof(m_cCmdBuf));
    sprintf(pcResult, CLI_DEF_TEXT);
}//end CliResetBuffer

//****************************************************************************
//                           L O C A L  F U N C T I O N S
//****************************************************************************
static uint8_t GetParameters(char *pcData,
                             uint8_t ucLength,
                             char cDelimiter,
                             char *pcParamBuf[])
{
    uint8_t ucParamCount  = 0;
    bool    bIsSpaceInCmd = false;

    pcParamBuf[ucParamCount++] = pcData;

    for (uint8_t ucCount = 0; ucCount < ucLength; ucCount++)
    {
        if (*(pcData + ucCount) == cDelimiter)
        {
            if (true != bIsSpaceInCmd)
            {
                *(pcData + ucCount)      = '\0';
                pcParamBuf[ucParamCount] = &pcData[ucCount + 1];
                ucParamCount++;
                bIsSpaceInCmd = true;
            }//end if
        }//end if
        else
        {
            bIsSpaceInCmd = false;
        }//end else
    }//end for

    if (true == bIsSpaceInCmd)
    {
        ucParamCount--;
    }

    return ucParamCount;
}//end GetParameters

static uint8_t RxHandler(const char *pcData, uint8_t ucBytesRec)
{
    bool bIsCmdRec = false;

    for (uint8_t ucCount = 0; ucCount < ucBytesRec; ucCount++)
    {
        m_cCmdBuf[m_ucIndex] = pcData[ucCount];

        if ('\r' == m_cCmdBuf[m_ucIndex])
        {
            m_cCmdBuf[m_ucIndex] = '\0';
            bIsCmdRec          = true;
        }
        if ('\b' == m_cCmdBuf[m_ucIndex])
        {
            if (m_ucIndex)
            {
                m_ucIndex--;
            }
        }
        else if (m_ucIndex < (sizeof(m_cCmdBuf) - 1))
        {
            m_ucIndex++;
        }
        m_cCmdBuf[m_ucIndex] = '\0';
    }

    return bIsCmdRec;
}//RxHandler

static uint8_t Help(const char **ppcParams, uint8_t ucParamCount, char *pcResult)
{
    uint16_t usLengthInBytes = 0;
    uint16_t usNumOfCmds     = 0;

    usLengthInBytes += sprintf(pcResult + usLengthInBytes, "\r\n");
    usNumOfCmds      = sizeof(m_CliCmdListBuf) / sizeof(m_CliCmdListBuf[0]);

    for (uint8_t ucCount = 0; ucCount < usNumOfCmds; ucCount++)
    {
        usLengthInBytes += sprintf(pcResult + usLengthInBytes, "\t%-15s" " - %s\r\n",
                                   m_CliCmdListBuf[ucCount].pcName,
                                   m_CliCmdListBuf[ucCount].pcDescription);
    }

    return true;
}//end Help

//****************************************************************************
//                             End of file
//****************************************************************************
//! @}
