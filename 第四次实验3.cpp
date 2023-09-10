#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int Key;         // 关键码
    int No;          // 学号
    int Primarykey;  // 主关键码
} RecordType;

// 生成一个随机整数
int random(int min, int max) {
    return min + rand() % (max - min + 1);
}

// 生成排序表S并写入文件
void generateSortFile() {
    FILE *fp = fopen("data.txt", "r+");
    int i, j, k, x, y;
    int KeyGroup[4][3];  // 四组相同关键码的集合
    RecordType S[200];

    // 初始化随机数种子
    srand((unsigned int)time(NULL));

    // 生成四组相同关键码的集合
    for (i = 0; i < 4; i++) {
        k = i * 50 + random(0, 49);  // 随机选择一个元素作为当前集合的关键码
        for (j = 0; j < 3; j++) {
            x = i * 50 + j * 16 + random(0, 15);       // 生成学号
            y = i * 50 + j * 16 + 1 + random(0, 15);   // 生成主关键码
            KeyGroup[i][j] = x;                        // 将学号作为当前集合的关键码
            S[k + j].Key = x;
            S[k + j].No = x;
            S[k + j].Primarykey = y;
        }
    }

    // 生成剩余的196个元素
    for (i = 0; i < 4; i++) {  // 对每一组相同关键码的集合
        for (j = 0; j < 50; j++) {  // 对每一组元素
            if (j >= 3) {
                x = i * 50 + j * 4 - 6 + random(0, 7);   // 生成学号
                y = i * 50 + j * 4 - 5 + random(0, 7);   // 生成主关键码
                S[i * 50 + j].Key = x;
                S[i * 50 + j].No = x;
                S[i * 50 + j].Primarykey = y;
            }
            fprintf(fp, "%d %d %d\n", S[i * 50 + j].Key, S[i * 50 + j].No, S[i * 50 + j].Primarykey);
        }
    }

    fclose(fp);
}
int main(){
	generateSortFile();
}
