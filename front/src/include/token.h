#pragma once

typedef struct {
    char *val;
    enum {
        TOKEN_ID = 0,
        TOKEN_EQUALS = 1,
        TOKEN_QUESTION = 2,
        TOKEN_COLON = 3,
        TOKEN_TYPE = 4,
        TOKEN_NOT = 5,
        TOKEN_GTHAN = 6,
        TOKEN_LTHAN = 7,
        TOKEN_DEFAULT = 8,
        TOKEN_STRING = 9,
        TOKEN_SEMI = 10,
        TOKEN_COMMA = 11,
        TOKEN_LPAREN = 12,
        TOKEN_RPAREN = 13,
        TOKEN_LCURL = 14,
        TOKEN_RCURL = 15
    } type;
} token_t;

token_t *tokenInit(uint32_t type, char *val);
