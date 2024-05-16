//#include "lists.h"
#include "stack&queque.h"
//#include "structs.h"
#include <stdlib.h>

void task1(team *team_head, FILE *r_file)
{
        printf_team_names(team_head, r_file);
}

void task2(team **team_head, FILE *r_file, int number_of_teams)
{
    int power=find_power_of2(number_of_teams);
    while(number_of_teams>power)
    {
        float minimum=find_minimum(*team_head);
        team *auxiliar=*team_head;
        int verif=1;
        while(auxiliar!=NULL && verif)
        {
            if(auxiliar->points==minimum)
                verif=0, eliminate_team(auxiliar, team_head);
            auxiliar=auxiliar->next;
        }
        number_of_teams--;
    }
    printf_team_names(*team_head, r_file);
}

void task3(queue *tail, match *fight, team *team_head, FILE *r_file, stack *top_winners, stack*top_losers)
{
    equip_cheue(tail, fight);
    int contor=1;
    printf_fights(tail, r_file);
 

}

int main(int argc, char* argv[])
{
        FILE *c_file, *d_file, *r_file;
        c_file=fopen(*(argv + 1), "r");
        d_file=fopen(*(argv + 2), "r");
        r_file=fopen(*(argv + 3), "w");

        team *team_head=NULL;
        player *player_head=NULL;
        char *cerinta;
        cerinta=(char*)malloc(sizeof(char)*11);
        fgets(cerinta, 10, c_file);

        int number_of_teams=scanf_teams(d_file, &team_head, player_head);

        queue *tail=create_cheue();
        stack *stack_winners=NULL, *stack_losers=NULL;
        if(*(cerinta+4)=='1')
       {
            task2(&team_head, r_file, number_of_teams);
            match *fight=create_matches(team_head);
            task3(tail, fight, team_head, r_file, stack_winners, stack_losers);
       }
            
        else if(*(cerinta+2)=='1')
            task2(&team_head, r_file, number_of_teams);
        else if(*(cerinta)=='1')
            task1(team_head, r_file);

}