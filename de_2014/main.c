#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include"function.h"

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
                    else if(opt_SV == 2){
                        printf("Chuc nang thay doi mat khau.\n");
                        func_SV_2(&root,&tmp); 
                        fflush(stdin);
                    }
                    else if(opt_SV == 3){
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
                    else if(opt_PT == 2){
                        printf("Xac nhan chuc nang in danh sach.\n");
                        func_PT_2(&root);
                        fflush(stdin);
                    }
                    else if(opt_PT == 3){
                        char user_del[20];
                        printf("Nhap ten sinh vien can xoa: ");
                        scanf("%s", user_del);
                        tmp = search(root, user_del);

                        if(tmp == NULL){
                            printf("Khong tim thay sinh vien.\n");
                            continue;
                        }
                        printf("%s\n", tmp->user);
                        printf("%s\n", tmp->pass);
                        printf("%.1f\n",tmp->score);
                        root = delete(&root, user_del);
                        printf("\nXoa thanh cong\n");
                    }
                    else if(opt_PT == 4){
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
