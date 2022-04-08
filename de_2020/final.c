#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

struct _Node{
    char place[40];
    int hour;
    int minute;
    struct _Node *next;
};

typedef struct _Node* Node;

Node create_log(char dest[], int hour, int minute){
    Node new = (Node)malloc(sizeof(struct _Node));
    new->next = NULL;
    strcpy(new->place,dest);
    new->hour = hour;
    new->minute = minute;
    return new;
}

Node add_log(Node root, Node add){
    if(root == NULL){
        root = add;
        return root;
    }

    Node cur = root;
    while(cur->next!= NULL){
        cur = cur->next;
    }
    cur->next = add;
    return root;
}

Node get_log(FILE *in){
    Node add, root = NULL;
    char str[50], dest[40];
    int hour, minute;

    while(fgets(str,50,in) != NULL){
        int i = 0;
        str[strlen(str) - 1] = '\0';
        char *s = strtok(str," ");
        while(s != NULL){
            if(i==0){
                strcpy(dest,s);
                //printf("%s ",dest);
            } else if(i==1){
                hour = atoi(s);
                //printf("%d ",hour);
            } else if(i==2){
                minute = atoi(s);
                //printf("%d\n",minute);
            }
            i++;
            s = strtok(NULL," ");
        }
        add = create_log(dest,hour,minute);
        root = add_log(root,add);
    }
    return root;
}

Node find_dest(Node root, char dest[]){
    Node p = root;
    Node add, q = NULL;

    while(p != NULL){
        if(strcmp(p->place,dest) == 0){
            add = create_log(p->place,p->hour,p->minute);
            q = add_log(q,add);
        }
        p = p->next;
    }
    return q;
}

void display_dest(Node root, char dest[]){
    Node q = find_dest(root,dest); 
    printf("%s\t",dest);
    if(q != NULL){
        while(q != NULL){
            printf("%d:%d ",q->hour,q->minute);
            if(q->next != NULL) printf(", ");
            q = q->next;
        }
    } else{
        printf("Ban khong toi dia diem nay");
    }
}

void find_time(Node root, int hour, int minute){
    Node p = root;
    Node q = NULL;
    printf("%d %d\t", hour, minute);
    while(p != NULL){
        if(p->hour == hour){
            if(p->minute == minute) 
                q = create_log(p->place,p->hour,p->minute);
        }
        p = p->next;
    }
    if(q != NULL){
        printf("%s",q->place);
    } else {
        printf("Khong tim thay lich su di chuyen");
    }

}

void check_COVID(Node root, char dest[], int hour, int minute){
    Node p = find_dest(root,dest);
    if(p == NULL){
        printf("lich su di chuyen an toan");
    } else{
        if(p->hour<hour){
            printf("lich su di chuyen an toan");
        } else{
            if(p->minute<minute){
                printf("Lich su di chuyen an toan");
            } else{
                printf("Ban co kha nang bi lay COVID, can phai khai bao y te ngay lap tuc");
            }
        }
    }
}

void traversing(Node root) {
    for(Node st = root; st != NULL; st = st->next) {
        printf("%50s%10d%10d\n", st->place, st->hour, st->minute);
    }
}

int main(){
    FILE *in;
    in = fopen("log.txt","r");
    Node root = get_log(in);
    fclose(in);

    traversing(root);

    printf("\n\n");
    
    char dest[40];
    printf("Nhap dia diem can kiem tra: ");
    scanf("%s",dest);
    display_dest(root,dest);

    printf("\n\n");
    int a,b;
    printf("Nhap thoi gian: ");
    scanf("%d %d",&a,&b);
    find_time(root,a,b);


    printf("\n\n");
    char place[40];
    int c,d;
    printf("Nhap dia diem da di chuyen: ");
    scanf("%s",place);
    printf("Nhap thoi gian duoc canh bao: ");
    scanf("%d %d",&c,&d);
    check_COVID(root,place,c,d);
}


