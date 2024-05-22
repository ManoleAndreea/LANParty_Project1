#include "suppplementary_functions.h"

float find_minimum(team *head_team)
{
    float minimum=99999;
    while(head_team!=NULL)
    {
        if(minimum>head_team->points)
            minimum=head_team->points;
        head_team=head_team->next;
    }
    return minimum;
}

int find_power_of2(int number)
{
    int power=1;
    while((power<<1)<number)
        power<<=1;
    return power;
}

match* create_matches(team *head_team, int number_teams)
{

    if(number_teams>=8)
    {
    team* end_of_teams=head_team;
    while(end_of_teams->next!=NULL)
        end_of_teams=end_of_teams->next;
    match *fight=NULL;
    fight=(match*)malloc(sizeof(match));
    fight->next=NULL;
    fight->team2=end_of_teams;
    fight->team1=end_of_teams->prev;
    end_of_teams=end_of_teams->prev->prev;

    while(end_of_teams->prev!=NULL && end_of_teams->prev->prev!=NULL && end_of_teams!=NULL) 
    {
        
        match *auxiliar=(match*)malloc(sizeof(match));
        auxiliar->next=fight;
        fight=auxiliar;
        fight->team2=end_of_teams;
        fight->team1=end_of_teams->prev;
        end_of_teams=end_of_teams->prev->prev;
    }
    match *auxiliar=(match*)malloc(sizeof(match));
    auxiliar->next=fight;
    fight=auxiliar;
    // free(auxiliar);
        
    fight->team2=end_of_teams;
    fight->team1=end_of_teams->prev;
    return fight;

    }
    else if(number_teams==4)
    {    
        team* end_of_teams=head_team;
        while(end_of_teams->next!=NULL)
            end_of_teams=end_of_teams->next;
    match *fight=NULL;
    fight=(match*)malloc(sizeof(match));
    fight->next=NULL;
    fight->team2=end_of_teams;
    fight->team1=end_of_teams->prev;
        return fight;
        
    }

    // else if(number_teams==4)
    // {

    // }
    
}

void delete_fights(match *fight)
{
    while(fight!=NULL)
    {
        match *auxiliar=fight;
        fight=fight->next;
        free(auxiliar);
    }
}

team *add_best8(team *head)
{
    team *auxiliar=(team*)malloc(sizeof(team));
    auxiliar->prev=NULL;
    auxiliar->next=NULL;
    auxiliar->points=head->points;
    auxiliar->name=(char*)malloc(sizeof(char)*50);
    strcpy(auxiliar->name, head->name);
    team *best=auxiliar;
    head=head->next;
    while(head!=NULL)
    {
        team *auxiliar=(team*)malloc(sizeof(team));
        auxiliar->prev=NULL;
        auxiliar->next=best;
        auxiliar->points=head->points;
        auxiliar->name=(char*)malloc(sizeof(char)*50);
        strcpy(auxiliar->name, head->name);
        best=auxiliar;
        head=head->next;

    }

    return best;
}
