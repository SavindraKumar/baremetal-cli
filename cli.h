/** \addtogroup Cli
 *  @{
 */
/*****************************************************************************/
/** @file cli.h
 *  @brief This contains the prototypes, macros, constants or global variables
 *  for the Cli
 *  @author Savindra Kumar(savindran1989@gmail.com)
 *  @bug No known bugs.
 */
/*****************************************************************************/
#ifndef _CLI_H
#define _CLI_H

/******************************************************************************
 *                           Includes
******************************************************************************/

/******************************************************************************
 *                           Constants and typedefs
******************************************************************************/
#define CLI_DEF_TEXT    "\r\nCli-> "

typedef uint8_t (*CliExecCommand)(char **argv, uint8_t argc, char *pcResult);

typedef struct
{
    char * pcName;
    CliExecCommand CliExecuteCommand;
    char * pcDescription;
    uint8_t ucExpectedNumOfParameters;
}CommandList_t;


/******************************************************************************
 *                           Global variables
******************************************************************************/
void CliInit (char *pcResult);
uint8_t CliProcessCommand (char *pcData, uint8_t ucBytesReceived, char *pcResult);
void CliResetBuffer (char *pcResult);

/******************************************************************************
 *                           Global Functions
******************************************************************************/


#endif /* _CONSOLE_H */
/******************************************************************************
 *                             End of file
******************************************************************************/
/** @}*/
