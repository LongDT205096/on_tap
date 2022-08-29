#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

struct _tree{
    int A_num;
    char toys[20];
    struct _tree *left;
    struct _tree *right;
};

typedef struct _array{
    int B_num;
    char B_toys[20];
}B_toys;

typedef struct _tree* A_info;
B_toys B_info[5];

A_info cre_node(int A_num, char toys[]){
    A_info new = (A_info)malloc(sizeof(struct _tree));
    new->A_num = A_num;
    strcpy(new->toys,toys);
    new->left = NULL;
    new->right = NULL;
    return new;
}

A_info add_node(A_info root, int A_num, char toys[]){
    if(root == NULL){
        root = cre_node(A_num,toys);
    } else if(root->A_num < A_num){
        root->right = add_node(root->right,A_num,toys);
    } else if(root->A_num > A_num){
        root->left = add_node(root->left,A_num,toys);
    }
    return root;
}

A_info get_file_A(FILE *in){
    A_info add, root = NULL;
    root = NULL;
    char str[20], toys[20];
    int num;

    while(fgets(str,20,in) != NULL){
        int i=0;
        str[strlen(str)-1]='\0';
        char *s = strtok(str," ");
        while(i<2){
            if(i==0){
                num = atoi(s);
                printf("%d\t",num);
            } else if(i==1){
                if(s!=NULL){
                    strcpy(toys,s);
                    printf("%s\n",toys);
                } else{
                    printf("\nNhap ten do choi cho ma %d: ",num);
                    scanf("%s",toys);
                    printf("%d\t%s\n",num,toys);
                }
            }   
            i++;
            s = strtok(NULL," ");
        }
        add = cre_node(num,toys);
        root = add_node(root,num,toys);
    }
    return root;
}

void get_file_B(FILE *in){
    char str[20], toys[20];
    int num;
    int j=0;
    
    while(fgets(str,20,in) != NULL){
        int i=0;
        str[strlen(str)-1]='\0';
        char *s = strtok(str," ");
        while(i<2){
            if(i==0){
                num = atoi(s);
                printf("%d\t",num);
            } else if(i==1){
                if(s!=NULL){
                    strcpy(toys,s);
                    printf("%s\n",toys);
                } else{
                    printf("\nNhap ten do choi cho ma %d: ",num);
                    scanf("%s",toys);
                    printf("%d\t%s\n",num,toys);
                }
            }   
            i++;
            s = strtok(NULL," ");
        }
        B_info[j].B_num = num;
        strcpy(B_info[j].B_toys,toys);
        j++;
    }
}

A_info searching(A_info root,int num){
    if(root != NULL){
        if(num < root->A_num){
            root = searching(root->left,num);
        } else if(num > root->A_num){
            root = searching(root->right,num);
        }
    }
    return root;
}

void print_A(A_info root){
    if(root != NULL){
        print_A(root->left);
        printf("%d\t%s\n",root->A_num,root->toys);
        print_A(root->right);
    }
}

int main(){
    FILE *in = fopen("B.txt","r");
    get_file_B(in);
    printf("\n");

    for (int i = 0; i < 4; i++){
        printf("%d\t%s\n",B_info[i].B_num,B_info[i].B_toys);
    }
    
    fclose(in);
}