#include <stdio.h>
#include <stdlib.h>
 
int main()
{
    int a[50],b[50],m,n,i,x,j=1,count=0;
    printf("please input m;");
    scanf("%d",&m);
    printf("please input n:");
    scanf("%d",&n);
    if(m==0||n==0)        //��m��n����һ��Ϊ0�����ᱨ��
    {
        printf("error");
    }
    else
    {
        x=m;               //��ֹ�ڱ��������������ݸ���
        for(i=1;i<=m;i++)  //�����洢��������
        {
            a[i]=i;
        }
        while(x>=1)
        {
            for(i=1;i<=m;i++)
            {
                if(a[i]!=0)
                {
                    count++;         //����
                }
                if(count==n)
                {
                    b[j]=a[i];      //����һ���������°�˳���¼
                    a[i]=0;         //�Ѿ��������Ľ���ֵ��Ϊ0
                    count=0;        //���¿�ʼ����
                    x--;            //�����ڼ���
                    j++;
                }
            }
        }
    for(i=1;i<=m;i++)               //���
    {
        printf("%d ",b[i]);
    }
    }
    return 0;
}
