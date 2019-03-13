//! @addtogroup Main
//! @brief Initialize Cli Interface from main application
//! @{
//
//****************************************************************************
//! @file main.c
//! @brief Start of application
//! @author Savindra Kumar(savindran1989@gmail.com)
//! @bug No known bugs.
//
//****************************************************************************
//****************************************************************************
//                           Includes
//****************************************************************************
//standard header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
//user defined header files
#include "cli.h"

//****************************************************************************
//                           Defines and typedefs
//****************************************************************************
#define REC_INPUT_SIZE_IN_BYTES     10
#define OUTPUT_SIZE_IN_BYTES      1024

//****************************************************************************
//                           external variables
//****************************************************************************

//****************************************************************************
//                           Local variables
//****************************************************************************

//****************************************************************************
//                           Local Functions
//****************************************************************************

//****************************************************************************
//                    G L O B A L  F U N C T I O N S
//****************************************************************************
//
//! @brief main function
//! @param[in]  None
//! @return     int
//
int main (void)
{
    char pcRxBuffer[REC_INPUT_SIZE_IN_BYTES];
    char pcResult[OUTPUT_SIZE_IN_BYTES];

    system("/bin/stty raw");

    cli_Init(pcResult);
    printf(pcResult);

    for (;;)
    {
        bool    bIsCmdProcess = false;
        uint8_t ucBytesRec    = 0;

        pcRxBuffer[0]   = getchar();
        ucBytesRec      = 1;

        if (0 != ucBytesRec)
        {
            bIsCmdProcess = cli_ProcessCmd(pcRxBuffer, ucBytesRec, pcResult);

            if (true == bIsCmdProcess)
            {
                printf(pcResult);
                cli_ResetBuffer(pcResult);
                printf(pcResult);
            } //end if
        } //end if
    } //end for

    return 0;
} //end main

//****************************************************************************
//                           L O C A L  F U N C T I O N S
//****************************************************************************

//****************************************************************************
//                             End of file
//****************************************************************************
//! @}
