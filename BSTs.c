


#include<stdio.h>
#include<stdlib.h>
#include"NoteSynth.c"

typedef struct BST_Node_Struct
{


    double key;
    double freq;
    int bar;
    double index;

    struct BST_Node_Struct *left, *right;
  
} BST_Node;

BST_Node *newBST_Node(double freq, int bar, double index)
{

        
     BST_Node *node = (BST_Node *)malloc(sizeof(BST_Node));
     if (!node) return NULL;
     node->freq = freq;
     node->bar = bar;
     node->index = index;
     node->key = (10.0 * bar) + index;
     node->left = node->right = NULL;
     return node;
}

BST_Node *BST_insert(BST_Node *root, BST_Node *new_node)
{
    

     if (!root) return new_node;
     if (new_node->key < root->key)
         root->left = BST_insert(root->left, new_node);
     else if (new_node->key > root->key)
         root->right = BST_insert(root->right, new_node);
     else
         printf("Duplicate node requested (bar:index)=%d,%lf, it was ignored\n", new_node->bar, new_node->index);
     return root;
}

BST_Node *BST_search(BST_Node *root, int bar, double index)
{
    

     double key = (10.0 * bar) + index;
     while (root)
     {
         if (key < root->key)
             root = root->left;
         else if (key > root->key)
             root = root->right;
         else
             return root;
     }
     return NULL;
}

BST_Node *find_successor(BST_Node *right_child_node)
{
    

    while (right_child_node && right_child_node->left)
    right_child_node = right_child_node->left;
    return right_child_node;
    
}

BST_Node *BST_delete(BST_Node *root, int bar, double index)
{
    
    
     if (!root) return NULL;
     double key = (10.0 * bar) + index;
     if (key < root->key)
         root->left = BST_delete(root->left, bar, index);
     else if (key > root->key)
         root->right = BST_delete(root->right, bar, index);
     else
     {
         if (!root->left)
         {
             BST_Node *temp = root->right;
             free(root);
             return temp;
         }
         else if (!root->right)
         {
             BST_Node *temp = root->left;
             free(root);
             return temp;
         }
         BST_Node *temp = find_successor(root->right);
         root->key = temp->key;
         root->freq = temp->freq;
         root->bar = temp->bar;
         root->index = temp->index;
         root->right = BST_delete(root->right, temp->bar, temp->index);
     }
     return root;
}

void BST_makePlayList(BST_Node *root)
{
    
    if (root == NULL) {
        return; 
    }

    
    BST_makePlayList(root->left);

    playlist_head = playlist_insert(playlist_head, root->freq, root->bar, root->index);

    BST_makePlayList(root->right);

}

void BST_inOrder(BST_Node *root, int depth)
{
   
    
   
     if (!root) return;
     BST_inOrder(root->left, depth + 1);
     printf("Depth=%d, Bar:Index (%d:%f), F=%f Hz\n", depth, root->bar, root->index, root->freq);
     BST_inOrder(root->right, depth + 1);

} 

void BST_preOrder(BST_Node *root, int depth)
{
    
    if (root == NULL) {
        return; 
    }

    
    printf("Depth=%d, Bar:Index (%d:%f), F=%f Hz\n", depth, root->bar, root->index, root->freq);

    
    BST_preOrder(root->left, depth + 1);

    
    BST_preOrder(root->right, depth + 1);

}

void BST_postOrder(BST_Node *root,int depth)
{
    
    if (root == NULL) {
        return; 
    }

    
    BST_postOrder(root->left, depth + 1);

    
    BST_postOrder(root->right, depth + 1);

 
    printf("Depth=%d, Bar:Index (%d:%f), F=%f Hz\n", depth, root->bar, root->index, root->freq);

} 

void delete_BST(BST_Node *root)
{
    
    if (!root) return;
    delete_BST(root->left);
    delete_BST(root->right);
    free(root);

}


int findMinBar(BST_Node *root) {
    if (!root) return __INT_MAX__;
    int leftMin = findMinBar(root->left);
    return (root->bar < leftMin) ? root->bar : leftMin;
}


int findMaxBar(BST_Node *root) {
    if (!root) return 0;
    int rightMax = findMaxBar(root->right);
    return (root->bar > rightMax) ? root->bar : rightMax;
}


BST_Node *insertBST(BST_Node *root, int bar, float index, float freq) {
    if (!root) {
        BST_Node *newNode = (BST_Node *)malloc(sizeof(BST_Node));
        newNode->bar = bar;
        newNode->index = index;
        newNode->freq = freq;
        newNode->left = newNode->right = NULL;
        return newNode;
    }
    if (bar < root->bar || (bar == root->bar && index < root->index))
        root->left = insertBST(root->left, bar, index, freq);
    else
        root->right = insertBST(root->right, bar, index, freq);
    return root;
}

void reverseAndRebuild(BST_Node *root, BST_Node **newRoot, int maxBar, int minBar) {
    if (!root) return;

    
    int new_bar = maxBar - (root->bar - minBar);
    float new_index = 1.0 - root->index;

    
    *newRoot = insertBST(*newRoot, new_bar, new_index, root->freq);

    
    reverseAndRebuild(root->left, newRoot, maxBar, minBar);
    reverseAndRebuild(root->right, newRoot, maxBar, minBar);
}

BST_Node *reverseSong(BST_Node *root)
{
    
    
    
    if (!root) return NULL;

    
    int minBar = findMinBar(root);
    int maxBar = findMaxBar(root);

    
    BST_Node *newRoot = NULL;
    reverseAndRebuild(root, &newRoot, maxBar, minBar);

    return newRoot;

}



 BST_Node *BST_harmonize_helper(BST_Node *root, BST_Node *new_root, int semitones, double time_shift) {
    if (!root) return new_root; 

    
    BST_Node *original_node = newBST_Node(root->freq, root->bar, root->index);
    new_root = BST_insert(new_root, original_node);

    
    int original_index = -1;
    for (int i = 0; i < 100; i++) {
        if (note_freq[i] == root->freq) {
            original_index = i;
            break;
        }
    }

    
    if (original_index != -1) {
        int new_index = original_index + semitones;

        
        if (new_index >= 0 && new_index < 100) {
            double new_freq = note_freq[new_index];
            double new_time_index = root->index + time_shift;

            
            if (new_time_index >= 0 && new_time_index < 1) {
                BST_Node *new_node = newBST_Node(new_freq, root->bar, new_time_index);
                new_root = BST_insert(new_root, new_node);
            }
        }
    }

    
    new_root = BST_harmonize_helper(root->left, new_root, semitones, time_shift);
    new_root = BST_harmonize_helper(root->right, new_root, semitones, time_shift);

    return new_root;
}


BST_Node *BST_harmonize(BST_Node *root, int semitones, double time_shift)
{
    
    
    BST_Node *new_root = NULL;
    return BST_harmonize_helper(root, new_root, semitones, time_shift);

}
