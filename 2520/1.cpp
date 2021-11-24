#include<iostream>
#include<stdlib.h>
#include<string.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2

using namespace std;

typedef int Status;
typedef char TElemType;
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
typedef int Status;

typedef struct BiTNode
{
    TElemType data;
    struct BiTNode* lchild, * rchild;
}BiTNode, * BiTree;
typedef BiTree SElemType;

typedef struct {
    SElemType* base;
    SElemType* top;
    int stacksize;
}SqStack;


Status InitStack(SqStack& s)
{
    s.base = (SElemType*)malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if (!s.base)
    {
        exit(OVERFLOW);
    }
    s.top = s.base;
    s.stacksize = STACKINCREMENT;
    return OK;
}
Status StackEmpty(SqStack& s)
{
    if (s.top == s.base)
        return TRUE;
    else return FALSE;
}

Status GetTop(SqStack& s, SElemType& e)
{
    if (s.top == s.base)
    {
        return ERROR;
    }
    e = *(--s.top);
    s.top++;
    return OK;
}

Status Push(SqStack& s, SElemType e)
{
    if (s.top - s.base >= s.stacksize)
    {
        s.base = (SElemType*)realloc(s.base, (s.stacksize + STACKINCREMENT) * sizeof(SElemType));
        if (!s.base)
            exit(OVERFLOW);
        s.top = s.base + s.stacksize;
        s.stacksize += STACKINCREMENT;
    }
    SElemType* p = s.top;
    *p = e;
    (s.top++);
    return OK;
}

Status Pop(SqStack& s, SElemType& e)
{
    if (s.top == s.base)
        return ERROR;
    e = *--s.top;
    return OK;
}


Status CreateBitTree(BiTree& T) {
    char ch;
    scanf("%c", &ch);
    if (ch == '#')
        T = NULL;
    else {
        if (!(T = (BiTNode*)malloc(sizeof(BiTNode))))
            exit(OVERFLOW);
        T->data = ch;
        CreateBitTree(T->lchild);
        CreateBitTree(T->rchild);
    }
    return OK;
}

Status CreateBitTree2(BiTree& T)
{
    BiTree p;
    struct kt {
        int le;
        int ri;
    }a[600];
    a[0].le = 0;
    a[0].ri = 0;
    SqStack Q;
    InitStack(Q);
    int i = 0;
    char ch[600];
    scanf("%s", &ch);
    T = (BiTree)malloc(sizeof(BiTNode));
    T->data = ch[0];
    Push(Q, T);
    int n = 1;
    while (ch[n] != '\0')
    {
        if (ch[n] == '#')
        {
            while (!StackEmpty(Q))
            {
                GetTop(Q, p);
                if (a[i].le == 0)
                {
                    p->lchild = NULL;
                    a[i].le = 1;
                    break;
                }
                else if (a[i].ri == 0)
                {
                    p->rchild = NULL;
                    a[i].ri = 1;
                    break;
                }
                else
                {
                    Pop(Q, p);
                    a[i].le = 0;
                    a[i].ri = 0;
                    i--;
                }
            }
        }
        else
        {
            BiTree m = (BiTree)malloc(sizeof(BiTNode));
            m->data = ch[n];
            while (!StackEmpty(Q))
            {
                GetTop(Q, p);
                if (a[i].le == 0)
                {
                    p->lchild = m;
                    a[i].le = 1;
                    break;
                }
                else if (a[i].ri == 0)
                {
                    p->rchild = m;
                    a[i].ri = 1;
                    break;
                }
                else
                {
                    Pop(Q, p);
                    a[i].le = 0;
                    a[i].ri = 0;
                    i--;
                }
            }
            Push(Q, m);
            i++;
            a[i].le = 0;
            a[i].ri = 0;
        }
        n++;
    }



    return 1;
}

SqStack S;
BiTree p;

Status Visit(TElemType e)
{
    cout << e;
    return 1;
}

Status InOrderTraverse(BiTree T, Status(*Visit)(TElemType e))
{
    InitStack(S);
    Push(S, T);
    while (!StackEmpty(S)) {
        while (GetTop(S, p) && p)
        {
            Push(S, p->lchild);
        }
        Pop(S, p);
        if (!StackEmpty(S)) {
            Pop(S, p);
            if (!Visit(p->data))
                return ERROR;
            Push(S, p->rchild);
        }
    }
    return OK;
}

Status PreOrderTraverse(BiTree T, Status(*Visit)(TElemType e))
{
    InitStack(S);
    Push(S, T);
    while (!StackEmpty(S)) {
        while (GetTop(S, p) && p)
        {
            Push(S, p->lchild);
            Visit(p->data);
        }
        Pop(S, p);
        if (!StackEmpty(S)) {
            Pop(S, p);
            Push(S, p->rchild);
        }
    }
    return OK;
}

Status PostOrderTraverse(BiTree T, Status(*Visit)(TElemType e))
{
    int top[600] = { 0 };
    int lef[600] = { 0 };
    int i = 0;
    InitStack(S);
    Push(S, T);
    while (!StackEmpty(S)) {
        while (GetTop(S, p) && p)
        {
            Push(S, p->lchild);
            if (lef[i] == 1)
            {
                i++;
                break;
            }
            lef[i] = 1;
            top[++i] = 0;

        }
        Pop(S, p);
        lef[i] = 0;
        i--;
        if (!StackEmpty(S)) {
            GetTop(S, p);
            if (p->rchild == NULL || top[i] == 1)
            {
                Pop(S, p);
                Visit(p->data);
                if (p->rchild != NULL && top[i] == 1)
                    top[i] = 0;
                lef[i] = 0;
                i--;
            }
            GetTop(S, p);
            if (p->rchild != NULL && top[i] == 0)
            {
                Push(S, p->rchild);
                top[i] = 1;
                i++;
            }
        }
    }
    return OK;
}

int depth = 0;
int leaves = 0;

void LayerTraverse(BiTree T)
{
    BiTree a[600];
    BiTree b[600];
    a[0] = T;
    a[1] = NULL;
    b[0] = T;
    b[1] = NULL;
    Visit(T->data);
    int num = 1;
    while (num != 0)
    {
        depth++;
        num = 0;
        for (int i = 0;a[i] != NULL;i++)
        {
            if (a[i]->lchild != NULL)
            {
                b[num++] = a[i]->lchild;
            }
            if (a[i]->rchild != NULL)
            {
                b[num++] = a[i]->rchild;
            }
            if (a[i]->lchild == NULL && a[i]->rchild == NULL)
                leaves++;
        }
        for (int i = 0;i < num;i++)
        {
            a[i] = b[i];
            Visit(a[i]->data);
        }
        a[num] = NULL;
    }

}
void fanzhuan(BiTree& T)
{
    BiTree a[600];
    BiTree b[600];
    a[0] = T;
    a[1] = NULL;
    b[0] = T;
    b[1] = NULL;
    int num = 1;
    while (num != 0)
    {
        num = 0;
        for (int i = 0;a[i] != NULL;i++)
        {
            BiTree m = a[i]->lchild;
            a[i]->lchild = a[i]->rchild;
            a[i]->rchild = m;
            if (a[i]->lchild != NULL)
            {
                b[num++] = a[i]->lchild;
            }
            if (a[i]->rchild != NULL)
            {
                b[num++] = a[i]->rchild;
            }
        }
        for (int i = 0;i < num;i++)
        {
            a[i] = b[i];
        }
        a[num] = NULL;
    }
}

int main()
{
    BiTree T;
    int kind = 0;
    printf("选择创建二叉树方式：0->递归创建  1->非递归i创建\n");
    scanf("%d", &kind);
    getchar();
    printf("创建二又树，按先序次序输入二又树中结点的值：\n");
    if (kind == 0)
        CreateBitTree(T);
    else
        CreateBitTree2(T);
    printf("先序遍历二叉树，结果是：\n");
    PreOrderTraverse(T, &Visit);
    printf("\n");
    printf("中序遍历二又树，结果是：\n");
    InOrderTraverse(T, &Visit);
    printf("\n");
    printf("后序遍历二叉树，结果是：\n");
    PostOrderTraverse(T, &Visit);
    printf("\n");
    printf("层次遍历二叉树，结果是：\n");
    LayerTraverse(T);
    printf("\n");
    printf("输出二叉树的叶子结点个数：%d\n", leaves);
    printf("输出二叉树的深度：%d\n", depth);
    printf("交换二叉树中所有结点的左右子树！\n");
    fanzhuan(T);
    printf("先序遍历二叉树，结果是：\n");
    PreOrderTraverse(T, &Visit);
    printf("\n");
    printf("中序遍历二又树，结果是：\n");
    InOrderTraverse(T, &Visit);
    printf("\n");
    printf("后序遍历二叉树，结果是：\n");
    PostOrderTraverse(T, &Visit);
    printf("\n");
    printf("层次遍历二叉树，结果是：\n");
    LayerTraverse(T);
    printf("\n");



}