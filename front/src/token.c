#include <stdlib.h>
#include <stdint.h>
#include "include/token.h"

token_t *tokenInit(uint32_t type, char *val) {
    token_t *token = calloc(1, sizeof(token_t));
    token->type = type;
    token->val = val;

    return token;
}
