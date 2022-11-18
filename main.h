#ifndef MAIN_H
#define MAIN_H

#include "gba.h"

// TODO: Create any necessary structs

/*
* For example, for a Snake game, one could be:
*
* struct snake {
*   int heading;
*   int length;
*   int row;
*   int col;
* };
*
* Example of a struct to hold state machine data:
*
* struct state {
*   int currentState;
*   int nextState;
* };
*
*/
struct astro {
   int row;
	 int col;
	 int rd;
	 int cd;
	 unsigned short color;
  };

  struct goal {
    int row;
    int col;
    int diameter;
    unsigned short color;
  };

  struct enemy {
    int row;
    int col;
    int width;
    unsigned short color; 
  };

    enum gba_state {
    START,
    PLAY,
    WIN,
    LOSE,
    };


void moveEnemyRandom(struct enemy *alien);
void checkAtroPos(struct astro *plr, struct enemy *alien1, struct enemy *alien2, struct enemy *alien3, struct goal *mars, enum gba_state *state);
void resetPos(struct astro *player, struct enemy *alien, struct enemy *alien2, struct enemy *alien3);
#endif
