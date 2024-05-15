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