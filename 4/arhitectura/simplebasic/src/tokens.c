#include "basic.h"
#include <string.h>

void tokenInit(TOKENS* tokens)
{
    tokens->tokenCapacity = MAX_TOKENS_ON_LINE;
    tokens->tokenCount = 0;
    memset(tokens->token, 0, sizeof(tokens->token));
}

int tokenAdd(TOKENS* tokens, int type, char* value, int line)
{
    if (tokens == NULL) {
        return -1;
    }
    if (tokens->tokenCount >= tokens->tokenCapacity) {
        return -1;
    }

    tokens->token[tokens->tokenCount]
            = (TOKEN){.line = line, .pos = tokens->tokenCount, .type = type};
    if (strlen(value) > MAX_TOKEN_LEN - 1) {
        return -1;
    }
    strcpy(tokens->token[tokens->tokenCount].value, value);

    tokens->tokenCount++;
    return 0;
}

int tokenDelLast(TOKENS* tokens)
{
    if (tokens == NULL) {
        return -1;
    }
    if (tokens->tokenCount == 0) {
        return 0;
    }

    tokens->tokenCount--;
    memset(&(tokens->token[tokens->tokenCount]), 0, sizeof(TOKEN));
    return 0;
}

TOKEN tokenGETLast(TOKENS* tokens)
{
    if (tokens == NULL) {
        return tokens->token[0];
    }
    if (tokens->tokenCount == 0) {
        return tokens->token[0];
    }
    return tokens->token[tokens->tokenCount - 1];
}