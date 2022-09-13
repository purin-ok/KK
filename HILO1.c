#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define FINISH 0
#define MAX_TO 13
#define BUFFER_SIZE 10

int cards_number() {
  //
  return ((rand() % (MAX_TO + 1)) + 1);
}

int main() {
  int player, number;
  char buf[BUFFER_SIZE];
  srand((unsigned)time(NULL));

  number = (rand() % MAX_TO) + 1;

  while (true) {
    printf("トランプの値は何でしょう\n");
    fgets(buf, sizeof(buf), stdin);
    player = atoi(buf);

    // highかlowかの判定
    if (player - number) {
      if (player > number)
        printf("High\n");
      else
        printf("Low\n");
    } else {
      printf("正解です．終了します．\n");
      return EXIT_SUCCESS;
    }
  }
}