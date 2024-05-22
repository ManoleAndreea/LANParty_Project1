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

void printf_drs(tree *root, FILE *r_file)
{
    if(root)
    {
        printf_drs(root->right, r_file);
       // printf("%s: %f\n", root->teams->name, root->teams->points);
       fprintf(r_file, "%s", root->teams->name);
        int contor=34-strlen(root->teams->name);
        while(contor)
            fprintf(r_file, " "), contor--;
        fprintf(r_file, "-  ");
        fprintf(r_file, "%.2f\n", root->teams->points);
        printf_drs(root->left, r_file);

    }
}