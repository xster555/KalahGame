#include "main.h"

/***** 游戏进程相关 *****/

// 检查是否获胜
bool checkWin()
{
  bool foundWinner = true;
  // 检测P1是否获胜
  for (int i = 0; i < 6; i++)
  {
    if (blockSeed[i] != 0)
    {
      foundWinner = false;
      break;
    }
  }

  if (foundWinner == false)
  {
    foundWinner = true;
    // 检测P2是否获胜
    for (int i = 7; i < 13; i++)
    {
      if (blockSeed[i] != 0)
      {
        foundWinner = false;
        break;
      }
    }
  }

  if (foundWinner)
  {
    gameOver = true;
  }
  return foundWinner;
}

// 创建Sprite
void createGameSprite()
{
  // P1
  p1GameBoard_spr.createSprite(TFT_HEIGHT, TFT_WIDTH / 2);

  for (int i = 0; i < 7; i++)
  {
    if (i != 6)
    {
      p1BlkSprs[i]->createSprite(PIT_WIDTH, PIT_HEIGHT);
    }
    else
    {
      p1BlkSprs[i]->createSprite(STORE_WIDTH, STORE_HEIGHT);
    }
  }

  // P2
  p2GameBoard_spr.createSprite(TFT_HEIGHT, TFT_WIDTH / 2);

  for (int i = 7; i < 14; i++)
  {
    if (i != 13)
    {
      p2BlkSprs[i - 7]->createSprite(PIT_WIDTH, PIT_HEIGHT);
    }
    else
    {
      p2BlkSprs[i - 7]->createSprite(STORE_WIDTH, STORE_HEIGHT);
    }
  }

  updateGameBoard();
}

// 更新游戏面板
void updateGameBoard()
{
  // P1
  p1GameBoard_spr.fillSprite(TFT_BLACK);

  for (int i = 0; i < 7; i++)
  {
    if (i != 6)
    {
      p1BlkSprs[i]->setTextDatum(MC_DATUM);

      if (isPlayer1 && currPos == i)
      {
        p1BlkSprs[i]->fillSprite(TFT_DARKGREEN);
        p1BlkSprs[i]->setTextColor(TFT_WHITE);
      }
      else
      {
        p1BlkSprs[i]->fillSprite(TFT_WHITE);
        p1BlkSprs[i]->setTextColor(TFT_BLACK);
      }
      p1BlkSprs[i]->drawString(String(blockSeed[i]), 19, 19, 2);
      p1BlkSprs[i]->pushToSprite(&p1GameBoard_spr, 40 * (i + 1), p1GameBoard_spr.height() - PIT_HEIGHT);
    }
    else
    {
      p1BlkSprs[i]->fillSprite(TFT_WHITE);
      p1BlkSprs[i]->setTextDatum(MC_DATUM);
      p1BlkSprs[i]->setTextColor(TFT_BLACK);
      p1BlkSprs[i]->drawString(String(blockSeed[i]), 19, 43, 2);
      p1BlkSprs[i]->pushToSprite(&p1GameBoard_spr, 40 * (i + 1), 0);
    }
  }

  p1GameBoard_spr.pushSprite(0, TFT_WIDTH / 2);

  // P2
  p2GameBoard_spr.fillSprite(TFT_BLACK);

  for (int i = 7; i < 14; i++)
  {
    if (i != 13)
    {
      p2BlkSprs[i - 7]->setTextDatum(MC_DATUM);
      if (!isPlayer1 && currPos == (i - 7))
      {
        p2BlkSprs[i - 7]->fillSprite(TFT_DARKGREEN);
        p2BlkSprs[i - 7]->setTextColor(TFT_WHITE);
      }
      else
      {
        p2BlkSprs[i - 7]->fillSprite(TFT_WHITE);
        p2BlkSprs[i - 7]->setTextColor(TFT_BLACK);
      }
      p2BlkSprs[i - 7]->drawString(String(blockSeed[i]), 19, 19, 2);
      p2BlkSprs[i - 7]->pushToSprite(&p2GameBoard_spr, 40 * (i - 6), p2GameBoard_spr.height() - PIT_HEIGHT);
    }
    else
    {
      p2BlkSprs[i - 7]->fillSprite(TFT_WHITE);
      p2BlkSprs[i - 7]->setTextDatum(MC_DATUM);
      p2BlkSprs[i - 7]->setTextColor(TFT_BLACK);
      p2BlkSprs[i - 7]->drawString(String(blockSeed[i]), 19, 43, 2);
      p2BlkSprs[i - 7]->pushToSprite(&p2GameBoard_spr, 40 * (i - 6), 0);
    }
  }

  tft.setPivot(TFT_WIDTH / 2 + 74, 84);
  p2GameBoard_spr.setPivot(p2GameBoard_spr.width() / 2, 0);
  p2GameBoard_spr.pushRotated(180);
}

// 更新特定游戏面板
void updateGameBoard(int pos)
{
  if (pos < 0 || pos > 13)
  {
    return;
  }

  if (pos < 6)
  {
    p1BlkSprs[pos]->setTextDatum(MC_DATUM);
    p1BlkSprs[pos]->fillSprite(TFT_BLUE);
    p1BlkSprs[pos]->setTextColor(TFT_WHITE);
    p1BlkSprs[pos]->drawString(String(blockSeed[pos]), 19, 19, 2);
    p1BlkSprs[pos]->pushToSprite(&p1GameBoard_spr, 40 * (pos + 1), p1GameBoard_spr.height() - p1Blk0_spr.height());
    p1GameBoard_spr.pushSprite(0, TFT_WIDTH / 2);
  }
  else if (pos == 6)
  {
    p1BlkSprs[pos]->setTextDatum(MC_DATUM);
    p1BlkSprs[pos]->fillSprite(TFT_BLUE);
    p1BlkSprs[pos]->setTextColor(TFT_WHITE);
    p1BlkSprs[pos]->drawString(String(blockSeed[pos]), 19, 43, 2);
    p1BlkSprs[pos]->pushToSprite(&p1GameBoard_spr, 40 * (pos + 1), 0);
    p1GameBoard_spr.pushSprite(0, TFT_WIDTH / 2);
  }
  else if (pos > 6 && pos < 13)
  {
    p2BlkSprs[pos - 7]->setTextDatum(MC_DATUM);
    p2BlkSprs[pos - 7]->fillSprite(TFT_BLUE);
    p2BlkSprs[pos - 7]->setTextColor(TFT_WHITE);
    p2BlkSprs[pos - 7]->drawString(String(blockSeed[pos]), 19, 19, 2);
    p2BlkSprs[pos - 7]->pushToSprite(&p2GameBoard_spr, 40 * (pos - 6), p2GameBoard_spr.height() - p1Blk0_spr.height());
    tft.setPivot(TFT_WIDTH / 2 + 74, 84);
    p2GameBoard_spr.setPivot(p2GameBoard_spr.width() / 2, 0);
    p2GameBoard_spr.pushRotated(180);
  }
  else if (pos == 13)
  {
    p2BlkSprs[pos - 7]->setTextDatum(MC_DATUM);
    p2BlkSprs[pos - 7]->fillSprite(TFT_BLUE);
    p2BlkSprs[pos - 7]->setTextColor(TFT_WHITE);
    p2BlkSprs[pos - 7]->drawString(String(blockSeed[pos]), 19, 43, 2);
    p2BlkSprs[pos - 7]->pushToSprite(&p2GameBoard_spr, 40 * (pos - 6), 0);
    tft.setPivot(TFT_WIDTH / 2 + 74, 84);
    p2GameBoard_spr.setPivot(p2GameBoard_spr.width() / 2, 0);
    p2GameBoard_spr.pushRotated(180);
  }

  // // P2
  // p2GameBoard_spr.fillSprite(TFT_BLACK);

  // for (int i = 7; i < 14; i++)
  // {
  //   if (i != 13)
  //   {
  //     p2BlkSprs[i - 7]->setTextDatum(MC_DATUM);
  //     if (!isPlayer1 && currPos == (i - 7))
  //     {
  //       p2BlkSprs[i - 7]->fillSprite(TFT_DARKGREEN);
  //       p2BlkSprs[i - 7]->setTextColor(TFT_WHITE);
  //     }
  //     else
  //     {
  //       p2BlkSprs[i - 7]->fillSprite(TFT_WHITE);
  //       p2BlkSprs[i - 7]->setTextColor(TFT_BLACK);
  //     }
  //     p2BlkSprs[i - 7]->drawString(String(blockSeed[i]), 19, 19, 2);
  //     p2BlkSprs[i - 7]->pushToSprite(&p2GameBoard_spr, 40 * (i - 6), p2GameBoard_spr.height() - p1Blk0_spr.height());
  //   }
  //   else
  //   {
  //     p2BlkSprs[i - 7]->fillSprite(TFT_WHITE);
  //     p2BlkSprs[i - 7]->setTextDatum(MC_DATUM);
  //     p2BlkSprs[i - 7]->setTextColor(TFT_BLACK);
  //     p2BlkSprs[i - 7]->drawString(String(blockSeed[i]), 19, 43, 2);
  //     p2BlkSprs[i - 7]->pushToSprite(&p2GameBoard_spr, 40 * (i - 6), 0);
  //   }
  // }

  // tft.setPivot(TFT_WIDTH / 2 + 74, 84);
  // p2GameBoard_spr.setPivot(p2GameBoard_spr.width() / 2, 0);
  // p2GameBoard_spr.pushRotated(180);
}

// 进入游戏
void enterGame()
{
  createGameSprite();
}

// 处理UP点击事件
void upClick()
{
  if (gameOver)
  {
    return;
  }

  if (isPlayer1)
  {
    currPos--;
    if (currPos < 0)
    {
      currPos = 5;
    }
  }
  else
  {
    currPos++;
    if (currPos > 5)
    {
      currPos = 0;
    }
  }

  updateGameBoard();
}

// 处理DOWN点击事件
void downClick()
{
  if (gameOver)
  {
    return;
  }

  if (isPlayer1)
  {
    currPos++;
    if (currPos > 5)
    {
      currPos = 0;
    }
  }
  else
  {
    currPos--;
    if (currPos < 0)
    {
      currPos = 5;
    }
  }

  updateGameBoard();
}

// 确认操作
void confirmPlay()
{
  if (gameOver)
  {
    return;
  }

  bool canReplay = false;  // 是否可以再次操作
  bool canCapture = false; // 是否可以捕获

  if (isPlayer1)
  {
    int plotSeedNum = blockSeed[currPos];
    if (plotSeedNum == 0)
    {
      return;
    }

    blockSeed[currPos] = 0;

    if (currPos + plotSeedNum == 6)
    {
      canReplay = true;
    }

    for (int i = 0; i < plotSeedNum; i++)
    {
      if ((i == plotSeedNum - 1) && ((currPos + 1 + i) < 6) && (blockSeed[(currPos + 1 + i) % 14] == 0) && (blockSeed[13 - currPos - plotSeedNum - 1] != 0))
      {
        canCapture = true;
      }
      blockSeed[(currPos + 1 + i) % 14] += 1;
      updateGameBoard((currPos + 1 + i) % 14);
      delay(100);
    }

    if (canCapture)
    {
      blockSeed[(currPos + plotSeedNum) % 14] = 0;
      blockSeed[6]++;
      blockSeed[6] += blockSeed[13 - currPos - plotSeedNum - 1];
      blockSeed[13 - currPos - plotSeedNum - 1] = 0;
    }
  }
  else
  {
    int plotSeedNum = blockSeed[currPos + 7];
    if (plotSeedNum == 0)
    {
      return;
    }

    blockSeed[currPos + 7] = 0;

    if (currPos + 7 + plotSeedNum == 13)
    {
      canReplay = true;
    }

    for (int i = 0; i < plotSeedNum; i++)
    {
      if ((i == plotSeedNum - 1) && ((currPos + 8 + i) > 6) && ((currPos + 8 + i) < 13) && (blockSeed[(currPos + 8 + i) % 14] == 0) && (blockSeed[13 - (currPos + 7) - plotSeedNum - 1] != 0))
      {
        canCapture = true;
      }
      blockSeed[(currPos + 8 + i) % 14] += 1;
      updateGameBoard((currPos + 8 + i) % 14);
      delay(100);
    }

    if (canCapture)
    {
      blockSeed[(currPos + 7 + plotSeedNum) % 14] = 0;
      blockSeed[13]++;
      blockSeed[13] += blockSeed[13 - (currPos + 7) - plotSeedNum - 1];
      blockSeed[13 - (currPos + 7) - plotSeedNum - 1] = 0;
    }
  }

  if (checkWin())
  {
    drawWinScreen();
    return;
  }

  if (!canReplay)
  {
    isPlayer1 = !isPlayer1;
  }

  updateGameBoard();
}

// 绘制胜利画面
void drawWinScreen()
{
  updateGameBoard();
  tft.setTextDatum(MC_DATUM);
  tft.setTextSize(3);

  if (blockSeed[6] > blockSeed[13])
  {
    tft.drawString("player1 wins", TFT_HEIGHT / 2, TFT_WIDTH / 2);
  }
  else if (blockSeed[6] < blockSeed[13])
  {
    tft.drawString("player2 wins", TFT_HEIGHT / 2, TFT_WIDTH / 2);
  }
  else
  {
    tft.drawString("tie", TFT_HEIGHT / 2, TFT_WIDTH / 2);
  }
}

void setup()
{
  Serial.begin(115200);
  randomSeed(analogRead(1));

  pinMode(UP_BUTTON, INPUT_PULLUP);
  pinMode(DOWN_BUTTON, INPUT_PULLUP);

  upBtn.attachClick(upClick);
  downBtn.attachClick(downClick);
  upBtn.attachDoubleClick(confirmPlay);
  downBtn.attachDoubleClick(confirmPlay);

  // 初始化屏幕
  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(TFT_WHITE);

  enterGame();
}

void loop()
{
  upBtn.tick();
  downBtn.tick();
}
