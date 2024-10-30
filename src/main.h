#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include "OneButton.h"

#define TFT_WIDTH 170
#define TFT_HEIGHT 320

#define UP_BUTTON 0
#define DOWN_BUTTON 14

OneButton upBtn(UP_BUTTON, true);
OneButton downBtn(DOWN_BUTTON, true);

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite p1GameBoard_spr = TFT_eSprite(&tft);
TFT_eSprite p2GameBoard_spr = TFT_eSprite(&tft);
TFT_eSprite p1Blk0_spr = TFT_eSprite(&tft);
TFT_eSprite p1Blk1_spr = TFT_eSprite(&tft);
TFT_eSprite p1Blk2_spr = TFT_eSprite(&tft);
TFT_eSprite p1Blk3_spr = TFT_eSprite(&tft);
TFT_eSprite p1Blk4_spr = TFT_eSprite(&tft);
TFT_eSprite p1Blk5_spr = TFT_eSprite(&tft);
TFT_eSprite p1Blk6_spr = TFT_eSprite(&tft);

TFT_eSprite p2Blk0_spr = TFT_eSprite(&tft);
TFT_eSprite p2Blk1_spr = TFT_eSprite(&tft);
TFT_eSprite p2Blk2_spr = TFT_eSprite(&tft);
TFT_eSprite p2Blk3_spr = TFT_eSprite(&tft);
TFT_eSprite p2Blk4_spr = TFT_eSprite(&tft);
TFT_eSprite p2Blk5_spr = TFT_eSprite(&tft);
TFT_eSprite p2Blk6_spr = TFT_eSprite(&tft);

TFT_eSprite *p1BlkSprs[] = {&p1Blk0_spr, &p1Blk1_spr, &p1Blk2_spr, &p1Blk3_spr, &p1Blk4_spr, &p1Blk5_spr, &p1Blk6_spr};
TFT_eSprite *p2BlkSprs[] = {&p2Blk0_spr, &p2Blk1_spr, &p2Blk2_spr, &p2Blk3_spr, &p2Blk4_spr, &p2Blk5_spr, &p2Blk6_spr};

int blockSeed[14] = {4, 4, 4, 4, 4, 4, 0, 4, 4, 4, 4, 4, 4, 0};
// int blockSeed[14] = {5, 5, 1, 0, 0, 7, 3, 6, 6, 1, 6, 0, 6, 2}; // Test P1 Capture
// int blockSeed[14] = {0, 8, 0, 3, 3, 2, 7, 2, 0, 0, 10, 4, 3, 6}; // Test P2 Capture
// int blockSeed[14] = {0, 0, 0, 0, 1, 0, 21, 3, 0, 0, 1, 0, 0, 22}; // Test P1 Win
// int blockSeed[14] = {3, 0, 0, 1, 0, 0, 22, 0, 0, 0, 0, 1, 0, 21}; // Test P1 Win
// int blockSeed[14] = {1, 2, 0, 0, 1, 2, 15, 0, 0, 0, 0, 0, 5, 22}; // Test P2 Win

bool isPlayer1 = true;
int currPos = 2;
bool gameOver = false;

/***** 游戏相关 *****/
bool checkWin();
void createGameSprite();
void enterGame();
void updateGameBoard();
void updateGameBoard(int pos);
void drawWinScreen();
void upClick();
void downClick();
void confirmPlay();

/***** 游戏相关（end） *****/