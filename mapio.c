/* MAP フ ァ イ ル 読 み 込 み */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* リ タ ー ン 値 （0 : 読 み 込 み 失 敗 、1 : 読 み 込 み 成 功 ） */
int read_map_file(const char* fname, /* フ ァ イ ル 名 */
                  char map[8][8]     /* 盤 面 記 憶 配 列 */
) {
  int x, y;
  char buf[81];
  FILE* fp;

  if ((fp = fopen(fname, "r")) == NULL) return 0;

  fgets(buf, sizeof(buf), fp);
  for (y = 0; y < 8; ++y) {
    fgets(buf, sizeof(buf), fp);
    map[y][0] = atoi(strtok(buf, ","));
    for (x = 1; x < 8; ++x) map[y][x] = atoi(strtok(NULL, ","));
  }
  fclose(fp);
  return 1;
}

