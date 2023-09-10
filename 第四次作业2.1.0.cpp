#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <random>
#define MaxSize 100
typedef char ElemType;

typedef struct Node
{
    ElemType data;
    struct Node *next;
}LinkList;

typedef struct SeqStack{
	ElemType data[MaxSize];
	int top;
}SeqStack;
LinkList *initList(LinkList *L);
LinkList *createList();
int insertLinkList(LinkList *L, int pos, ElemType e);
int getLen(LinkList *L);
int isEmpty(LinkList *L);
void printLinkList(LinkList *L);
LinkList *initList(LinkList *L)
{
    L = (LinkList *) malloc(sizeof(LinkList));
    L->next = NULL;
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
        printf("%c",p->data);
        p = p->next;
        if(p==NULL)printf("\n");
    }
}    

void InitStack(SeqStack &S){
	S.top = -1;
}
 

int Push(SeqStack &S,ElemType x){
	if(S.top==MaxSize-1) 
		return 0;
	S.data[++S.top] = x; 
	return 1;
}
 

int Pop(SeqStack &S,ElemType &x){
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
		printf("%c",S.data[S.top-i]);
		if(i==S.top)printf("\n");
	}
	
	return 1;
}
LinkList *createList()
{
    int i;
    ElemType e;
    LinkList *L = initList(L), *r, *n;
    r = L;
    for(i = 0;i < 100;i ++)
    {
        scanf("%c", &e);
        if(e=='@'){return L;}
        n = (LinkList *) malloc(sizeof(LinkList));
        n->data = e;
        n->next = NULL;
        r->next = n;
        r = r->next;
    }
    return L;
}

int main(){
 	LinkList *A,*p;
 	SeqStack S;
 	initList(A);
 	InitStack(S);
 	A=createList();
 	p=A->next;	
	char c;
	while(p){
		Push(S,p->data);
		p=p->next;
		}
	p=A->next;
		printf("正读:");
		printLinkList(A);
			printf("反读:");
			PrintStack(S);
			
	for(int i=1;i<=getLen(A);i++){
		Pop(S,c);
			if(p->data!=c){printf("该字符序列不是为回文");return 0;}
				p=p->next;
	}
	printf("该字符序列是为回文");

}
 
