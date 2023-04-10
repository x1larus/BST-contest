#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>

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

// 3 (cheating: require <vector> and <algorithm> libs)
void get_values(node *root, std::vector<int> *a)
{
    if (root)
    {
        get_values(root->left, a);
        a->push_back(root->value);
        get_values(root->right, a);
    }
}

bool isOneSwapAwayFromBST(node* root)
{
    std::vector<int> a;
    get_values(root, &a);
    int c = 0;
    auto sorted = a;
    std::sort(sorted.begin(), sorted.end());
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i] != sorted[i])
        {
            c++;
        }
    }

    return c == 2 ? true : false;
}
// OK

// 4
void replace_bt(node** root, int* val)
{
	if ((*root)->left)
		replace_bt(&(*root)->left, val);
	else
	{
		*val = (*root)->value;
		node* temp = (*root);
		*root = (*root)->right;
		free(temp);	
	}
}

node* delete_node(node* root)
{
	if (!root->left && !root->right)
	{
		free(root);
		return NULL;
	}
	if (root->left && !root->right)
	{
		node* temp = root->left;
		free(root);
		return temp;
	}
	if (!root->left && root->right)
	{
		node* temp = root->right;
		free(root);
		return temp;
	}
	if (root->left && root->right)
	{
		int a = 0;
		replace_bt(&root->right, &a);
		root->value = a;
		return root;
	}
}

node* DeleteOutsideRange(node* root, int begin, int end)
{
    if (root)
    {
        root->left = DeleteOutsideRange(root->left, begin, end);
        root->right = DeleteOutsideRange(root->right, begin, end);
        if (root->value < begin || root->value > end)
            root = delete_node(root);
    }
    return root;
}
// OK

// task 5
node* lowestCommonAncestor(node* root, node* elem1, node* elem2) 
{
    if (!root || root == elem1 || root == elem2) return root;
    node* left = lowestCommonAncestor(root->left, elem1, elem2);
    node* right = lowestCommonAncestor(root->right, elem1, elem2);
    return !left ? right : !right ? left : root;
}

int LeastCommonAncestor(node* root, node* elem1, node* elem2)
{
    return lowestCommonAncestor(root, elem1, elem2)->value;
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

    // task OK

    // task 4 OK
    //root = DeleteOutsideRange(root, 5, 15);
    printf("TASK 4: ");
    print(root);
    printf("\n");

    // task 5 OK
    printf("TASK 5: %d\n", LeastCommonAncestor(root, root->left->right, root->right->right));  

    return 0;
}
