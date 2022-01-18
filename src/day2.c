#include <stdio.h>
#define COUNT 1000

typedef struct {
    char l, w, h;
} Box;

int parse_input(FILE *fp, Box *boxes);
long calc_total_wrapping_area(Box *boxes, int count);
long calc_wrapping_area(Box *box);
long calc_total_ribbon_length(Box *boxes, int count);
long calc_ribbon_length(Box *boxes);

int main(int argc, char const *argv[])
{
    FILE *fp;
    Box boxes[COUNT];
    long wrapping_amount, ribbon_length;
    fp = fopen("../input/day2.txt", "r");
    if (fp == NULL) {
        perror("Error in opening file");
        return(-1);
    }
    parse_input(fp, boxes);
    fclose(fp);

    // Part 1
    wrapping_amount = calc_total_wrapping_area(boxes, COUNT);
    printf("Square feet of wrapping paper required: %ld\n", wrapping_amount);

    // Part 2
    ribbon_length = calc_total_ribbon_length(boxes, COUNT);
    printf("Total feet of ribbon required: %ld\n", ribbon_length);

    return 0;
}

int parse_input(FILE *fp, Box *boxes)
{
    int i = 0;
    char c, side;
    while ((c = fgetc(fp)) != EOF) {
        // get length
        side = c - '0';
        while ((c = fgetc(fp)) != 'x') {
            side *= 10;
            side += c - '0';
        }
        boxes[i].l = side;
        // get width
        side = 0;
        while ((c = fgetc(fp)) != 'x') {
            side *= 10;
            side += c - '0';
        }
        boxes[i].w = side;
        // get height
        side = 0;
        while ((c = fgetc(fp)) != '\n') {
            side *= 10;
            side += c - '0';
        }
        boxes[i].h = side;
        ++i;
    }
    return i;
}

long calc_total_wrapping_area(Box *boxes, int count)
{
    long result = 0;
    int i;
    for (i = 0; i < count; ++i) {
        result += calc_wrapping_area(&boxes[i]);
    }
    return result;
}

long calc_wrapping_area(Box *box)
{
    int s1, s2, s3, min;
    s1 = box->l * box->w;
    s2 = box->w * box->h;
    s3 = box->h * box->l;
    min = s1 < s2 ? (s1 < s3 ? s1 : s3) : (s2 < s3 ? s2 : s3);
    return ((s1 + s2 + s3) << 1) + min;
}

long calc_total_ribbon_length(Box *boxes, int count)
{
    long result = 0;
    int i;
    for (i = 0; i < count; ++i) {
        result += calc_ribbon_length(&boxes[i]);
    }
    return result;
}

long calc_ribbon_length(Box *box)
{
    char s1,s2;
    if (box->l < box->w) {
        s1 = box->l;
        s2 = box->w;
    } else {
        s1 = box->w;
        s2 = box->l;
    }
    if (box->h < s2) {
        s2 = box->h;
    }
    return ((s1+s2) << 1) + box->l*box->w*box->h;
}
