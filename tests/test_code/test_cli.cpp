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

#define RESULT_BUF_SIZE            (256u)
#define HELP_CMD_SIZE              (6u) 
#define INFO_CMD_SIZE              (6u)
#define SUM_CMD_SIZE               (9u)
#define SUM_CMD_SPACE_SIZE         (11u)
#define SUM_CMD_SPACE_AT_LAST_SIZE (13u)
#define WRONG_CMD_SIZE             (7u)
#define WRONG_PARAMETERS_CMD_SIZE  (5u)

TEST_GROUP(Module)
{
    char *pcResult = NULL;

    void setup()
    {
        //allocate memory for storing cli result
        pcResult = (char*)calloc(RESULT_BUF_SIZE, sizeof(char));
    }

    void teardown()
    {
        //free result memory
        free(pcResult);
    }
};

TEST(Module, cli_Init_test)
{
    //function under test
    cli_Init(pcResult);
    //check function output
    STRCMP_EQUAL(CLI_DEF_TEXT, pcResult);
}

TEST(Module, cli_process_cmd_null_test)
{
    char *pcInput      = NULL;
    bool bIsCmdProcess = false;

    //function under test
    bIsCmdProcess = cli_ProcessCmd(pcInput, 2, pcResult);
    //check function return
    CHECK_EQUAL(false, bIsCmdProcess);
}

TEST(Module, cli_process_cmd_help_test)
{
    char pcInputBuf[HELP_CMD_SIZE] = "help\r";
    bool bIsCmdProcess             = false;

    //function under test
    bIsCmdProcess = cli_ProcessCmd(pcInputBuf, HELP_CMD_SIZE, pcResult);
    printf("%s", pcResult);
    cli_ResetBuffer(pcResult);
    printf("%s", pcResult);
    //check function return
    CHECK_EQUAL(true, bIsCmdProcess);
}

TEST(Module, cli_process_cmd_info_test)
{
    char pcInputBuf[INFO_CMD_SIZE] = "info\r";
    bool bIsCmdProcess             = false;

    //function under test
    bIsCmdProcess = cli_ProcessCmd(pcInputBuf, INFO_CMD_SIZE, pcResult);
    printf("%s", pcResult);
    cli_ResetBuffer(pcResult);
    printf("%s", pcResult);	
    //check function return
    CHECK_EQUAL(true, bIsCmdProcess);
}

TEST(Module, cli_process_cmd_sum_test)
{
    char pcInputBuf[SUM_CMD_SIZE] = "sum 1 2\r";
    bool bIsCmdProcess            = false;

    //function under test
    bIsCmdProcess = cli_ProcessCmd(pcInputBuf, SUM_CMD_SIZE, pcResult);
    printf("%s", pcResult);
    cli_ResetBuffer(pcResult);
    printf("%s", pcResult);
    //check function return
    CHECK_EQUAL(true, bIsCmdProcess);
}

TEST(Module, cli_process_cmd_with_space_in_between_test)
{
    char pcInputBuf[SUM_CMD_SPACE_SIZE] = "sum  1  2\r";
    bool bIsCmdProcess                  = false;

    //function under test
    bIsCmdProcess = cli_ProcessCmd(pcInputBuf, SUM_CMD_SPACE_SIZE, pcResult);
    printf("%s", pcResult);
    cli_ResetBuffer(pcResult);
    printf("%s", pcResult);
    //check function return
    CHECK_EQUAL(true, bIsCmdProcess);
}

TEST(Module, cli_process_cmd_with_space_at_last_test)
{
    char pcInputBuf[SUM_CMD_SPACE_AT_LAST_SIZE] = "sum  1  2  \r";
    bool bIsCmdProcess                          = false;

    //function under test
    bIsCmdProcess = cli_ProcessCmd(pcInputBuf, SUM_CMD_SPACE_AT_LAST_SIZE, pcResult);
    printf("%s", pcResult);
    cli_ResetBuffer(pcResult);
    printf("%s", pcResult);	
    //check function return
    CHECK_EQUAL(true, bIsCmdProcess);
}

TEST(Module, cli_wrong_cmd_test)
{
    char pcInputBuf[WRONG_CMD_SIZE] = "wrong\r";
    bool bIsCmdProcess              = false;

    //function under test
    bIsCmdProcess = cli_ProcessCmd(pcInputBuf, WRONG_CMD_SIZE, pcResult);
    printf("%s", pcResult);
    cli_ResetBuffer(pcResult);
    printf("%s", pcResult);
    //check function return
    CHECK_EQUAL(true, bIsCmdProcess);
}

TEST(Module, cli_wrong_parameters_test)
{
    char pcInputBuf[WRONG_PARAMETERS_CMD_SIZE] = "sum\r";
    bool bIsCmdProcess                         = false;

    //function under test
    bIsCmdProcess = cli_ProcessCmd(pcInputBuf, WRONG_PARAMETERS_CMD_SIZE, pcResult);
    printf("%s", pcResult);
    cli_ResetBuffer(pcResult);
    printf("%s", pcResult);
    //check function return
    CHECK_EQUAL(true, bIsCmdProcess);
}

TEST(Module, cli_null_cmd_test)
{
    char *pcInput       = NULL;
    bool bIsCmdProcess  = false;

    //function under test
    bIsCmdProcess = cli_ProcessCmd(pcInput, WRONG_PARAMETERS_CMD_SIZE, pcResult);
    printf("%s", pcResult);
    cli_ResetBuffer(pcResult);
    printf("%s", pcResult);
    //check function return
    CHECK_EQUAL(false, bIsCmdProcess);
}

TEST(Module, cli_process_cmd_backspace_test)
{
    char pcInputBuf[SUM_CMD_SIZE] = "sum 1 2\b";
    bool bIsCmdProcess            = false;

    //function under test
    bIsCmdProcess = cli_ProcessCmd(pcInputBuf, SUM_CMD_SIZE, pcResult);
    printf("%s", pcResult);
    cli_ResetBuffer(pcResult);
    printf("%s", pcResult);
	//check function return
    CHECK_EQUAL(false, bIsCmdProcess);
}
