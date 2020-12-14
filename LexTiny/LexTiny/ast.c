#include "ast.h"
#include <malloc.h>
#include <string.h>
#include <stdio.h>

Node* createDefaultNode(const char* nodeName, unsigned int linksCount)
{
	Node* retNode = (Node*)malloc(sizeof(Node));
	if (retNode)
	{
		memset(retNode, 0, sizeof(Node));
		if (nodeName)
		{
			strcpy(retNode->type, nodeName);
		}
		
		retNode->numLinks = linksCount;
		if (linksCount > 0)
		{
			retNode->links = (Node**)malloc(linksCount * sizeof(Node*));
		}
	}
	return retNode;
}

Node* resizeNodeLinks(Node* nodeToResize, unsigned int newSize)
{
	if (nodeToResize->numLinks == 0)
	{
		nodeToResize->links = (Node**)malloc(newSize * sizeof(Node*));
	}
	else
	{
		nodeToResize->links = (Node**)realloc(nodeToResize->links, newSize * sizeof(Node*));
	}
	nodeToResize->numLinks = newSize;
	return nodeToResize;
}

Node* createListNode(const char* listName, Node* firstLink)
{
	Node* retNode = createDefaultNode(listName, 1);
	retNode->links[0] = firstLink;
	return retNode;
}

void addLinkToList(Node* listNode, Node* linkToAdd)
{
	unsigned int numLinks = listNode->numLinks;
	resizeNodeLinks(listNode, numLinks + 1);
	listNode->links[numLinks] = linkToAdd;
}

Node* createProgramNode(Node* declaration)
{
	Node* retNode = createDefaultNode("Program", 1);
	if (retNode)
	{
		retNode->links[0] = declaration;
	}

	return retNode;

}

Node* createDeclarationNode(Node* varFunDeclaration)
{
	Node* retNode = createDefaultNode("Declaration", 1);
	if (retNode)
	{
		retNode->links[0] = varFunDeclaration;
	}
	return retNode;
}

Node* createFunctionDeclarationNode(Node* typeSpecifier, const char* functionName, Node* paramsList, Node* block)
{

	Node* retNode = createDefaultNode("FunctionDefinition", 3);

	if (retNode)
	{
		retNode->links[0] = typeSpecifier;
		retNode->links[1] = paramsList;
		retNode->links[2] = block;
		if (functionName)
			strcpy(retNode->extraData, functionName);
	}

	return retNode;
}



Node* createIntVarDeclaration(Node* type, const char* varName, int value)
{
	Node* retNode = createDefaultNode("VariableDeclaration", 2);

	if (retNode)
	{
		retNode->links[0] = type;
		if (varName)
			sprintf(retNode->extraData, "%s", varName);
		retNode->links[1] = createDefaultNode("IntValue", 0);
		sprintf(retNode->links[1]->extraData, "%d", value);
	}

	return retNode;

}

Node* createCharVarDeclaration(Node* type, const char* varName, char value)
{
	Node* retNode = createDefaultNode("VariableDeclaration", 2);
	//printf("%c", value); // de rezolvat, imi ia random char in loc sa ia charul citit din fisier
	if (retNode)
	{
		retNode->links[0] = type;
		if (varName)
			sprintf(retNode->extraData, "%s", varName);
		retNode->links[1] = createDefaultNode("CharValue", 0);
		sprintf(retNode->links[1]->extraData, "%c", value);
	}

	return retNode;

}

Node* createType(const char* typeName)
{
	Node* retVal = createDefaultNode("Type", 0);
	if (typeName)
		sprintf(retVal->extraData, "%s", typeName);
	return retVal;
}

Node* createArrayDeclaration(Node* type, const char* varName, int arraySize)
{
	Node* retNode = createDefaultNode("VariableDeclaration", 2);

	if (retNode)
	{
		retNode->links[0] = type;
		if (varName)
			sprintf(retNode->extraData, "%s", varName);
		retNode->links[1] = createDefaultNode("Array", 0);
		sprintf(retNode->links[1]->extraData, "%d", arraySize);
	}

	return retNode;
}

Node* createBlock(Node* localDeclList, Node* instructionsList)
{
	Node* retNode = createDefaultNode("Block", 2);
	retNode->links[0] = localDeclList;
	retNode->links[1] = instructionsList;
	return retNode;
}

Node* createIfStatement(Node* expression, Node* thenStatement, Node* elseStatement)
{

	Node* retNode = createDefaultNode("IfStatement", 3);
	retNode->links[0] = expression;
	retNode->links[1] = thenStatement;
	retNode->links[2] = elseStatement;
	
	return retNode;
}

Node* createWhileStatement(Node* expression, Node* statement)
{

	Node* retNode = createDefaultNode("WhileStatement", 2);
	retNode->links[0] = expression;
	retNode->links[1] = statement;
	
	return retNode;
}

Node* createAssignStatement(Node* leftExpression, Node* rightExpression)
{

	Node* retNode = createDefaultNode("AssignStatement", 2);
	retNode->links[0] = leftExpression;
	retNode->links[1] = rightExpression;

	return retNode;
}

Node* createReturnStatement(Node* expression)
{

	Node* retNode = createDefaultNode("ReturnStatement", 1);
	retNode->links[0] = expression;

	return retNode;
}

Node* createFunctionCall(const char* funcName, Node* parameters)
{

	Node* retNode = createDefaultNode("FunctionCall", 1);

	retNode->links[0] = parameters;

	if (funcName)
		sprintf(retNode->extraData, "%s", funcName);

	return retNode;
}

Node* createWriteNode(Node* expression)
{

	Node* retNode = createDefaultNode("WriteNode", 1);
	retNode->links[0] = expression;

	return retNode;
}

Node* createReadNode(Node* expression)
{

	Node* retNode = createDefaultNode("ReadNode", 1);
	retNode->links[0] = expression;

	return retNode;
}

Node* createExpArray(Node* lexpression, Node* expression)
{
	Node* retNode = createDefaultNode("ExpressionArray", 2);
	retNode->links[0] = lexpression;
	retNode->links[1] = expression;
	return retNode;
}

Node* createBinopExp(Node* lexpression, Node* rexpression)
{
	Node* retNode = createDefaultNode("BinopExpression", 2);
	retNode->links[0] = lexpression;
	retNode->links[1] = rexpression;

	return retNode;
}

Node* createUnopExp(Node* expression)
{
	Node* retNode = createDefaultNode("UnopExpression", 1);
	retNode->links[0] = expression;
	return retNode;
}

Node* createParameterExp(Node* expression)
{
	Node* retNode = createDefaultNode("ParamExpression", 1);
	retNode->links[0] = expression;
	return retNode;
}

Node* createQCharNode(const char* qchar)
{
	Node* retNode = createDefaultNode("QCharNode", 0);
	sprintf(retNode->extraData, "%s", qchar);
	return retNode;
}

Node* createNumberNode(int number)
{
	Node* retNode = createDefaultNode("NumberNode", 0);
		sprintf(retNode->extraData, "%d", number);
	return retNode;
}

Node* createVarNameNode(const char* name)
{
	Node* retNode = createDefaultNode("VarNameNode", 0);
	sprintf(retNode->extraData, "%s", name);
	return retNode;
}

Node* createSizeArrayExpression(Node* expression)
{
	Node* retNode = createDefaultNode("SizeArrayExpression", 1);
	retNode->links[0] = expression;
	return retNode;
}



void printAst(Node* ast, int level)
{
	int idx = 0;
	if (ast)
	{
		for (idx = 0; idx < level; idx++)
		{
			printf(" ");
		}
		if (ast->type)
		{
			printf("%s ", ast->type);
		}
		if (ast->numLinks)
		{
			printf(" - %d - %s\n", ast->numLinks, ast->extraData);
		}
		else
		{
			printf(" - %s\n", ast->extraData);
		}
		for (idx = 0; idx < ast->numLinks; idx++)
		{

			printAst(ast->links[idx], level + 1);
		}
	}
}
