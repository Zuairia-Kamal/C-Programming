#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 1024

// Define structures
typedef struct Restaurant_Score {
    char restaurant_name[MAX_STRING_LENGTH];
    char restaurant_address[MAX_STRING_LENGTH];
    int score;
} Review;

typedef struct BST_Node_Struct {
    Review rev;
    struct BST_Node_Struct *left;
    struct BST_Node_Struct *right;
} BST_Node;

// Function prototypes
BST_Node *new_BST_Node(void);
BST_Node *BST_insert(BST_Node *root, BST_Node *new_node);
BST_Node *BST_search(BST_Node *root, char name[MAX_STRING_LENGTH]);
BST_Node *BST_delete(BST_Node *root, char name[MAX_STRING_LENGTH]);
void inorder_traversal(BST_Node *root);

int main() {
    BST_Node *root = NULL;
    int choice;
    char name[MAX_STRING_LENGTH];
    BST_Node *new_node;
    BST_Node *found;

    while (1) {
        printf("\n====== Restaurant Review BST ======\n");
        printf("1. Insert Restaurant Review\n");
        printf("2. Search for a Restaurant\n");
        printf("3. Delete a Review\n");
        printf("4. Display All Reviews (In-order Traversal)\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline

        switch (choice) {
            case 1:
                new_node = new_BST_Node();
                printf("Enter restaurant name: ");
                fgets(new_node->rev.restaurant_name, MAX_STRING_LENGTH, stdin);
                new_node->rev.restaurant_name[strcspn(new_node->rev.restaurant_name, "\n")] = 0; // Remove newline
                
                printf("Enter restaurant address: ");
                fgets(new_node->rev.restaurant_address, MAX_STRING_LENGTH, stdin);
                new_node->rev.restaurant_address[strcspn(new_node->rev.restaurant_address, "\n")] = 0; // Remove newline

                printf("Enter review score: ");
                scanf("%d", &new_node->rev.score);
                getchar(); // Consume newline

                root = BST_insert(root, new_node);
                printf("Review added successfully!\n");
                break;

            case 2:
                printf("Enter restaurant name to search: ");
                fgets(name, MAX_STRING_LENGTH, stdin);
                name[strcspn(name, "\n")] = 0; // Remove newline

                found = BST_search(root, name);
                if (found) {
                    printf("Restaurant Found!\n");
                    printf("Name: %s\n", found->rev.restaurant_name);
                    printf("Address: %s\n", found->rev.restaurant_address);
                    printf("Score: %d\n", found->rev.score);
                } else {
                    printf("Restaurant not found.\n");
                }
                break;

            case 3:
                printf("Enter restaurant name to delete: ");
                fgets(name, MAX_STRING_LENGTH, stdin);
                name[strcspn(name, "\n")] = 0; // Remove newline

                root = BST_delete(root, name);
                printf("Review deleted successfully (if found).\n");
                break;

            case 4:
                printf("\nAll restaurant reviews (sorted by name):\n");
                inorder_traversal(root);
                break;

            case 5:
                printf("Exiting program...\n");
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}

// Function to create a new BST node
BST_Node *new_BST_Node(void) {
    BST_Node *new_node = (BST_Node *)calloc(1, sizeof(BST_Node));
    if (new_node == NULL) {
        printf("Error: Not enough memory to create a new node.\n");
        return NULL;
    }
    new_node->rev.score = -1;
    strcpy(new_node->rev.restaurant_name, "");
    strcpy(new_node->rev.restaurant_address, "");
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

// Function to insert a new node into the BST
BST_Node *BST_insert(BST_Node *root, BST_Node *new_node) {
    if (root == NULL)
        return new_node;

    if (strcmp(new_node->rev.restaurant_name, root->rev.restaurant_name) == 0) {
        printf("Duplicate restaurant name detected. Ignoring.\n");
        return root;
    }

    if (strcmp(new_node->rev.restaurant_name, root->rev.restaurant_name) < 0)
        root->left = BST_insert(root->left, new_node);
    else
        root->right = BST_insert(root->right, new_node);

    return root;
}

// Function to search for a restaurant review in BST
BST_Node *BST_search(BST_Node *root, char name[MAX_STRING_LENGTH]) {
    if (root == NULL)
        return NULL;

    if (strcmp(root->rev.restaurant_name, name) == 0)
        return root;

    if (strcmp(name, root->rev.restaurant_name) < 0)
        return BST_search(root->left, name);
    else
        return BST_search(root->right, name);
}

// Function to delete a restaurant review from BST
BST_Node *BST_delete(BST_Node *root, char name[MAX_STRING_LENGTH]) {
    if (root == NULL) return NULL;

    BST_Node *tmp;

    if (strcmp(name, root->rev.restaurant_name) == 0) {
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

            root->rev = tmp->rev;  // Copy successor's data to root
            root->right = BST_delete(root->right, tmp->rev.restaurant_name);  // Delete successor
            return root;
        }
    }

    if (strcmp(name, root->rev.restaurant_name) < 0)
        root->left = BST_delete(root->left, name);
    else
        root->right = BST_delete(root->right, name);

    return root;
}

// Function for in-order traversal of BST
void inorder_traversal(BST_Node *root) {
    if (root != NULL) {
        inorder_traversal(root->left);
        printf("Name: %s, Address: %s, Score: %d\n", root->rev.restaurant_name, root->rev.restaurant_address, root->rev.score);
        inorder_traversal(root->right);
    }
}
