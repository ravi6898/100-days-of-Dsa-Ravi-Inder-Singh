#include <stdio.h>
#include <stdlib.h>

// Define a tree node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Utility function to create a new node
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// Search for index of value in inorder[]
int search(int inorder[], int start, int end, int value) {
    for (int i = start; i <= end; i++) {
        if (inorder[i] == value)
            return i;
    }
    return -1;
}

// Recursive function to build tree
struct Node* buildTree(int inorder[], int postorder[], int inStart, int inEnd, int* postIndex) {
    if (inStart > inEnd)
        return NULL;

    // Take current root from postorder
    int rootVal = postorder[*postIndex];
    (*postIndex)--;

    struct Node* root = newNode(rootVal);

    // If no children
    if (inStart == inEnd)
        return root;

    // Find root in inorder
    int inIndex = search(inorder, inStart, inEnd, rootVal);

    // Build right subtree first (because postorder is left-right-root)
    root->right = buildTree(inorder, postorder, inIndex + 1, inEnd, postIndex);
    root->left = buildTree(inorder, postorder, inStart, inIndex - 1, postIndex);

    return root;
}

// Print preorder traversal
void printPreorder(struct Node* root) {
    if (root == NULL)
        return;
    printf("%d ", root->data);
    printPreorder(root->left);
    printPreorder(root->right);
}

int main() {
    int N;
    scanf("%d", &N);

    int inorder[N], postorder[N];
    for (int i = 0; i < N; i++)
        scanf("%d", &inorder[i]);
    for (int i = 0; i < N; i++)
        scanf("%d", &postorder[i]);

    int postIndex = N - 1;
    struct Node* root = buildTree(inorder, postorder, 0, N - 1, &postIndex);

    printPreorder(root);
    return 0;
}