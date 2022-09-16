#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BOMB_AREA 10
#define BUFFER_SIZE 10
#define ABS(a) ((a) < 0 ? -(a) : (a))

int random() {
  //
  return ((rand() % (BOMB_AREA)) + 1);
}

int main() {
  int x, y, player_x, player_y, distance = -1;
  char buf[BUFFER_SIZE];

  srand((unsigned)time(NULL));
  x = random();
  y = random();
  while (distance) {
    printf(
        "縦横それぞれ0から%dの範囲で指し手を入力してください．\n入力例:1,0\n",
        BOMB_AREA - 1);
    fgets(buf, sizeof(buf), stdin);
    player_y = atoi(strtok(buf, ","));
    player_x = atoi(strtok(NULL, "\0"));
    distance = ABS(x - player_x) + ABS(y - player_y);
    printf("入力地点との距離は%dです．\n", distance);
  }
  printf("正解！");
  return EXIT_SUCCESS;
}