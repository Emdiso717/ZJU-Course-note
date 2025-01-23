#include<stdio.h>
#include <stdlib.h>

struct Tree;
typedef struct Tree *tree;
struct Tree
{
    tree right;
    tree left;
    int num;
    int height;
};

int reheight(tree t)
{
    if (t == NULL)
        return -1;
    else
        return t->height;
}

void newheight(tree t)
{
    if(reheight(t->left)>=reheight(t->right))
        t->height = reheight(t->left) + 1;
    else
        t->height = reheight(t->right) + 1;
}

tree roationleft(tree t)
{
    tree temp = t->right;
    t->right = temp->left;
    temp->left = t;
    newheight(t);
    newheight(temp);
    return temp;
}
tree roationright(tree t)
{
    tree temp = t->left;
    t->left = temp->right;
    temp->right = t;
    newheight(t);
    newheight(temp);
    return temp;
}
tree insert(int k,tree t)
{
    if (t == NULL)
    {
        t = (tree)malloc(sizeof(struct Tree));
        t->left = NULL;
        t->right = NULL;
        t->num = k;
        t->height = 0;
    }
    else
    {
        if (k < t->num)
        {
            t->left = insert(k, t->left);
            if (reheight(t->left) - reheight(t->right) == 2)
            {
                if (k < t->left->num)
                    t = roationright(t);
                else
                {
                    t->left = roationleft(t->left);
                    newheight(t);
                    t = roationright(t);
                }
            }
        }
        else
        {
            t->right = insert(k, t->right);
            if (reheight(t->right) - reheight(t->left) == 2)
            {
                if (k > t->right->num)
                    t = roationleft(t);
                else
                {
                    t->right = roationright(t->right);
                    newheight(t);
                    t = roationleft(t);
                }
            }
        }
    }
    newheight(t);
    return t;
}

int main(){
    int n;
    scanf("%d", &n);
    int k;
    tree root = NULL;
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &k);
        root = insert(k, root);
    }
    printf("%d", root->num);
}