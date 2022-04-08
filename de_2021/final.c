#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

typedef struct _Stock{
    char code[4];
    double open[30];
    double close[30];
    double avg[30];
    int day_up;
} Stock;

typedef Stock ElementType;

typedef struct _Node{
    ElementType key;

    struct _Node *right, *left;
} Node;

typedef Node* tree;

tree insert(tree* root, ElementType X){
    if((*root) == NULL){
        *root = (Node*)malloc(sizeof(Node));
        (*root)->key = X;
        (*root)->left = NULL;
        (*root)->right = NULL;
    } else if(strcmp(((*root)->key).code, X.code) < 0){
        (*root)->right = insert(&(*root)->right, X);
    } else if(strcmp(((*root)->key).code, X.code) > 0){
        (*root)->left = insert(&(*root)->left, X);
    }
    return *root;
}

tree BST_search(tree root, ElementType X){
    if(root == NULL) return NULL;
    else if(strcmp((root->key).code, X.code) == 0 ) return root;
    else if(strcmp((root->key).code, X.code) < 0 ){
        return BST_search(root->right, X);
    } else{
        return BST_search(root->left, X);
    }
}

void inOrder(tree root, int n){
    if(root != NULL){
        double sum = 0;
        inOrder(root->left,n);
        for(int i = 1; i <= n; i++){
            sum += (root->key).avg[i]; 
        }
        printf("%s     %.3lf\n",root->key.code,sum/n);
        inOrder(root->right,n);
    }
}

void function1(tree* root){
    *root = NULL;
    FILE *in = fopen("data.txt","r");
    int days = 10;
    int count;
    fscanf(in,"%d",&count);
    tree search;
    
    for(int i = 0; i < days; i++){
        for(int j = 0; j < count; j++){
            Stock tmp;
            double open, close, avg;
            avg = close - open;

            fscanf(in,"%s %lf %lf",tmp.code,&open,&close);

            search = BST_search(*root,tmp);
            if(search == NULL){
                tmp.open[i] = open;
                tmp.close[i] = close;
                tmp.avg[i] = avg;
                tmp.day_up = 0;

                *root = insert(root,tmp);
            } else{
                (search->key).open[i] = open;
                (search->key).close[i] = close;
                (search->key).avg[i] = avg;
                (search->key).day_up = 0;
            }
        }
    }
    printf("ma CK   gia tri TB\n");
    inOrder(*root,days);
    fclose(in);
}

void function2(tree* root){
    Stock check;
    printf("Nhap ma co phieu can kiem tra: ");
    scanf("%s",check.code);
    tree found = BST_search(*root,check);
    if(found == NULL) printf("Ma co phieu khong ton tai.\n");
    else{
        double max, min;
        max = found->key.close[0];
        min = max;
        for(int i = 1; i<10; i++){
            if(min > found->key.close[i]) min = found->key.close[i];
            if(max < found->key.close[i]) max = found->key.close[i];
        }
        printf("Gia co phieu be nhat: %.3lf\n",min);
        printf("Gia co phieu lon nhat: %.3lf\n",max);
    }
}
 
void function3(tree* root){
    if((*root) != NULL){
        function3(&((*root)->left));
        if((*root)->key.close[0] - (*root)->key.open[0] > 0){
            if((*root)->key.close[1] - (*root)->key.open[1] > 0){
                for(int i = 0; i<=1; i++){
                    printf("%s %.3lf %.3lf\n",(*root)->key.code,(*root)->key.open[i],(*root)->key.close[i]);
                }
            }  
        }
        function3(&((*root)->right));
    } 
}

void check_day_up(tree* root, int* max){
    if ((*root)!=NULL){
        check_day_up(&((*root)->left),&(*max));
        if(*max == (*root)->key.day_up){
            printf("%s\t%d\n",(*root)->key.code,(*root)->key.day_up);
        }
        check_day_up(&((*root)->right),&(*max));
    }    
}

void function4(tree* root, int* max){
    if((*root) != NULL){
        function4(&((*root)->left),&(*max));
        for(int i=0; i < 10; i++){
            if((*root)->key.close[i] - (*root)->key.open[i] > 0){
                (*root)->key.day_up++;
            }
        }
        if(*max < (*root)->key.day_up) *max = (*root)->key.day_up;
        function4(&((*root)->right),&(*max));   
    }
}

void menu(){
    printf("1. Doc thong tin chung khoan.\n");
    printf("2. Tim kiem theo ma chung khoan.\n");
    printf("3. Tim kiem nhung ma chung khoan co xu huong tang.\n");
    printf("4. Tim ma co so ngay tang lon nhat.\n");
    printf("5. Thoat chuong trinh.\n");
}

int main(){
    menu();
    tree root = NULL;
    int option, max = 0;
    do {
        printf("\n>> ");
        scanf("%d", &option);
        if(option < 1 || option > 5) {
            printf("[ERROR] Chuc nang khong hop le. Hay nhap lai\n");
            continue;
        }
        if(option == 1){
            function1(&root);
        }
        if(option == 2){
            function2(&root);
        }
        if(option == 3){
            function3(&root);
        }
        if(option == 4){
            function4(&root,&max);
            check_day_up(&root,&max);
            //printf("%d\n",max);
        }
        if(option == 5){
            fflush(stdin);
            printf("Dinh Thanh Long 20205096\n");
            printf("Ban da thoat chuong trinh\n");
            exit(0);
        }
    } while(option != 5);   
}
