#include "main.h"

#include <stdio.h>
#include <stdlib.h>

#include "gba.h"
/* TODO: */
// Include any header files for title screen or exit
// screen images generated by nin10kit. Example for the provided garbage
// image:
// #include "images/garbage.h"
#include "images/garbage.h"
#include "images/download.h"
#include "images/images.h"
#include "images/world.h"
#include "images/mars1.h"
#include "images/mars2.h"
#include "images/playerimage.h"
#include "images/grassybackground.h"



#define SCREEN_HEIGHT 160
#define SCREEN_WIDTH 240

#define NBUTTONS (10)


/* TODO: */
// Add any additional states you need for your app. You are not requried to use
// these specific provided states.


int main(void) {
  /* TODO: */
  // Manipulate REG_DISPCNT here to set Mode 3. //
  REG_DISPCNT = 0x403;
  //int buttonWasDown[NBUTTONS] = {0};

	// unsigned short bgcolor = BLACK;

  // struct state {
	// 	int size;
	// 	struct rect rects;
	// };


  // struct rect *bp, *obp;
  struct astro player;
  struct goal mars;
  struct enemy alien;
  struct enemy alien2;
  struct enemy alien3;

	// // current and previous states
	// struct state cs, ps;
  //initialize goal
  mars.row = 218;
  mars.col = 70;
  mars.diameter = 20;
  mars.color = COLOR(26,22,3);

	// initialize player
	player.row = 0;
	player.col = 0;
	player.rd = 1;
	player.cd = 1;
	player.color = RED;

  //initialize aliens
  alien.row = rand() % SCREEN_WIDTH;
  alien.col = rand() % SCREEN_HEIGHT;
  alien.width = 15;
  alien.color = GREEN;

  alien2.row = rand() % SCREEN_WIDTH;
  alien2.col = rand() % SCREEN_HEIGHT;
  alien2.width = 15;
  alien2.color = GREEN;

  alien3.row = rand() % SCREEN_WIDTH;
  alien3.col = rand() % SCREEN_HEIGHT;
  alien3.width = 15;
  alien3.color = GREEN;


  // Save current and previous state of button input.
   u32 previousButtons = BUTTONS;
   u32 currentButtons = BUTTONS;

  // Load initial application state
  enum gba_state state = START;

  //setPixel(SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2, BLUE);
  //drawRectDMA(0,0, 20, 20, GREEN);
  //drawString(30, 30, "Hello", YELLOW);
  //drawFullScreenImageDMA(garbage);
  //drawImageDMA(0,0, DOWNLOAD_WIDTH, GARBAGE_LENGTH, download);
  //drawImageDMA(0,0, GARBAGE_WIDTH, GARBAGE_HEIGHT, garbage);
  //drawImageDMA(0,0, IMAGES_WIDTH, IMAGES_HEIGHT, images);
  //drawImageDMA(0,0, WORLD_WIDTH, WORLD_HEIGHT, world);
  //drawFullScreenImageDMA(world);
  //drawFullScreenImageDMA(garbage);
  int backgroundIsDrawn = 0;
  int grassybackgroudnIsDrawn = 0;

  while (1) {
    currentButtons = BUTTONS; // Load the current state of the buttons

    /* TODO: */
    // Manipulate the state machine below as needed //
    // NOTE: Call waitForVBlank() before you draw
    // Keep track of the state we're about to overwrite
    switch (state) {
      case START:

        // state = ?
        if (backgroundIsDrawn == 0) {
          drawFullScreenImageDMA(world);
          backgroundIsDrawn = 1;
        }
        drawRectDMA(70, 80, 80, 10, BLUE);
        //drawRectDMA(30, 60, 120, 10, BLUE);
        char start[] =  "Press Start";
        //drawCenteredString(30, 60, 120, 10,  "Journey to Mars", WHITE);
        drawCenteredString(71, 100, 40, 8, start, WHITE);
        waitForVBlank();

        if (KEY_DOWN(BUTTON_START, BUTTONS)) {
          state = PLAY;
  
        }
  
        break;
      case PLAY:
        waitForVBlank();
        fillScreenDMA(BLACK);

        drawImageDMA(player.col, player.row, 5, 5, playerimage);
        drawImageDMA(mars.col, mars.row, mars.diameter, mars.diameter, mars1);
        drawRectDMA(alien.col, alien.row, alien.width, alien.width, alien.color);
        drawRectDMA(alien2.col, alien2.row, alien2.width, alien2.width, alien2.color);
        drawRectDMA(alien3.col, alien3.row, alien3.width, alien3.width, alien3.color);
       
        moveEnemyRandom(&alien);
        moveEnemyRandom(&alien2);
        moveEnemyRandom(&alien3);

        if(KEY_DOWN(BUTTON_SELECT, BUTTONS)) {
          backgroundIsDrawn = 0;
          state = START;
        }

        if (KEY_DOWN(BUTTON_RIGHT, BUTTONS)) {
          player.row += 1;
        }
        if (KEY_DOWN(BUTTON_LEFT, BUTTONS)) {
          player.row -= 1;
        }
        if (KEY_DOWN(BUTTON_DOWN, BUTTONS)) {
          player.col += 1;
        }
        if (KEY_DOWN(BUTTON_UP, BUTTONS)) {
          player.col -= 1;
        }
        // if (player.row <= 0){
        //   player.row = 0;
        // }
        // if (player.col <= 0){
        //   player.col = 0;
        // }
        // if (player.row >= 235){
        //   player.row = 235;
        // }
        // if (player.col >= 155){
        //   player.col = 155;
        // }

        checkAtroPos(&player, &alien, &alien2, &alien3, &mars, &state);
        // state = ?
        break;
      case WIN:
        if (grassybackgroudnIsDrawn == 0) {
          drawFullScreenImageDMA(grassybackground);
          grassybackgroudnIsDrawn = 1;
        }
        drawFullScreenImageDMA(grassybackground);
        char won[] = "YAY";
        drawCenteredString(71, 100, 35, 8, won, BLACK);
        waitForVBlank();
        resetPos(&player, &alien, &alien2, &alien3);

        if(KEY_DOWN(BUTTON_SELECT, BUTTONS)) {
          backgroundIsDrawn = 0;
          grassybackgroudnIsDrawn = 0;
          state = START;
        }
        // state = ?
        break;
      case LOSE:
        resetPos(&player, &alien, &alien2, &alien3);
        char dead[] = "you died...";
        drawCenteredString(71, 100, 40, 8, dead, RED);
        waitForVBlank();
        fillScreenDMA(BLACK);
        if(KEY_DOWN(BUTTON_SELECT, BUTTONS)) {
          backgroundIsDrawn = 0;
          state = START;
        }
        // state = ?
        break;
    }

  previousButtons = currentButtons; // Store the current state of the buttons
 }


  UNUSED(previousButtons); // You can remove this once previousButtons is used

  return 0;
}

void moveEnemyRandom(struct enemy *alien) {
  (*alien).col += randint(-10, 11);
  (*alien).row += randint(-10, 11);
  if ((*alien).row <= 0){
    (*alien).row = 0;
  }
  if ((*alien).col <= 0){
    (*alien).col = 0;
  }
  if ((*alien).row >= 225){
    (*alien).row = 225;
  }
  if ((*alien).col >= 145){
    (*alien).col = 145;
 }
}

void checkAtroPos(struct astro *plr, struct enemy *alien1, struct enemy *alien2, struct enemy *alien3, struct goal *mars, enum gba_state *state) {
  if ((*plr).col + 3 >= (*mars).col && (*plr).row + 3 >= (*mars).row && (*plr).col + 3 <= (*mars).col + 20 && (*plr).row + 3 <= (*mars).row + 20) {
      (*state) = WIN;
  }

  if ((*plr).col + 3 >= (*alien1).col && (*plr).row + 3 >= (*alien1).row && (*plr).col + 3 <= (*alien1).col + 15 && (*plr).row + 3 <= (*alien1).row + 15) {
    (*state) = LOSE;
  }

  if ((*plr).col + 3 >= (*alien2).col && (*plr).row + 3 >= (*alien2).row && (*plr).col + 3 <= (*alien2).col + 15 && (*plr).row + 3 <= (*alien2).row + 15) {
    (*state) = LOSE;
  }

  if ((*plr).col + 3 >= (*alien3).col && (*plr).row  + 3 >= (*alien3).row && (*plr).col + 3 <= (*alien3).col + 15 && (*plr).row + 3 <= (*alien1).row + 15) {
    (*state) = LOSE;
  }

}

void resetPos(struct astro *player, struct enemy *alien, struct enemy *alien2, struct enemy *alien3) {
  (*player).row = 0;
	(*player).col = 0;
	(*player).rd = 1;
	(*player).cd = 1;
	(*player).color = RED;

  //initialize aliens
  (*alien).row = rand() % SCREEN_WIDTH;
  (*alien).col = rand() % SCREEN_HEIGHT;
  (*alien).width = 15;
  (*alien).color = GREEN;

  (*alien2).row = rand() % SCREEN_WIDTH;
  (*alien2).col = rand() % SCREEN_HEIGHT;
  (*alien2).width = 15;
  (*alien2).color = GREEN;

  (*alien3).row = rand() % SCREEN_WIDTH;
  (*alien3).col = rand() % SCREEN_HEIGHT;
  (*alien3).width = 15;
  (*alien3).color = GREEN;
}