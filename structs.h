#include <stdio.h>
#include <string.h>
#include <stdlib.h>

////////////////////////////////////////////////
struct players
{
    char *name, *surname;
    int points;
    struct players *next, *prev;
};
typedef struct players player;
////////////////////////////////////////////////
struct teams
{
    char *name;
    int number_players;
    float points;
    player *  jucator;
    struct teams *next, *prev;
};
typedef struct teams team;
////////////////////////////////////////////////
struct match
{
    team *team1, *team2;
    struct match *next;
};
typedef struct match match;
/////////////////////////////////////////////////
struct cheue
{
    match *front, *rear;
};
typedef struct cheue queue;
//////////////////////////////////////////////////
struct stack
{
    team *teams;
    struct stack *next;
};
typedef struct stack stack;
//////////////////////////////////////////////////
struct tree
{
    team *teams;
    struct tree *left, *right;
};
typedef struct tree tree;
//////////////////////////////////////////////////

