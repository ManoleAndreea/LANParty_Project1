#include "stack&queque.h"

queue* create_cheue()
{
    queue *tail=NULL;
    tail=(queue*)malloc(sizeof(queue));
    tail->front=NULL;
    tail->rear=NULL;
    return tail;
}

void en_cheue(queue *tail, match *fight)
{
    match *fight2=(match*)malloc(sizeof(match));
    fight2->team1=fight->team1;
    fight2->team2=fight->team2;
    fight2->next=NULL;

   if(tail->rear==NULL)
        tail->rear=fight2;
    else
    {
        tail->rear->next=fight2;
        tail->rear=fight2;
    }
    if(tail->front==NULL)
        tail->front=tail->rear;
}

void de_cheue(queue **tail)
{
    match *exterminate=(*tail)->front;
   (*tail)->front=(*tail)->front->next;
    if((*tail)->front==NULL)
        (*tail)->rear=NULL;
   // else
        exterminate=NULL;
    free(exterminate);
}

void equip_cheue(queue *tail, match *fight)
{

    while(fight!=NULL)
    {
        match* auxiliar=fight->next;
        en_cheue(tail, fight);
        free(fight);
        fight=auxiliar;

    }
}

void push_stack(stack **stac, team *team)
{
    stack *auxiliar=(stack*)malloc(sizeof(stack));
    auxiliar->teams=team;
    auxiliar->next=*stac;
    *stac=auxiliar;
}

void pop_stack(stack **stac)
{
    stack *auxiliar=*stac;
    *stac=(*stac)->next;
    free(auxiliar);
}

void who_the_stronger_team(queue *tail, stack **top_g, stack **top_l)
{
    if(tail->front->team1->points>tail->front->team2->points)
    {
        tail->front->team1->points++;
        push_stack(top_g, tail->front->team1);
        push_stack(top_l, tail->front->team2);
    }
    else
    {
        tail->front->team2->points++;
        push_stack(top_g, tail->front->team2);
        push_stack(top_l, tail->front->team1);
    }
}

void printf_fights(queue *tail, FILE* r_file, stack **top_winners, stack **top_losers)
{
    while(tail->front!=tail->rear)
    {
        char *name=(char*)malloc(sizeof(char)*50);
        strcpy(name, tail->front->team1->name);
        if(*(name+strlen(name)-1)==' ')
        {
            *(name+strlen(name)-1)=*(name+strlen(name));
            strcpy(tail->front->team1->name, name);
     
        }
        strcpy(name, tail->front->team2->name);
        if(*(name+strlen(name)-1)==' ')
        {
            *(name+strlen(name)-1)=*(name+strlen(name));
            strcpy(tail->front->team2->name, name);
        }
        fprintf(r_file, "%s", tail->front->team1->name);
        int contor=33-strlen(tail->front->team1->name);
        while(contor)
            fprintf(r_file, " "), contor--;
        fprintf(r_file, "-");
        contor=33-strlen(tail->front->team2->name);
        while(contor)
            fprintf(r_file, " "), contor--;
        fprintf(r_file, "%s\n", tail->front->team2->name);
        who_the_stronger_team(tail, top_winners, top_losers);
        de_cheue(&tail);
    }
    fprintf(r_file, "%s", tail->front->team1->name);
    int contor=33-strlen(tail->front->team1->name);
    while(contor)
        fprintf(r_file, " "), contor--;
    fprintf(r_file, "-");
    contor=33-strlen(tail->front->team2->name);
    while(contor)
        fprintf(r_file, " "), contor--;
    fprintf(r_file, "%s", tail->front->team2->name);
        who_the_stronger_team(tail, top_winners, top_losers);
    de_cheue(&tail);
}

void printf_winners(stack *top, FILE* r_file)
{
    while(top!=NULL)
    {
        
        int contor=34;
        fprintf(r_file, "%s", top->teams->name);
        contor-=strlen(top->teams->name);
        while(contor)
            fprintf(r_file, " "), contor--;
        fprintf(r_file, "-  ");
        fprintf(r_file, "%.2f\n", top->teams->points);
        top=top->next;
    }
}

void delete_stack(stack **top)
{
    while((*top)!=NULL)
    {
        pop_stack(top);
        (*top)=(*top)->next;
    }
}

team* re_create_teams(stack *top)
{
    team *head=(team*)malloc(sizeof(team));
    head=top->teams;
    head->prev=NULL;
    head->next=NULL;
    //printf("%s\n", top->teams->name);
    top=top->next;
    team *auxiliar=head;
    while(top!=NULL)
    {
       // printf("%s\n", top->teams->name);
        auxiliar->next=top->teams;
        top->teams->prev=auxiliar;
        auxiliar=top->teams;
        auxiliar->next=NULL;
        top=top->next;
    }
   // printf("\n---------------------------------------\n");
    return head;

}