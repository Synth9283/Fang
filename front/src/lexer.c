#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "include/lexer.h"
#include "include/token.h"

lexer_t *lexerInit(char *content) {
    lexer_t *lexer = calloc(1, sizeof(lexer_t));
    lexer->content = content;
    lexer->i = 0;
    lexer->len = strlen(lexer->content);
    lexer->c = lexer->content[lexer->i];

    return lexer;
}

void lexerAdvance(lexer_t *lexer) {
    if (lexer->c && lexer->i < lexer->len) {
        lexer->prev = lexer->c;
        lexer->i++;
        lexer->c = lexer->content[lexer->i];
    }
}

void lexerWhiteSpace(lexer_t *lexer) {
    while (lexer->c == ' ' || lexer->c == '\n') lexerAdvance(lexer);
}

void lexerComment(lexer_t *lexer) {
    lexerAdvance(lexer);
    
    if (lexer->c == '/' && lexer->prev == '/') while (lexer->c != '\n') lexerAdvance(lexer);
}

token_t *lexerNextToken(lexer_t *lexer) {
    while (lexer->c && lexer->i < lexer->len) {
        if (lexer->c == ' ' || lexer->c == '\n') lexerWhiteSpace(lexer);
        if (isalnum(lexer->c)) return lexerGetId(lexer);
        if (lexer->c == '"') return lexerGetString(lexer);
        else if (lexer->c == '/') lexerComment(lexer);
        switch (lexer->c) {
            case '+': return lexerGetOperatorToken(lexer); break;
            case '-': return lexerGetOperatorToken(lexer); break;
            case '*': return lexerGetOperatorToken(lexer); break;
            case '/': return lexerGetOperatorToken(lexer); break;
            case '%': return lexerGetOperatorToken(lexer); break;
            case '=': return lexerGetOperatorToken(lexer); break;
            case '!': return lexerGetOperatorToken(lexer); break;
            case '&': return lexerGetOperatorToken(lexer); break;
            case '|': return lexerGetOperatorToken(lexer); break;
            case '^': return lexerGetOperatorToken(lexer); break;
            case '>': return lexerGetOperatorToken(lexer); break;
            case '<': return lexerGetOperatorToken(lexer); break;
            case '~': return lexerNextWithToken(lexer, tokenInit(TOKEN_BNOT, lexerCharToString(lexer))); break;
            case '_': return lexerNextWithToken(lexer, tokenInit(TOKEN_DEFAULT, lexerCharToString(lexer))); break;
            case '?': return lexerNextWithToken(lexer, tokenInit(TOKEN_IF, lexerCharToString(lexer))); break;
            case ':': return lexerNextWithToken(lexer, tokenInit(TOKEN_COLON, lexerCharToString(lexer))); break;
            case ';': return lexerNextWithToken(lexer, tokenInit(TOKEN_SEMI, lexerCharToString(lexer))); break;
            case '.': return lexerNextWithToken(lexer, tokenInit(TOKEN_PERIOD, lexerCharToString(lexer))); break;
            case ',': return lexerNextWithToken(lexer, tokenInit(TOKEN_COMMA, lexerCharToString(lexer))); break;
            case '[': return lexerNextWithToken(lexer, tokenInit(TOKEN_LBRACKET, lexerCharToString(lexer))); break;
            case ']': return lexerNextWithToken(lexer, tokenInit(TOKEN_RBRACKET, lexerCharToString(lexer))); break;
            case '(': return lexerNextWithToken(lexer, tokenInit(TOKEN_LPAREN, lexerCharToString(lexer))); break;
            case ')': return lexerNextWithToken(lexer, tokenInit(TOKEN_RPAREN, lexerCharToString(lexer))); break;
            case '{': return lexerNextWithToken(lexer, tokenInit(TOKEN_LCURL, lexerCharToString(lexer))); break;
            case '}': return lexerNextWithToken(lexer, tokenInit(TOKEN_RCURL, lexerCharToString(lexer))); break;

            // TOKEN_ID,
            // TOKEN_ADD, // +
            // TOKEN_SUB, // -
            // TOKEN_MULT, // *
            // TOKEN_DIV, // /
            // TOKEN_MOD, // %
            // TOKEN_INC, // ++
            // TOKEN_DEC, // --
            // TOKEN_EQU, // ==
            // TOKEN_NEQU, // !=
            // TOKEN_GTHAN, // >
            // TOKEN_GTEQU, // >=
            // TOKEN_LTHAN, // <
            // TOKEN_LTEQU, // <=
            // TOKEN_NOT, // !
            // TOKEN_LAND, // &&
            // TOKEN_LOR, // ||
            // TOKEN_BNOT, // ~
            // TOKEN_BAND, // &
            // TOKEN_OR, // |
            // TOKEN_XOR, // ^
            // TOKEN_LSHIFT, // <<
            // TOKEN_RSHIFT, // >>
            // TOKEN_ASSIGN, // =
            // TOKEN_AASSIGN, // +=
            // TOKEN_SASSIGN, // -=
            // TOKEN_MULTASSIGN, // *=
            // TOKEN_DASSIGN, // /=
            // TOKEN_MODASSIGN, // %=
            // TOKEN_ANDASSIGN, // &=
            // TOKEN_ORASSIGN, // |=
            // TOKEN_XORASSIGN, // ^=
            // TOKEN_LSHIFTASSIGN, // <<=
            // TOKEN_RSHIFTASSIGN, // >>=
            // TOKEN_DREF, // ->
            // TOKEN_DEFAULT, // _
            // TOKEN_STRING, // "
            // TOKEN_IF, // ?
            // TOKEN_COLON, // :
            // TOKEN_SEMI, // ;
            // TOKEN_PERIOD, // .
            // TOKEN_COMMA, // ,
            // TOKEN_LBRACKET, // [
            // TOKEN_RBRACKET, // ]
            // TOKEN_LPAREN, // (
            // TOKEN_RPAREN, // )
            // TOKEN_LCURL, // {
            // TOKEN_RCURL // }
        }
    }
    return NULL;
}

token_t *lexerNextWithToken(lexer_t *lexer, token_t *token) {
    lexerAdvance(lexer);

    return token;
}

token_t *lexerGetString(lexer_t *lexer) {
    lexerAdvance(lexer);

    char *val = calloc(1, sizeof(char));
    val[0] = '\0';

    while (lexer->c != '"') {
        char *s = lexerCharToString(lexer);
        val = realloc(val, (strlen(val)+strlen(s)+1)*sizeof(char));

        if (lexer->c == '\\') {
            lexerAdvance(lexer);
            switch (lexer->c) {
                case 'b': strcat(val, "\b"); break;
                case 'f': strcat(val, "\f"); break;
                case 'n': strcat(val, "\n"); break;
                case 'r': val[0] = '\0'; break;  
                case 't': strcat(val, "\t"); break;
                case 'v': strcat(val, "\v"); break;
                case '"': strcat(val, "\""); break;
                case '\\': strcat(val, "\\"); break;
                default: break;
            }
        }
        else {
            strcat(val, s);
        }
        lexerAdvance(lexer);
    }

    lexerAdvance(lexer);
    return tokenInit(TOKEN_STRING, val);
}

token_t *lexerGetOperatorToken(lexer_t *lexer) {
    lexerAdvance(lexer);

    switch (lexer->prev) {
        case '+': switch (lexer->c) {
            case '+': lexerAdvance(lexer); return tokenInit(TOKEN_INC, "++"); break;
            case '=': lexerAdvance(lexer); return tokenInit(TOKEN_AASSIGN, "+="); break;
            default: return tokenInit(TOKEN_ADD, "+"); break;
        }
        case '-': switch (lexer->c) {
            case '-': lexerAdvance(lexer); return tokenInit(TOKEN_DEC, "--"); break;
            case '=': lexerAdvance(lexer); return tokenInit(TOKEN_DASSIGN, "-="); break;
            case '>': lexerAdvance(lexer); return tokenInit(TOKEN_DREF, "->"); break;
            default: return tokenInit(TOKEN_SUB, "-"); break;
        }
        case '*': switch (lexer->c) {
            case '=': lexerAdvance(lexer); return tokenInit(TOKEN_MULTASSIGN, "*="); break;
            default: return tokenInit(TOKEN_MULT, "*"); break;
        }
        case '/': switch (lexer->c) {
            case '=': lexerAdvance(lexer); return tokenInit(TOKEN_DASSIGN, "/="); break;
            default: return tokenInit(TOKEN_DIV, "/"); break;
        }
        case '%': switch (lexer->c) {
            case '=': lexerAdvance(lexer); return tokenInit(TOKEN_MODASSIGN, "%="); break;
            default: return tokenInit(TOKEN_MOD, "%"); break;
        }
        case '=': switch (lexer->c) {
            case '=': lexerAdvance(lexer); return tokenInit(TOKEN_EQU, "=="); break;
            default: return tokenInit(TOKEN_ASSIGN, "="); break;
        }
        case '!': switch (lexer->c) {
            case '=': lexerAdvance(lexer); return tokenInit(TOKEN_NEQU, "!="); break;
            default: return tokenInit(TOKEN_NOT, "!"); break;
        }
        case '&': switch (lexer->c) {
            case '&': lexerAdvance(lexer); return tokenInit(TOKEN_LAND, "&&"); break;
            case '=': lexerAdvance(lexer); return tokenInit(TOKEN_ANDASSIGN, "&="); break;
            default: return tokenInit(TOKEN_BAND, "&"); break;
        }
        case '|': switch (lexer->c) {
            case '|': lexerAdvance(lexer); return tokenInit(TOKEN_LOR, "||"); break;
            case '=': lexerAdvance(lexer); return tokenInit(TOKEN_ORASSIGN, "|="); break;
            default: return tokenInit(TOKEN_OR, "|"); break;
        }
        case '^': switch (lexer->c) {
            case '=': lexerAdvance(lexer); return tokenInit(TOKEN_XORASSIGN, "^="); break;
            default: return tokenInit(TOKEN_XOR, "^"); break;
        }
        case '>': switch (lexer->c) {
            case '=': lexerAdvance(lexer); return tokenInit(TOKEN_GTEQU, ">="); break;
            case '>': {
                lexerAdvance(lexer);
                if (lexer->c == '=') {
                    lexerAdvance(lexer);
                    return tokenInit(TOKEN_RSHIFTASSIGN, ">>=");
                }
                else return tokenInit(TOKEN_RSHIFT, ">>");
                break;
            }
            default: return tokenInit(TOKEN_GTHAN, ">"); break;
        }
        case '<': switch (lexer->c) {
            case '=': lexerAdvance(lexer); return tokenInit(TOKEN_LTEQU, "<="); break;
            case '<': {
                lexerAdvance(lexer);
                if (lexer->c == '=') {
                    lexerAdvance(lexer);
                    return tokenInit(TOKEN_LSHIFTASSIGN, "<<=");
                }
                else return tokenInit(TOKEN_LSHIFT, "<<");
                break;
            }
            default: return tokenInit(TOKEN_LTHAN, "<"); break;
        }
    }
}

token_t *lexerGetId(lexer_t *lexer) {
    char *val = calloc(1, sizeof(char));
    val[0] = '\0';

    while (isalnum(lexer->c)) {
        char *s = lexerCharToString(lexer);
        val = realloc(val, (strlen(val)+strlen(s)+1)*sizeof(char));
        strcat(val, s);

        lexerAdvance(lexer);
    }

    return tokenInit(TOKEN_ID, val);
}

char *lexerCharToString(lexer_t *lexer) {
    char *s = calloc(2, sizeof(char));
    s[0] = lexer->c;
    s[1] = '\0';

    return s;
}
