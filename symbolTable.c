#include "symbolTable.h"

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
            temp = (SymbolTableElement *) malloc(sizeof(SymbolTableElement));
            temp -> next = NULL;
            temp -> element -> lexeme = (char *) malloc(sizeof(char) * strlen(lexeme) + 1);
            temp -> element -> type = tokenType;
            strcpy(temp -> element -> lexeme, lexeme);
            return temp;
        } else if(temp -> element -> lexeme == NULL) {
            temp -> next = NULL;
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
    // TODO: Populate the symbol Table with keywords
    return symbolTable;
}