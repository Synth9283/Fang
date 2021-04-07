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
        lexer->i++;
        lexer->c = lexer->content[lexer->i];
    }
}

void lexerWhiteSpace(lexer_t *lexer) {
    while (lexer->c == ' ' || lexer->c == '\n') lexerAdvance(lexer);
}

void lexerComment(lexer_t *lexer) {
    lexerAdvance(lexer);
    
    if (lexer->c == '/') while (lexer->c != '\n') lexerAdvance(lexer);
}

token_t *lexerNextToken(lexer_t *lexer) {
    while (lexer->c && lexer->i < lexer->len) {
        if (lexer->c == ' ' || lexer->c == '\n') lexerWhiteSpace(lexer);
        if (isalnum(lexer->c)) return lexerGetId(lexer);
        if (lexer->c == '"') return lexerGetString(lexer);
        else if (lexer->c == '/') lexerComment(lexer);
        switch (lexer->c) {
            case '=': return lexerNextWithToken(lexer, tokenInit(TOKEN_EQUALS, lexerCharToString(lexer))); break;
            case '?': return lexerNextWithToken(lexer, tokenInit(TOKEN_QUESTION, lexerCharToString(lexer))); break;
            case ':': return lexerNextWithToken(lexer, tokenInit(TOKEN_COLON, lexerCharToString(lexer))); break;
            case '!': return lexerNextWithToken(lexer, tokenInit(TOKEN_NOT, lexerCharToString(lexer))); break;
            case '>': return lexerNextWithToken(lexer, tokenInit(TOKEN_GTHAN, lexerCharToString(lexer))); break;
            case '<': return lexerNextWithToken(lexer, tokenInit(TOKEN_LTHAN, lexerCharToString(lexer))); break;
            case '_': return lexerNextWithToken(lexer, tokenInit(TOKEN_DEFAULT, lexerCharToString(lexer))); break;
            case ';': return lexerNextWithToken(lexer, tokenInit(TOKEN_SEMI, lexerCharToString(lexer))); break;
            case ',': return lexerNextWithToken(lexer, tokenInit(TOKEN_COMMA, lexerCharToString(lexer))); break;
            case '(': return lexerNextWithToken(lexer, tokenInit(TOKEN_LPAREN, lexerCharToString(lexer))); break;
            case ')': return lexerNextWithToken(lexer, tokenInit(TOKEN_RPAREN, lexerCharToString(lexer))); break;
            case '{': return lexerNextWithToken(lexer, tokenInit(TOKEN_LCURL, lexerCharToString(lexer))); break;
            case '}': return lexerNextWithToken(lexer, tokenInit(TOKEN_RCURL, lexerCharToString(lexer))); break;

            // TOKEN_ID = 0,
            // TOKEN_EQUALS = 1,
            // TOKEN_QUESTION = 2,
            // TOKEN_COLON = 3,
            // TOKEN_TYPE = 4,
            // TOKEN_NOT = 5,
            // TOKEN_GTHAN = 6,
            // TOKEN_LTHAN = 7,
            // TOKEN_DEFAULT = 8,
            // TOKEN_STRING = 9,
            // TOKEN_SEMI = 10,
            // TOKEN_COMMA = 11,
            // TOKEN_LPAREN = 12,
            // TOKEN_RPAREN = 13,
            // TOKEN_LCURL = 14,
            // TOKEN_RCURL = 15
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
