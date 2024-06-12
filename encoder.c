#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// The flag looks like FLAG{md5}

void encode(const char *filename, const char *text)
{
    FILE *fd = fopen(filename, "wb");
    if (fd == NULL) {
        printf("[*] Cannot open '%s'\n", filename);
        exit(EXIT_FAILURE);
    }

    int c = 0x7f;
    printf("[*] Initialize number: 0x%02x\n", c);
    for (size_t i = 0; i < strlen(text); i++) {
        fputc(c ^ text[i], fd);
        c ^= text[i];
    }

    fclose(fd);
}

void decode(const char *filename)
{
    FILE *fd = fopen(filename, "rb");
    if (fd == NULL) {
        printf("[*] Cannot open '%s'\n", filename);
        exit(EXIT_FAILURE);
    }

    int leng_string = 0;
    int c = 0x7f;
    int m;
    int j;

    while(fgetc(fd) != EOF) {
        leng_string++;
    }
    rewind(fd);

    char *string = malloc(leng_string + 1);
    if (!string) {
        perror("malloc");
        fclose(fd);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < leng_string; ++i) {
        j = fgetc(fd);
        if (j == EOF) {
            break;
        }
        m = c ^ j;
        c = j;

        string[i] = (char)m;
    }
    string[leng_string] = '\0';
    printf("%s\n", string);

    fclose(fd);
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
    if (argc < 3) {
        printf("Usage: %s <FILENAME> <TEXT>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (strcmp(argv[1], "-d") == 0) {
        decode(argv[2]);
    }

    printf("[*] Encoding...\n");
    encode(argv[1], argv[2]);

    printf("[*] Result in '%s'\n", argv[1]);

    exit(EXIT_SUCCESS);
}
