/** \addtogroup Main
 *  @{
 */
/*****************************************************************************/
/** @file main.c
 *  @brief Start of application
 *  @author Savindra Kumar(savindran1989@gmail.com)
 *  @bug No known bugs.
 */
/*****************************************************************************/
/******************************************************************************
 *                           Includes
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include "cli.h"

/******************************************************************************
 *                           Defines and typedefs
 ******************************************************************************/
#define REC_INPUT_SIZE_IN_BYTES     10
#define OUTPUT_SIZE_IN_BYTES      1024

/******************************************************************************
 *                           external variables
 ******************************************************************************/

/******************************************************************************
 *                           Local variables
 ******************************************************************************/


/******************************************************************************
 *                           Local Functions
 ******************************************************************************/

/******************************************************************************
 *                    G L O B A L  F U N C T I O N S
 ******************************************************************************/
/** @brief main function
 *  @param[in]  None
 *  @return     int
 */
int main(void)
{
	char pcRxBuffer[REC_INPUT_SIZE_IN_BYTES];
	char pcResult[OUTPUT_SIZE_IN_BYTES];

	system ("/bin/stty raw");

	CliInit(pcResult);
	printf(pcResult);

	for(;;)
	{
		uint8_t ucReturn        = false;
		uint8_t ucBytesReceived = 0;

		pcRxBuffer[0] = getchar();
		ucBytesReceived = 1;

		if (0!= ucBytesReceived)
		{
			ucReturn = CliProcessCommand(pcRxBuffer, ucBytesReceived, pcResult);

			if (true == ucReturn)
			{
				printf(pcResult);
				CliResetBuffer(pcResult);
				printf(pcResult);
			}//end if
		}//end if
	}//end for

	return 0;
}//end main

/******************************************************************************
 *                           L O C A L  F U N C T I O N S
 ******************************************************************************/

/******************************************************************************
 *                             End of file
 ******************************************************************************/
/** @}*/
