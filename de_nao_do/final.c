#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

int ram[] = {1,2,4,8,16,32};
typedef struct _computer{
    char cpu[3];
} computer;

computer CPU[4] = {{"I3"},
                   {"I5"},
                   {"I7"},
                   {"I9"}};

typedef struct _list{
    char name[3];
    int id;
    int ram;

    struct _list *next;
} list;

typedef list* info;

info cre_node(char name[], int id, int ram){
    info new = (list*)malloc(sizeof(list));
    strcpy(new->name,name);
    new->id = id;
    new->ram = ram;
    new->next = NULL;
    return new;
}

info add_node(info *root, info *new){
    info p;

    if((*root) == NULL){
        (*root) = (*new);
    } else{
        p = (*root);
        while(p->next != NULL){
            p = p->next;
        }
        p->next = (*new);
    }
    return *root;
}

void show_list(info *root){
    info p = *root;

    printf("Danh sach day du:\n");
    if((*root) != NULL){
        while(p != NULL){
            printf("%d. %s %d\n",p->id,p->name,p->ram);
            p = p->next;
        }
    }
}

static int id = 1;
info get_info(FILE *in, info *root){
    int n;
    fscanf(in,"%d",&n);

    char name[3];
    int ram;

    info new;;
    
    for(int i=1; i<=n; i++){
        fscanf(in,"%s %d",name,&ram);
        new = cre_node(name,id,ram);
        *root = add_node(&(*root),&new);
        id++;
        if(id == 21){
            printf("Danh sach da day"); 
            break;
        }
    }

    return *root;
}

void menu(){
    printf("1. Load data files:\n");
    printf("2. Update CPU info:\n");
    printf("3. Update RAM info:\n");
    printf("4. Search:\n");
    printf("5. Quit.\n");
}

void function1(FILE *in, info *root){
    char a[10];
    (*root) = NULL;
    int n;
    printf("Nhap so file can nhap: ");
    scanf("%d",&n);
    
    for(int i=1; i<=n; i++){
        printf("Nhap ten file: ");
        scanf("%s",a);
        in = fopen(a,"r");
        if(in == NULL){
            printf("File khong ton tai.\n");
        } else{
            (*root) = get_info(in,&(*root));
        }
        fclose(in);
    }   
    printf("\n");
    show_list(&(*root));
    printf("\n\n");
}

int check_CPU(char update[]){
    int i;
    for(i=0; i<4; i++){
        if(strcmp(update,CPU[i].cpu) == 0){
            return 1;
        }
    }
    return 0;
}

void function2(info *root){
    char n[5];
    char opt[] = {"STOP"};

    printf("\nNhap ID may can update: ");

    do{
        scanf("%s",n);
        if(atoi(n) > id) printf("ID sai.\n");  
    } while(atoi(n) > id && strcmp(n,opt) != 0);

    if(strcmp(n,opt) == 0) return;
    else{
        info p = (*root);
        while (p->id != atoi(n)){
            p = p->next;
        }

        char update[5];
        
        do{
            printf("Cap nhat ten CPU cua may %d: ",p->id);
            scanf("%s",update);
            if(strcmp(update,opt) == 0) break;
            else if(check_CPU(update) == 0) printf("Ten khong hop le.\n");
            else if(check_CPU(update) == 1){
                strcpy(p->name,update);
                p = p->next;
            }
        } while(p != NULL);
    }

    show_list(&(*root));
    printf("\n\n");
}

int check_RAM(char update[]){
    int i;
    for(i = 0; i<6; i++){
        if(atoi(update) == ram[i]){
            return 1;
        }
    }
    return 0;
}

void function3(info *root){
    char n[5];
    char opt[] = {"STOP"};

    printf("\nNhap ID may can update: ");

    do{
        scanf("%s",n);
        if(atoi(n) > id) printf("ID sai.\n");  
    } while(atoi(n) > id && strcmp(n,opt) != 0);

    if(strcmp(n,opt) == 0) return;
    else{
        info p = (*root);
        while (p->id != atoi(n)){
            p = p->next;
        }

        char update[5];
        
        do{
            printf("Cap nhat ten CPU cua may %d: ",p->id);
            scanf("%s",update);
            if(strcmp(update,opt) == 0) break;
            else if(check_RAM(update) == 0) printf("Ten khong hop le.\n");
            else if(check_RAM(update) == 1){
                p->ram = atoi(update);
                p = p->next;
            }
        } while(p != NULL);
    }

    show_list(&(*root));
    printf("\n\n");
}

void function4(info *root){
    char search[3];
    char opt[] = {"STOP"};
    info p = (*root);

    printf("\nNhap ten CPU hoac so RAM can tim: ");
    scanf("%s",search);
    
    if(check_RAM(search) == 1){
        printf("Tim may co so Ram la %d:\n",atoi(search));
        do{
            if(p->ram == atoi(search)) printf("%d. %s %d\n",p->id,p->name,p->ram);
            p = p->next;
        } while (p != NULL);
    } else if(check_CPU(search) == 1){
        do{
            if(strcmp(p->name,search) == 0) printf("%d. %s %d\n",p->id,p->name,p->ram);
            p = p->next;
        } while (p != NULL);    
    } else printf("Gia tri khong hop le\n");
    printf("\n\n");
}

int main(){
    info root = NULL;
    int option;
    FILE *in;

    do {
        menu();
        printf("\n>> ");
        scanf("%d", &option);
        if(option < 1 || option > 5) {
            printf("[ERROR] Chuc nang khong hop le. Hay nhap lai\n");
            continue;
        }

        if(option == 1) function1(in,&root);
        if(option == 2) function2(&root);
        if(option == 3) function3(&root);
        if(option == 4) function4(&root);
        if(option == 5){
            fflush(stdin);
            printf("Dinh Thanh Long 20205096\n");
            printf("Ban da thoat chuong trinh\n");
            exit(0);
        }
    } while(option != 5);
}