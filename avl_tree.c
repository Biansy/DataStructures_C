#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct avl_node* position;
typedef struct avl_node* avl_tree;

struct avl_node
{
    int element;
    avl_tree left;
    avl_tree right;
    int height;
};

static void In_Order(avl_tree t)
{
    if (t != NULL)
    {
        In_Order(t->left);
        printf("%d ", t->element);
        In_Order(t->right);
    }
}

static int Max(int a, int b)
{
    if (a >= b)
        return a;
    else 
        return b;
}

static int Height(position p)
{
    if (p == NULL)
        return -1;
    else
        return p->height;
}

static position Single_Rotate_With_Left(position k2)
{
    position k1;
    
    k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;

    k2->height = Max(Height(k2->left), Height(k2->right)) + 1;
    k1->height = Max(Height(k1->left), Height(k1->right)) + 1;

    return k1;
}

static position Single_Rotate_With_Right(position k1)
{
    position k2;

    k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;

    k1->height = Max(Height(k1->left), Height(k1->right)) + 1;
    k2->height = Max(Height(k2->left), Height(k2->right)) + 1;
    
    return k2;
}

static position Double_Rotate_With_Left(position k3)
{
    k3->left = Single_Rotate_With_Right(k3->left);
    return Single_Rotate_With_Left(k3);
}

static position Double_Rotate_With_Right(position k1)
{
    k1->right = Single_Rotate_With_Left(k1->right);
    return Single_Rotate_With_Right(k1);
}

avl_tree Inset(avl_tree t, int x)
{
    if (t == NULL)
    {
        t = malloc(sizeof(struct avl_node));
        if (t == NULL)
            printf("out of space\n");
        else
        {
            t->element = x;
            t->left = NULL;
            t->right = NULL;
            t->height = 0;
        }
    }
    else if (x < t->element) 
    {
        t->left = Inset(t->left, x);
        //相对于查找树,新增以下代码,是谓旋转
        if (Height(t->left) - Height(t->right) == 2)    //左右子树高度相差2,需要旋转平衡
        {
            if (x < t->left->element)   //x比左子节点小,说明x插在了左子树左边,那么只需要单旋转
            {
                printf("Single_Rotate_With_Left\n");
                t = Single_Rotate_With_Left(t);
            }
            else                        //x比左子节点大,说明x插在了左子树右边,那么需要双旋转
            {
                printf("Double_Rotate_With_Left\n");    
                t = Double_Rotate_With_Left(t);
            }
        }
    }
    else if (x > t->element)
    {
        t->right = Inset(t->right, x);
        //相对于查找树,新增以下代码,是谓旋转
        if (Height(t->right) - Height(t->left) == 2)
        {
            if (x > t->right->element)
            {
                printf("Single_Rotate_With_Right\n");
                t = Single_Rotate_With_Right(t);
            }
            else
            {
                printf("Double_Rotate_With_Right\n");
                t = Double_Rotate_With_Right(t);  
            }
        }
    }

    t->height = Max(Height(t->left), Height(t->right)) + 1;
    return t;
}

int main()
{
    int arr[8] = {6,3,4,8,9,5,2,1};
    avl_tree tree = NULL;

    for (int i = 0; i < 8; i ++)
    {
        tree = Inset(tree, arr[i]);
    }

    In_Order(tree);
    return 0;
}