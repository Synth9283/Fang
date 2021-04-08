#pragma once
#include <stdint.h>
#include "token.h"

typedef struct {
    char c, prev;
    uint32_t i, len;
    char *content;
} lexer_t;

lexer_t *lexerInit(char *content);
void lexerAdvance(lexer_t *lexer);
void lexerWhiteSpace(lexer_t *lexer);
token_t *lexerNextToken(lexer_t *lexer);
token_t *lexerNextWithToken(lexer_t *lexer, token_t *token);
token_t *lexerGetString(lexer_t *lexer);
token_t *lexerGetOperatorToken(lexer_t *lexer);
token_t *lexerGetId(lexer_t *lexer);
char *lexerCharToString(lexer_t *lexer);
