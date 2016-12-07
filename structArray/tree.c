//I need to finish complement
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct node
{
    int value;
    struct node *left;
    struct node *right;
}node;

node* min(node *);
node* insert(node *, int);
node* insertHelp1(int);
node* insertHelp2(node*, int);
void sorted(node *);
node* delete(node*, int);
int count(node*, int);
int search(node*, int);
int complement(node*, int);
node* table[10];

int main() {
    FILE *inputFile,*output;
    inputFile = fopen("./test2.txt", "r");
    output = fopen("./output.txt","w+");
    char command;
    int i, num, input;

    command = getc(inputFile);
    while(command != EOF) {
        if(command == 'I') {
            fscanf(inputFile,"(%d",&input);
            fprintf(output,"i ");
            table[input%10] = insert(table[input%10],input);
        }
        else if(command == 'D') {
            fscanf(inputFile,"(%d",&input);
            fprintf(output,"d ");
            table[input%10] = delete(table[input%10],input);
        }
        else if(command == 'M') {
            fscanf(inputFile,"(%d",&input);
            if(search(table[input%10],input)) fprintf(output,"yes ");
            else fprintf(output,"no ");
        }
        else if(command == 'S') {
            fscanf(inputFile,"(%d",&input);
            int result = 0;
            for(i = 0; i < 10; i++){
                result = complement(table[i%10],input);
                if(result != 0) {
                    fprintf(output,"yes ");
                    break;
                }
            }
            if(result == 0) fprintf(output,"no ");
        }
        else if(command == 'C') {
            fscanf(inputFile, "(%d", &input);
            int counter = 0;
            if(search(table[input%10],input)) counter = count(table[input%10],input);
            fprintf(output,"%d ",counter);
        }
        command = getc(inputFile);
    }
}

node* min(node *root) {
    node *curr = root;
    while(curr->left != NULL) {
        curr = curr->left;
    }
    return curr;
}

node* insert(node *root, int num) {
    if(root == NULL) return insertHelp1(num);
    else {
        if(num < root->value) root->left = insert(root->left, num);
        else if(num == root->value) root->left = insertHelp2(root->left,num);
        else root->right = insert(root->right, num);
        return root;
    }
}

node* insertHelp1(int num){
    node *new = malloc(sizeof(node));
    new->value = num;
    new->right = NULL;
    new->right = NULL;
    return new;
}

node* insertHelp2(node *child, int num) {
    node *new = malloc(sizeof(node));
    new->value = num;
    new->right = NULL;
    new->left = child;
    return new;
}

void sorted(node *root) {
    if(root != NULL)
    {
        printf("%d ",root->value);
        sorted(root->left);
        sorted(root->right);
    }
}

node* delete(node *root, int val) {
    if(root == NULL) return root;
    else if(val < root->value) root->left = delete(root->left,val);
    else if(val > root->value) root->right = delete(root->right,val);
    else {
        if(root->left == NULL && root->right != NULL) {
            node *temp = root->right;
            free(root);
            return temp;
        }
        else if(root->right == NULL && root->left != NULL) {
            node *temp = root->left;
            free(root);
            return root->left;
        }
        else if(root->right != NULL && root->left != NULL) {
            node *temp = min(root->right);
            root->value = temp->value;
            root->right = delete(root->right, temp->value);
            return root;
        }
        else return NULL;
    }
    return root;
}

int count(node *root, int val) {
    int counter = 0;
    if(root == NULL) return 0;
    else if(root->value == val) return counter = 1 + count(root->left,val);
    else if(root->value > val) return count(root->left,val);
    else if(root->value < val) return count(root->right,val);
    else return 0;
}

int search(node *root, int val) {
    if(root == NULL) return 0;
    else if(root->value == val) return 1;
    else if(root->value > val) return search(root->left,val);
    else if(root->value < val) return search(root->right,val);
    else return 0;
}

int complement(node *root, int goal) {
    if(root == NULL) return 0;
    else {
        int searchFor = goal-root->value;
        if(search(table[searchFor%10],searchFor)) return 1;
        else {
            complement(root->left,goal);
            complement(root->right,goal);
        }
    }
}
