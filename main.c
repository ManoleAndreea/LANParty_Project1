#include "tree.h"
#include <stdlib.h>

void task1(team *team_head, FILE *r_file)
{
        printf_team_names(team_head, r_file);
}

int task2(team **team_head, FILE *r_file, int number_of_teams)
{
    if((number_of_teams&(number_of_teams-1))!=0)///aici verific daca number_of_teams nu este putere a lui 2 
    {
        int power=find_power_of2(number_of_teams);
        while(number_of_teams>power)
        {
            float minimum=find_minimum(*team_head);
            team *auxiliar=*team_head;
            int verif=1;
            while(auxiliar!=NULL && verif)
            {
                if(auxiliar->points==minimum) ///daca punctajul echipei curente e minim atunci o elimin
                    verif=0, eliminate_team(auxiliar, team_head);
                auxiliar=auxiliar->next;
            }
            number_of_teams--;
        }
    }
   printf_team_names(*team_head, r_file);
   return number_of_teams;
}

team *task3(queue *tail, match *fight, team *team_head, FILE *r_file, stack *top_winners, stack *top_losers, int number_teams)
{
    team *best8=NULL;
    equip_cheue(tail, fight);
    int contor=1;
   while(number_teams>2)
   {
        fprintf(r_file, "\n--- ROUND NO:%d\n", contor);
        printf_fights(tail, r_file, &top_winners, &top_losers);
        fprintf(r_file, "\n\nWINNERS OF ROUND NO:%d\n", contor);
        printf_winners(top_winners, r_file);
        contor++;
        team *head=re_create_teams(top_winners);
        if(number_teams==16)///verific daca sunt 8 meciuri si daca da adaug in lista cu cele mai bune 8 echipe
            best8=add_best8(head);
        match *fight=create_matches(head, number_teams);
        equip_cheue(tail, fight);
        delete_stack(&top_losers);
        delete_stack(&top_winners);
        number_teams/=2;;
   }
    fprintf(r_file, "\n--- ROUND NO:%d\n", contor);
    printf_fights(tail, r_file, &top_winners, &top_losers);
    fprintf(r_file, "\n\nWINNERS OF ROUND NO:%d\n", contor);
    printf_winners(top_winners, r_file);
    return best8;

}

team* task4(tree *root, team *team8, FILE *r_file)
{
    while(team8!=NULL)
        root=insert_in_tree(root, team8), team8=team8->next;
    fprintf(r_file, "\nTOP 8 TEAMS:\n");
    printf_drs(root, r_file, &team8);
    return team8;
}

void task5(FILE *r_file, avl_tree *root, team *team8)
{
        while(team8!=NULL)
            root=insert_avl(root, team8), team8=team8->next;
        int level=-1;///pornest de la -1 ca atunci cand intru pe radacina sa se faca nivelul 0
        fprintf(r_file, "\nTHE LEVEL 2 TEAMS ARE:\n");
        printf_drs_avl(root, r_file, level);
}

int main(int argc, char* argv[])
{
        FILE *c_file, *d_file, *r_file;
        c_file=fopen(*(argv + 1), "r");
        d_file=fopen(*(argv + 2), "r");
        r_file=fopen(*(argv + 3), "w");

        team *team_head=NULL;
        player *player_head=NULL;
        char *cerinta=(char*)malloc(sizeof(char)*11);
        fgets(cerinta, 10, c_file);

        int number_of_teams=scanf_teams(d_file, &team_head, player_head);///aici fac citirea echipelor

        queue *tail=create_cheue();
        stack *stack_winners=NULL, *stack_losers=NULL;
        avl_tree *root_avl=NULL;
        tree *root=NULL;

        if(*(cerinta+8)=='1')
        {
            number_of_teams=task2(&team_head, r_file, number_of_teams);///aici aflu numarul de echipe dupa eliminarea echipelor pana se ajunge la un numar putere a lui 2
            match *fight=create_matches(team_head, number_of_teams);
            team *team8=task3(tail, fight, team_head, r_file, stack_winners, stack_losers, number_of_teams);
            team8=task4(root, team8, r_file); ///aici repopulez team8 cu echipele ordonate in functie de punctaj
            task5(r_file, root_avl, team8);
        }
        else if(*(cerinta+6)=='1')
        {
            number_of_teams=task2(&team_head, r_file, number_of_teams);
            match *fight=create_matches(team_head, number_of_teams);
            team *team8=task3(tail, fight, team_head, r_file, stack_winners, stack_losers, number_of_teams);
            task4(root, team8, r_file);
        }
        else if(*(cerinta+4)=='1')
        {
            number_of_teams=task2(&team_head, r_file, number_of_teams);
            match *fight=create_matches(team_head, number_of_teams);
            task3(tail, fight, team_head, r_file, stack_winners, stack_losers, number_of_teams);
        }
        else if(*(cerinta+2)=='1')
            task2(&team_head, r_file, number_of_teams);
        else if(*(cerinta)=='1')
            task1(team_head, r_file);

}