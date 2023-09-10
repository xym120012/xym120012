#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct {
	int weight;
	int parent, lchild, rchild;
	char value;
} HTNode, * HuffmanTree;//动态分配数组存储哈夫曼树
 
typedef char** HuffmanCode;//动态分配数组存储哈夫曼编码表
 
int m;
 
void Select(HuffmanTree HT, int n, int& s1, int& s2) {
	int min = n;
	for (int i = 1; i <= n; i++)
	{
		if (HT[i].parent != 0) continue;
		else {
			if (HT[i].weight <= HT[min].weight) min = i;
		}
	}
	s1 = min; min = 1;
	while (HT[min].parent != 0 || min == s1) min++;
	for (int i = 1; i <= n; i++)
	{
		if (HT[i].parent != 0||i==s1) continue;
		else {
			if (HT[i].weight <= HT[min].weight) min = i;
		}
	}
	s2 = min;
}
 
void HuffmanCoding(HuffmanTree& HT, HuffmanCode& HC, int* w, int n,char *c) {
	//w存放n个字符权值，构造哈夫曼树HT，并求出n个字符的哈夫曼编码C
	FILE* fp;
	int f,i;
	fp = fopen("file4.txt", "w+");
	HuffmanTree p;
	if (n <= 1) return;
	m = 2 * n - 1;
	HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));//0号单元未用
	for (p = HT + 1, i = 1; i <= n; ++i, ++p, ++w,++c) *p = { *w,0,0,0,*c };
	for (; i <= m; ++i, ++p) *p = { 0,0,0,0,'0' };
	for (i = n + 1; i <= m; ++i) {//建立哈夫曼树
		int s1, s2;
		Select(HT, i - 1, s1, s2);
	
		HT[s1].parent = i; HT[s2].parent = i;
		HT[i].lchild = s1; HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}	
	//从叶子到根逆向求每个字符的哈夫曼编码
	HC = (HuffmanCode)malloc((n + 1) * sizeof(char*));
	char* cd = (char*)malloc(n * sizeof(char));
	cd[n - 1] = '\0';//编码结束符
	for (i = 1; i <= n; ++i) {//逐个求解
		int start = n - 1;//编码结束位置
		for (int c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent)
		{
			if (HT[f].lchild == c) cd[--start] = '0';
			else cd[--start] = '1';
		}
		HC[i] = (char*)malloc((n - start) * sizeof(char));
		strcpy(HC[i], &cd[start]);//从cd复制到HC
	}
	free(cd);
	for (int i = 1; i <= n ; i++)
	{
		 fprintf(fp,"%c\t\t\t",HT[i].value);fputs(HC[i], fp); fprintf(fp, "\n");
	}//把编码输出到文件file4.txt中
	fclose(fp);
}
 
void Encrypt(HuffmanTree HT,HuffmanCode HC)
{//通过HT与HC对文件数据进行编译
	char a[124],c,mood;
	FILE* fp1, * fp2;
	fp1 = fopen("file1.txt", "r+");		
	fgets(a, 124, fp1);	
	fp2 = fopen("file2.txt", "r+");
	
		for (int i = 0; a[i] != '\0'; i++) {
			for (int j = 1; j <= 26; j++)
				{
					if (a[i] == HT[j].value) fputs(HC[j], fp2);
					//编译输出到file2.txt中
				}				
			}
	fclose(fp2);
	fclose(fp1);
}
 
void Translate(HuffmanTree HT)
{//通过HT对文件数据进行翻译
	FILE* fp1,*fp2;
	char c;
	int i=m;
	fp1 = fopen("file2.txt", "r+");
	fp2 = fopen("file3.txt", "r+");
		c = fgetc(fp1);
		 while (c != EOF)
		{
			if (HT[i].value != '0')
			{
				fputc(HT[i].value, fp2);
				i = m;
							}
			else
				{
					if (c == '0')	i = HT[i].lchild;
					else if (c == '1') i = HT[i].rchild;c = fgetc(fp1);
								}			 
		}//逐个比对，对密码进行翻译
		 fputc(HT[i].value, fp2);//翻译内容输出到file3.txt中
	
	fclose(fp1);
	fclose(fp2);
} 
int main(){
	FILE *fp;
	HuffmanTree HT;
	HuffmanCode HC;
	char ciphercode[30];
	int w[30];
	
	 fp = fopen("FreqData.txt", "r");
		for (int i = 0; i < 26; i++)
		{
			fscanf(fp, "%C %d\n", &ciphercode[i],&w[i]);
		}//将字母和数据输入到ciphercode,w中
		fclose(fp);
		HuffmanCoding(HT, HC, w, 26,ciphercode);
		//建立树和编码
		Encrypt(HT, HC);
		//编译文件
		Translate(HT);	
		//翻译文件
	return 0;
}
