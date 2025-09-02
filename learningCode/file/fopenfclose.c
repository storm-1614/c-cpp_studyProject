//This file is an example of fopen and fclose function.

#include <stdio.h>

int main(int argc, char *argv[]) {
    FILE *fp; //File stream pointer.
    int iflag;

    //If without parameters
    if (argc <= 1) {
        printf("usage: %s filename\n", argv[0]);
        return 1;
    }

    // Return FILE pointer
    fp = fopen(argv[1], "a+b");
    // If return null, file is not exist.
    if (fp == NULL) {
        printf("Open files %s failed", argv[1]);
        return 2;
    }
    printf("Open file %s successd!\n", argv[1]);

    //if fclose is successd, return 0, oterwise return EOF(a macro defined as -1).
    iflag = fclose(fp);
    if (iflag == 0){
        printf("Close files %s successd!\n", argv[1]);
    } else {
        printf("Close file %s failed! ", argv[1]);
        return 3;
    }
    return 0;
}
