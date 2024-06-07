#include "binary_trees.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Maximum number of digits in a number */
#define MAX_DIGITS 10

/* Structure for printing a binary tree */
typedef struct print_node_s
{
    int depth;
    int pos;
    char s[MAX_DIGITS];
} print_node_t;

/* Helper function to print a binary tree */
static int print_t(const binary_tree_t *tree, int is_left, int offset, int depth, print_node_t s[20][255]);

/**
 * binary_tree_print - Prints a binary tree
 * @tree: Pointer to the root node of the tree to print
 */
void binary_tree_print(const binary_tree_t *tree)
{
    print_node_t s[20][255];
    int i, j;

    if (!tree)
        return;

    for (i = 0; i < 20; i++)
    {
        for (j = 0; j < 255; j++)
        {
            s[i][j].depth = -1;
        }
    }

    print_t(tree, 0, 0, 0, s);

    for (i = 0; i < 20; i++)
    {
        for (j = 0; j < 255; j++)
        {
            if (s[i][j].depth == -1)
            {
                printf(" ");
            }
            else
            {
                printf("%s", s[i][j].s);
            }
        }
        printf("\n");
    }
}

/**
 * print_t - Recursively prints a binary tree
 * @tree: Pointer to the root node of the tree to print
 * @is_left: 1 if the node is a left child, 0 otherwise
 * @offset: The current horizontal offset in the print grid
 * @depth: The current depth of the tree
 * @s: The print grid
 *
 * Return: The width of the current subtree
 */
static int print_t(const binary_tree_t *tree, int is_left, int offset, int depth, print_node_t s[20][255])
{
    char b[MAX_DIGITS];
    int width, left, right, i;

    if (!tree)
        return 0;

    sprintf(b, "(%03d)", tree->n);
    width = strlen(b);

    left = print_t(tree->left, 1, offset, depth + 1, s);
    right = print_t(tree->right, 0, offset + left + width, depth + 1, s);

    for (i = 0; i < width; i++)
    {
        s[depth][offset + left + i].depth = depth;
        s[depth][offset + left + i].pos = offset + left + i;
        s[depth][offset + left + i].s[i] = b[i];
    }

    if (depth && is_left)
    {
        for (i = 0; i < width + right; i++)
        {
            s[depth - 1][offset + left + width / 2 + i].depth = depth - 1;
            s[depth - 1][offset + left + width / 2 + i].pos = offset + left + width / 2 + i;
            s[depth - 1][offset + left + width / 2 + i].s[i] = '-';
        }
        s[depth - 1][offset + left + width / 2].depth = depth - 1;
        s[depth - 1][offset + left + width / 2].pos = offset + left + width / 2;
        s[depth - 1][offset + left + width / 2].s[0] = '.';
    }
    else if (depth && !is_left)
    {
        for (i = 0; i < left + width; i++)
        {
            s[depth - 1][offset - width / 2 + i].depth = depth - 1;
            s[depth - 1][offset - width / 2 + i].pos = offset - width / 2 + i;
            s[depth - 1][offset - width / 2 + i].s[i] = '-';
        }
        s[depth - 1][offset - width / 2 + left].depth = depth - 1;
        s[depth - 1][offset - width / 2 + left].pos = offset - width / 2 + left;
        s[depth - 1][offset - width / 2 + left].s[0] = '.';
    }

    return left + width + right;
}

