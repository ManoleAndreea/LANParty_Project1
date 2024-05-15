#include "lists.h"

void add_beginning_teams(team **head, int num_players, char *name)
{
    team* auxiliar=(team*)malloc(sizeof(team));
    auxiliar->name=(char*)malloc(sizeof(char)*strlen(name));
	strcpy(auxiliar->name, name);
	auxiliar->number_players=num_players;
    if((*head)==NULL)
    {
        auxiliar->next=NULL;
        auxiliar->prev=NULL;
        (*head)=auxiliar;
    }
    else
    {
        auxiliar->next=(*head);
        auxiliar->prev=NULL;
        (*head)->prev=auxiliar;
	    (*head)=auxiliar; 
    }
  //  printf("%s \n", auxiliar->name);
 
}

void add_beginning_players(team *team_head, player **player_head, char *name, char *surname, int points)
{
    player* auxiliar=(player*)malloc(sizeof(player));

    auxiliar->name=(char*)malloc(sizeof(char)*strlen(name));
    strcpy(auxiliar->name, name);
    auxiliar->surname=(char*)malloc(sizeof(char)*strlen(surname));
    strcpy(auxiliar->surname, surname);
    auxiliar->points=points;
    if((*player_head)==NULL)
    {
        auxiliar->next=NULL;
        auxiliar->prev=NULL;
        (*player_head)=auxiliar;
        team_head->jucator=(*player_head);
    }
    else
    {
        auxiliar->next=(*player_head);
        auxiliar->prev=NULL;
        (*player_head)->prev=auxiliar;
        (*player_head)=auxiliar;
        team_head->jucator=(*player_head);
    }
}

void printf_team_names(team *team_head, FILE *r_file)
{
    while(team_head!=NULL)
    {
        fprintf(r_file, "%s\n", team_head->name);
        team_head=team_head->next;
    }
}

int scanf_teams(FILE *d_file, team **head_team, player *head_player)
{
    int contor=0, number_players, points, number_teams;
    char *team_name, *name, *surname;

    name=(char*)malloc(sizeof(char)*50);
    surname=(char*)malloc(sizeof(char)*50);

    fscanf(d_file, "%d", &number_teams);

    while(contor<number_teams)
    {
        fscanf(d_file, "%d", &number_players);
        team_name=(char*)malloc(sizeof(char)*50);
    
        fgets(team_name, 50, d_file);      
        *(team_name+(strlen(team_name)-2))='\0'; ///aici sterg spatiul si \n
        for(int i=0; i<strlen(team_name); i++)   ///aici sterg spatiul dintre numarul de jucatori si numele echipei
            *(team_name+i)=*(team_name+1+i);
        
        add_beginning_teams(head_team, number_players, team_name);

        for(int i=0; i<number_players; i++)
        {
            fscanf(d_file, "%s%s%d", name, surname, &points);
            (*head_team)->points+=points;
            add_beginning_players(*head_team, &head_player, name, surname, points);
        }
        (*head_team)->points/=(float)number_players;

        contor++;

    }
    return number_teams;

}

void eliminate_team(team *exterminate, team **head_team)
{
    if(exterminate->prev==NULL)
    {
        (*head_team)=(*head_team)->next;
        (*head_team)->prev=NULL;
        free(exterminate);
    }
    else if(exterminate->next==NULL)
    {
        exterminate->prev->next=NULL;
        free(exterminate);
    }
    else
    {
        exterminate->prev->next=exterminate->next;
        exterminate->next->prev=exterminate->prev;
        free(exterminate);
    }
}

team* search_for_team(team *head_team, int number)
{
    while(head_team!=NULL)
    {
        if(head_team->points==number)
            return head_team;
        head_team=head_team->next;
    }
}

