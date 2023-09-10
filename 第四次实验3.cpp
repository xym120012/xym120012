#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int Key;         // �ؼ���
    int No;          // ѧ��
    int Primarykey;  // ���ؼ���
} RecordType;

// ����һ���������
int random(int min, int max) {
    return min + rand() % (max - min + 1);
}

// ���������S��д���ļ�
void generateSortFile() {
    FILE *fp = fopen("data.txt", "r+");
    int i, j, k, x, y;
    int KeyGroup[4][3];  // ������ͬ�ؼ���ļ���
    RecordType S[200];

    // ��ʼ�����������
    srand((unsigned int)time(NULL));

    // ����������ͬ�ؼ���ļ���
    for (i = 0; i < 4; i++) {
        k = i * 50 + random(0, 49);  // ���ѡ��һ��Ԫ����Ϊ��ǰ���ϵĹؼ���
        for (j = 0; j < 3; j++) {
            x = i * 50 + j * 16 + random(0, 15);       // ����ѧ��
            y = i * 50 + j * 16 + 1 + random(0, 15);   // �������ؼ���
            KeyGroup[i][j] = x;                        // ��ѧ����Ϊ��ǰ���ϵĹؼ���
            S[k + j].Key = x;
            S[k + j].No = x;
            S[k + j].Primarykey = y;
        }
    }

    // ����ʣ���196��Ԫ��
    for (i = 0; i < 4; i++) {  // ��ÿһ����ͬ�ؼ���ļ���
        for (j = 0; j < 50; j++) {  // ��ÿһ��Ԫ��
            if (j >= 3) {
                x = i * 50 + j * 4 - 6 + random(0, 7);   // ����ѧ��
                y = i * 50 + j * 4 - 5 + random(0, 7);   // �������ؼ���
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
