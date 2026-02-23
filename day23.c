#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* create_list(int* arr, int size) {
    if (size == 0) return NULL;
    struct Node* head = (struct Node*)malloc(sizeof(struct Node));
    head->data = arr[0];
    head->next = NULL;
    struct Node* current = head;
    for (int i = 1; i < size; i++) {
        current->next = (struct Node*)malloc(sizeof(struct Node));
        current = current->next;
        current->data = arr[i];
        current->next = NULL;
    }
    return head;
}

struct Node* merge_lists(struct Node* head1, struct Node* head2) {
    struct Node* dummy = (struct Node*)malloc(sizeof(struct Node));
    struct Node* tail = dummy;
    while (head1 && head2) {
        if (head1->data < head2->data) {
            tail->next = head1;
            head1 = head1->next;
        } else {
            tail->next = head2;
            head2 = head2->next;
        }
        tail = tail->next;
    }
    if (head1) tail->next = head1;
    if (head2) tail->next = head2;
    struct Node* merged_head = dummy->next;
    free(dummy);
    return merged_head;
}

void print_list(struct Node* head) {
    while (head) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

void free_list(struct Node* head) {
    struct Node* temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    int* list1 = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &list1[i]);
    }
    int m;
    scanf("%d", &m);
    int* list2 = (int*)malloc(m * sizeof(int));
    for (int i = 0; i < m; i++) {
        scanf("%d", &list2[i]);
    }
    struct Node* head1 = create_list(list1, n);
    struct Node* head2 = create_list(list2, m);
    struct Node* merged = merge_lists(head1, head2);
    print_list(merged);
    free_list(merged);
    free(list1);
    free(list2);
    return 0;
}