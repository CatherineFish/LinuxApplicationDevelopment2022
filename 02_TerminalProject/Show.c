#include <ncurses.h>
#include <stdlib.h>

#define DX 3

int max(int a, int b);
int min(int a, int b);


int max(int a, int b)
{
    return a >= b ? a : b;
}

int min(int a, int b)
{
    return a <= b ? a : b;
}

int main(int argc, char* argv[])
{
    unsigned fileSize;
    char *buffer, charBuffer, **lineBuffer;
    int control = 0, currentSize = 0, lineCnt = 0, longestStr = 0, curLine = 0, i, j = 0, m = 0;
    int start = 0, addStr = 0;
    bool notEnd = TRUE;
    FILE *file;
    
    if (argc < 2)
    {
        printf("No file name\n");
        exit(1);
    }

    if ((file = fopen(argv[1],"r")) == NULL)
    {
       printf("Error opening file");
       exit(1);
    }

    fseek(file, 0, SEEK_END); 
    fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    buffer = (char*)malloc(sizeof(char) * (fileSize + 1));
    if (buffer == NULL)
    {
        printf("Malloc error\n");
        exit(1);
    }

    WINDOW *win;
    initscr();
    noecho();
    cbreak();
    printw("File: %s; size: %d", argv[1], fileSize);
    refresh();

    win = newwin(LINES - 2 * DX, COLS - 2 * DX, DX, DX);
    scrollok (win, TRUE);
    keypad(win, TRUE);

    box(win, 0, 0);
    wmove(win, 1, 0);
    do
    {
        charBuffer = fgetc(file);
        if (charBuffer =='\n')
        {
            lineCnt++;
            if (curLine > longestStr)
            {
                longestStr = curLine;
            }
            curLine = 0;
        }
        buffer[currentSize++] = charBuffer;
        curLine++;
    } while (charBuffer != EOF);
    
    lineCnt++;

    lineBuffer = (char**)malloc(sizeof(char*) * (lineCnt + 1));
    if (lineBuffer == NULL)
    {
        printf("Malloc error\n");
        exit(1);
    }
    for (i = 0; i < lineCnt; i++)
    {
        m = 0;
        lineBuffer[i] = (char*)malloc(sizeof(char) * (longestStr + 1));
        if (lineBuffer[i] == NULL)
        {
            printf("Malloc error\n");
            exit(1);
        }
        while(buffer[j] && buffer[j] != '\n')
        {
            lineBuffer[i][m] = buffer[j];
            m++;
            j++;
        }
        lineBuffer[i][m] = '\0';
        j++;
    }
    while(notEnd) 
    {
        werase(win);
        wmove(win, 1, 0);
        start = max(0, min(addStr, lineCnt - 1));
        for (i =start ; i < min(lineCnt, start + LINES - 2 * DX - 2); i++)
        {
            wprintw(win, "%4d %s\n", i, lineBuffer[i]);
        }
        box(win, 0, 0); 
        wrefresh(win);
        control = wgetch(win);
        if (control == 27)
        {
            notEnd = FALSE;
        } else if (control == 32 || control == KEY_DOWN)
        {
            if (addStr < lineCnt - 1)
                addStr++;
        } else if (control == KEY_UP)
        {
            if (addStr)
                addStr--;
        }
        
    }
    endwin();
    if (buffer)
        free(buffer);
    for (i = 0; i < lineCnt; i++)
        free(lineBuffer[i]);
    if (lineBuffer)
        free(lineBuffer);
    fclose(file);
    return 0;
}