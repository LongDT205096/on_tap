#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

typedef struct _rank{
    char team[10];
    int score;

    struct _rank* left;
    struct _rank* right;
} rank;

typedef rank *tree;

tree cre_node(char team[]){
    tree new = (rank*)malloc(sizeof(rank));
    strcpy(new->team,team);
    new->score = 0;
    new->left = NULL;
    new->right = NULL;
    return new;
}

tree add_node(tree *root, tree *new){
    if((*root) == NULL){
        (*root) = (*new);
    } else if(strcmp((*root)->team,(*new)->team) < 0){
        (*root)->right = add_node(&(*root)->right,&(*new));
    } else if(strcmp((*root)->team,(*new)->team) > 0){
        (*root)->left = add_node(&(*root)->left,&(*new));
    }
    return *root;
}

tree search(tree root, char team[]){
    if(root != NULL){
        if(strcmp(root->team,team) == 0) return root;
        else if (strcmp(root->team,team) < 0) return search(root->right,team);
        else if (strcmp(root->team,team) > 0) return search(root->left,team);
    }
}

tree function1(FILE *in, tree* root){
    (*root) = NULL;
    char line[256];

    while(fgets(line,256,in) != NULL){ 
        tree new1, new2;
        char team1[10], team2[10];
        int score1, score2;
        
        sscanf(line,"%s %s %d %d",team1,team2,&score1,&score2);

        new1 = search((*root),team1);
        new2 = search((*root),team2);

        if(new1 == NULL){
            new1 = cre_node(team1);
            (*root) = add_node(&(*root),&new1);
        }

        if(new2 == NULL){
            new2 = cre_node(team2);
            (*root) = add_node(&(*root),&new2);
        }

        if(score1 > score2) new1->score = new1->score + 3;
        else if(score1 < score2) new2->score = new2->score + 3;
        else if(score1 == score2){
            ++new1->score;
            ++new2->score;
        }
    }
    return *root;
}

void BST_InOrder(tree* Root) {
    if((*Root) != NULL) {
        BST_InOrder(&(*Root)->left);
        printf("%s %d\n", (*Root)->team,(*Root)->score);
        BST_InOrder(&(*Root)->right);
    }
}

void rewrite(FILE *in, tree *root){
    if((*root) != NULL){
        rewrite(in,&(*root)->left);
        fprintf(in,"%s %d\n",(*root)->team,(*root)->score);
        rewrite(in,&(*root)->right);
    }
}

void menu(){
    printf("1. Doc thong tin doi bong.\n");
    printf("2. In ra ket qua.\n");
    printf("3. Tim kiem doi bong.\n");
    printf("4. Hien thi cac doi xuong hang.\n");
    printf("5. Xuat file.\n\n");
}

int main(){
    FILE *in = fopen("bongda.txt","r");
    tree root = NULL;

    int option;

    do{
        menu();
        

        printf("Chon chuc nang: ");
        scanf("%d",&option);

        if(option == 1){
            printf("Lay thong tin doi bong.\n\n"); 
            function1(in,&root); 
        }
        if(option == 2){
            printf("Hien thi thong tin:\n"); 
            BST_InOrder(&root); 
            printf("\n");
        }
        if(option == 3){
            char team_find[10];
            tree check;

            printf("Tim kiem doi bong.\n");
            printf("Nhap ten doi bong: ");
            scanf("%s",team_find);
            check = search(root,team_find);
            if(check == NULL) printf("Khong tim thay doi bong.\n\n");
            else printf("%s %d\n\n",check->team,check->score);
        }
        if(option == 4){
       
        }
        if(option == 5){
            printf("Luu danh sach.\n");
            FILE *fo = fopen("ketqua.txt","w");
            rewrite(fo,&root);
            fclose(fo);
            printf("Luu thanh cong.\n");
        }
        
    }while(option < 6 && option > 0);

    fclose(in);
    exit(0);
}
