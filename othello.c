/* MAP フ ァ イ ル 読 み 込 み */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define ABS(a) ((a) < 0 ? -(a) : (a))
#define ADJ(d) ((d < 0) ? -1 : ((d > 0) ? 1 : 0))

int read_map_file(const char*, char map[8][8]);
// リターン値(1:読み込み失敗, 0:読み込み成功)
int map_reset(char map[8][8]);  // マップ状態を初期化
int map_save(char map[8][8]);   // マップ状態を保存
int othello_game(char map[8][8], double pmap[8][8], int*);  // ゲームほんへ
void turn_over(char map[8][8], int, int, int, int, int,int);  // コマをひっくり返す
void board_display(char map[8][8]);                       // マップ表示
int put_search(char map[8][8], double pmap[8][8], int);  // おける枚数保存

int main(int argc, char** argv) {
  int tmp = 0;
  int i = 0, turn_flag = 1, finish_flag = 0;  // -1が先行,最初に-1をかける．
  char map[8][8];
  double pmap[8][8] = {0.0};
  if (read_map_file(argv[1], map)) {  // 盤面読み込み
    printf("ファイルが読み込めません");
    return EXIT_FAILURE;
  }
if(atoi(argv[1])==0){
  map_reset(map);
  printf("初期盤面にしました。");
  return 0;
}
  do {
    // １ターン分の流れを他の関数に渡してそれを繰り返す形にする．条件式で呼び出せば流石に行けるはず．
    // system("cls");
    // printf("turn%d\n", i);
    turn_flag *= -1;

    // おける場所サーチする関数作って置ける場所なかったらcontinueでどうだろう
    if (put_search(map, pmap, turn_flag) == 0) {  // おけなかったら
      if (finish_flag) break;  // フラグが立ってたらおわり
      finish_flag++;  // 立ってなかったらこのループ最初から
      printf("パスです\n");
      Sleep(1000);
      continue;
      // return 0;
    }
    finish_flag = 0;  // おけそうならフラグ折ります．
    tmp = 1;
    // uuu
    board_display(map);
  } while (othello_game(map, pmap, &turn_flag) == 0);  // 値だけでいい
  // 成功したら0を返す．失敗で1とか返したい．
  printf("finish");
  return 0;
}

int read_map_file(const char* fname, /*ファイル名*/
                  char map[8][8] /*盤面記憶配列*/) {
  int x, y;
  char buf[81];
  FILE* fp;

  if ((fp = fopen(fname, "r")) == NULL) return 1;

  fgets(buf, sizeof(buf), fp);
  for (y = 0; y < 8; ++y) {
    fgets(buf, sizeof(buf), fp);
    map[y][0] = atoi(strtok(buf, ","));
    for (x = 1; x < 8; ++x) map[y][x] = atoi(strtok(NULL, ","));
  }
  fclose(fp);
  return 0;
}

int map_reset(char map[8][8]) {
  for (int i; i < 8; i++) {
    for (int j; j < 8; j++) {
      map[i][j] = 0;
    }
  }
  map[3][3] = 1;
  map[3][4] = -1;
  map[4][3] = -1;
  map[4][4] = 1;
  if (map_save(map)) return 1;
  return 0;
}

int map_save(char map[8][8]) {
  FILE* fp;
  if ((fp = fopen("map1.csv", "w")) == NULL)
    return 1;  // 内容消し飛ばして書き込み
  fprintf(fp, "8, 8\n");
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 7; j++) {  // 途中まで"値, "を出力
      fprintf(fp, "%d, ", map[i][j]);
    }
    fprintf(fp, "%d\n", map[i][7]);  // 最後の行にはカンマではなく改行を出力
  }
  fclose(fp);
  return 0;
}

int othello_game(char map[8][8], double pmap[8][8],
                 int* player) {  // ターン一回分
  char buf[81];
  char* tmp;
  int x_in, y_in;
  int dx = 1, dy = -1, tmp_int, i, j, k, count;
  printf(
      "座標を入力してください．横軸をaからhのアルファベットで表します．例:a,"
      "0\n");
  fgets(buf, sizeof(buf), stdin);
  tmp = strtok(buf, ",");  // 文字コードが欲しい
  x_in = *tmp - (int)'a';
  // 文字コード97が小文字のaだから，こう書けば入力がaの時x_inは0になる．
  y_in = atoi(strtok(NULL, "\0"));
  if (pmap[y_in][x_in] == 0) {
    printf("置けません");
    Sleep(1000);
    *player *= -1;
    return 0;
  }
  if ((x_in > 8) && (x_in < 0) && (y_in > 8) && (y_in < 0)) {
    printf("入力する値がおかしい\n");
    return EXIT_FAILURE;
  }
  // printf("%d,%d", x_in, y_in);
  if (map[y_in][x_in] == 0)  // コマがおいてなければ
    for (i = 0; i < 8; ++i) {  // すべての方向に敵のコマがないか確認する.
      tmp_int = dx;
      dx -= dy;
      dy += tmp_int;
      dx = ADJ(dx);
      dy = ADJ(dy);
      for (j = y_in + dy, k = x_in + dx, count = 0;  // 周りにあるのはなにか
           ((j > 0) && (j < 8) && (k > 0) && (k < 8)); j += dy, k += dx,
          count++) {  // 盤面内なら動作する．各方向にみょ～んって伸ばしていく．
        if (*player * map[j][k] == 0) {
          break;  // コマがなければこれ以降比較の意味はなし．
        }
        if (((*player * map[j][k]) > 0)) {  // もし自分のコマを見つけた時
          if (((ABS(k - x_in) + ABS(j - y_in)) / (ABS(dy) + ABS(dx))) > 1) {
            // (|x|+|y|)/(|dx|+|dy|)>=2ならヨシひっくり返そう！
            // ひっくり返す処理が入る．
            turn_over(map, dx, dy, x_in, y_in, count,*player);
            map[y_in][x_in] = *player;
            // 方向の座標，コマ置く座標，自分の駒までに何回ループしたか
            // printf("%d", map[y_in + dy][x_in + dx]);
          } else {
            // そうじゃなければ次ループへ
            break;
          }
        }
      }
    }  // 8方向に対して見終わる
  // board_display(map, 1);
  map_save(map);
  return 0;
}

void turn_over(char map[8][8], int dx, int dy, int x_in, int y_in, int count, int player) {
  int i, j;
  for (i = 1; i <= count; i++) {
    if(map[y_in + dy * i][x_in + dx * i] == player*-1)
    map[y_in + dy * i][x_in + dx * i] *= -1;
  }
  return;
}

void board_display(char map[8][8]) {
  HANDLE hStdOut;
  COORD position;
  DWORD numWritten;
  WORD color;

  system("cls");

  hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hStdOut, BACKGROUND_GREEN);
  printf("   a  b  c  d  e  f  g  h \n");
  printf(" -------------------------\n");
  printf("0|●|●|●|●|●|●|●|●|\n");
  printf(" -------------------------\n");
  printf("1|●|●|●|●|●|●|●|●|\n");
  printf(" -------------------------\n");
  printf("2|●|●|●|●|●|●|●|●|\n");
  printf(" -------------------------\n");
  printf("3|●|●|●|●|●|●|●|●|\n");
  printf(" -------------------------\n");
  printf("4|●|●|●|●|●|●|●|●|\n");
  printf(" -------------------------\n");
  printf("5|●|●|●|●|●|●|●|●|\n");
  printf(" -------------------------\n");
  printf("6|●|●|●|●|●|●|●|●|\n");
  printf(" -------------------------\n");
  printf("7|●|●|●|●|●|●|●|●|\n");
  printf(" -------------------------\n");

  color =
      FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | BACKGROUND_GREEN;
  // position.X = 10;
  // position.Y = 7;
  // FillConsoleOutputAttribute(hStdOut, color, 2, position, &numWritten);
  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 8; x++) {
      position.X = x * 3 + 2;
      position.Y = y * 2 + 2;
      if (map[y][x] == 0) {  // 緑着色
        color = FOREGROUND_GREEN | BACKGROUND_GREEN;
        FillConsoleOutputAttribute(hStdOut, color, 2, position, &numWritten);

      } else if (map[y][x] == -1) {  // 黒着色
        color = BACKGROUND_GREEN;
        FillConsoleOutputAttribute(hStdOut, color, 2, position, &numWritten);

      } else if (map[y][x] == 1) {  // 白着色
        color = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED |
                BACKGROUND_GREEN;
        FillConsoleOutputAttribute(hStdOut, color, 2, position, &numWritten);
      } else {  // 値がおかしい場合赤着色
        color = FOREGROUND_RED | BACKGROUND_GREEN;
        FillConsoleOutputAttribute(hStdOut, color, 2, position, &numWritten);
      }
    }
  }
  color = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
  SetConsoleTextAttribute(hStdOut, color);
  return;
}

int put_search(char map[8][8], double pmap[8][8], int player) {
  // printf("a");
  char* tmp;
  int x_in, y_in;
  int dx = 1, dy = -1, tmp_int, i, j, k, count, put_possible = 0;
  for (y_in = 0; y_in < 8; y_in++) {
    for (x_in = 0; x_in < 8; x_in++) {
      if (map[y_in][x_in] == 0)  // コマがおいてなければ
        for (i = 0; i < 8; ++i) {  // すべての方向に敵のコマがないか確認する.
          tmp_int = dx;
          dx -= dy;
          dy += tmp_int;
          dx = ADJ(dx);
          dy = ADJ(dy);
          for (
              j = y_in + dy, k = x_in + dx, count = 0;  // 周りにあるのはなにか
              ((j > 0) && (j < 8) && (k > 0) && (k < 8)); j += dy, k += dx,
             count++) {  // 盤面内なら動作する．各方向にみょ～んって伸ばしていく．
            if (player * map[j][k] == 0) {
              break;  // コマがなければこれ以降比較の意味はなし．
            }
            if (((player * map[j][k]) > 0)) {  // もし自分のコマを見つけた時
              if (((ABS(k - x_in) + ABS(j - y_in)) / (ABS(dy) + ABS(dx))) > 1) {
                // (|x|+|y|)/(|dx|+|dy|)>=2ならヨシひっくり返そう！
                // ひっくり返す処理が入る．
                // turn_over(map, dx, dy, x_in, y_in, count);
                pmap[y_in][x_in] += ((ABS(k - x_in) + ABS(j - y_in)) /
                                     (ABS(dy) + ABS(dx)));  // おける方向の合計
                put_possible++;
                // 方向の座標，コマ置く座標，自分の駒までに何回ループしたか
                printf("%d,%d,%d\n", put_possible, x_in, y_in);
              } else {
                // そうじゃなければ次ループへ
                break;
              }
            }
          }
        }  // 8方向に対して見終わる
    }
  }
  return put_possible;  //
}