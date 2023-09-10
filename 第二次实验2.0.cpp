#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef char* ElemType; // ʹ��ָ���������

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
    L->data = NULL; // ��ʼ��ͷ�������Ϊ��
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
	rewind(fp);										//���������	
    
    for (int i = 1; i <= 30; i++)
    {
        LinkList *n;
        int no;
        ElemType data = (ElemType) malloc(sizeof(char) * 20); // ����洢�ռ�
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
   
       if(i==30){n->next=A->next;A->next->prior=n;}                          //ͷβ����������ѭ������
    }
	    fclose(fp);
    r = A->next;
    for (int i = 0; i < 30; i++)
    {
        printf("%d,%s\n", r->no, r->data);
        r = r->next;
    }
    
    r = A->next;
    while (r->no != 11) // Ѱ�ҵ�һ�����еĽ��
    {
        r = r->next;
    }

    for (int j = 30; j > 1; j--)
    {
        for (int i = 1; i <= 18; i++)
        {
            if (i == 18)
            {
                printf("��%d��ɾ�����:%d,��ʼλ��:%d,������Ϊ%d\n", 31-j, r->no, r->pos, j-1);
                p = r;
                r = r->next;
                p->prior->next = p->next;
                p->next->prior = p->prior;
                free(p->data); // �ͷŴ洢�ռ�
                free(p);
            }
            else
            {
                r = r->next;
            }
        }
    }

    printf("���һλ�ı��:%d,��ʼλ��:%d\n", r->next->no, r->next->pos); // ������Ľ��
	free(A);

	
	return 0;

}
