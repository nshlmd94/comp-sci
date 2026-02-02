#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

typedef struct node
{
    char operator;      // '+', '-', '*', '/', or '\0' if leaf
    int value;          // Only used if this is a leaf node
    struct node *left;  // Left child
    struct node *right; // Right child
} node;

node *createLeaf(int value);
node *createOperation(char operator, node *left, node *right);
int evaluate(node *tree);
void freeTree(node *tree);

int main(void)
{
    node *eight = createLeaf(8);
    node *three = createLeaf(3);
    node *left = createOperation('-', eight, three);

    node *two = createLeaf(2);
    node *four = createLeaf(4);
    node *right = createOperation('+', two, four);

    node *root = createOperation('*', left, right);

    printf("Test Result: %d\n", evaluate(root)); // Should print 30
    freeTree(root);
}

node *createLeaf(int value)
{
    node *leaf = malloc(sizeof(node));

    if (leaf != NULL)
    {
        leaf->operator = '\0';
        leaf->value = 0;
        leaf->left = NULL;
        leaf->right = NULL;
    }

    leaf->value = value;

    return leaf;
}

node *createOperation(char operator, node *left, node *right)
{
    node *operation = malloc(sizeof(node));

    if (operation != NULL)
    {
        operation->operator = '\0';
        operation->value = 0;
        operation->left = NULL;
        operation->right = NULL;
    }

    if (operator == '+' || operator == '-' || operator == '*' || operator == '/')
    {
        operation->operator = operator;
        operation->value = 0;
        operation->left = left;
        operation->right = right;
    }

    return operation;
}

int evaluate(node *tree)
{
    int result = 0;

    if (tree->left == NULL && tree->right == NULL)
    {
        return tree->value;
    }

    int leftResult = evaluate(tree->left);
    int rightResult = evaluate(tree->right);

    if (tree->operator == '+')
    {
        tree->value = leftResult + rightResult;
    }
    else if (tree->operator == '-')
    {
        tree->value = leftResult - rightResult;
    }
    else if (tree->operator == '*')
    {
        tree->value = leftResult * rightResult;
    }
    else if (tree->operator == '/')
    {
        tree->value = leftResult / rightResult;
    }
    else
    {
        return 1;
    }

    return tree->value;
}

void freeTree(node *tree)
{
    if (tree == NULL)
    {
        return;
    }

    freeTree(tree->left);
    freeTree(tree->right);

    free(tree);
}
