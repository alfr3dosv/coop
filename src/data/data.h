#ifndef DATA_H
#define DATA_H

#define MAXLINE 1000
#define MAXDESCR 1000000
#define MAXLINES 1000

// estructuras auxiliare
typedef struct {
    int hora;
    int dia;
    int mes;
    int ano;
    int minuto;
} Fecha;

typedef struct {
    int size;
    char *str;
} BigString;


#endif