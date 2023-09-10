#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <random>
#include <string.h>
typedef char ElemType;

typedef struct Node
{	struct Node *prior;
	int no;
	int pos;
    ElemType data[20];
    struct Node *next;
}LinkList;

LinkList *initList(LinkList *L)
{
    L = (LinkList *) malloc(sizeof(LinkList));
    L->next = NULL;
    return L;
}

int randRange(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

int main(){
	LinkList *A,*r,*p;
	FILE *fp;
	A=initList(A);
	fp=fopen("C:\\Users\\XYM\\Desktop\\input.ifo","r+");
	r=A;
	
	/*	for(int i=1;i<=30;i++){	
		fprintf(fp,"%d,%c\n",randRange(1,30),randRange(65,90));}*/
		
		/*	int num[30]={0};
			
					for(int i=0;i<30;i++){
						num[i]=randRange(1,30);
							for(int j=0;j<i;j++){
								if(num[j]==num[i]){
									num[i]=randRange(1,30);
									j=-1;
								}
							}
						}
			
				for(int i=0;i<30;i++){	
					fprintf(fp,"%d,%c\n",num[i],randRange(65,90));}		*/
		
		
		
	rewind(fp);
	for(int i=1;i<=30;i++){
		LinkList *n;
		int no;
		ElemType data[20];
		  n = (LinkList *) malloc(sizeof(LinkList));
		  fscanf(fp,"%d,%s\n",&no,data);
		  n->no=no;
		  strcpy(n->data,data);
		  n->next=NULL;
		  n->prior=r;
		  n->pos=i;
		  r->next=n;
		  r=r->next;
		  
		  if(i==30){
		  	n->next=A->next;
		  	A->next->prior=n;
		  }
	}
	
	r=A->next;
	for(int i=0;i<30;i++){
		printf("%d,%s\n",r->no,r->data);
		r=r->next;
	}		
	r=A->next;
	for(int i=1;i<=30;i++){
		if(r->no==11){printf("编号为11的结点初始位置在%d\n",r->pos);break;}
		r=r->next;}
		
for(int j=30;j>1;j--){			
	for(int i=1;i<=18;i++){
		if(i==18){
		printf("第%d次删除编号:%d,初始位置:%d\n", 31-j, r->no, r->pos);
		p = r; 
		r = r->next; 
		p->prior->next = p->next; 
		p->next->prior = p->prior; 
		free(p);
		}
		else{r=r->next;}
	}
	if(j==2) printf("最后一位的编号:%d,初始位置:%d",r->no,r->pos);}
	free(A);
	return 0;
	
}
