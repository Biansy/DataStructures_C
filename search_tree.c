#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct tree_node* position;
typedef struct tree_node* search_tree;

struct tree_node
{
    int element;
    search_tree left;
    search_tree right;
};

search_tree Make_Empty(search_tree t)
{
    if (t != NULL)
    {
        Make_Empty(t->left);
        Make_Empty(t->right);
        free(t);
    }
    return NULL;
}

position Find(search_tree t, int x)
{
    if (t == NULL)
        return NULL;
    
    if (x < t->element)
        return Find(t->left, x);
    else if (x > t->element)
        return Find(t->right, x);
    else
        return t;
}

position Find_Min(search_tree t)
{
    if (t == NULL)
        return NULL;
    else if (t->left == NULL)
        return t;
    else
        return Find_Min(t->left);    
}

position Find_Max(search_tree t)
{
    if (t != NULL)
    {
        while (t->right != NULL)
        {
            t = t->right;
        }
    }
    return t;
}

search_tree Inset(search_tree t, int x)
{
    if (t == NULL)
    {
        t = malloc(sizeof(struct tree_node));
        if (t == NULL)
            printf("out of space\n");
        else
        {
            t->element = x;
            t->left = NULL;
            t->right = NULL;
        }
    }
    else if (x < t->element)
        t->left = Inset(t->left, x);
    else if (x > t->element)
        t->right = Inset(t->right, x);
    else {}  //already,do nothing

    return t;
}

search_tree Delete(search_tree t, int x)
{
    position temp;

    if (t == NULL)
        printf("element not found\n");
    else if (x < t->element)
        t->left = Delete(t->left, x);
    else if (x > t->element)
        t->right = Delete(t->right, x);
    else if (t->left && t->right)   //有两个子节点
    {
        temp = Find_Min(t->right);
        t->element = temp->element;
        t->right = Delete(t->right, x);
    }
    else    //有一或两个子节点
    {
        temp = t;
        if (t->left == NULL)
            t = t->right;
        else
            t = t->left;
        free(temp);
    }
    return t;
}
    
int main()
{
    int arr[8] = {2,6,4,8,9,5,1,3};
    search_tree tree = NULL;

    for (int i = 0; i < 8; i ++)
    {
        tree = Inset(tree, arr[i]);
    }

    printf("Min:%d\n", Find_Min(tree)->element);
    printf("Max:%d\n", Find_Max(tree)->element);

    search_tree t = Find(tree, 7);
    if (t != NULL)
        printf("7 is finded\n");
    else
        printf("7 is not finded\n");

    t = Find(tree, 8);
    if (t != NULL)
        printf("8 is finded\n");
    else
        printf("8 is not finded\n");

    printf("delete 8\n");
    tree = Delete(tree, 8);

    t = Find(tree, 8);
    if (t != NULL)
        printf("8 is finded\n");
    else
        printf("8 is not finded\n");

    return 0;
}