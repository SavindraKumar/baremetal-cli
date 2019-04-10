//! @addtogroup Application
//! @{
//
//****************************************************************************
//! @file app.h
//! @brief This contains the prototypes, macros, constants or global variables
//!        for application
//! @author Savindra Kumar(savindran1989@gmail.com)
//! @bug No known bugs.
//
//****************************************************************************
#ifndef _APP_H
#define _APP_H

//****************************************************************************
//                           Includes
//****************************************************************************

//****************************************************************************
//                           Constants and typedefs
//****************************************************************************


//****************************************************************************
//                           Global variables
//****************************************************************************

//****************************************************************************
//                           Global Functions
//****************************************************************************
//
//! @brief Display Project Information
//! @param[in]  ppcParams    Pointer to parameters string
//! @param[in]  ucParamCount Number of Parameters
//! @param[out] pcResult     Pointer to result buffer
//! @return     uint8_t      true -Command executed successfully
//!                          false-Command not executed
//
uint8_t app_ShowInfo (const char **ppcParams,
                      uint8_t ucParamCount,
                      char *pcResult);

//
//! @brief Exit from application
//! @param[in]  ppcParams    Pointer to parameters string
//! @param[in]  ucParamCount Number of Parameters
//! @param[out] pcResult     Pointer to result buffer
//! @return     uint8_t      true -Command executed successfully,
//!                          false-Command not executed
//
uint8_t app_Exit (const char **ppcParams,
                  uint8_t ucParamCount,
                  char *pcResult);

//
//! @brief Sum of two numbers
//! @param[in]  ppcParams    Pointer to parameters string
//! @param[in]  ucParamCount Number of Parameters
//! @param[out] pcResult     Pointer to result buffer
//! @return     uint8_t      true -Command executed successfully,
//!                          false-Command not executed
//
uint8_t app_Sum (const char **ppcParams, uint8_t ucParamCount, char *pcResult);


#endif // _APP_H
//****************************************************************************
//                             End of file
//****************************************************************************
//! @}
