#include<stdio.h>
#include <stdlib.h>
struct Tree;
typedef struct Tree *tree;
struct Tree
{
    int leaf;
    int size;
    int num[4];
    tree p[4];
    tree parent;
};
tree init()
{
    tree t = (tree)malloc(sizeof(struct Tree));
    t->size = 0;
    for (int i = 0; i < 3;i++)
        t->p[i] = NULL;
    t->parent = NULL;
    return t;
}
tree insert(tree t,int k)
{
    tree root = t;
    //find leaf
    while (t->leaf != 1)
    {
        if(t->size==2)
        {
            if (k < t->num[0])
                t = t->p[0];
            else if (k > t->num[0] && k < t->num[1])
                t = t->p[1];
            else
                t = t->p[2];
        }
        else
        {
            if (k < t->num[0])
                t = t->p[0];
            else
                t = t->p[1];
        }
    }
    //add node
    t->num[t->size] = k;
    t->size++;
    for (int i = 0; i < t->size-1;i++)
        for (int j = 0; j < t->size - 1 - i;j++)
            if (t->num[j] > t->num[j + 1])
            {
                int temp = t->num[j];
                t->num[j] = t->num[j + 1];
                t->num[j + 1] = temp;
            }
    if (t->size == 4)
    {
        tree m = init();
        m->leaf = 1;
        m->num[0] = t->num[2];
        m->num[1] = t->num[3];
        t->size = 2;
        m->size = 2;
        if (t->parent == NULL)
        {
            tree f = init();
            f->leaf = 0;
            f->p[0] = t;
            t->parent = f;
            root = f;
        }
        t->parent->num[t->parent->size] = m->num[0];
        t->parent->size++;
        t->parent->p[t->parent->size] = m;
        m->parent = t->parent;
        t = t->parent;
        for (int i = 0; i < t->size - 1;i++)
            for (int j = 0; j < t->size - 1 - i;j++)
            {
                if(t->num[j]>t->num[j+1])
                {
                    int temp = t->num[j];
                    t->num[j] = t->num[j + 1];
                    t->num[j + 1] = temp;
                    tree tt = t->p[j + 1];
                    t->p[j + 1] = t->p[j + 2];
                    t->p[j + 2] = tt;
                }
            }
        // control parent
        while (t->size == 3)
        {
            tree q = init();
            q->leaf = 0;
            q->num[0] = t->num[2];
            q->p[0] = t->p[2];
            t->p[2]->parent = q;
            q->p[1] = t->p[3];
            t->p[3]->parent = q;
            t->size = 1;
            q->size = 1;
            if (t->parent == NULL)
            {
                tree f = init();
                f->leaf = 0;
                f->p[0] = t;
                t->parent = f;
                root = f;
            }
            q->parent = t->parent;
            t->parent->num[t->parent->size] = t->num[1];
            t->parent->size++;
            t->parent->p[t->parent->size] = q;
            t = t->parent;
            for (int i = 0; i < t->size - 1;i++)
                for (int j = 0; j < t->size - 1 - i;j++)
                {
                    if(t->num[j]>t->num[j+1])
                    {
                        int temp = t->num[j];
                        t->num[j] = t->num[j + 1];
                        t->num[j + 1] = temp;
                        tree tt = t->p[j + 1];
                        t->p[j + 1] = t->p[j + 2];
                        t->p[j + 2] = tt;
                    }
                }
        }
    }
    return root;
}
int main()
{
    int n;
    scanf("%d", &n);
    int a[n];
    tree root=init();
    root->leaf = 1;
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
        int find = 0;
        for (int j = 0; j < i;j++)
        {
            if(a[j]==a[i])
            {
                find++;
                break;
            }
        }
        if(find==0)
        root = insert(root, a[i]);
        else
            printf("Key %d is duplicated\n", a[i]);
    }
    //
    tree squeue[10000];
    int start = 0, end = 0;
    squeue[end] = root;
    end++;
    if(root->leaf==0){
    squeue[end] = NULL;
    end++;}
    while(start<end)
    {
        if(squeue[start]==NULL)
        {
            printf("\n");
            start++;
            if(squeue[start+1]->leaf==0)
            {
                squeue[end] = NULL;
                end++;
            }
        }
        else{
            printf("[%d", squeue[start]->num[0]);
            for (int i = 1; i < squeue[start]->size; i++)
            {
                printf(",%d", squeue[start]->num[i]);
            }
            printf("]");
            if (squeue[start]->leaf == 0)
            {
                for (int i = 0; i <= squeue[start]->size; i++)
                {
                    squeue[end] = squeue[start]->p[i];
                    end++;
                }
            }
            start++;
        }
    }
}