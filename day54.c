#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* newNode(int val) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

TreeNode* buildTree(int* arr, int n) {
    if (n == 0 || arr[0] == -1) return NULL;
    
    TreeNode* root = newNode(arr[0]);
    TreeNode** queue = (TreeNode**)malloc(n * sizeof(TreeNode*));
    int front = 0, rear = 0;
    
    queue[rear++] = root;
    int i = 1;
    
    while (i < n && front < rear) {
        TreeNode* curr = queue[front++];
        
        if (i < n) {
            if (arr[i] != -1) {
                curr->left = newNode(arr[i]);
                queue[rear++] = curr->left;
            }
            i++;
        }
        
        if (i < n) {
            if (arr[i] != -1) {
                curr->right = newNode(arr[i]);
                queue[rear++] = curr->right;
            }
            i++;
        }
    }
    
    free(queue);
    return root;
}

void zigzagTraversal(TreeNode* root) {
    if (root == NULL) {
        printf("\n");
        return;
    }
    
    TreeNode** queue = (TreeNode**)malloc(10000 * sizeof(TreeNode*));
    int front = 0, rear = 0;
    bool leftToRight = true;
    int* result = (int*)malloc(10000 * sizeof(int));
    int resIndex = 0;
    
    queue[rear++] = root;
    
    while (front < rear) {
        int levelSize = rear - front;
        int* level = (int*)malloc(levelSize * sizeof(int));
        int levelIdx = 0;
        
        for (int i = 0; i < levelSize; i++) {
            TreeNode* node = queue[front++];
            level[levelIdx++] = node->val;
            
            if (node->left) queue[rear++] = node->left;
            if (node->right) queue[rear++] = node->right;
        }
        
        if (!leftToRight) {
            for (int i = levelSize - 1; i >= 0; i--) {
                result[resIndex++] = level[i];
            }
        } else {
            for (int i = 0; i < levelSize; i++) {
                result[resIndex++] = level[i];
            }
        }
        
        leftToRight = !leftToRight;
        free(level);
    }
    
    for (int i = 0; i < resIndex; i++) {
        printf("%d", result[i]);
        if (i < resIndex - 1) printf(" ");
    }
    printf("\n");
    
    free(queue);
    free(result);
}

int main() {
    int N;
    scanf("%d", &N);
    
    int* arr = (int*)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
    }
    
    TreeNode* root = buildTree(arr, N);
    zigzagTraversal(root);
    
    free(arr);
    return 0;
}