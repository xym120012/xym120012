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
    // ������Ա��Ϣ
    srand(time(NULL));
    const int PERSON_COUNT = 30;
    const int ID_RANGE = 100;
    Person **people = (Person**)malloc(sizeof(Person*) * PERSON_COUNT);
    for (int i = 0; i < PERSON_COUNT; ++i) {
        people[i] = (Person*)malloc(sizeof(Person));
        sprintf(people[i]->name, "Name%d", i + 1); // �����Լ�����Ϊ"Name"
        while (1) { // ��֤�����Ų�ͬ
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
    
    // ����ѭ������
    Person *head = people[0];
    head->next = NULL;
    Person *tail = head;
    for (int i = 1; i < PERSON_COUNT; ++i) {
        tail->next = people[i];
        people[i]->next = NULL;
        tail = people[i];
    }
    tail->next = head; // �νӳ�ѭ������
    
    PrintList(head); // ���ѭ������
    
    // ���ұ��Ϊ11����
    int target_id = 11;
    Person *target_person = FindPerson(head, target_id);
    if (target_person == NULL) {
        printf("Can't find person with ID=%d!\n", target_id);
        FreeList(head);
        return 0;
    }
    printf("\nTarget person: %s, ID=%d\n", target_person->name, target_person->id);
    
    // ������ɾ����Ա
    int count = 1;
    Person *curr = target_person;
    Person *prev = tail; // ��ʼʱǰһ���������һ����
    while (head != NULL && head->next != head) { // ����2����������������
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
    
    // ������ʣ�����Ա
    printf("\nThe winner is: %s, ID=%d. Initial position: %d", head->name, head->id, PERSON_COUNT - 1);

    FreeList(head); // �ͷ��ڴ�
    return 0;
}

// ���ѭ�����������ֵ
void PrintList(Person *head) {
    printf("Initial list:\n");
    Person *curr = head;
    do {
        printf("%s(ID=%d)\n", curr->name, curr->id);
        curr = curr->next;
    } while (curr != head);
}

// ��ѭ�������в��ҵ����Ϊid�Ľ��
Person* FindPerson(Person *head, int id) {
    if (head == NULL) return NULL;

    Person *curr = head;
    do {
        if (curr->id == id) {
            return curr;
        }
        curr = curr->next;
    } while (curr != head);

    return NULL; // û���ҵ�������NULL
}

// ��ѭ��������ɾ��curr��㣬�����ر�ɾ�����ĵ�ַ
int DeletePerson(Person *head, Person *prev, Person *curr) {
    if (head == NULL || prev == NULL || curr == NULL) return -1;

    if (prev->next == curr && curr->next == head) { // ɾ��β���
        prev->next = head;
        free(curr);
        return 0;
    }

    prev->next = curr->next;
    free(curr);
    return 0;
}

// �ͷ������ڴ�
void FreeList(Person *head) {
    if (head == NULL) return;

    Person *curr = head->next;
    while (curr != head) {
        Person *temp = curr;
        curr = curr->next;
        free(temp);
    }
    free(head); // ע�ⲻҪ©��ͷ���
}
