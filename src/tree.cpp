#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "..\inc\tree.h"

static bool AddNode(TreeNode* node, Line* line);

bool AddItemToTree(Tree* tree, Line* line)
{
    if (tree->root == nullptr)
    {
        tree->root = (TreeNode*)calloc(1, sizeof(TreeNode));
        
        if (tree->root == nullptr)
        {
            puts("Ошибка выделения памяти");
            FreeTreeMemory(tree->root);
            tree->root = nullptr;
            return false;
        }

        tree->root->count = 1;
        tree->root->line  = line;
        tree->root->left  = nullptr;
        tree->root->right = nullptr;
    }
    else
    {
        bool res = AddNode(tree->root, line);

        if (!res)
        {
            FreeTreeMemory(tree->root);
            tree->root = nullptr;
        }

        return res;
    }

    return true;
}

static bool AddNode(TreeNode* node, Line* line)
{
    int compareResult = CompareLines(line, node->line);
    if (compareResult == 0)
    {
        node->count++;
    }
    else if (compareResult < 0)
    {
        if (node->left == nullptr)
        {
            node->left = (TreeNode*)calloc(1, sizeof(TreeNode));

            if (node->left == nullptr)
            {
                puts("Ошибка выделения памяти");
                return false;
            }

            node->left->count = 1;
            node->left->line  = line;
            node->left->left  = nullptr;
            node->left->right = nullptr;
        }
        else
            return AddNode(node->left, line);
    }
    else
    {
        if (node->right == nullptr)
        {
            node->right = (TreeNode*)calloc(1, sizeof(TreeNode));
            
            if (node->right == nullptr)
            {
                puts("Ошибка выделения памяти");
                return false;
            }

            node->right->count = 1;
            node->right->line  = line;
            node->right->left  = nullptr;
            node->right->right = nullptr;
        }
        else
            return AddNode(node->right, line);
    }
    return true;
}

void FreeTreeMemory(TreeNode* node)
{
    if (node->left == nullptr && node->right == nullptr)
    {
        FreeLineMemory(node->line);
        free(node);
    }
    else
    {
        if (node->left)
            FreeTreeMemory(node->left);

        if (node->right)
            FreeTreeMemory(node->right);

        FreeLineMemory(node->line);
        free(node);
    }
}