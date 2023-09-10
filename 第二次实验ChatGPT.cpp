#include <stdio.h>
#include <stdlib.h>
 
int main()
{
    int a[50],b[50],m,n,i,x,j=1,count=0;
    printf("please input m;");
    scanf("%d",&m);
    printf("please input n:");
    scanf("%d",&n);
    if(m==0||n==0)        //当m或n中有一个为0，都会报错
    {
        printf("error");
    }
    else
    {
        x=m;               //防止在编译过程中造成数据更改
        for(i=1;i<=m;i++)  //将数存储到数组里
        {
            a[i]=i;
        }
        while(x>=1)
        {
            for(i=1;i<=m;i++)
            {
                if(a[i]!=0)
                {
                    count++;         //报数
                }
                if(count==n)
                {
                    b[j]=a[i];      //用另一个数组重新按顺序记录
                    a[i]=0;         //已经报过数的将其值赋为0
                    count=0;        //重新开始报数
                    x--;            //总数在减少
                    j++;
                }
            }
        }
    for(i=1;i<=m;i++)               //输出
    {
        printf("%d ",b[i]);
    }
    }
    return 0;
}
