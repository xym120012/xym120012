#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct {
	int weight;
	int parent, lchild, rchild;
	char value;
} HTNode, * HuffmanTree;//��̬��������洢��������
 
typedef char** HuffmanCode;//��̬��������洢�����������
 
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
	//w���n���ַ�Ȩֵ�������������HT�������n���ַ��Ĺ���������C
	FILE* fp;
	int f,i;
	fp = fopen("file4.txt", "w+");
	HuffmanTree p;
	if (n <= 1) return;
	m = 2 * n - 1;
	HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));//0�ŵ�Ԫδ��
	for (p = HT + 1, i = 1; i <= n; ++i, ++p, ++w,++c) *p = { *w,0,0,0,*c };
	for (; i <= m; ++i, ++p) *p = { 0,0,0,0,'0' };
	for (i = n + 1; i <= m; ++i) {//������������
		int s1, s2;
		Select(HT, i - 1, s1, s2);
	
		HT[s1].parent = i; HT[s2].parent = i;
		HT[i].lchild = s1; HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}	
	//��Ҷ�ӵ���������ÿ���ַ��Ĺ���������
	HC = (HuffmanCode)malloc((n + 1) * sizeof(char*));
	char* cd = (char*)malloc(n * sizeof(char));
	cd[n - 1] = '\0';//���������
	for (i = 1; i <= n; ++i) {//������
		int start = n - 1;//�������λ��
		for (int c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent)
		{
			if (HT[f].lchild == c) cd[--start] = '0';
			else cd[--start] = '1';
		}
		HC[i] = (char*)malloc((n - start) * sizeof(char));
		strcpy(HC[i], &cd[start]);//��cd���Ƶ�HC
	}
	free(cd);
	for (int i = 1; i <= n ; i++)
	{
		 fprintf(fp,"%c\t\t\t",HT[i].value);fputs(HC[i], fp); fprintf(fp, "\n");
	}//�ѱ���������ļ�file4.txt��
	fclose(fp);
}
 
void Encrypt(HuffmanTree HT,HuffmanCode HC)
{//ͨ��HT��HC���ļ����ݽ��б���
	char a[124],c,mood;
	FILE* fp1, * fp2;
	fp1 = fopen("file1.txt", "r+");		
	fgets(a, 124, fp1);	
	fp2 = fopen("file2.txt", "r+");
	
		for (int i = 0; a[i] != '\0'; i++) {
			for (int j = 1; j <= 26; j++)
				{
					if (a[i] == HT[j].value) fputs(HC[j], fp2);
					//���������file2.txt��
				}				
			}
	fclose(fp2);
	fclose(fp1);
}
 
void Translate(HuffmanTree HT)
{//ͨ��HT���ļ����ݽ��з���
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
		}//����ȶԣ���������з���
		 fputc(HT[i].value, fp2);//�������������file3.txt��
	
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
		}//����ĸ���������뵽ciphercode,w��
		fclose(fp);
		HuffmanCoding(HT, HC, w, 26,ciphercode);
		//�������ͱ���
		Encrypt(HT, HC);
		//�����ļ�
		Translate(HT);	
		//�����ļ�
	return 0;
}
