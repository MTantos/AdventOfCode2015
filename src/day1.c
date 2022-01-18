#include <stdio.h>

int main(int argc, char const *argv[])
{
    FILE *fp;
    int c, count, i;

    fp = fopen("../input/day1.txt", "r");
    if (fp == NULL) {
        perror("Error in opening file");
        return(-1);
    }

    // Part 1
    count = 0;
    while ((c = fgetc(fp)) != EOF) {
        if (c == '(') {
            count++;
        } else {
            count--;
        }
    }
    printf("Count: %d\n", count);

    // Part 2
    fseek(fp, 0, 0);
    i = count = 0;
    while (((c = fgetc(fp)) != EOF) && (count != -1)) {
        ++i;
        if (c == '(') {
            count++;
        } else {
            count--;
        }
    }
    printf("First time in basement: %d\n", i);

    fclose(fp);
    return 0;
}
