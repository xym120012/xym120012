#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include<string.h>
#include <windows.h>
#define MAX_NUM 1000

typedef struct {
    int key; // 关键码
    int no; // 学号
    int primarykey; // 主关键码
} SortedItem;

int random(int min, int max) {
    return min + rand() % (max - min + 1);
}

// 随机生成一个元素
SortedItem generateItem() {
    SortedItem item;
    
    item.key = random(0, 200);
    item.no =  random(0, 200);
    item.primarykey = random(0, 200);
    return item;
}

// 自动生成排序表
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
    QueryPerformanceFrequency(&freq); // 获取计时器的频率（每秒多少个计数值）
    QueryPerformanceCounter(&t_start); // 记录排序开始时的计数值
    for (int i = 1; i < length; i++) {
        SortedItem temp = table[i];
        int j;
        for (j = i - 1; j >= 0 && table[j].key > temp.key; j--) {
            table[j + 1] = table[j];
            (*compare)++; // 记录比较次数
            (*move)++; // 记录移动次数
        }
        table[j + 1] = temp;
        (*move)++; // 记录移动次数
        (*compare)++; // 记录比较次数
    }
    QueryPerformanceCounter(&t_end); // 记录排序结束时的计数值
    (*time_spend) = (t_end.QuadPart - t_start.QuadPart) * 1.0 / freq.QuadPart * 1000000; // 计算排序时间（精度为微秒）
}//直接插入排序

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
    /* 程序开始执行时的计数值 */
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

    /* 程序结束执行时的计数值 */
    LARGE_INTEGER t2;
    QueryPerformanceCounter(&t2);
	
    /* 计算程序执行时间（单位：微秒）*/
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    double cost_time = (t2.QuadPart - t1.QuadPart) * 1000000.0 / freq.QuadPart;
    *time_spend = cost_time;
}//冒泡排序


void selectionSort(SortedItem table[], int length, int *compare, int *move, double *time_spend) {
		*compare=*move=0;
		*time_spend=0;
    /* 程序开始执行时的计数值 */
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

    /* 程序结束执行时的计数值 */
    LARGE_INTEGER t2;
    QueryPerformanceCounter(&t2);

    /* 计算程序执行时间（单位：微秒）*/
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    double cost_time = (t2.QuadPart - t1.QuadPart) * 1000000.0 / freq.QuadPart;
    *time_spend = cost_time;
}//选择排序

void quickSort(SortedItem table[], int left, int right, int *compare, int *move, double *time_spend) {

    if (left >= right) {
        return;
    }
    int i = left, j = right;
    SortedItem pivot = table[left];
		
    /* 程序开始执行时的计数值 */
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
    quickSort(table, i + 1, right, compare, move, time_spend);//递归调用

    /* 程序结束执行时的计数值 */
    LARGE_INTEGER t2;
    QueryPerformanceCounter(&t2);

    /* 计算程序执行时间（单位：微秒）*/
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    double cost_time = (t2.QuadPart - t1.QuadPart) * 1000000.0 / freq.QuadPart;
    *time_spend += cost_time;
}//快速排序

void shuffle1(SortedItem table[], int n) {
	// 从最后一个元素开始，向前遍历数组
	for (int i = n-1; i > 0; i--) {
   // 生成一个随机索引 j，范围为 [0, i]
     int j = random(0, i);
	        
	        // 交换位置
	    SortedItem temp = table[j];
	    table[j] = table[i];
	    table[i] = temp;
	    }
	}//shuffle1() 采用了倒序遍历数组的方式，每次将当前位置与前面某个位置（包括当前位置）交换
	
void shuffle2(SortedItem table[], int n) {
	    // 从第一个元素开始，向后遍历数组
	for (int i = 0; i < n-1; i++) {
	        // 生成一个随机索引 j，范围为 [i+1, n-1]
	    int j = random(i+1, n-1);
	    // 交换位置
	    SortedItem temp = table[j];
	    table[j] = table[i];
	    table[i] = temp;
	    }
	}//shuffle2() 则采用了顺序遍历数组的方式，每次将当前位置与后面某个位置（不包括当前位置）交换
	
int main()
{	
SortedItem *S,*s1,*s2,*s3,*s4;
int compare, move;
double time_spend;//定义计数器
FILE *fp;
fp=fopen("output.ifo","w+");

S = (SortedItem *) malloc(200 * sizeof(SortedItem));
s1 = (SortedItem *) malloc(200 * sizeof(SortedItem));
s2 = (SortedItem *) malloc(200 * sizeof(SortedItem));
s3 = (SortedItem *) malloc(200 * sizeof(SortedItem));
s4 = (SortedItem *) malloc(200 * sizeof(SortedItem));//动态分配空间

	generateSortedTable(S,200);
	
	int times[4][4];
	int times1[4][4];
	double times2[4][4];//用二维数组记录比较，移动次数和执行时间
	SortedItem *items[4]={s1,s2,s3,s4};
	
			memcpy(s1, S, 200 * sizeof(SortedItem)); // 复制一份原表
			quickSort(s1, 0, 199,&compare,&move,&time_spend); 
										    
			memcpy(s2, S, 200 * sizeof(SortedItem));      
			instraightInsertionSort(s2, 200);
										 	
			memcpy(s3, s1, 200 * sizeof(SortedItem));
			memcpy(s4, s1, 200 * sizeof(SortedItem));
										 	
			shuffle1(s3,200);
			shuffle2(s4,200); //打乱生成s3，s4
			
			compare=0;
			move=0;
			time_spend=0;//s1，s2，s3，s4的初始化
											
							
							for(int i=0;i<4;i++)
							{straightInsertionSort(items[i], 200,&compare,&move,&time_spend);
							times[0][i]=compare;
							times1[0][i]=move;
							times2[0][i]=time_spend;
							compare=0;
							move=0;
							time_spend=0;}	//A1数据			
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
										time_spend=0;}	//再次生成4个表，与之前相同								
							for(int i=0;i<4;i++)
							{bubbleSort(items[i], 200,&compare,&move,&time_spend);
							times[1][i]=compare;
							times1[1][i]=move;
							times2[1][i]=time_spend;
							compare=0;
							move=0;
							time_spend=0;}	//A2数据						
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
										time_spend=0;}	//再次生成4个表，与之前相同										
							for(int i=0;i<4;i++)
							{selectionSort(items[i], 200, &compare, &move, &time_spend);
							times[2][i]=compare;
							times1[2][i]=move;
							times2[2][i]=time_spend;
							compare=0;
							move=0;
							time_spend=0;}//A3数据		
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
										time_spend=0;}		//再次生成4个表，与之前相同				
							for(int i=0;i<4;i++)
							{quickSort(items[i],0, 199,&compare,&move,&time_spend);
							times[3][i]=compare;
							times1[3][i]=move;
							times2[3][i]=time_spend;
							compare=0;
							move=0;
							time_spend=0;}//A4数据
							
							fprintf(fp,"------------------------------------------------------\n");
							fprintf(fp,"比较次数表\tA1\tA2\tA3\tA4\n");
							fprintf(fp, "        S1\t%d\t%d\t%d\t%d \n", times[0][0],times[1][0],times[2][0],times[3][0]);
							fprintf(fp, "        S2\t%d\t%d\t%d\t%d \n", times[0][1],times[1][1],times[2][1],times[3][1]);
							fprintf(fp, "        S3\t%d\t%d\t%d\t%d \n", times[0][2],times[1][2],times[2][2],times[3][2]);
							fprintf(fp, "        S4\t%d\t%d\t%d\t%d \n", times[0][3],times[1][3],times[2][3],times[3][3]);
							fprintf(fp,"------------------------------------------------------\n");
							fprintf(fp,"------------------------------------------------------\n");
							fprintf(fp,"移动次数表\tA1\t\tA2\t\tA3\t\tA4\n");
							fprintf(fp, "        S1\t%d\t\t%d\t\t%d\t\t%d \n", times1[0][0],times1[1][0],times1[2][0],times1[3][0]);
							fprintf(fp, "        S2\t%d \t%d \t%d \t\t%d \n", times1[0][1],times1[1][1],times1[2][1],times1[3][1]);
							fprintf(fp, "        S3\t%d \t%d \t%d \t\t%d \n", times1[0][2],times1[1][2],times1[2][2],times1[3][2]);
							fprintf(fp, "        S4\t%d\t\t%d\t\t%d \t\t%d \n", times1[0][3],times1[1][3],times1[2][3],times1[3][3]);
							fprintf(fp,"------------------------------------------------------\n");
							fprintf(fp,"------------------------------------------------------\n");
							fprintf(fp,"执行时间表\tA1\t\tA2\t\tA3\t\tA4\n");
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
