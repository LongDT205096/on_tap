#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include"function.h"

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
            } else if(check == 1){
                strcpy(pass,s);
            } else if(check == 2){
                score = atof(s);
            }
            check++;
            s = strtok(NULL," ");
        }
    new = cre_node(user,pass,score);
    root = add_node(&root,&new);
    }
    return root;
}


tree LeftMostValue(tree* root){
    while ((*root)->left != NULL)
        (*root) = (*root)->left;
    return *root;
}

tree delete(tree *root, char user_del[]){
    if((*root) == NULL) 
        return *root;
    if(strcmp((*root)->user, user_del) > 0)
        (*root)->left = delete(&(*root)->left, user_del);
    else if (strcmp((*root)->user, user_del) < 0)
        (*root)->right = delete(&(*root)->right, user_del);
    else{
        if((*root)->left == NULL){
            tree new = (*root)->right;
            free((*root));
            return new;
        }

        if((*root)->right == NULL){
            tree new = (*root)->left;
            free((*root));
            return new;
        }

        tree p = LeftMostValue(&(*root)->right);
        strcpy((*root)->user, p->user);
        (*root)->right = delete(&(*root)->right, (*root)->user);
    }
    return *root;
}