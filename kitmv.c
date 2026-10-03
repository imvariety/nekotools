#include <stdio.h>
int main(int argc, char** argv) {
        if (argc < 3) {
                printf("Neko: Too less arguments. Try at least 4.");
          return 1;
        }
        rename(argv[1], argv[2]);
}
