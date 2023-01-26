#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define FINISH 0
#define MAX_SAI 1
#define BUFFER_SIZE 10

int sai() {
  //
  return ((rand() % (MAX_SAI + 1)) + 1);
}

int odd_or_even(int sai1, int sai2) {
  //偶数か奇数か求める.丁：0,半：1を返す
  return (sai1 + sai2) % 2;
}

int main() {
  //
  int sai1, sai2, continue_flag = 0, player = 0;
  char buf[BUFFER_SIZE];
  srand((unsigned)time(NULL));
  printf("サイコロの最大値は%dです．\n", MAX_SAI + 1);
  do {
    sai1 = sai();
    sai2 = sai();

    printf("丁:0か半:1か\n");
    fgets(buf, sizeof(buf), stdin);

    player = atoi(buf);
    printf("サイコロの値は%dと%dなので", sai1, sai2);

    if (player - odd_or_even(sai1, sai2))
      printf("不正解です．\n");
    else
      printf("正解です．\n");

    printf("続けますか？Yes:1  No:0\n");
    fgets(buf, sizeof(buf), stdin);
    continue_flag = atoi(buf);
  } while (continue_flag);

  printf("終了します.");
  return EXIT_SUCCESS;
}