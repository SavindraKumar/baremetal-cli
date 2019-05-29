#include "CppUTest/TestHarness.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>


extern "C"
{
	#include "app.h"
	#include "cli.h"
}

#define RESULT_BUF_SIZE          256
#define HELP_CMD_SIZE              6 
#define INFO_CMD_SIZE              6
#define SUM_CMD_SIZE               9
#define SUM_CMD_SPACE_SIZE        11
#define WRONG_CMD_SIZE             7
#define WRONG_PARAMETERS_CMD_SIZE  5



TEST_GROUP(Module)
{
	char *pcResultBuf = NULL;

    void setup()
    {	
	    pcResultBuf = (char*)calloc(RESULT_BUF_SIZE, sizeof(char));

    }

    void teardown()
    {
		free(pcResultBuf);
    }
};

TEST(Module, cli_Init_test)
{
    cli_Init(pcResultBuf);
	STRCMP_EQUAL(CLI_DEF_TEXT, pcResultBuf);
}

TEST(Module, cli_process_cmd_null_test)
{
	char *pcInput      = NULL;
	bool bIsCmdProcess = false;
	
	bIsCmdProcess = cli_ProcessCmd(pcInput, 2, pcResultBuf);
	CHECK_EQUAL(false, bIsCmdProcess);
}


TEST(Module, cli_process_cmd_help_test)
{
	char pcInput[HELP_CMD_SIZE]  = "help\r";
	bool bIsCmdProcess           = false;
	
	bIsCmdProcess = cli_ProcessCmd(pcInput, HELP_CMD_SIZE, pcResultBuf);
	printf("%s", pcResultBuf);
	cli_ResetBuffer(pcResultBuf);
	printf("%s", pcResultBuf);
	CHECK_EQUAL(true, bIsCmdProcess);
}

TEST(Module, cli_process_cmd_info_test)
{
	char pcInput[INFO_CMD_SIZE]  = "info\r";
	bool bIsCmdProcess           = false;
	
	bIsCmdProcess = cli_ProcessCmd(pcInput, INFO_CMD_SIZE, pcResultBuf);
	printf("%s", pcResultBuf);
	cli_ResetBuffer(pcResultBuf);
	printf("%s", pcResultBuf);	
	CHECK_EQUAL(true, bIsCmdProcess);
}


TEST(Module, cli_process_cmd_sum_test)
{
	char pcInput[SUM_CMD_SIZE]  = "sum 1 2\r";
	bool bIsCmdProcess          = false;
	
	bIsCmdProcess = cli_ProcessCmd(pcInput, SUM_CMD_SIZE, pcResultBuf);
	printf("%s", pcResultBuf);
	cli_ResetBuffer(pcResultBuf);
	printf("%s", pcResultBuf);		
	CHECK_EQUAL(true, bIsCmdProcess);
}


TEST(Module, cli_process_cmd_sum_with_space_test)
{
	char pcInput[SUM_CMD_SPACE_SIZE]  = "sum  1  2\r";
	bool bIsCmdProcess                = false;
	
	bIsCmdProcess = cli_ProcessCmd(pcInput, SUM_CMD_SPACE_SIZE, pcResultBuf);
	printf("%s", pcResultBuf);
	cli_ResetBuffer(pcResultBuf);
	printf("%s", pcResultBuf);	
	CHECK_EQUAL(true, bIsCmdProcess);
}

TEST(Module, cli_wrong_cmd_test)
{
	char pcInput[WRONG_CMD_SIZE]  = "wrong\r";
	bool bIsCmdProcess            = false;
	
	bIsCmdProcess = cli_ProcessCmd(pcInput, WRONG_CMD_SIZE, pcResultBuf);
	printf("%s", pcResultBuf);
	cli_ResetBuffer(pcResultBuf);
	printf("%s", pcResultBuf);	
	CHECK_EQUAL(true, bIsCmdProcess);
}


TEST(Module, cli_wrong_parameters_test)
{
	char pcInput[WRONG_PARAMETERS_CMD_SIZE] = "sum\r";
	bool bIsCmdProcess                      = false;
	
	bIsCmdProcess = cli_ProcessCmd(pcInput, WRONG_PARAMETERS_CMD_SIZE, pcResultBuf);
	printf("%s", pcResultBuf);
	cli_ResetBuffer(pcResultBuf);
	printf("%s", pcResultBuf);	
	CHECK_EQUAL(true, bIsCmdProcess);
}

TEST(Module, cli_null_cmd_test)
{
	char *pcInput       = NULL;
	bool bIsCmdProcess  = false;
	
	bIsCmdProcess = cli_ProcessCmd(pcInput, WRONG_PARAMETERS_CMD_SIZE, pcResultBuf);
	printf("%s", pcResultBuf);
	cli_ResetBuffer(pcResultBuf);
	printf("%s", pcResultBuf);	
	CHECK_EQUAL(false, bIsCmdProcess);
}
