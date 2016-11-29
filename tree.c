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
void insert(node **, int);
void sorted(node *);
node* pickTree(int);
node* delete(node*, int);
int search(node*, int);
int complement(node*, int);
node *t1,*t2,*t3,*t4,*t5,*t6,*t7,*t8,*t9,*t0;

int main()
{
    FILE *inputFile,*output;
    inputFile = fopen("./test2.txt", "r");
    output = fopen("./output.txt","w+");
    int arr[1000000], arr1[1000000];
    char command;
    int i, num, input;
    //initializing the each moded tree
    t0 = NULL;
    t1 = NULL;
    t2 = NULL;
    t3 = NULL;
    t4 = NULL;
    t5 = NULL;
    t6 = NULL;
    t7 = NULL;
    t8 = NULL;
    t9 = NULL;
    command = getc(inputFile);
    while(command != EOF) {
        if(command == 'I') {
            fscanf(inputFile,"(%d",&input);
            fprintf(output,"i ");
            switch(input % 10){
                case 0:
                    insert(&t0,input);
                    sorted(t0);
                    break;
                case 1:
                    insert(&t1,input);
                    sorted(t1);
                    break;
                case 2:
                    insert(&t2,input);
                    sorted(t2);
                    break;
                case 3:
                    insert(&t3,input);
                    sorted(t3);
                    break;
                case 4:
                    insert(&t4,input);
                    sorted(t4);
                    break;
                case 5:
                    insert(&t5,input);
                    sorted(t5);
                    break;
                case 6:
                    insert(&t6,input);
                    sorted(t6);
                    break;
                case 7:
                    insert(&t7,input);
                    sorted(t7);
                    break;
                case 8:
                    insert(&t8,input);
                    sorted(t8);
                    break;
                case 9:
                    insert(&t9,input);
                    sorted(t9);
                    break;
                default: break;
            }
        }
        else if(command == 'D') {
            fscanf(inputFile,"(%d",&input);
            fprintf(output,"d ");
            delete(pickTree(input),input);
        }
        else if(command == 'M') {
            fscanf(inputFile,"(%d",&input);
            if(search(pickTree(input),input)) fprintf(output,"yes ");
            else fprintf(output,"no ");
        }
        else if(command == 'S') {
            fscanf(inputFile,"(%d",&input);
            int result = 0;
            for(i = 0; i < 10; i++){
                result = complement(pickTree(i),input);
                if(result != 0) {
                    fprintf(output,"yes ");
                    break;
                }
            }
            if(result == 0) fprintf(output,"no ");
        }
        else if(command == 'C') {
            fscanf(inputFile, "(%d", &input);
            int count = 0;
            while(search(pickTree(input),input)){
                count++;
                delete(pickTree(input),input);
            }
            fprintf(output,"%d ",count);
            node **ptr;
            node *tmp;
            tmp = pickTree(input);
            ptr = &tmp;
            for(count;count>0;count--){
                insert(ptr,input);
            }
        }
        command = getc(inputFile);
    }
}

node* min(node *root) {
    node *curr = root;
    while(curr->left != NULL){
        curr = curr->left;
    }
    return curr;
}

void insert(node **root, int num1) {
    if(*root == NULL)
    {
        *root = malloc(sizeof(node));

       (*root)->right = NULL;
       (*root)->value = num1;
       (*root)->right = NULL;
    }
    else
    {
        if(num1 <(*root)->value)
            insert(&((*root)->left), num1);
        else
            insert(&((*root)->right), num1);
    }
}

void sorted(node *root) {
    if(root != NULL)
    {
        sorted(root->left);
        sorted(root->right);
    }
}

node* pickTree(int val){
    switch(val % 10){
        case 0:
            return t0;
            break;
        case 1:
            return t1;
            break;
        case 2:
            return t2;
            break;
        case 3:
            return t3;
            break;
        case 4:
            return t4;
            break;
        case 5:
            return t5;
            break;
        case 6:
            return t6;
            break;
        case 7:
            return t7;
            break;
        case 8:
            return t8;
            break;
        case 9:
            return t9;
            break;
    }
}

node* delete(node *root, int val) {
    if(root == NULL) return root;
    if(val < root->value) root->left = delete(root->left,val);
    else if(val > root->value) root->right = delete(root->right,val);
    else {
        if(root->left == NULL) {
            node *temp = root->right;
            free(root);
            return temp;
        }
        else if(root->right == NULL) {
            node *temp = root->left;
            free(root);
            return temp;
        }
        node *temp = min(root->right);
        root->value = temp->value;
        root->right = delete(root->right, temp->value);
    }
    return root;
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
        if(search(pickTree(searchFor),searchFor)) return 1;
        else {
            complement(root->left,goal);
            complement(root->right,goal);
        }
    }
}

//int complement()
