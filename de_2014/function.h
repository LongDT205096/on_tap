#ifndef function
#define function

typedef struct _info{
    char user[20];
    char pass[20];
    float score;

    struct _info* left;
    struct _info* right;
} info;
typedef info *tree;
tree cre_node(char user[], char pass[], float score);
tree add_node(tree* root, tree* new);
tree search(tree root, char user[]);
tree get_info(FILE *in);


void menuSV();
void menuPT();
void main_menu();
void login(tree *tmp);
void func_SV_2(tree *root, tree *tmp);
void func_SV_3(FILE *in, tree *root);
void func_PT_1(tree *root, tree *new);
void func_PT_2(tree *root);

void SV_programs(char username[], char role[]);
void PT_programs(char username[], char role[]);

#endif