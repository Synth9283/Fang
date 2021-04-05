#include <stdlib.h>
#include <stdio.h>

int checkFile(char *path) {
    FILE *fp = fopen(path, "r");

    if (fp) {
        fclose(fp);
        return 1;  
    }
    else return 0;
}

char *readFile(char *path) {
    char c, *contents = NULL;
    int fileLen = 0;

    FILE *fp = fopen(path, "r");

    fseek(fp, 0L, SEEK_END);
    fileLen = ftell(fp);
    contents = malloc(fileLen);

    rewind(fp);
    fread(contents, 1, fileLen, fp);
    fclose(fp);

    return contents;
}
