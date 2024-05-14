#include <stdio.h>
#include <string.h>
#include <stdlib.h>

////////////////////////////////////////////////
struct player
{
    char *name, *surname;
    int points;
    struct player *next, *prev;
};
typedef struct player player;
////////////////////////////////////////////////
struct team
{
    char *name;
    int number_players, points;
    player *  jucator;
    struct team *next, *prev;
};
typedef struct team team;
////////////////////////////////////////////////
