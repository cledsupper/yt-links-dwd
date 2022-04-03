#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[]) {
    FILE * flist;

    if (argc != 2) {
        fprintf(stderr, "Erro na linha de comando: insira o nome/endereço do arquivo para começar\n");
        fprintf(stderr, "1. Os endereços dos vídeos devem ser no formato: https://www.youtube.com/watch?v=xxxxxxxxxxx\n");
        fprintf(stderr, "2. Os endereços devem ser separados por quebras de linha, sem caracteres especiais!\n");
        return 1;
    }

    flist = fopen(argv[1], "r");
    if (!flist) {
        perror("Erro");
        return errno;
    }

    bool ok = true;
    while (true) {
        char link[100];
        ok = fgets(link, 99, flist) != NULL;
        if (!ok) break;
        link[strlen(link)-1] = 0;

        char cmd[135];
        snprintf(cmd, 135, "youtube-dl -x --audio-format mp3 %s", link);
        puts(cmd);
    }
    fclose(flist);

    return 0;
}
