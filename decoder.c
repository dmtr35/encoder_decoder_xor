#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int check_symbol(int m) {
    if (m >= 32 && m <= 127) {
        return 1;
    } else {
        return 0;
    }
}

int main(int argc, char *argv[])
{
    if (argc < 3) {
        printf("Usage: %s <FILENAME_FROM> <FILENAME_TO>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    char *from = argv[1];
    char *to = argv[2];
    int leng_buf = 0;
    int copy_c = 0;
    int m;
    int j;
    _Bool br = 0;

    FILE *fd_from = fopen(from, "rb");
    if (fd_from == NULL) {
        printf("[*] Cannot open '%s'\n", from);
        exit(EXIT_FAILURE);
    }
    FILE *fd_to = fopen(to, "wb");
    if (fd_to == NULL) {
        printf("[*] Cannot open '%s'\n", to);
        fclose(fd_from);
        exit(EXIT_FAILURE);
    }


    while(fgetc(fd_from) != EOF) {
        leng_buf++;
    }
    rewind(fd_from);

    char *buf = malloc(leng_buf + 1);
    if (!buf) {
        perror("malloc");
        fclose(fd_from);
        exit(EXIT_FAILURE);
    }

    int q = 0;
    for (int i = 0; i < leng_buf; ++i) {
        q = fgetc(fd_from);
        buf[i] = (char)q;
    }
    buf[leng_buf] = '\0';


    for (int c = 1; c <= 127; c++) {
        copy_c = c;
        for (int i = 0; i < leng_buf; ++i) {
            j = buf[i];
            m = c ^ j;
            c = j;
            int check = check_symbol(m);
            if (check) {
                fputc((char)m, fd_to);
            } else {
                br = 1;
                break;
            }
        }
        if (!br)
            fputc('\n', fd_to);
        br = 0;    
        c = copy_c;
    }


    fclose(fd_from);
    fclose(fd_to);

    return 0;
}
