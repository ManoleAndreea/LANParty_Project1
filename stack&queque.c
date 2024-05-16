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
    fight->next=NULL;
    if(tail->rear==NULL)
        tail->rear=fight;
    else
    {
        tail->rear->next=fight;
        tail->rear=fight;
    }
    if(tail->front==NULL)
        tail->front=tail->rear;
}

void de_cheue(queue **tail)
{
    match *exterminate=(*tail)->front;
   (*tail)->front=(*tail)->front->next;
    free(exterminate);
}

void equip_cheue(queue *tail, match *fight)
{

    while(fight!=NULL)
    {
        match*auxiliar=fight->next;
        en_cheue(tail, fight);
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
    if(tail->front->team1->points>=tail->front->team2->points)
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

void printf_fights(queue *tail, FILE* r_file)
{
    while(tail->front!=tail->rear)
    {
        //char *name=(char*)malloc(sizeof(char)*50);
       // strcpy(name, tail->front->team1->name);
        fprintf(r_file, "%s", tail->front->team1->name);
        int contor=33-strlen(tail->front->team1->name);
        while(contor)
            fprintf(r_file, " "), contor--;
        fprintf(r_file, "-");
        contor=33-strlen(tail->front->team2->name);
        while(contor)
            fprintf(r_file, " "), contor--;
        fprintf(r_file, "%s\n", tail->front->team2->name);
        tail->front=tail->front->next;
        
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
}

// void printf_winners(stack *top, FILE* r_file)
// {
//     printf("!!!!!!!!!!!!");
//     while(top!=NULL)
//     {
        
//         int contor=34;
//         fprintf(r_file, "%s", top->teams->name);
//         contor-=strlen(top->teams->name);
//         while(contor)
//             fprintf(r_file, " "), contor--;
//         fprintf(r_file, "-  ");
//         fprintf(r_file, "%.2f\n", top->teams->points);
//         top=top->next;
//     }
// }

// void delete_stack(stack **top)
// {
//     while((*top)!=NULL)
//     {
//         pop_stack(top);
//         (*top)=(*top)->next;
//     }
//     if((*top)==NULL)
//         printf("!!!!!!!!!!");

// }
