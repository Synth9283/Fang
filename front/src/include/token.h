#pragma once

typedef struct {
    char *val;
    enum {
        TOKEN_ID,
        TOKEN_ADD, // +
        TOKEN_SUB, // -
        TOKEN_MULT, // *
        TOKEN_DIV, // /
        TOKEN_MOD, // %
        TOKEN_INC, // ++
        TOKEN_DEC, // --
        TOKEN_EQU, // ==
        TOKEN_NEQU, // !=
        TOKEN_GTHAN, // >
        TOKEN_GTEQU, // >=
        TOKEN_LTHAN, // <
        TOKEN_LTEQU, // <=
        TOKEN_NOT, // !
        TOKEN_LAND, // &&
        TOKEN_LOR, // ||
        TOKEN_BNOT, // ~
        TOKEN_BAND, // &
        TOKEN_OR, // |
        TOKEN_XOR, // ^
        TOKEN_LSHIFT, // <<
        TOKEN_RSHIFT, // >>
        TOKEN_ASSIGN, // =
        TOKEN_AASSIGN, // +=
        TOKEN_SASSIGN, // -=
        TOKEN_MULTASSIGN, // *=
        TOKEN_DASSIGN, // /=
        TOKEN_MODASSIGN, // %=
        TOKEN_ANDASSIGN, // &=
        TOKEN_ORASSIGN, // |=
        TOKEN_XORASSIGN, // ^=
        TOKEN_LSHIFTASSIGN, // <<=
        TOKEN_RSHIFTASSIGN, // >>=
        TOKEN_DREF, // ->
        TOKEN_DEFAULT, // _
        TOKEN_STRING, // "
        TOKEN_IF, // ?
        TOKEN_COLON, // :
        TOKEN_SEMI, // ;
        TOKEN_PERIOD, // .
        TOKEN_COMMA, // ,
        TOKEN_LBRACKET, // [
        TOKEN_RBRACKET, // ]
        TOKEN_LPAREN, // (
        TOKEN_RPAREN, // )
        TOKEN_LCURL, // {
        TOKEN_RCURL // }
    } type;
} token_t;

token_t *tokenInit(uint32_t type, char *val);
char *tokenTypeString(token_t *token);
