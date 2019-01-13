/** \addtogroup Cli
 *  @{
 */
/*****************************************************************************/
/** @file cli.c
 *  @brief cli interface
 *
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
static uint8_t GetParameters (char *pcData, uint8_t ucLength, char cDelimiter, char *Tokens[]);
static uint8_t Help (char **argv, uint8_t argc, char *pcResult);

/******************************************************************************
 *                           external variables
 ******************************************************************************/

/******************************************************************************
 *                           Private variables
 ******************************************************************************/
static const CommandList_t CommandList[] =
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
	char * Parameters[8];
	uint8_t ucCommandReceived = false;
	uint8_t ucParameterCount  = 0;
	uint8_t ucCount           = 0;
	uint8_t ucReturn          = false;

	ucCommandReceived = RxHandler(pcData, ucBytesReceived);

	if ((true == ucCommandReceived) && (strlen((const char *)m_pcCommand) > 0))
	{
		ucParameterCount = GetParameters((char *)m_pcCommand, strlen((const char *)m_pcCommand), ' ', Parameters);

		for (ucCount = 0; ucCount < sizeof (CommandList) / sizeof (CommandList[0]); ucCount++)
		{
			if (!strcmp(Parameters[COMMAND_START_OFFSET], CommandList[ucCount].pcName))
			{
				uint8_t ucParametersInCommmand = 0;

				ucParametersInCommmand = (ucParameterCount - 1);

				if( ucParametersInCommmand == CommandList[ucCount].ucExpectedNumOfParameters)
				{
					ucReturn = CommandList[ucCount].CliExecuteCommand(&Parameters[PARAMETER_START_OFFSET], ucParametersInCommmand, pcResult);
				}
				else
				{
					strcpy(pcResult, "\nIncorrect Parameters\r\n");
					ucReturn =true;
				}
				break;
			}//end if
		}//end for

		if (ucCount == sizeof (CommandList) / sizeof (CommandList[0]))
		{
			strcpy(pcResult, "\nCommand not found\r\n");
			ucReturn = true;
		}//end if
	}//end if

	return ucReturn;
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
static uint8_t GetParameters(char *pcData, uint8_t ucLength, char cDelimiter, char *Parameter[])
{
	uint8_t ucParameterCount = 0;
	uint8_t ucSpace          = false;

	Parameter[ucParameterCount++] = pcData;

	for (uint8_t ucCount = 0; ucCount < ucLength; ucCount++)
	{
		if (*(pcData + ucCount) == cDelimiter)
		{
			if (true != ucSpace)
			{
				*(pcData + ucCount) = '\0';
				Parameter[ucParameterCount] = &pcData[ucCount + 1];
				ucParameterCount++;
				ucSpace = true;
			}
		}
		else
		{
			ucSpace = false;
		}
	}

	if (true == ucSpace)
	{
		ucParameterCount--;
	}

	return ucParameterCount;
}//end GetParameters

/** @brief Handles Received characters from Cli
 *  @param[in] pcData  Pointer to Received characters
 *  @param[in] argc    Number of character received
 *  @return    uint8_t true - Command received, false - command not received yet
 *
 */
static uint8_t RxHandler(char *pcData, uint8_t ucBytesReceived)
{
	uint8_t ucReturn = false;

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
			ucReturn = true;
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

	return ucReturn;
}//RxHandler

/** @brief Display available commands
 *  @param[in] argv      Pointer to parameters string
 *  @param[in] argc      Number of Parameters
 *  @param[out] pcResult Pointer to result buffer
 *  @return     uint8_t  true-Command executed successfully,
 *                       false-Command not executed
 */
static uint8_t Help(char **argv, uint8_t argc, char *pcResult)
{
	uint16_t usLength = 0;

	usLength += sprintf(pcResult + usLength, "\r\n");

	for (uint8_t ucCount = 0; ucCount < sizeof (CommandList) / sizeof (CommandList[0]); ucCount++)
	{
		usLength += sprintf(pcResult + usLength, "\t%-15s"" - %s\r\n", CommandList[ucCount].pcName, CommandList[ucCount].pcDescription);
	}

	return true;
}//end Help

/******************************************************************************
 *                             End of file
 ******************************************************************************/
/** @}*/
