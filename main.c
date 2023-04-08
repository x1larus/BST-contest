#include <stdio.h>
#include <stdlib.h>

// --------------- base realization ---------------

typedef struct node
{
    int value;
    struct node *left;
    struct node *right;
} node;

void add(node** root, int value)
{
    if (!*root)
    {
        *root = (node*)malloc(sizeof(node));
        (*root)->value = value;
        (*root)->left = NULL;
        (*root)->right = NULL;
        return;
    }
    if (value < (*root)->value)
        add(&(*root)->left, value);
    else
        add(&(*root)->right, value);
}

void print(node* root)
{
    if (root)
    {
        print(root->left);
        printf("%d ", root->value);
        print(root->right);
    }
}

void print_graphic(node* root, int level)
{
    // read this scheme left to right
	if (root)
	{
		print_graphic(root->right, level + 1);
		for (int i = 0; i < level; ++i)
			printf("\t");
		printf("%d\n", root->value);
		print_graphic(root->left, level + 1);
	}
}

// ------------- base realization end -------------

// --------------- tasks ---------------

int FindKthLargestSmallest(node* root, int k)
{
    
}

// ------------- tasks end -------------

int main()
{
    node *root;
    int values[] = {5, 3, 7, 1, 6, 2, 9, 4, 8, 0};
    for (int i = 0; i < 10; i++)
    {
        add(&root, values[i]);
    }
    print(root);
    printf("\n");
    print_graphic(root, 0);
    return 0;
}
