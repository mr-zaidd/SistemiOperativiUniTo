#include "../include/inc.h"


typedef struct node{
    int x,y;
}node;

void bfs(int startx, int starty, int endx, int endy){

    int i;
    int rr;
    int cc;
    int dr[4] = {-1, +1, 0, 0};
    int dc[4] = {0, 0, +1, -1};

    for(i = 0; i < 4; i++){

        rr = startx + dr[i];
        cc = starty + dc[i];

        if(rr < 0 || cc < 0)
            continue;
        if(rr >= H || cc >= W)
            continue;

    }

}
