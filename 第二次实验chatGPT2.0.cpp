#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NAME_LEN 20

typedef struct _Person {
    char name[NAME_LEN];
    int id;
    struct _Person *next;
} Person;

void PrintList(Person *head);
Person* FindPerson(Person *head, int id);
int DeletePerson(Person *head, Person *prev, Person *curr);
void FreeList(Person *head);

int main() {
    // 生成人员信息
    srand(time(NULL));
    const int PERSON_COUNT = 30;
    const int ID_RANGE = 100;
    Person **people = (Person**)malloc(sizeof(Person*) * PERSON_COUNT);
    for (int i = 0; i < PERSON_COUNT; ++i) {
        people[i] = (Person*)malloc(sizeof(Person));
        sprintf(people[i]->name, "Name%d", i + 1); // 假设自己名字为"Name"
        while (1) { // 保证随机编号不同
            int id = rand() % ID_RANGE + 1;
            int existed = 0;
            for (int j = 0; j < i; ++j) {
                if (id == people[j]->id) {
                    existed = 1;
                    break;
                }
            }
            if (!existed) {
                people[i]->id = id;
                break;
            }
        }
    }
    
    // 构造循环链表
    Person *head = people[0];
    head->next = NULL;
    Person *tail = head;
    for (int i = 1; i < PERSON_COUNT; ++i) {
        tail->next = people[i];
        people[i]->next = NULL;
        tail = people[i];
    }
    tail->next = head; // 衔接成循环链表
    
    PrintList(head); // 输出循环链表
    
    // 查找编号为11的人
    int target_id = 11;
    Person *target_person = FindPerson(head, target_id);
    if (target_person == NULL) {
        printf("Can't find person with ID=%d!\n", target_id);
        FreeList(head);
        return 0;
    }
    printf("\nTarget person: %s, ID=%d\n", target_person->name, target_person->id);
    
    // 报数并删除人员
    int count = 1;
    Person *curr = target_person;
    Person *prev = tail; // 初始时前一个人是最后一个人
    while (head != NULL && head->next != head) { // 还有2个以上人在链表中
        if (count == 18) {
            prev = curr;
            curr = curr->next;
            DeletePerson(head, prev, curr);
            printf("%s(ID=%d) is deleted at position %d.\n", curr->name, curr->id, count);
            curr = curr->next;
            count = 1;
        } else {
            prev = curr;
            curr = curr->next;
            count++;
        }
    }
    
    // 输出最后剩余的人员
    printf("\nThe winner is: %s, ID=%d. Initial position: %d", head->name, head->id, PERSON_COUNT - 1);

    FreeList(head); // 释放内存
    return 0;
}

// 输出循环链表各结点的值
void PrintList(Person *head) {
    printf("Initial list:\n");
    Person *curr = head;
    do {
        printf("%s(ID=%d)\n", curr->name, curr->id);
        curr = curr->next;
    } while (curr != head);
}

// 在循环链表中查找到编号为id的结点
Person* FindPerson(Person *head, int id) {
    if (head == NULL) return NULL;

    Person *curr = head;
    do {
        if (curr->id == id) {
            return curr;
        }
        curr = curr->next;
    } while (curr != head);

    return NULL; // 没有找到，返回NULL
}

// 从循环链表中删除curr结点，并返回被删除结点的地址
int DeletePerson(Person *head, Person *prev, Person *curr) {
    if (head == NULL || prev == NULL || curr == NULL) return -1;

    if (prev->next == curr && curr->next == head) { // 删除尾结点
        prev->next = head;
        free(curr);
        return 0;
    }

    prev->next = curr->next;
    free(curr);
    return 0;
}

// 释放链表内存
void FreeList(Person *head) {
    if (head == NULL) return;

    Person *curr = head->next;
    while (curr != head) {
        Person *temp = curr;
        curr = curr->next;
        free(temp);
    }
    free(head); // 注意不要漏掉头结点
}
