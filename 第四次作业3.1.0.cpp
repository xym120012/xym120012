#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <random>
#define MaxSize 100
typedef int ElemType;

typedef struct Node
{
    ElemType data;
    struct Node *next;
}LinkList;

typedef struct SeqStack{
	int data[MaxSize];
	int top;
}SeqStack;
LinkList *initList(LinkList *L);
LinkList *createList(int len);
int insertLinkList(LinkList *L, int pos, ElemType e);
int deleteLinkList(LinkList *L, int pos, ElemType *e);
void reverseLinkList(LinkList *L);
int seachLinkList(LinkList *L, ElemType e);
int getLen(LinkList *L);
int isEmpty(LinkList *L);
void printLinkList(LinkList *L);
int Pop(SeqStack &S,int &x);
int Push(SeqStack &S,int x);
void InitStack(SeqStack &S);
void InitStack(SeqStack &S);
LinkList *initList(LinkList *L)
{
    L = (LinkList *) malloc(sizeof(LinkList));
    L->next = NULL;
    return L;
}

LinkList *createList(int len)
{
    int i;
    ElemType e;
    LinkList *L = initList(L), *r, *n;
    r = L;
    for(i = 0;i < len;i ++)
    {
        scanf("%d", &e);
        n = (LinkList *) malloc(sizeof(LinkList));
        n->data = e;
        n->next = NULL;
        r->next = n;
        r = r->next;
    }
    return L;
}

int insertLinkList(LinkList *L, int pos, ElemType e)
{	
 
	  	
	  
    if(pos < 1 || pos > getLen(L)+1) return 0;
    LinkList *r = L, *n;
    n = (LinkList *) malloc(sizeof(LinkList));
    n->data = e;
    n->next = NULL;
    while(--pos > 0)
    {
        r = r->next;
    }
    n->next = r->next;
    r->next = n;
    return 1;
}

int deleteLinkList(LinkList *L, int pos, ElemType *e)
{
    if(pos < 1 || pos > getLen(L)) return 0;
    LinkList *r = L, *d;
    while(--pos > 0)
    {
        r = r->next;
    }
    d = r->next;
    *e = d->data;
    r->next = d->next;
    free(d);
    return 1;
}

int seachLinkList(LinkList *L, ElemType e)
{
    if(isEmpty(L)) return -1;
    int pos = 1;
    LinkList *r = L->next;
    while(r)
    {
        if(r->data == e) return pos;
        r = r->next;
        pos ++;
    }
    return -1;
}
int getLen(LinkList *L)
{
    if(L->next == NULL) return 0;
    int len = 0;
    LinkList *r = L->next;
    while(r)
    {
        r = r->next;
        len++;
    }
    return len;
}
int isEmpty(LinkList *L)
{
    return !L->next;
}
void printLinkList(LinkList *L)
{
	
    LinkList *p;
    p = L->next;
    while(p)
    {
        printf("%d ",p->data);
        p = p->next;
    }
}    

void InitStack(SeqStack &S){
	S.top = -1; //初始化栈顶指针
}
 

int Push(SeqStack &S,int x){
	if(S.top==MaxSize-1) 
		return 0;
	S.data[++S.top] = x; 
	return 1;
}

int Pop(SeqStack &S,int &x){
	if(S.top==-1)
		return 0;
	x = S.data[S.top--]; 
		return 1;
}
int PrintStack(SeqStack S){
	if(S.top==-1){
		printf("栈为空");
		return 0;}
	for(int i =0;i<=S.top;i++){
		printf("%d ",S.data[S.top-i]);
		if(i==S.top)printf("\n");
	}
	
	return 1;
}
void reverseLinkList(LinkList *L)
{
 	initList(L);
 	SeqStack S;
	InitStack(S);
    ElemType e;
    int len;
    len=getLen(L);
	for(int i =1;i<=len;i++){
		deleteLinkList(L,1,&e);
		Push(S,e);
	}
	for(int i =1;i<=len;i++){
		Pop(S,e);
		insertLinkList(L,i,e);
	}
}

int main(){
	LinkList *A;
	int m;
	printf("请输入链表长度:");
	scanf("%d",&m);
	printf("请输入链表数据:");
	A=createList(m);
 	reverseLinkList(A);
 	printf("逆置后链表中数据为:");
 	printLinkList(A);	
}
 
