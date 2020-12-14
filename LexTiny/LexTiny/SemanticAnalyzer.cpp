#include "SemanticAnalyzer.h"
#include <malloc.h>
#include <string.h>



void createSymbolList(Node* ast, int level, SymTableNode** root) {
	int index = 0;
	if (ast) {
		SymTableEntry* symTableEntry = (SymTableEntry*)malloc(sizeof(SymTableEntry));
		memset(symTableEntry, 0, sizeof(SymTableEntry));

		if (strcmp(ast->type, "VariableDeclaration") == 0) {
			//SymTableEntry* symTableEntry = (SymTableEntry*)malloc(sizeof(SymTableEntry));

			strcpy(symTableEntry->contextName, ast->type);
			strcpy(symTableEntry->dataType, ast->links[0]->extraData);
			strcpy(symTableEntry->symbolName, ast->extraData);
			symTableEntry->symbolType = 1;
			if (level = 1) {
				symTableEntry->symbolScope = IdentifierScope(1);
			}
			else {
				symTableEntry->symbolScope = IdentifierScope(0);
			}
		}
		else if (strcmp(ast->type, "FunctionDefinition") == 0) {
			//SymTableEntry* symTableEntry = (SymTableEntry*)malloc(sizeof(SymTableEntry));

			strcpy(symTableEntry->contextName, ast->type);
			strcpy(symTableEntry->dataType, ast->links[0]->extraData);
			strcpy(symTableEntry->symbolName, ast->extraData);
			symTableEntry->symbolType = 2;
			if (level = 1) {
				symTableEntry->symbolScope = IdentifierScope(1);
			}
			else {
				symTableEntry->symbolScope = IdentifierScope(0);
			}
		}

		SymTableNode* symTableroot;
		symTableroot = addEntryToSymbolTable(*root, symTableEntry);

		root = &symTableroot;

		for (index = 0; index < ast->numLinks; index++) {
			createSymbolList(ast->links[index], level + 1, root);
		}
		

	}
}

void printSymbolList(SymTableNode* symTableroot) {
	SymTableNode* aux = symTableroot;
	while (aux != NULL) {
		printf("Symbol Name ->  %s\n", aux->symbolEntry->symbolName);
		printf("Data Type ->  %s\n", aux->symbolEntry->dataType);
		printf("Symbol Type ->  %d\n", aux->symbolEntry->symbolType);
		printf("Symbol Scope ->  %d\n", aux->symbolEntry->symbolScope);
		printf("Context Name ->  %s\n", aux->symbolEntry->contextName);
		printf("\n\n");
		if (aux->next != NULL) {
			aux = aux->next;
		}
	}
}

SymTableNode* addEntryToSymbolTable(SymTableNode* symTableroot, SymTableEntry* nodeToAdd) {
	if (!symTableroot) {
		SymTableNode* symTableroot = (SymTableNode*)malloc(sizeof(SymTableNode));
		memset(symTableroot, 0, sizeof(SymTableNode));
		symTableroot->symbolEntry == NULL;
		symTableroot->next == NULL;
	}
	SymTableNode* aux = symTableroot;
	while (aux->next != NULL) {
		aux = aux->next;
	}

	SymTableNode* symTableNode = (SymTableNode*)malloc(sizeof(SymTableNode));
	memset(symTableNode, 0, sizeof(SymTableNode));

	aux->next = symTableNode;

	symTableNode->symbolEntry = nodeToAdd;
	symTableNode->next = NULL;

	return symTableroot;
}