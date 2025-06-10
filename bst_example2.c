#include <stdio.h>
#include <stdlib.h>

// Define BST Node structure
typedef struct BST_Node {
    int data;
    struct BST_Node *left;
    struct BST_Node *right;
} BST_Node;

// Function prototypes
BST_Node *new_BST_Node(int value);
BST_Node *BST_insert(BST_Node *root, int value);
BST_Node *BST_search(BST_Node *root, int value);
BST_Node *BST_delete(BST_Node *root, int value);
void inorder_traversal(BST_Node *root);
void preorder_traversal(BST_Node *root);
void postorder_traversal(BST_Node *root);

int main() {
    BST_Node *root = NULL;
    int choice, value;
    BST_Node *found;

    while (1) {
        printf("\n====== Integer BST ======\n");
        printf("1. Insert Value\n");
        printf("2. Search for a Value\n");
        printf("3. Delete a Value\n");
        printf("4. Display All Values (In-order Traversal)\n");
        printf("5. Display All Values (pre-order Traversal)\n");
        printf("5. Display All Values (post-order Traversal)\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = BST_insert(root, value);
                printf("Value added successfully!\n");
                break;

            case 2:
                printf("Enter value to search: ");
                scanf("%d", &value);
                found = BST_search(root, value);
                if (found) {
                    printf("Value Found: %d\n", found->data);
                } else {
                    printf("Value not found.\n");
                }
                break;

            case 3:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                root = BST_delete(root, value);
                printf("Value deleted successfully (if found).\n");
                break;

            case 4:
                printf("\nAll values (sorted):\n");
                inorder_traversal(root);
                printf("\n");
                break;

            case 5:
                printf("\nPre order:\n");
                preorder_traversal(root);
                printf("\n");
                break;

            case 6:
                printf("\nPost order:\n");
                postorder_traversal(root);
                printf("\n");
                break;

            case 7:
                printf("Exiting program...\n");
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}

// Function to create a new BST node
BST_Node *new_BST_Node(int value) {
    BST_Node *new_node = (BST_Node *)malloc(sizeof(BST_Node));
    if (new_node == NULL) {
        printf("Error: Not enough memory to create a new node.\n");
        return NULL;
    }
    new_node->data = value;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

// Function to insert a new value into the BST
BST_Node *BST_insert(BST_Node *root, int value) {
    if (root == NULL)
        return new_BST_Node(value);

    if (value < root->data)
        root->left = BST_insert(root->left, value);
    else if (value > root->data)
        root->right = BST_insert(root->right, value);
    else
        printf("Duplicate value detected. Ignoring.\n");

    return root;
}

// Function to search for a value in BST
BST_Node *BST_search(BST_Node *root, int value) {
    if (root == NULL || root->data == value)
        return root;

    if (value < root->data)
        return BST_search(root->left, value);
    else
        return BST_search(root->right, value);
}

// Function to delete a value from BST
BST_Node *BST_delete(BST_Node *root, int value) {
    if (root == NULL) return NULL;

    BST_Node *tmp;

    if (value < root->data)
        root->left = BST_delete(root->left, value);
    else if (value > root->data)
        root->right = BST_delete(root->right, value);
    else {
        // Case a: No children
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }
        // Case b: One child (left)
        else if (root->right == NULL) {
            tmp = root->left;
            free(root);
            return tmp;
        }
        // Case b: One child (right)
        else if (root->left == NULL) {
            tmp = root->right;
            free(root);
            return tmp;
        }
        // Case c: Two children
        else {
            tmp = root->right;
            while (tmp->left != NULL)
                tmp = tmp->left;  // Finding the inorder successor

            root->data = tmp->data;  // Copy successor's value
            root->right = BST_delete(root->right, tmp->data);  // Delete successor
        }
    }
    return root;
}

// Function for in-order traversal of BST
void inorder_traversal(BST_Node *root) {
    if (root != NULL) {
        inorder_traversal(root->left);
        printf("%d ", root->data);
        inorder_traversal(root->right);
    }
}

void preorder_traversal(BST_Node *root) {
    if (root != NULL) {
        printf("%d ", root->data);
        inorder_traversal(root->left);
        inorder_traversal(root->right);
    }
}

void postorder_traversal(BST_Node *root) {
    if (root != NULL) {
        inorder_traversal(root->left);
        inorder_traversal(root->right);
        printf("%d ", root->data);
    }
}
