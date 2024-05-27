#include "tree.h"

tree *insert_in_tree(tree *node, team *team)
{
    if(node==NULL)
    {
        tree *node=(tree*)malloc(sizeof(tree));
        node->teams=team;
        node->left=node->right=NULL;
        return node;
    }
    if(team->points<node->teams->points)
        node->left=insert_in_tree(node->left, team);
    else if(team->points>node->teams->points)
        node->right=insert_in_tree(node->right, team);
    else if(strcmp(node->teams->name, team->name)<0)
        node->right=insert_in_tree(node->right, team);
    else
        node->left=insert_in_tree(node->left, team);
    return node;

}

void printf_drs(tree *root, FILE *r_file, team **best8)
{
    if(root)
    {
        printf_drs(root->right, r_file, best8);
        fprintf(r_file, "%s", root->teams->name); ///afisez numele echipei si punctajul
        int contor=34-strlen(root->teams->name); 
        while(contor)
            fprintf(r_file, " "), contor--;
        fprintf(r_file, "-  ");
        fprintf(r_file, "%.2f\n", root->teams->points);
        if((*best8)==NULL)///aici creez noua lista a celor mai buni 8, dar ordonata
         {
            (*best8)=root->teams;
            (*best8)->next=NULL;
         }  
         else
         {
            team* auxiliar=(*best8);
            //int verif=1;
            while(auxiliar->next!=NULL)
                auxiliar=auxiliar->next;
            auxiliar->next=root->teams;
            root->teams->next=NULL;
         } 
        printf_drs(root->left, r_file, best8);
    }
}

int node_height(avl_tree *root)
{
    if(root==NULL)
        return -1;
     return root->height;
}

avl_tree *right_rotation(avl_tree *middle)
{
    avl_tree *left=middle->left;
    avl_tree *right=left->right;
    left->right=middle;
    middle->left=right;
    middle->height=maxx(node_height(middle->left), node_height(middle->right))+1;
    left->height=maxx(node_height(left->left), node_height(left->right))+1;
    return left;
}

avl_tree *left_rotation(avl_tree *middle)
{
    avl_tree *right=middle->right;
    avl_tree *left=right->left;
    right->left=middle;
    middle->right=left;
    middle->height=maxx(node_height(middle->left), node_height(middle->right))+1;
    right->height=maxx(node_height(right->left), node_height(right->right))+1;
    return right;
}

avl_tree* lrr_rotation(avl_tree *middle)
{
    middle->left=left_rotation(middle->left);
    return right_rotation(middle);
}

avl_tree* rlr_rotation(avl_tree *middle)
{
    middle->right=right_rotation(middle->right);
    return left_rotation(middle);
}

avl_tree* insert_avl(avl_tree *root, team *team)
{
    if(root==NULL)
    {
        root=(avl_tree*)malloc(sizeof(avl_tree));
        root->teams=team;
        root->height=0;
        root->left=root->right=NULL;
        return root;
    }

     if(team->points<root->teams->points) ///aici daca e mai mic punem in stanga si daca e mai mare punem in dreapta
        root->left=insert_avl(root->left, team);
    else if(team->points>root->teams->points)
        root->right=insert_avl(root->right, team);
    else
    {
        if(strcmp(root->teams->name, team->name)>0)
            root->left=insert_avl(root->left, team);
        else if (strcmp(root->teams->name, team->name)<0)
            root->right=insert_avl(root->right, team); 
    } 
    root->height=1+maxx(node_height(root->left), node_height(root->right));
    int k=(node_height(root->left)-node_height(root->right)); ///aici vad cat de mare e dezechilibrul si in ce parte
    float left, right;
    if(root->left!=NULL) ///aici le am scurtat eu denumirile ca m au ametit rau de tot la un moment dat if urile de mai jos ;-;
        left=root->left->teams->points;
    if(root->right!=NULL)
        right=root->right->teams->points;
    if (k>1 && ((team->points < left) || (strcmp( root->left->teams->name,team->name)>0 && team->points == left)))
        return right_rotation(root);
    if (k<(-1) && ((team->points > right) || (strcmp( root->right->teams->name,team->name)<0 && team->points == right)))
        return left_rotation(root);
    if (k>1 && ((team->points > left)))/* || (strcmp(root->teams->name, team->name)<0 && team->points == root->left->teams->points))*/
        return lrr_rotation(root);
    if (k<(-1) && ((team->points < right)))/* || (strcmp(root->teams->name, team->name)>0 && team->points == root->left->teams->points))*/
        return rlr_rotation(root);
    return root;
}

void printf_drs_avl(avl_tree *root, FILE *r_file, int level)
{
    if(root)
    {
        level++;
        printf_drs_avl(root->right, r_file, level);
       if(level==2)
            fprintf(r_file, "%s\n", root->teams->name);
        printf_drs_avl(root->left, r_file, level);
    }
}
