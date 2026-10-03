#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/ioctl.h>
#include <linux/limits.h>
int main(int argc, char** argv) {

char srcdd[4096];
struct winsize w;
ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
bool smd = false;
int nl = 0;
if (!argv[1]) strcpy(srcdd, ".");
else strcpy(srcdd, argv[1]);
DIR *dir;
char ascc[4096] = "";
char end[] = "";
struct dirent *ent;
struct stat sb;
if ((dir = opendir (srcdd)) != NULL) {
  while ((ent = readdir (dir)) != NULL) {
        strcpy(ascc, "");
   if (nl == w.ws_col / 5) {
        printf("\n");
        nl = 0;
   }
   smd = false;
   if (stat(ent->d_name, &sb) == 0 && S_ISDIR(sb.st_mode) ) strcpy(ascc, "\033[0;34m");
   else if (stat(ent->d_name, &sb) == 0 && sb.st_mode & S_IXUSR) strcpy(ascc, "\033[0;32m");
   else smd = true;
   if (!smd) printf ("%s%s%s ",ascc, ent->d_name, end);
   else printf("\033[0m%s ", ent->d_name);
   nl++;
}
  closedir(dir);
} else {
        printf("\n");
        return 1;
}
printf("\n");
}
