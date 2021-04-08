#include <stdio.h>
#include "front/src/include/file.h"
#include "front/src/include/lexer.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        puts("Please specify a file");
        return 1;
    }
    if (!checkFile(argv[1])) printf("Unable to read from file: %s\n", argv[1]);
    else {
        lexer_t *lexer = lexerInit(readFile(argv[1]));
        token_t *token = NULL;

        while (token = lexerNextToken(lexer)) printf("Type: %s, Value: %s\n", tokenTypeString(token), token->val);
    }

    return 0;
}
