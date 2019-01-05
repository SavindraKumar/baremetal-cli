/** \addtogroup Cli
 *  @{
 */
/*****************************************************************************/
/** @file cli.c
 *  @brief cli interface
 *
 *  @author Savm_ucIndexra Kumar(savm_ucIndexran1989@gmail.com)
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
//user defined header files
#include "cli.h"
#include "app.h"

/******************************************************************************
 *                           Defines and typedefs
 ******************************************************************************/
#define COMMAND_SIZE_IN_BYTES   100

/******************************************************************************
 *                           Private Functions
 ******************************************************************************/
static void RxHandler (char *pcData, uint8_t ucBytesReceived);
static uint8_t GetParameters (char *pcData, uint8_t ucLength, char cDelimiter, char *Tokens[]);
static uint8_t Help (uint8_t **argv, uint8_t argc);


/******************************************************************************
 *                           external variables
 ******************************************************************************/
/*volatile uint64_t SysTick;

uint64_t ConsoleReadTimer =0;*/
/******************************************************************************
 *                           Private variables
 ******************************************************************************/
static const CommandList_t CommandList[] =
{
		{"help", Help, "Displays list of supported commands"},
		{"info", AppShowInfo, "Shows device info"},
		{"exit", AppExit, "Exit from program"},
		{"sum", AppSum, "Sum of two numbers"},
};

static char m_pcCommand[COMMAND_SIZE_IN_BYTES];
static uint8_t m_pcCommandReceived              = 0;
static uint8_t m_ucIndex                        = 0;


/******************************************************************************
 *                    G L O B A L  F U N C T I O N S
 ******************************************************************************/

/** @brief Initialise Cli
 *  @param[in] None
 *  @return    None
 */
void CliInit(void)
{
	printf(CLI_DEF_TEXT);
}//end CliInit

/** @brief Process characters received from Cli
 *  @param[in] pcData          Pointer to characters received
 *  @param[in] ucBytesReceived Number of characters received
 *  @return    None
 */
void CliProcessCommand(char *pcData, uint8_t ucBytesReceived)
{
	char * Parameters[8];
	uint8_t ucParameterCount = 0;
	uint8_t ucCount          = 0;

	RxHandler(pcData, ucBytesReceived);

	if ((1 == m_pcCommandReceived) && (strlen((const char *)m_pcCommand) > 0))
	{
		ucParameterCount = GetParameters((char *)m_pcCommand, strlen((const char *)m_pcCommand), ' ', Parameters);

		if (ucParameterCount > 0)
		{
			for (ucCount = 0; ucCount < sizeof (CommandList) / sizeof (CommandList[0]); ucCount++)
			{
				if (!strcmp(Parameters[0], CommandList[ucCount].pcName))

				{
					CommandList[ucCount].CliExecuteCommand((uint8_t **)Parameters, ucParameterCount);
					break;
				}
			}
			if (ucCount == sizeof (CommandList) / sizeof (CommandList[0]))
			{
				printf("\nCommand not found\r\n");
			}

		}
		else
		{
			printf("\nCommand not found\r\n");
		}
	}

	if (1 == m_pcCommandReceived)
	{
		m_pcCommandReceived = 0;
		m_ucIndex           = 0;

		memset(m_pcCommand, 0, sizeof(m_pcCommand));
		printf(CLI_DEF_TEXT);
	}

}//end CliProcessCommand

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
	uint8_t ucSpace = 0;

	Parameter[ucParameterCount++] = pcData;

	for (uint8_t ucCount = 0; ucCount < ucLength; ucCount++)
	{
		if (*(pcData + ucCount) == cDelimiter)
		{
			if (1 != ucSpace)
			{
				*(pcData + ucCount) = '\0';
				Parameter[ucParameterCount] = &pcData[ucCount + 1];
				ucParameterCount++;
				ucSpace = 1;
			}
		}
		else
		{
			ucSpace = 0;
		}
	}

	if (1 == ucSpace)
	{
		ucParameterCount--;
	}

	return ucParameterCount;
}//end GetParameters

/** @brief Handles Received characters from Cli
 *  @param[in] pcData  Pointer to Received characters
 *  @param[in] argc    Number of character received
 *  @return    None
 */
static void RxHandler(char *pcData, uint8_t ucBytesReceived)
{
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
			m_pcCommandReceived = 1;
			m_pcCommand[m_ucIndex] = '\0';
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
}//RxHandler

/** @brief Display available commands
 *  @param[in] argv    Pointer to parameters string
 *  @param[in] argc    Number of Parameters
 *  @return    uint8_t
 */
static uint8_t Help(uint8_t **argv, uint8_t argc)
{
	printf("\r\n");

	for (uint8_t ucCount = 0; ucCount < sizeof (CommandList) / sizeof (CommandList[0]); ucCount++)
	{
		printf("\t%-15s"" - %s\r\n", CommandList[ucCount].pcName, CommandList[ucCount].pcDescription);
	}

	return 0;
}//end Help

/******************************************************************************
 *                             End of file
 ******************************************************************************/
/** @}*/
