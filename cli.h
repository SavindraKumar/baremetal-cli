//! @addtogroup Cli
//! @{
//
//****************************************************************************
//! @file cli.h
//! @brief This contains the prototypes, macros, constants or global variables
//        for the Cli
//! @author Savindra Kumar(savindran1989@gmail.com)
//! @bug No known bugs.
//
//****************************************************************************
#ifndef _CLI_H
#define _CLI_H

//****************************************************************************
//                           Includes
//****************************************************************************

//****************************************************************************
//                           Constants and typedefs
//****************************************************************************
typedef uint8_t (*CliExecCmd) (char **ppcParameters, uint8_t ucParameterCount, char *pcResult);

typedef struct
{
    char * pcName;                        //!<Command name
    CliExecCmd CliExecuteCmd;             //!<Command execute function
    char * pcDescription;                 //!<Command description
    uint8_t ucExpectedNumOfParameters;    //!<Number of parameters in command
} CliCmdList_t;

//****************************************************************************
//                           Global variables
//****************************************************************************
void CliInit (char *pcResult);
uint8_t CliProcessCmd (char *pcData, uint8_t ucBytesReceived, char *pcResult);
void CliResetBuffer (char *pcResult);

//****************************************************************************
//                           Global Functions
//****************************************************************************

#endif // _CONSOLE_H
//****************************************************************************
//                             End of file
//****************************************************************************
//! @}
