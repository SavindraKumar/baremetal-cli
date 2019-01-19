/** @addtogroup Cli
 *  @brief Cli Interface
 *  @{
 */
/*****************************************************************************/
/** @file cli.c
 *  @brief Cli interface
 *  @author Savindra Kumar(savindran1989@gmail.com)
 *  @bug No known bugs.
 */
/*****************************************************************************/
/******************************************************************************
 *                           Includes
 ******************************************************************************/
//standard header files
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
//user defined header files
#include "cli.h"
#include "app.h"

/******************************************************************************
 *                           Defines and typedefs
 ******************************************************************************/
#define COMMAND_SIZE_IN_BYTES      100
#define COMMAND_START_OFFSET         0
#define PARAMETER_START_OFFSET       1

/******************************************************************************
 *                           Private Functions
 ******************************************************************************/
static uint8_t RxHandler (char *pcData, uint8_t ucBytesReceived);
static uint8_t GetParameters (char *pcData, uint8_t ucLength, char cDelimiter, char *ppcTokens[]);
static uint8_t Help (char **ppcParameters, uint8_t ucParameterCount, char *pcResult);

/******************************************************************************
 *                           external variables
 ******************************************************************************/

/******************************************************************************
 *                           Private variables
 ******************************************************************************/
static const CliCommandList_t m_pCliCommandList[] =
{
	{"help", Help, "Displays list of supported commands", 0},
	{"info", AppShowInfo, "Shows device info", 0},
	{"exit", AppExit, "Exit from program", 0},
	{"sum", AppSum, "Sum of two numbers", 2},
};

static char m_pcCommand[COMMAND_SIZE_IN_BYTES];
static uint8_t m_ucIndex                        = 0;


/******************************************************************************
 *                    G L O B A L  F U N C T I O N S
 ******************************************************************************/

/** @brief Initialise Cli
 *  @param[in]  None
 *  @param[out] pcResult   Pointer to result buffer
 *  @return    None
 */
void CliInit(char *pcResult)
{
	sprintf(pcResult, CLI_DEF_TEXT);
}//end CliInit

/** @brief Process characters received from Cli
 *  @param[in]  pcData          Pointer to characters received
 *  @param[in]  ucBytesReceived Number of characters received
 *  @param[out] pcResult        Pointer to result buffer
 *  @return     uint8_t         true-Command executed successfully,
 *                              false-Command not executed
 */
uint8_t CliProcessCommand(char *pcData, uint8_t ucBytesReceived, char *pcResult)
{
	char *ppcParameters[8];
	bool bCommandReceived     = false;
	bool bReturn              = false;
	uint8_t ucParameterCount  = 0;
	uint8_t ucCount           = 0;


	bCommandReceived = RxHandler(pcData, ucBytesReceived);

	if ((true == bCommandReceived) && (strlen((const char *)m_pcCommand) > 0))
	{
		ucParameterCount = GetParameters(m_pcCommand, strlen((const char *)m_pcCommand), ' ', ppcParameters);

		for (ucCount = 0; ucCount < sizeof (m_pCliCommandList) / sizeof (m_pCliCommandList[0]); ucCount++)
		{
			if (!strcmp(ppcParameters[COMMAND_START_OFFSET], m_pCliCommandList[ucCount].pcName))
			{
				uint8_t ucParametersInCommmand = 0;

				ucParametersInCommmand = (ucParameterCount - 1);

				if( ucParametersInCommmand == m_pCliCommandList[ucCount].ucExpectedNumOfParameters)
				{
					bReturn = m_pCliCommandList[ucCount].CliExecuteCommand(&ppcParameters[PARAMETER_START_OFFSET], ucParametersInCommmand, pcResult);
				}
				else
				{
					strcpy(pcResult, "\nIncorrect Parameters\r\n");
					bReturn =true;
				}
				break;
			}//end if
		}//end for

		if (ucCount == sizeof (m_pCliCommandList) / sizeof (m_pCliCommandList[0]))
		{
			strcpy(pcResult, "\nCommand not found\r\n");
			bReturn = true;
		}//end if
	}//end if

	return bReturn;
}//end CliProcessCommand

/** @brief Clear Cli buffer
 *  @param[in]  None
 *  @param[out] pcResult Pointer to command text
 *  @return     None
 *
 */
void CliResetBuffer(char *pcResult)
{
	m_ucIndex          = 0;
	memset(m_pcCommand, 0, sizeof(m_pcCommand));
	sprintf(pcResult, CLI_DEF_TEXT);
}//end CliResetBuffer

/******************************************************************************
 *                           L O C A L  F U N C T I O N S
 ******************************************************************************/
/** @brief Get Parameters from commands
 *  @param[in] pcData     Pointer to command string
 *  @param[in] ucLength   Size of command string
 *  @param[in] cDelimiter Delimiter used to separate parameters
 *  @param[in] Parameters Pointer to parameters array of string
 *  @return    uint8_t    Number of parameters in command string
 */
static uint8_t GetParameters(char *pcData, uint8_t ucLength, char cDelimiter, char *ppcParameters[])
{
	uint8_t ucParameterCount = 0;
	uint8_t ucSpace          = false;

	ppcParameters[ucParameterCount++] = pcData;

	for (uint8_t ucCount = 0; ucCount < ucLength; ucCount++)
	{
		if (*(pcData + ucCount) == cDelimiter)
		{
			if (true != ucSpace)
			{
				*(pcData + ucCount) = '\0';
				ppcParameters[ucParameterCount] = &pcData[ucCount + 1];
				ucParameterCount++;
				ucSpace = true;
			}//end if
		}//end if
		else
		{
			ucSpace = false;
		}//end else
	}//end for

	if (true == ucSpace)
	{
		ucParameterCount--;
	}

	return ucParameterCount;
}//end GetParameters

/** @brief Handles Received characters from Cli
 *  @param[in] pcData           Pointer to Received characters
 *  @param[in] ucParameterCount Number of character received
 *  @return    uint8_t          true - Command received, false - command not received yet
 *
 */
static uint8_t RxHandler(char *pcData, uint8_t ucBytesReceived)
{
	bool bReturn = false;

	for (uint8_t ucCount = 0; ucCount < ucBytesReceived; ucCount++)
	{
		//Convert string to lowercase
		if ((pcData[ucCount] >= 65) && (pcData[ucCount] <= 90))
		{
			pcData[ucCount] += 32;
		}

		m_pcCommand[m_ucIndex] = pcData[ucCount];

		if ('\r' == m_pcCommand[m_ucIndex])
		{
			m_pcCommand[m_ucIndex] = '\0';
			bReturn = true;
		}
		if ('\b' == m_pcCommand[m_ucIndex])
		{
			if(m_ucIndex)
			{
				m_ucIndex--;
			}
		}
		else if (m_ucIndex < (sizeof(m_pcCommand) - 1))
		{
			m_ucIndex++;
		}
		m_pcCommand[m_ucIndex] = '\0';
	}

	return bReturn;
}//RxHandler

/** @brief Display available commands
 *  @param[in]  ppcParameters      Pointer to parameters string
 *  @param[in]  ucParameterCount   Number of Parameters
 *  @param[out] pcResult           Pointer to result buffer
 *  @return     uint8_t            true-Command executed successfully,
 *                                 false-Command not executed
 */
static uint8_t Help(char **ppcParameters, uint8_t ucParameterCount, char *pcResult)
{
	uint16_t usLength = 0;

	usLength += sprintf(pcResult + usLength, "\r\n");

	for (uint8_t ucCount = 0; ucCount < sizeof (m_pCliCommandList) / sizeof (m_pCliCommandList[0]); ucCount++)
	{
		usLength += sprintf(pcResult + usLength, "\t%-15s"" - %s\r\n", m_pCliCommandList[ucCount].pcName, m_pCliCommandList[ucCount].pcDescription);
	}

	return true;
}//end Help

/******************************************************************************
 *                             End of file
 ******************************************************************************/
/** @}*/
