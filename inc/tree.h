
#ifndef TREE_H_
#define TREE_H_

#include "line.h"

struct TreeNode
{
    TreeNode* left;
    TreeNode* right;
    Line* line;
    int count;
};

struct Tree
{
    TreeNode* root;
};

bool AddItemToTree(Tree* tree, Line* line);

void FreeTreeMemory(TreeNode* node);

#endif