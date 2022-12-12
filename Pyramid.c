/* Pyramid.c
 * a pascals pyramid generator for large sizes
 * This program prints the first N rows of a number pyramid
 * where N is a number entered by the user.
 * The first row has 1, the second row has 2, the third row has 3, etc.
 * where the value of each number is the sum of its parents
 * (the two numbers above it).
 * returns 0 on success
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


void pyramidtoterm(int height);
void pyramidtofile(int height, FILE* fp);

int main(int argc, char *argv[])
{
    int n=10;
    int f=0;
    int c;
    //get flags from command line
    //if -h is present, print help message and exit
    //if -f is present, print to file
    //if -n is present, set the height of the pyramid
    //if no flags are present, print to console
    while ((c = getopt(argc, argv, "hfn:")) != -1) {
        switch (c) {
            case 'h':
                printf("Pyramid.c\n\r");
                break;
            case 'f':
                f = 1;
                break;
            case 'n':
                n = atoi(optarg);
                break;
            default:
                break;
        }
    }
    if (f) {
        FILE *fp = fopen("pyramid.txt", "w");
        if (fp == NULL) {
            printf("Error opening file!\n");
            exit(1);
        }
        pyramidtofile(n, fp);
        fclose(fp);
    } else {
        pyramidtoterm(n);
    }
    return 0;
}

void pyramidtoterm(int height){
    long long *currentRow = calloc(height, sizeof(long long));
    long long *previousRow = calloc(height, sizeof(long long));
    currentRow[0] = 1;
    
    for (long long i = 1; i < height; i++) {
        //print " " (space) height - i times
        for (int j = 0; j < height - i; j++) {
            printf("          ");
        }
        //print the current row
        for (int j = 0; j < i; j++) {
            printf("%20lld", currentRow[j]);
        }
        printf("\n\r");
        // swap the current and previous rows
        long long *temp = currentRow;
        currentRow = previousRow;
        previousRow = temp;

        //calculate the next row
        for (int j = 0; j < i + 1; j++) {
            if (j == 0) {
                currentRow[j] = previousRow[j];
            } else if (j == i) {
                currentRow[j] = previousRow[j - 1];
            } else {
                currentRow[j] = previousRow[j - 1] + previousRow[j];
            }
        }
    }
    //print the last row
    for (int j = 0; j < height; j++) {
        printf("%20lld", currentRow[j]);
    }
    printf("\n\r");
    //free the memory
    free(currentRow);
    free(previousRow);
}
void pyramidtofile(int height, FILE *fp){
    long long *currentRow = calloc(height, sizeof(long long));
    long long *previousRow = calloc(height, sizeof(long long));
    currentRow[0] = 1;
    
    for (int i = 1; i < height; i++) {
        //print " " (space) height - i times
        for (int j = 0; j < height - i; j++) {
            fprintf(fp, "          ");
        }
        //print the current row
        for (int j = 0; j < i; j++) {
            fprintf(fp, "%20lld", currentRow[j]);
        }
        fprintf(fp, "\n\r");
        // swap the current and previous rows
        long long *temp = currentRow;
        currentRow = previousRow;
        previousRow = temp;

        //calculate the next row
        for (int j = 0; j < i + 1; j++) {
            if (j == 0) {
                currentRow[j] = previousRow[j];
            } else if (j == i) {
                currentRow[j] = previousRow[j - 1];
            } else {
                currentRow[j] = previousRow[j - 1] + previousRow[j];
            }
        }
    }
    //print the last row
    for (int j = 0; j < height; j++) {
        fprintf(fp, "%20lld", currentRow[j]);
    }
    fprintf(fp, "\n\r");
    //free the memory
    free(currentRow);
    free(previousRow);
}


