/** \addtogroup Application
 *  @{
 */
/*****************************************************************************/
/** @file app.c
 *  @brief Implement application functions
 *  @author Savindra Kumar(savindran1989@gmail.com)
 *  @bug No known bugs.
 */
 /*****************************************************************************/
/******************************************************************************
 *                           Includes
******************************************************************************/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "projectinfo.h"
#include "app.h"

/******************************************************************************
 *                           Defines and typedefs
******************************************************************************/

/******************************************************************************
 *                           external variables
 ******************************************************************************/

/******************************************************************************
 *                           Private variables
******************************************************************************/

/******************************************************************************
 *                           Private Functions
******************************************************************************/


/******************************************************************************
 *                    G L O B A L  F U N C T I O N S
******************************************************************************/
/** @brief Display Project Information
 *  @param[in] argv    Pointer to parameters string
 *  @param[in] argc    Number of Parameters
 *  @return    uint8_t
 */
uint8_t AppShowInfo(uint8_t **argv, uint8_t argc)
{
	printf("\r\n");
	printf("................................................................\r\n");
	printf("\tPROJECT.. [ %s ]\r\n", PROJECT_TITLE);
	printf("\tVERSION.. [ %s ]\r\n", FIRMWARE_VERSION);

	printf("\tDATE..... [ %s %s]\r\n", __DATE__, __TIME__);
	printf("................................................................\r\n");
    return 0;
}//end AppShowInfo

/** @brief Exit from application
 *  @param[in] argv    Pointer to parameters string
 *  @param[in] argc    Number of Parameters
 *  @return    uint8_t
 */
uint8_t AppExit(uint8_t **argv, uint8_t argc)
{
	exit(0);
	return 0;
}//end AppExit

/** @brief Sum of two numbers
 *  @param[in] argv    Pointer to parameters string
 *  @param[in] argc    Number of Parameters
 *  @return    uint8_t
 */
uint8_t AppSum(uint8_t **argv, uint8_t argc)
{
	int32_t iNum1  = 0;
	int32_t iNum2  = 0;
	int32_t iSum   = 0;

	iNum1 = atoi((const char *)argv[1]);
	iNum2 = atoi((const char *)argv[2]);

	if (3 != argc)
	{
		printf("\n Please enter: sum2<space><num1><space><num2>\r\n");
		return 0;
	}

	iSum = iNum1 + iNum2;

	printf("\r\n");
	printf("Sum =%d\n", iSum);
	printf("\r\n");

	return 0;
}//AppSum

/******************************************************************************
 *                           L O C A L  F U N C T I O N S
******************************************************************************/

/******************************************************************************
 *                             End of file
******************************************************************************/
/** @}*/
