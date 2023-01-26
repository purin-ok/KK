#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define FINISH 0
#define MARK_AREA 3
#define BUFFER_SIZE 10
#define PLAYER1 1
#define PLAYER2 -1

#define ABS(a) ((a) < 0 ? -(a) : (a))

int random() {
  //
  return ((rand() % (MARK_AREA)) + 1);
}

void mark_output(int vect[][MARK_AREA]) {
  int x, y;
  for (y = 0; y < MARK_AREA; y++) {
    for (x = 0; x < MARK_AREA; x++) {
      if (vect[y][x] == 1)
        printf(" ○");
      else if (vect[y][x] == -1)
        printf(" ×");
      else
        printf("  ");
      // printf(" ");
    }
    printf("\n");
  }
}

void mark_memo(int vect[][MARK_AREA], int player_num, int x, int y) {
  vect[y][x] = player_num;
}

int main() {
  int x, y, player_flag = 1, count = 0;
  char buf[BUFFER_SIZE];
  int area[MARK_AREA][MARK_AREA] = {0};
  while (true) {
    printf(
        "横縦それぞれ0から%dの範囲で指し手を入力してください．\n入力例:1,0\n",
        MARK_AREA - 1);
    //入力部分
    fgets(buf, sizeof(buf), stdin);
    x = atoi(strtok(buf, ","));
    y = atoi(strtok(NULL, "\0"));
    if ((x >= 0) && (x < MARK_AREA) && (y >= 0) && (y < MARK_AREA) &&
        !(area[y][x])) {
      //指し手記録
      mark_memo(area, player_flag, x, y);

      //盤面表示
      mark_output(area);
      printf("----------------------------\n");

      //指す人交代
      player_flag *= -1;
      count++;
      if (count >= MARK_AREA * MARK_AREA) break;
    } else
      printf("コマが置けません.\n----------------------------\n");
  }
  return EXIT_SUCCESS;
}