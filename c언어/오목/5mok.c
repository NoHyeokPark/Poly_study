#include <stdio.h>
#include <stdlib.h>

#define SIZE 9

int plane[SIZE][SIZE];
int u, v;
int color = 0;
int win = 0;

int checkWin(int v, int u);

int* Auto(int len) {
    int dx[4] = {1,0,1,1}, dy[4] = {0,1,1,-1};
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            int stone = plane[row][col];
            if (!stone) continue;
            for (int dir = 0; dir < 4; dir++) {
                int cnt = 1;
                for (int k = 1; k < len; k++) {
                    int nr = row + dy[dir]*k;
                    int nc = col + dx[dir]*k;
                    if (nr<0||nr>=SIZE||nc<0||nc>=SIZE||plane[nr][nc]!=stone)
                        break;
                    cnt++;
                }
                if (cnt == len) {
                    // 양끝 자리 계산
                    int br = row - dy[dir], bc = col - dx[dir];
                    if (br>=0&&br<SIZE&&bc>=0&&bc<SIZE&&plane[br][bc]==0) {
                        v = br;
                        u = bc;
                        return &plane[br][bc];
                    }
                    int fr = row + dy[dir]*len, fc = col + dx[dir]*len;
                    if (fr>=0&&fr<SIZE&&fc>=0&&fc<SIZE&&plane[fr][fc]==0) {
                        v = fr;
                        u = fc;
                        return &plane[fr][fc];
                    }         
                }
            }
        }
    }
    return Auto(len - 1);
}

int checkWin(int v, int u){
    int dx[4] = {1, 0, 1, 1};
    int dy[4] = {0, 1, 1, -1};
    int stone = plane[v][u];
    for (int dir = 0; dir < 4; dir++) {
        int cnt = 1;
        for (int step = 1; step < 5; step++) {
            int nx = u + dx[dir] * step;
            int ny = v + dy[dir] * step;
            if (nx < 0 || nx >= SIZE || ny < 0 || ny >= SIZE || plane[ny][nx] != stone)
                break;
            cnt++;
        }
        for (int step = 1; step < 5; step++) {
            int nx = u - dx[dir] * step;
            int ny = v - dy[dir] * step;
            if (nx < 0 || nx >= SIZE || ny < 0 || ny >= SIZE || plane[ny][nx] != stone)
                break;
            cnt++;
        }
        if (cnt >= 5)
            return 1;
    }
    return 0;
}

void InputPosition(){
    while (1) {
        if (color == 0) {
            printf("Player's turn\ninput number(x y): ");
             if (scanf("%d %d", &u, &v) != 2) {
                printf("Invalid input. Try again.\n");
                while (getchar() != '\n');
                continue;
            }
            if (u >= 0 && u < SIZE && v >= 0 && v < SIZE && plane[v][u] == 0) {
                plane[v][u] = color + 1;
                break;
            } else {
                printf("Invalid move, try again.\n");
            }
        } else {
            printf("Computer's turn...\n");
            int* point = Auto(4);
            if(point)
            *point = 2;
            break;
        }
        
    }
    
    win = checkWin(v, u);
    
}

int main(){
    for (int y = 0; y < SIZE; y++)
        for (int x = 0; x < SIZE; x++)
            plane[y][x] = 0;

    while (1) {
        printf("\nComputer Stone : 2\nPlayer Stone : 1\n0 1 2 3 4 5 6 7 8\n-----------------\n");
        for (int y = 0; y < SIZE; y++) {  
            for (int x = 0; x < SIZE; x++)
                printf("%d ", plane[y][x]);
            printf("|%d ", y);
            printf("\n");
        }
        if (win) {
            if (color == 0)
                printf("Computer wins!\n");
            else
                printf("Player wins!\n");
            break;
        }
        InputPosition();
        color = 1 - color;
    }
    return 0;
}