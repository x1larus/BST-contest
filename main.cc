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

// 1
void getKthSmallest(node *root, int *k, int *res)
{
    if (root)
    {
        getKthSmallest(root->left, k, res);
        (*k)--;
        if (*k == 0)
            *res = root->value;
        getKthSmallest(root->right, k, res);
    };
}

void getKthLargest(node *root, int *k, int *res)
{
    if (root)
    {
        getKthLargest(root->right, k, res);
        (*k)--;
        if (*k == 0)
            *res = root->value;
        getKthLargest(root->left, k, res);
    };
} 

int FindKthLargestSmallest(node* root, int k)
{
    int res;
    if (k > 0)
        getKthLargest(root, &k, &res);
    else
    {
        k = -k;
        getKthSmallest(root, &k, &res);
    }
    return res;
}
// OK

// 2
void findFloorCeiling(node* root, int e, int& floor, int& ceiling)
{
    if (!root)
        return;
    
    if (root->value == e)
    {
        floor = ceiling = root->value;
    }
    else if (e < root->value)
    {
        ceiling = root->value;
        findFloorCeiling(root->left, e, floor, ceiling);
    }
    else 
    {
        floor = root->value;
        findFloorCeiling(root->right, e, floor, ceiling);
    }
}
// OK

// ------------- tasks end -------------

int main()
{
    node *root;
    int values[] = {10, 4, 14, 8, 0, 2, 20, 12};
    for (int i = 0; i < 8; i++)
    {
        add(&root, values[i]);
    }
    print(root);
    printf("\n------------------------------------\n");
    print_graphic(root, 0);
    printf("------------------------------------\n");
    // task 1 OK
    printf("TASK 1: %d\n", FindKthLargestSmallest(root, -2));

    // task 2 OK
    int floor, ceiling;
    findFloorCeiling(root, 3, floor, ceiling);
    printf("TASK 2: %d %d\n", floor, ceiling);

    
    return 0;
}
