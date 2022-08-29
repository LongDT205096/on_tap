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

A_info cre_node(int A_num, char toys[20]){
    A_info new = (A_info)malloc(sizeof(struct _tree));
    new->A_num = A_num;
    strcpy(new->toys,toys);
    new->left = NULL;
    new->right = NULL;
    return new;
}

A_info add_node(A_info root, int A_num, char toys[20]){
    A_info add = cre_node(A_num,toys);
    if(root == NULL){
        root = add;
    } else if(root->A_num < add->A_num){
        add_node(root->right,A_num,toys);
    } else if(root->A_num > add->A_num){
        add_node(root->left,A_num,toys);
    }
    return root;
}

void get_info(FILE *in, char str[], char toys[], int num){
    while(fgets(str,20,in) != NULL){
        int i=0;
        str[strlen(str)-1]='\0';
        char *s = strtok(str," ");
        while(s != NULL){
            if(i==0){
                num = atoi(s);
                printf("%d\t",num);
            } else if(i==1){
                strcpy(toys,s);
                printf("%s",toys);
            }
            i++;
            s = strtok(NULL," ");
            
            if(toys == NULL){
                printf("Nhap ten do choi: ");
                scanf("%s",toys);
            }
        }
    }
}

A_info get_file_A(FILE *in){
    A_info add, root = NULL;
    char str[20], toys[20];
    int num;

    while(fgets(str,20,in) != NULL){
        int i=0;
        str[strlen(str)-1]='\0';
        char *s = strtok(str," ");
        while(s != NULL){
            if(i==0){
                num = atoi(s);
                printf("%d\t",num);
            } else if(i==1){
                strcpy(toys,s);
                printf("%s",toys);
            }
            i++;
            s = strtok(NULL," ");
            
            if(toys == NULL){
                printf("Nhap ten do choi: ");
                scanf("%s",toys);
            }
        }
        add = cre_node(num,toys);
        root = add_node(root,num,toys);
    }
    return root;
}

void get_file_B(FILE *in){

}


int main(){

}