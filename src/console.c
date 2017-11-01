#include "console.h"
void Number(char *msg, int *dest)
{
    printf(" %s", msg);
    scanf("%d", dest);
}

void Double(char *msg, double *dest)
{
    printf(" %s", msg);
    scanf("%lf", dest);
}

void String(char *msg, char *dest)
{
    // fflush(stdout);
    // fflush(stdin);
    // getchar();
    printf(" %s", msg);
    do {
        fgets(dest, MAXLINE, stdin);
    } while(strlen(dest) < 2);
    char *newline = strchr(dest,'\n');
    *newline = '\0';
}

void NewLine()
{
    printf("\n");
}

void Intervalo(char *msg,int *dest, int menor, int mayor) {
    do {
        printf(" %s", msg);
        scanf("%d", dest);
    } while((*dest < menor) || (*dest > mayor));
}