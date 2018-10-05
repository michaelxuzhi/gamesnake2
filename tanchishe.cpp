#include <stdio.h>  
#include <Windows.h>  
#include <conio.h>  
#include <time.h>  
  
#define MAX_WIDE  50  
#define MAX_HIGH  16  
  
short dx = 1, dy = 0, randxy, score = 0;  
COORD coord;  
  
struct Snake{  
    short len;  
    short body[MAX_WIDE*MAX_HIGH];  
}snake;  
  
void draw()  
{  
    for(short i = 0; i < snake.len; i++){  
        coord.X = snake.body[i] & 127;  
        coord.Y = snake.body[i] >> 8;  
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);  
        putchar('*');  
    }  
    coord.X = randxy & 127;  
    coord.Y = randxy >> 8;  
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);  
    putchar('*');  
}  
void  run()  
{  
    char key;  
    short i, j;  
    while( snake.body[0] > 0 && ( (snake.body[0] & 127) < MAX_WIDE) && (snake.body[0]>>8 < MAX_HIGH) ){  
        draw();  
        for(;kbhit();)  key = getch();  
        switch(key){  
        case 'W': dx = 0, dy = -1; break;  
        case 'S': dx = 0, dy = 1; break;  
        case 'A': dx = -1, dy = 0; break;  
        case 'D': dx = 1, dy = 0; break;  
        }  
        for(j = 1; j < snake.len; j++)  
            if(snake.body[j] == snake.body[0])  
                return;  
        if(randxy == snake.body[0]){  
                snake.len++, score += 10;  
                randxy = ((rand() % 16 + 0) <<8) | (rand() % 50 + 0);  
        }  
        for(i = snake.len-1; i > 0; i--)  
            snake.body[i] = snake.body[i-1];  
        snake.body[0] = ((snake.body[0] & 127) + dx) | ((snake.body[0] >>8) + dy)<<8;  
        Sleep(500);  
        system("cls");    
    }  
}  
int main()  
{  
    snake.body[MAX_WIDE*MAX_HIGH] = 0;  
    snake.body[0] = (MAX_HIGH/2)<<8 | MAX_WIDE/2;  
    snake.len = 1;  
    srand((unsigned)time(NULL));   
    randxy = ((rand() % 16 + 0) <<8) | (rand() % 50 + 0);  
    SMALL_RECT rect;  
    rect.Top = 0, rect.Left = 0;  
    rect.Bottom = MAX_HIGH, rect.Right  = MAX_WIDE;  
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), true, &rect);  
    run();  
    printf("Your Score:%d", score);  
    return 0;  
}