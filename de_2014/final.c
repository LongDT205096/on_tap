#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

typedef struct _info{
    char user[20];
    char pass[20];
    float score;

    struct _info* left;
    struct _info* right;
} info;

typedef info *tree;

tree cre_node(char user[], char pass[], float score){
    tree new = (info*)malloc(sizeof(info));
    strcpy(new->user,user);
    strcpy(new->pass,pass);
    new->score = score;
    new->left = NULL;
    new->right = NULL;
    return new; 
}

tree add_node(tree* root, tree* new){
    if((*root) == NULL){
        (*root) = (*new);
    } else if(strcmp((*root)->user,(*new)->user) < 0){
        (*root)->right = add_node(&(*root)->right,&(*new));
    } else if(strcmp((*root)->user,(*new)->user) > 0){
        (*root)->left = add_node(&(*root)->left,&(*new));
    }
    return *root;
}

tree search(tree root, char user[]){
    if(root == NULL){
        return NULL;
    } else if(strcmp(root->user,user) == 0){
        return root;
    } else if(strcmp(root->user,user) < 0){
        return search(root->right,user);
    } else if(strcmp(root->user,user) > 0){
        return search(root->left,user);
    }
}

tree get_info(FILE *in){
    tree root = NULL, new;
    char user[20], pass[20];
    float score;
    char str[100];

    while (fgets(str,100,in) != NULL){
        int check = 0;
        str[strlen(str) - 1] = '\0';
        char *s = strtok(str," ");
        
        while(s != NULL){
            if(check == 0){
                strcpy(user,s);
                printf("%s\t",user);
            } else if(check == 1){
                strcpy(pass,s);
                printf("%s\t",pass);
            } else if(check == 2){
                score = atof(s);
                printf("%.1lf\n",score);
            }
            check++;
            s = strtok(NULL," ");
        }
    new = cre_node(user,pass,score);
    root = add_node(&root,&new);
    }
    return root;
}

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


int main(){
    FILE *in = fopen("sinhvien.txt","r");
    tree tmp, new;
    tree root = get_info(in);
    fclose(in);

    int option;
    do{
        main_menu();
        printf("\nChon chuc nang: ");
        scanf("%d",&option);

        if (option == 1){
            char username[20];
            char role[20] = "Admin";

            do{
                printf("\nNhap ten dang nhap: ");
                scanf("%s",username);
                tmp = search(root,username);
            } while(tmp == NULL);  

            login(&tmp);
        
            if(strcmp(username,role) != 0){
                menuSV();
                int opt_SV;

                do{ 
                    printf("\nChon chuc nang: ");
                    scanf("%d",&opt_SV);
                    if(opt_SV < 1 || opt_SV > 3) {
                        printf("[Error] Vui long nhap dung chuc nang.\n");
                        continue;
                    }

                    if(opt_SV == 1){
                        printf("Chuc nang xem diem cua sinh vien.\n");
                        printf("So diem: %.lf\n",tmp->score); 
                        fflush(stdin);
                    }
                    if(opt_SV == 2){
                        printf("Chuc nang thay doi mat khau.\n");
                        func_SV_2(&root,&tmp); 
                        fflush(stdin);
                    }
                    if(opt_SV == 3){
                        printf("Tien hanh luu danh sach.\n");
                        in = fopen("sinhvien.txt","w");
                        func_SV_3(in,&root); 
                        printf("Luu thanh cong.\n");
                        fclose(in);
                    }
                } while(opt_SV != 3);
            }

            if(strcmp(username,role) == 0){
                menuPT();
                int opt_PT;

                do{
                    printf("\nChon chuc nang: ");
                    scanf("%d",&opt_PT);
                    if(opt_PT < 1 || opt_PT > 4) {
                        printf("[Error] Vui long nhap dung chuc nang.\n");
                        continue;
                    }

                    if(opt_PT == 1){
                        printf("Xac nhan chuc nang them sinh vien.\n");
                        func_PT_1(&root,&new);
                        fflush(stdin);
                    }
                    if(opt_PT == 2){
                        printf("Xac nhan chuc nang in danh sach.\n");
                        func_PT_2(&root);
                        fflush(stdin);
                    }
                    if(opt_PT == 3){

                    }
                    if(opt_PT == 4){
                        printf("Tien hanh luu danh sach.\n");
                        in = fopen("sinhvien.txt","w");
                        func_SV_3(in,&root); 
                        printf("Luu thanh cong.\n");
                        fclose(in);
                    }
                } while(opt_PT != 4); 
            }
        } 
    
        if(option == 2){
            printf("Ban da thoat chuong trinh.");
            exit(0);
        }
    } while(option < 2 && option > 0);
}