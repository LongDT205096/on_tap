#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include"function.h"

void menuSV(){
    printf("1. Xem diem.\n");
    printf("2. Doi pass.\n");
    printf("3. Luu thong tin.\n");
}

void menuPT(){
    printf("1. Them SV.\n");
    printf("2. In danh sach.\n");
    printf("3. Xoa SV.\n");
    printf("4. Luu thong tin.\n");
}

void main_menu(){
    printf("\n1. Dang nhap\n");
    printf("2. Thoat.\n");
}

void login(tree *tmp){
    char password[20];
        
    int check = 0;
    if(tmp != NULL){
        do{
            printf("Nhap mat khau: ");
            scanf("%s",password);
            if(strcmp((*tmp)->pass,password) != 0) check++;
        } while(strcmp((*tmp)->pass,password) != 0 && check < 3);
    }
    if(check == 3){
        printf("Nhap sai qua 3 lan.");
        exit(0);
    }

    printf("Dang nhap thanh cong.\n\n");
}

void func_SV_2(tree *root, tree *tmp){
    char pass_new[20];
    char pass_check[20];

    printf("\nNhap mat khau moi: ");
    scanf("%s",pass_new);
    printf("Xac nhan lai mat khau: ");
    do{
        scanf("%s",pass_check);
    } while(strcmp(pass_check,pass_new) != 0);

    strcpy((*tmp)->pass,pass_new);
    printf("Doi mat khau thanh cong.\n");
}

void func_SV_3(FILE *in, tree *root){
    if((*root)!=NULL){
        func_SV_3(in,&(*root)->left);
        fprintf(in,"%s %s %.1lf\n",(*root)->user,(*root)->pass,(*root)->score);
        func_SV_3(in,&(*root)->right);
    }
}

void func_PT_1(tree *root, tree *new){
    char user[20];
    char pass[20];
    float score;
    

    printf("\nNhap ten dang nhap: ");
    scanf("%s",user);
    printf("Nhap mat khau: ");
    scanf("%s",pass);
    printf("Nhap diem: ");
    scanf("%f",&score);

    tree check = search((*root),user);
    if(check != NULL){
        printf("Ten dang nhap da ton tai.\n");
        return;
    }

    *new = cre_node(user,pass,score);
    (*root) = add_node(&(*root),&(*new));
    
    printf("Them sinh vien thanh cong.\n");
}

void func_PT_2(tree *root){
    if((*root) != NULL){
        func_PT_2(&(*root)->left);
        printf("%s %s %.1lf\n",(*root)->user,(*root)->pass,(*root)->score);
        func_PT_2(&(*root)->right);
    }
}