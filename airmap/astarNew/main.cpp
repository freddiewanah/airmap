//
//  main.cpp
//  astarNew
//
//  Created by nmchgx on 15/4/11.
//  Copyright (c) 2015年 nmchgx. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <queue>
#include <stdlib.h>

using namespace std;

struct Dot{
    int x;
    int y;
    int z;
    int f;
    int g;
    int h;
    int status;
    int Fx;
    int Fy;
    friend bool operator < (Dot a, Dot b)
    {
        if (a.h == b.h)
            return a.f > b.f; //结构体中，x小的优先级高
        return a.h > b.h;
    }
}dot[110][110];

priority_queue<Dot>q;
Dot Start, End, now;

int arr[16] = { 0, 1, 1, 0, -1, 0, 0, -1, 1, 1, -1, -1, 1, -1, -1, 1 };

bool canbe(int x, int y)
{
    if (x >= 0 && x < 100 && y >= 0 && y < 100 && dot[x][y].status != 1){
        return true;
    }
    return false;
}

void Recall(Dot now)
{
    int i = 1;
    printf("(%d,%d),", now.x, now.y);
    while (now.Fx >= 0) {
        now = dot[now.Fx][now.Fy];
        //printf("%d\n", i++);
        printf("(%d,%d),", now.x, now.y);
    }
}

bool Search(Dot now, int value, int startarr, int endarr) {
    int x = now.x, y = now.y;
    bool flag = false;
    for (int i = startarr; i < endarr; i++) {
        if (canbe(x + arr[2 * i], y + arr[2 * i + 1])) {
            Dot *current = &dot[x + arr[2 * i]][y + arr[2 * i + 1]];
            if ((*current).status == 2) {
                (*current).g = now.g + value;
                (*current).Fx = now.x;
                (*current).Fy = now.y;
                printf("%d\n", (*current).g);
                Recall((*current));
                flag = true;
                break;
            }
            if ((*current).g > now.g + value) {
                (*current).g = now.g + value;
                (*current).h = abs((*current).x - End.x)
                + abs((*current).y - End.y);
                (*current).f = (*current).g + (*current).h;
                (*current).Fx = now.x;
                (*current).Fy = now.y;
                q.push((*current));
                //printf("{%d,%d}\n", (*current).Fx, (*current).Fy);
            }
        }
    }
    return flag;
}

int main(void) {
    int startX, startY, endX, endY;
    scanf("%d %d %d %d", &startX, &startY, &endX, &endY);
    
    //memset(dot, 0, sizeof(dot));
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            //dot[i][j] = new Dot();
            dot[i][j].x = i;
            dot[i][j].y = j;
            dot[i][j].f = 10000;
            dot[i][j].g = 10000;
            dot[i][j].h = 0;
            dot[i][j].status = 0;
            dot[i][j].Fx = -1;
            dot[i][j].Fy = -1;
        }
    }
    End = dot[endX][endY];
    dot[endX][endY].status = 2;
    dot[startX][startY].g = 0;
    Start = dot[startX][startY];
    
    Start.h = abs(Start.x - End.x) + abs(Start.y - End.y);
    Start.f = Start.g + Start.h;
    //printf("h=%d\nf=%d\n", Start.h, Start.f);
    
    q.push(Start);
    
    while (!q.empty())
    {
        now = q.top();
        //printf("[%d,%d],", now.x, now.y);
        q.pop();
        
        if (now.status == 1){
            continue;
        }
        
        if (Search(now, 10, 0, 4)){
            break;
        }
        else {
            if (Search(now, 14, 4, 8)){
                break;
            }
        }
        dot[now.x][now.y].status = 1;
    }
    return 0;
}
