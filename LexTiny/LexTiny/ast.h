#ifndef __AST_H
#define __AST_H

#define MAX_NODE_TYPE 50
#define MAX_EXTRA_DATA 50




typedef struct node {
	char type[MAX_NODE_TYPE];
	int numLinks;
	char extraData[MAX_EXTRA_DATA];
	struct node** links;
}Node;





Node* createType(const char* typeName);
Node* createArrayDeclaration(Node* type, const char* varName, int arraySize);
Node* createProgramNode(Node* declaration);
Node* createDeclarationNode(Node* varFunDeclaration);
Node* createFunctionDeclarationNode(Node* typeSpecifier, const char* functionName, Node* paramsList, Node* compoundStatement);
Node* createIntVarDeclaration(Node* type, const char* varName, int value);
Node* createCharVarDeclaration(Node* type, const char* varName, char value);
Node* createBlock(Node* localDeclList, Node* instructionsList);
Node* createIfStatement(Node* expression, Node* thenStatement, Node* elseStatement);
Node* createWhileStatement(Node* expression, Node* statement);
Node* createAssignStatement(Node* leftExpression, Node* rightExpression);
Node* createReturnStatement(Node* expression);
Node* createFunctionCall(const char* funcName, Node* parameters);
Node* createWriteNode(Node* expression);
Node* createReadNode(Node* expression);
Node* createExpArray(Node* lexpression, Node* expression);
Node* createBinopExp(Node* lexpression, Node* rexpression);
Node* createUnopExp(Node* expression);
Node* createParameterExp(Node* expression);
Node* createNumberNode(int number);
Node* createQCharNode(const char* qchar);
Node* createSizeArrayExpression(Node* expression);
Node* createVarNameNode(const char* name);

Node* createDefaultNode(const char* nodeName, unsigned int linksCount);
Node* resizeNodeLinks(Node* nodeToResize, unsigned int newSize);
Node* createListNode(const char* listName, Node* firstLink);
void addLinkToList(Node* listNode, Node* linkToAdd);
void printAst(Node* ast, int level);
#endif
