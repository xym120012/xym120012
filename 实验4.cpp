#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include<string.h>
#include <windows.h>
#define MAX_NUM 1000

typedef struct {
    int key; // �ؼ���
    int no; // ѧ��
    int primarykey; // ���ؼ���
} SortedItem;

int random(int min, int max) {
    return min + rand() % (max - min + 1);
}

// �������һ��Ԫ��
SortedItem generateItem() {
    SortedItem item;
    
    item.key = random(0, 200);
    item.no =  random(0, 200);
    item.primarykey = random(0, 200);
    return item;
}

// �Զ����������
void generateSortedTable(SortedItem table[], int length) {
      
     for (int i = 0; i < length; i++) {
	         table[i] = generateItem();
	       for(int j = 0; j < i; j++){
			 	if(table[j].no==table[i].no||table[j].primarykey==table[i].primarykey){table[i] = generateItem();
				 							j=-1;}
			 }
	     }
     int j=1;
	for(int i=0;j<=4;j++){
		table[i].key=table[i+1].key=table[i+2].key=j;
		i=i+3;
	}
	}

void straightInsertionSort(SortedItem table[], int length, int *compare, int *move, double *time_spend) {
	*compare=*move=0;
	*time_spend=0;
    LARGE_INTEGER freq;
    LARGE_INTEGER t_start, t_end;
    QueryPerformanceFrequency(&freq); // ��ȡ��ʱ����Ƶ�ʣ�ÿ����ٸ�����ֵ��
    QueryPerformanceCounter(&t_start); // ��¼����ʼʱ�ļ���ֵ
    for (int i = 1; i < length; i++) {
        SortedItem temp = table[i];
        int j;
        for (j = i - 1; j >= 0 && table[j].key > temp.key; j--) {
            table[j + 1] = table[j];
            (*compare)++; // ��¼�Ƚϴ���
            (*move)++; // ��¼�ƶ�����
        }
        table[j + 1] = temp;
        (*move)++; // ��¼�ƶ�����
        (*compare)++; // ��¼�Ƚϴ���
    }
    QueryPerformanceCounter(&t_end); // ��¼�������ʱ�ļ���ֵ
    (*time_spend) = (t_end.QuadPart - t_start.QuadPart) * 1.0 / freq.QuadPart * 1000000; // ��������ʱ�䣨����Ϊ΢�룩
}//ֱ�Ӳ�������

void instraightInsertionSort(SortedItem table[], int length) {
    for (int i = 1; i < length; i++) {
        SortedItem temp = table[i];
        int j;
        for (j = i - 1; j >= 0 && table[j].key < temp.key; j--) {
            table[j + 1] = table[j];
        }
        table[j + 1] = temp;
    }
}

void bubbleSort(SortedItem table[], int length, int *compare, int *move, double *time_spend) {
		*compare=*move=0;
		*time_spend=0;
    /* ����ʼִ��ʱ�ļ���ֵ */
    LARGE_INTEGER t1;
    QueryPerformanceCounter(&t1);
	
    for (int i = 0; i < length - 1; i++) {
  
        for (int j = 0; j < length - i - 1; j++) {
            if (table[j].key > table[j + 1].key) {
                SortedItem temp = table[j];
                table[j] = table[j + 1];
                table[j + 1] = temp;
                (*move) += 3;
            }
            (*compare)++;
        }(*compare)++;
       
    }(*compare)++;

    /* �������ִ��ʱ�ļ���ֵ */
    LARGE_INTEGER t2;
    QueryPerformanceCounter(&t2);
	
    /* �������ִ��ʱ�䣨��λ��΢�룩*/
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    double cost_time = (t2.QuadPart - t1.QuadPart) * 1000000.0 / freq.QuadPart;
    *time_spend = cost_time;
}//ð������


void selectionSort(SortedItem table[], int length, int *compare, int *move, double *time_spend) {
		*compare=*move=0;
		*time_spend=0;
    /* ����ʼִ��ʱ�ļ���ֵ */
    LARGE_INTEGER t1;
    QueryPerformanceCounter(&t1);

    for (int i = 0; i < length - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < length; j++) {
            if (table[j].key < table[minIndex].key) {
                minIndex = j;
            }
            (*compare)++;
        }
        (*compare)++;
        if (minIndex != i) {
            SortedItem temp = table[i];
            table[i] = table[minIndex];
            table[minIndex] = temp;
            (*move) += 3;
        }
        (*compare)++;
    }

    /* �������ִ��ʱ�ļ���ֵ */
    LARGE_INTEGER t2;
    QueryPerformanceCounter(&t2);

    /* �������ִ��ʱ�䣨��λ��΢�룩*/
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    double cost_time = (t2.QuadPart - t1.QuadPart) * 1000000.0 / freq.QuadPart;
    *time_spend = cost_time;
}//ѡ������

void quickSort(SortedItem table[], int left, int right, int *compare, int *move, double *time_spend) {

    if (left >= right) {
        return;
    }
    int i = left, j = right;
    SortedItem pivot = table[left];
		
    /* ����ʼִ��ʱ�ļ���ֵ */
    LARGE_INTEGER t1;
    QueryPerformanceCounter(&t1);

    while (i < j) {
        while (i < j && table[j].key >= pivot.key) {
            (*compare)++;
            j--;
        }
        table[i] = table[j];
        (*move)++;
        while (i < j && table[i].key <= pivot.key) {
            (*compare)++;
            i++;
        }
        table[j] = table[i];
        (*move)++;
    }
    table[i] = pivot;
    quickSort(table, left, i - 1, compare, move, time_spend);
    quickSort(table, i + 1, right, compare, move, time_spend);//�ݹ����

    /* �������ִ��ʱ�ļ���ֵ */
    LARGE_INTEGER t2;
    QueryPerformanceCounter(&t2);

    /* �������ִ��ʱ�䣨��λ��΢�룩*/
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    double cost_time = (t2.QuadPart - t1.QuadPart) * 1000000.0 / freq.QuadPart;
    *time_spend += cost_time;
}//��������

void shuffle1(SortedItem table[], int n) {
	// �����һ��Ԫ�ؿ�ʼ����ǰ��������
	for (int i = n-1; i > 0; i--) {
   // ����һ��������� j����ΧΪ [0, i]
     int j = random(0, i);
	        
	        // ����λ��
	    SortedItem temp = table[j];
	    table[j] = table[i];
	    table[i] = temp;
	    }
	}//shuffle1() �����˵����������ķ�ʽ��ÿ�ν���ǰλ����ǰ��ĳ��λ�ã�������ǰλ�ã�����
	
void shuffle2(SortedItem table[], int n) {
	    // �ӵ�һ��Ԫ�ؿ�ʼ������������
	for (int i = 0; i < n-1; i++) {
	        // ����һ��������� j����ΧΪ [i+1, n-1]
	    int j = random(i+1, n-1);
	    // ����λ��
	    SortedItem temp = table[j];
	    table[j] = table[i];
	    table[i] = temp;
	    }
	}//shuffle2() �������˳���������ķ�ʽ��ÿ�ν���ǰλ�������ĳ��λ�ã���������ǰλ�ã�����
	
int main()
{	
SortedItem *S,*s1,*s2,*s3,*s4;
int compare, move;
double time_spend;//���������
FILE *fp;
fp=fopen("output.ifo","w+");

S = (SortedItem *) malloc(200 * sizeof(SortedItem));
s1 = (SortedItem *) malloc(200 * sizeof(SortedItem));
s2 = (SortedItem *) malloc(200 * sizeof(SortedItem));
s3 = (SortedItem *) malloc(200 * sizeof(SortedItem));
s4 = (SortedItem *) malloc(200 * sizeof(SortedItem));//��̬����ռ�

	generateSortedTable(S,200);
	
	int times[4][4];
	int times1[4][4];
	double times2[4][4];//�ö�ά�����¼�Ƚϣ��ƶ�������ִ��ʱ��
	SortedItem *items[4]={s1,s2,s3,s4};
	
			memcpy(s1, S, 200 * sizeof(SortedItem)); // ����һ��ԭ��
			quickSort(s1, 0, 199,&compare,&move,&time_spend); 
										    
			memcpy(s2, S, 200 * sizeof(SortedItem));      
			instraightInsertionSort(s2, 200);
										 	
			memcpy(s3, s1, 200 * sizeof(SortedItem));
			memcpy(s4, s1, 200 * sizeof(SortedItem));
										 	
			shuffle1(s3,200);
			shuffle2(s4,200); //��������s3��s4
			
			compare=0;
			move=0;
			time_spend=0;//s1��s2��s3��s4�ĳ�ʼ��
											
							
							for(int i=0;i<4;i++)
							{straightInsertionSort(items[i], 200,&compare,&move,&time_spend);
							times[0][i]=compare;
							times1[0][i]=move;
							times2[0][i]=time_spend;
							compare=0;
							move=0;
							time_spend=0;}	//A1����			
							{memcpy(s1, S, 200 * sizeof(SortedItem)); 
										quickSort(s1, 0, 199,&compare,&move,&time_spend); 
																	    
										memcpy(s2, S, 200 * sizeof(SortedItem));      
										instraightInsertionSort(s2, 200);
																	 	
										memcpy(s3, s1, 200 * sizeof(SortedItem));
										memcpy(s4, s1, 200 * sizeof(SortedItem));
																	 	
										shuffle1(s3,200);
										shuffle2(s4,200); 
										
										compare=0;
										move=0;
										time_spend=0;}	//�ٴ�����4������֮ǰ��ͬ								
							for(int i=0;i<4;i++)
							{bubbleSort(items[i], 200,&compare,&move,&time_spend);
							times[1][i]=compare;
							times1[1][i]=move;
							times2[1][i]=time_spend;
							compare=0;
							move=0;
							time_spend=0;}	//A2����						
							{memcpy(s1, S, 200 * sizeof(SortedItem)); 
										quickSort(s1, 0, 199,&compare,&move,&time_spend); 
																	    
										memcpy(s2, S, 200 * sizeof(SortedItem));      
										instraightInsertionSort(s2, 200);
																	 	
										memcpy(s3, s1, 200 * sizeof(SortedItem));
										memcpy(s4, s1, 200 * sizeof(SortedItem));
																	 	
										shuffle1(s3,200);
										shuffle2(s4,200); 
										
										compare=0;
										move=0;
										time_spend=0;}	//�ٴ�����4������֮ǰ��ͬ										
							for(int i=0;i<4;i++)
							{selectionSort(items[i], 200, &compare, &move, &time_spend);
							times[2][i]=compare;
							times1[2][i]=move;
							times2[2][i]=time_spend;
							compare=0;
							move=0;
							time_spend=0;}//A3����		
							{memcpy(s1, S, 200 * sizeof(SortedItem)); 
										quickSort(s1, 0, 199,&compare,&move,&time_spend);
																	    
										memcpy(s2, S, 200 * sizeof(SortedItem));      
										instraightInsertionSort(s2, 200);
																	 	
										memcpy(s3, s1, 200 * sizeof(SortedItem));
										memcpy(s4, s1, 200 * sizeof(SortedItem));
																	 	
										shuffle1(s3,200);
										shuffle2(s4,200); 
										
										compare=0;
										move=0;
										time_spend=0;}		//�ٴ�����4������֮ǰ��ͬ				
							for(int i=0;i<4;i++)
							{quickSort(items[i],0, 199,&compare,&move,&time_spend);
							times[3][i]=compare;
							times1[3][i]=move;
							times2[3][i]=time_spend;
							compare=0;
							move=0;
							time_spend=0;}//A4����
							
							fprintf(fp,"------------------------------------------------------\n");
							fprintf(fp,"�Ƚϴ�����\tA1\tA2\tA3\tA4\n");
							fprintf(fp, "        S1\t%d\t%d\t%d\t%d \n", times[0][0],times[1][0],times[2][0],times[3][0]);
							fprintf(fp, "        S2\t%d\t%d\t%d\t%d \n", times[0][1],times[1][1],times[2][1],times[3][1]);
							fprintf(fp, "        S3\t%d\t%d\t%d\t%d \n", times[0][2],times[1][2],times[2][2],times[3][2]);
							fprintf(fp, "        S4\t%d\t%d\t%d\t%d \n", times[0][3],times[1][3],times[2][3],times[3][3]);
							fprintf(fp,"------------------------------------------------------\n");
							fprintf(fp,"------------------------------------------------------\n");
							fprintf(fp,"�ƶ�������\tA1\t\tA2\t\tA3\t\tA4\n");
							fprintf(fp, "        S1\t%d\t\t%d\t\t%d\t\t%d \n", times1[0][0],times1[1][0],times1[2][0],times1[3][0]);
							fprintf(fp, "        S2\t%d \t%d \t%d \t\t%d \n", times1[0][1],times1[1][1],times1[2][1],times1[3][1]);
							fprintf(fp, "        S3\t%d \t%d \t%d \t\t%d \n", times1[0][2],times1[1][2],times1[2][2],times1[3][2]);
							fprintf(fp, "        S4\t%d\t\t%d\t\t%d \t\t%d \n", times1[0][3],times1[1][3],times1[2][3],times1[3][3]);
							fprintf(fp,"------------------------------------------------------\n");
							fprintf(fp,"------------------------------------------------------\n");
							fprintf(fp,"ִ��ʱ���\tA1\t\tA2\t\tA3\t\tA4\n");
							fprintf(fp, "        S1\t%.2fus\t%.2fus\t%.2fus\t%.2fus \n", times2[0][0],times2[1][0],times2[2][0],times2[3][0]);
							fprintf(fp, "        S2\t%.2fus\t%.2fus\t%.2fus\t%.2fus \n", times2[0][1],times2[1][1],times2[2][1],times2[3][1]);
							fprintf(fp, "        S3\t%.2fus\t%.2fus\t%.2fus\t%.2fus \n", times2[0][2],times2[1][2],times2[2][2],times2[3][2]);
							fprintf(fp, "        S4\t%.2fus\t%.2fus\t%.2fus\t%.2fus \n", times2[0][3],times2[1][3],times2[2][3],times2[3][3]);	
							fprintf(fp,"------------------------------------------------------\n");	
			
		fclose(fp);
		free(S);
		free(s1);
		free(s2);
		free(s3);
		free(s4);
		return 0;
}	
