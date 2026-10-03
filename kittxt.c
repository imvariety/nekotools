#include <stdio.h>
#include <termios.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#define ESC 27
#define BACKSPACE 127
#define cursor(x,y) printf("\033[%d;%dH", (y), (x));
void clear() {
printf("\033[H\033[J");
}
void cursorn(int x, int y) {
        if (x <= 0) return;
        if (y <= 0) return;
        cursor(x, y);
}
int main() {
        clear();
        char mott[] = "Neko Edit luvs you >:3";
        printf("%s\n", mott);
        char prompt[100] = "\033[35m~\033[0m \n";
        int promptvsz = 3;
        int cx = promptvsz;
        int cy = 3;
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        int c;
        int ln = 0;
        for (int x=0; x<w.ws_col; x++) printf("─");
        printf("\n");
        for (int i=0; i<(w.ws_row - 3); i++) printf("%s", prompt);
        cursor(cx, cy);
        system("stty -icanon -echo");
        while (1) {
                c = getchar();
                if (c == '\n') {
                        cx = promptvsz;
                        cy++;
                        ln++;
                        cursorn(cx, cy);
                        continue;
                }
                if (c == BACKSPACE) {
                        cx--;
                        cursorn(cx, cy);
                        printf("\033[2K\rverity");
                        fflush(stdout);
                        continue;
                }
                if (c == ESC) {
                        cursor(w.ws_row, 1);
                        printf("\033[2K\rUh-oh.. you have unsaved content! I to ignore.");
                        if (tolower(getchar()) == 'i') break;
                }
                cx++;
                printf("%c", c);
                fflush(stdout);
        }
        system("stty icanon echo");
        clear();
}
