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

typedef uint8_t (*CliExecCommand)(uint8_t **argv, uint8_t argc);

typedef struct
{
    char * pcName;
    CliExecCommand CliExecuteCommand;
    char * pcDescription;
}CommandList_t;


/******************************************************************************
 *                           Global variables
******************************************************************************/
void CliInit (void);
void CliProcessCommand (char *pcData, uint8_t ucBytesReceived);

/******************************************************************************
 *                           Global Functions
******************************************************************************/


#endif /* _CONSOLE_H */
/******************************************************************************
 *                             End of file
******************************************************************************/
/** @}*/
