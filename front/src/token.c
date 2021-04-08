#include <stdlib.h>
#include <stdint.h>
#include "include/token.h"

token_t *tokenInit(uint32_t type, char *val) {
    token_t *token = calloc(1, sizeof(token_t));
    token->type = type;
    token->val = val;

    return token;
}

char *tokenTypeString(token_t *token) {
    switch (token->type) {
        case TOKEN_ID: return token->val; break;
        case TOKEN_ADD: return "TOKEN_ADD"; break; // +
        case TOKEN_SUB: return "TOKEN_SUB"; break; // -
        case TOKEN_MULT: return "TOKEN_MULT"; break; // *
        case TOKEN_DIV: return "TOKEN_DIV"; break; // /
        case TOKEN_MOD: return "TOKEN_MOD"; break; // %
        case TOKEN_INC: return "TOKEN_INC"; break; // ++
        case TOKEN_DEC: return "TOKEN_DEC"; break; // --
        case TOKEN_EQU: return "TOKEN_EQU"; break; // ==
        case TOKEN_NEQU: return "TOKEN_NEQU"; break; // !=
        case TOKEN_GTHAN: return "TOKEN_GTHAN"; break; // >
        case TOKEN_GTEQU: return "TOKEN_GTEQU"; break; // >=
        case TOKEN_LTHAN: return "TOKEN_LTHAN"; break; // <
        case TOKEN_LTEQU: return "TOKEN_LTEQU"; break; // <=
        case TOKEN_NOT: return "TOKEN_NOT"; break; // !
        case TOKEN_LAND: return "TOKEN_LAND"; break; // &&
        case TOKEN_LOR: return "TOKEN_LOR"; break; // ||
        case TOKEN_BNOT: return "TOKEN_BNOT"; break; // ~
        case TOKEN_BAND: return "TOKEN_BNOT"; break; // &
        case TOKEN_OR: return "TOKEN_OR"; break; // |
        case TOKEN_XOR: return "TOKEN_XOR"; break; // ^
        case TOKEN_LSHIFT: return "TOKEN_LSHIFT"; break; // <<
        case TOKEN_RSHIFT: return "TOKEN_RSHIFT"; break; // >>
        case TOKEN_ASSIGN: return "TOKEN_ASSIGN"; break; // =
        case TOKEN_AASSIGN: return "TOKEN_AASSIGN"; break; // +=
        case TOKEN_SASSIGN: return "TOKEN_SASSIGN"; break; // -=
        case TOKEN_MULTASSIGN: return "TOKEN_MULTASSIGN"; break; // *=
        case TOKEN_DASSIGN: return "TOKEN_DASSIGN"; break; // /=
        case TOKEN_MODASSIGN: return "TOKEN_MODASSIGN"; break; // %=
        case TOKEN_ANDASSIGN: return "TOKEN_ANDASSIGN"; break; // &=
        case TOKEN_ORASSIGN: return "TOKEN_ORASSIGN"; break; // |=
        case TOKEN_XORASSIGN: return "TOKEN_XORASSIGN"; break; // ^=
        case TOKEN_LSHIFTASSIGN: return "TOKEN_LSHIFTASSIGN"; break; // <<=
        case TOKEN_RSHIFTASSIGN: return "TOKEN_RSHIFTASSIGN"; break; // >>=
        case TOKEN_DREF: return "TOKEN_DREF"; break; // ->
        case TOKEN_DEFAULT: return "TOKEN_DEFAULT"; break; // _
        case TOKEN_STRING: return "TOKEN_STRING"; break; // "
        case TOKEN_IF: return "TOKEN_IF"; break; // ?
        case TOKEN_COLON: return "TOKEN_COLON"; break; // :
        case TOKEN_SEMI: return "TOKEN_SEMI"; break; // ;
        case TOKEN_PERIOD: return "TOKEN_PERIOD"; break; // .
        case TOKEN_COMMA: return "TOKEN_COMMA"; break; // ,
        case TOKEN_LBRACKET: return "TOKEN_LBRACKET"; break; // [
        case TOKEN_RBRACKET: return "TOKEN_RBRACKET"; break; // ]
        case TOKEN_LPAREN: return "TOKEN_LPAREN"; break; // (
        case TOKEN_RPAREN: return "TOKEN_RPAREN"; break; // )
        case TOKEN_LCURL: return "TOKEN_LCURL"; break; // {
        case TOKEN_RCURL: return "TOKEN_RCURL"; break; // }
        default: return "Unknown"; break;
    }
}
