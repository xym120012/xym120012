#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef char* ElemType; // 使用指针代替数组

typedef struct Node
{
    struct Node *prior;
    int no;
    int pos;
    ElemType data;
    struct Node *next;
} LinkList;

LinkList *initList(LinkList *L)
{
    L = (LinkList *) malloc(sizeof(LinkList));
    L->data = NULL; // 初始化头结点数据为空
    L->next = L;
    L->prior = L;
    return L;
}

int randRange(int min, int max)
{
    return rand() % (max - min + 1) + min;
}


int main()
{
    LinkList *A, *r, *p;
    FILE *fp;
    A = initList(A);
    fp = fopen("input.ifo", "w+");
    r = A;
    
    	int num[30]={0};	
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
				fprintf(fp,"%d,xie\n",num[i]);}	
	rewind(fp);										//建立随机数	
    
    for (int i = 1; i <= 30; i++)
    {
        LinkList *n;
        int no;
        ElemType data = (ElemType) malloc(sizeof(char) * 20); // 分配存储空间
        n = (LinkList *) malloc(sizeof(LinkList));
        fscanf(fp, "%d,%s\n", &no, data);
        n->no = no;
        n->data = data;
        n->next = A;
        n->prior = r;
        n->pos = i;
        r->next = n;
        A->prior = n;
        r = r->next;
   
       if(i==30){n->next=A->next;A->next->prior=n;}                          //头尾相连，建立循环链表
    }
	    fclose(fp);
    r = A->next;
    for (int i = 0; i < 30; i++)
    {
        printf("%d,%s\n", r->no, r->data);
        r = r->next;
    }
    
    r = A->next;
    while (r->no != 11) // 寻找第一个出列的结点
    {
        r = r->next;
    }

    for (int j = 30; j > 1; j--)
    {
        for (int i = 1; i <= 18; i++)
        {
            if (i == 18)
            {
                printf("第%d次删除编号:%d,初始位置:%d,链表长度为%d\n", 31-j, r->no, r->pos, j-1);
                p = r;
                r = r->next;
                p->prior->next = p->next;
                p->next->prior = p->prior;
                free(p->data); // 释放存储空间
                free(p);
            }
            else
            {
                r = r->next;
            }
        }
    }

    printf("最后一位的编号:%d,初始位置:%d\n", r->next->no, r->next->pos); // 输出最后的结点
	free(A);

	
	return 0;

}
