#include <stdio.h>
#define MAXSIZE 100

typedef int ElemType;
typedef struct SeqStack{
	ElemType data[MAXSIZE];
	int top[2];
}SeqStack;

int Pop(SeqStack &S,int i,int &x);
int Push(SeqStack &S,int i,int x);
void InitStack(SeqStack &S);
int Top(SeqStack &S,int i);

void InitStack(SeqStack &S){
	S.top[0]=-1;
	S.top[1]=MAXSIZE;
		}

int Push(SeqStack &S,int i,int x){
	if(S.top[1]-1==S.top[0]) return 0;
	else{
	if(i==0){
		S.data[++S.top[0]]=x;
		return 1;
			}
	if(i==1){
		S.data[--S.top[1]]=x;
		return 1;
			}
		}
}		
int Pop(SeqStack &S,int i,int &x){
	if(i==0){
			if(S.top[0]==-1){return 0;}
			x=S.data[S.top[0]--];
			return 1;
				}
	if(i==1){
			if(S.top[1]==MAXSIZE){return 0;}
			x=S.data[S.top[1]++];
			return 1;
				}
}
int Top(SeqStack &S,int i){
	if(i==0&&S.top[0]!=-1){
		return S.data[S.top[0]];
	}
	if(i==1&&S.top[1]!=MAXSIZE){
		return S.data[S.top[1]];
		}
		else printf("ERROR");
		return 0;
}
int main() {
    SeqStack s;
    InitStack(s);
    int x;  
    
	Push(s,0,1);
	Push(s,1,2);
	Push(s,0,3);
	Push(s,1,4);
	Push(s,0,5);
	Push(s,1,6);
	
	
	Pop(s,0,x);
	printf("%d\n",x);//输出5
	Pop(s,1,x);
	printf("%d\n",x);//输出6
	
	printf("%d\n",Top(s,0));//输出3
	printf("%d\n",Top(s,1));//输出4
	
    return 0;
}
