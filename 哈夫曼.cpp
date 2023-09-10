#include<stdio.h>
#include<stdlib.h>
#include<string.h>
 
typedef struct {
	int weight;
	int parent, lchild, rchild;
	char value;
} HTNode, * HuffmanTree;
 
typedef char** HuffmanCode;
 
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
	FILE* fp1, * fp2;
	int f,i;
	fp1 = fopen("HfmTree.txt", "w+");
	fp2 = fopen("CodeFile.txt", "w+");
	HuffmanTree p;
	if (n <= 1) return;
	m = 2 * n - 1;
	HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));
	for (p = HT + 1, i = 1; i <= n; ++i, ++p, ++w,++c) *p = { *w,0,0,0,*c };
	for (; i <= m; ++i, ++p) *p = { 0,0,0,0,'0' };
	for (i = n + 1; i <= m; ++i) {
		int s1, s2;
		Select(HT, i - 1, s1, s2);
	
		HT[s1].parent = i; HT[s2].parent = i;
		HT[i].lchild = s1; HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}

	fclose(fp1);
	
	HC = (HuffmanCode)malloc((n + 1) * sizeof(char*));
	char* cd = (char*)malloc(n * sizeof(char));
	cd[n - 1] = '\0';
	for (i = 1; i <= n; ++i) {
		int start = n - 1;
		for (int c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent)
		{
			if (HT[f].lchild == c) cd[--start] = '0';
			else cd[--start] = '1';
		}
		HC[i] = (char*)malloc((n - start) * sizeof(char));
		strcpy(HC[i], &cd[start]);
	}
	free(cd);
	for (int i = 1; i <= n ; i++)
	{
		 fprintf(fp2,"%c\t\t\t",HT[i].value);fputs(HC[i], fp2); fprintf(fp2, "\n");
	}
	fclose(fp2);
}
 
void Encrypt(HuffmanTree HT,HuffmanCode HC)
{
	char a[124],c,mood;
	FILE* fp2, * fp4;
	fp2 = fopen("file1.txt", "r+");

		fgets(a, 124, fp2);
		if ((fp4 = fopen("file2.txt", "r+")) == NULL) printf("无法打开加密结果文件！\n");
		else {
			for (int i = 0; a[i] != '\0'; i++) {
				for (int j = 1; j <= 26; j++)
				{
					if (a[i] == HT[j].value) fputs(HC[j], fp4);
				}
				
			}

		fclose(fp4);
	
	fclose(fp2);
}
}
 
void Translate(HuffmanTree HT)
{
	FILE* fp1,*fp2;
	char c;
	int i=m;
	fp1 = fopen("file2.txt", "r+");
	fp2 = fopen("file3.txt", "r+");
	if ((fp1 = fopen("file2.txt", "r+")) == NULL) printf("无法打开待翻译文件！\n");
	if ((fp2 = fopen("file3.txt", "r+")) == NULL) printf("无法打翻译结果文件！\n");
	else
	{

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
			 
		}
		 fputc(HT[i].value, fp2);
	}

	fclose(fp1);
	fclose(fp2);
}
 
int Interface(){
	printf("请选择要进行的操作：\n");
	printf("1.加密文档\n\n2.文档解密\n\n3.退出程序\n");
	int ans;
	scanf("%d", &ans);
	return ans;
}
 
int main(){
	FILE *fp1,*fp3;
	HuffmanTree HT;
	HuffmanCode HC;
	char ciphercode[30];
	int w[30];
	
	 fp1 = fopen("FreqData.txt", "r");
     fp3 = fopen("CharSet.txt", "r");

		for (int i = 0; i < 26; i++)
		{
			fscanf(fp1, "%d", &w[i]);
			fscanf(fp3, "%C", &ciphercode[i]);
		}
		HuffmanCoding(HT, HC, w, 26,ciphercode);
		
		Encrypt(HT, HC);
		Translate(HT);	
	/*	do {
			int temp = Interface();
			switch (temp)
				{
				
				case 1:Encrypt(HT, HC); break;
				case 2:Translate(HT); break;
				case 3:return 0;
				};
		} while (1);*/
	
		
	
	return 0;
}
