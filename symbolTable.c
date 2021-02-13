#include "symbolTable.h"
#include <stdlib.h>

Token keywords[] = {
    {.lexeme = "integer", .token = INTEGER},
    {.lexeme = "real", .token = REAL},
    {.lexeme = "boolean", .token = BOOLEAN},
    {.lexeme = "of", .token = OF},
    {.lexeme = "array", .token = ARRAY},
    {.lexeme = "start", .token = START},
    {.lexeme = "end", .token = END},
    {.lexeme = "declare", .token = DECLARE},
    {.lexeme = "module", .token = MODULE},
    {.lexeme = "driver", .token = DRIVER},
    {.lexeme = "program", .token = PROGRAM},
    {.lexeme = "record", .token = RECORD},
    {.lexeme = "tagged", .token = TAGGED},
    {.lexeme = "union", .token = UNION},
    {.lexeme = "get_value", .token = GET_VALUE},
    {.lexeme = "print", .token = PRINT},
    {.lexeme = "use", .token = USE},
    {.lexeme = "with", .token = WITH},
    {.lexeme = "parameters", .token = PARAMETERS},
    {.lexeme = "true", .token = TRUE},
    {.lexeme = "false", .token = FALSE},
    {.lexeme = "takes", .token = TAKES},
    {.lexeme = "input", .token = INPUT},
    {.lexeme = "returns", .token = RETURNS},
    {.lexeme = "AND", .token = AND},
    {.lexeme = "OR", .token = OR},
    {.lexeme = "for", .token = FOR},
    {.lexeme = "in", .token = IN},
    {.lexeme = "switch", .token = SWITCH},
    {.lexeme = "break", .token = BREAK},
    {.lexeme = "default", .token = DEFAULT},
    {.lexeme = "while", .token = WHILE},
};

int calculateHash(char *lexeme) {
    int hash = 0;
    for(int i = 0; i < strlen(lexeme); i++) {
        hash += (((int) lexeme[i]) * i);
        hash = hash % SIZE_OF_HASH_TABLE;
    }
    return hash;
}

SymbolTableElement *exists(char *lexeme, SymbolTable symbolTable) {
    int hash = calculateHash(lexeme);
    SymbolTableNode *temp = symbolTable + hash;
    if(temp == NULL || temp -> element == NULL) {
        return NULL;
    }
    while(temp != NULL) {
        if(strcmp(lexeme, temp -> element -> lexeme) == 0) {
            return temp -> element;
        }
        temp = temp -> next;
    }
    return NULL;
}

SymbolTableElement *insertToken(char *lexeme, TokenType tokenType, SymbolTable symbolTable) {
    if(exists(lexeme, symbolTable) == NULL) {
        int hash = calculateHash(lexeme);
        SymbolTableNode *temp = symbolTable + hash;
        if(temp == NULL) {
            temp = (SymbolTableNode *) malloc(sizeof(SymbolTableNode));
            temp -> element = (SymbolTableElement *) malloc(sizeof(SymbolTableElement));
            temp -> next = NULL;
            temp -> element -> lexeme = (char *) malloc(sizeof(char) * strlen(lexeme) + 1);
            temp -> element -> type = tokenType;
            strcpy(temp -> element -> lexeme, lexeme);
            return temp -> element;
        } else if(temp -> element == NULL) {
            temp -> next = NULL;
            temp -> element = (SymbolTableElement *) malloc(sizeof(SymbolTableElement));
            temp -> element -> lexeme = (char *) malloc(sizeof(char) * strlen(lexeme) + 1);
            temp -> element -> type = tokenType;
            strcpy(temp -> element -> lexeme, lexeme);
            return temp;
        } else {
            while(temp -> next != NULL) {
                temp = temp -> next;
            }   
            temp -> next = (SymbolTableElement *) malloc(sizeof(SymbolTableElement));
            temp = temp -> next;
            temp -> element = (SymbolTableElement *) malloc(sizeof(SymbolTableElement));
            temp -> element -> lexeme = (char *) malloc(sizeof(char) * strlen(lexeme) + 1);
            temp -> element -> type = tokenType;
            strcpy(temp -> element -> lexeme, lexeme);
            temp -> next = NULL;
            return temp;
        }
    } else {
        return exists(lexeme, symbolTable);
    }
}

SymbolTable newSymbolTable() {
    SymbolTable symbolTable = (SymbolTable) malloc(sizeof(SymbolTableNode) * SIZE_OF_HASH_TABLE);
    for(int i = 0; i < NO_OF_KEYWORDS; i++) {
        insertToken(keywords[i].lexeme, keywords[i].token, symbolTable);
    }
    return symbolTable;
}

void printSymbolTable(SymbolTable symbolTable) {
    if(symbolTable == NULL) {
        printf("Error in printing. Symbol Table doesn't exist\n");
        return;
    }
    for(int i = 0; i < SIZE_OF_HASH_TABLE; i++) {
        SymbolTableNode *temp = symbolTable + i;
        while(temp != NULL) {
            printf("Value = %s\n", temp -> element -> lexeme);
            temp = temp -> next;
        }
    }
}