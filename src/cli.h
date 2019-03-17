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
typedef uint8_t (*CliExecCmd) (char **ppcParams, uint8_t ucParamCount, char *pcResult);

typedef struct
{
    char       *pcName;                   //!<Command name
    CliExecCmd CliExecuteCmd;             //!<Command execute function
    char       *pcDescription;            //!<Command description
    uint8_t    ucExpectedNumOfParams;     //!<Number of parameters in command
}CliCmdList_t;

//****************************************************************************
//                           Global variables
//****************************************************************************
void cli_Init (char *pcResult);
uint8_t cli_ProcessCmd (char *pcData, uint8_t ucBytesRec, char *pcResult);
void cli_ResetBuffer (char *pcResult);

//****************************************************************************
//                           Global Functions
//****************************************************************************

#endif // _CLI_H
//****************************************************************************
//                             End of file
//****************************************************************************
//! @}
