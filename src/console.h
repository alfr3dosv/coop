// Console.h
// Una libreria que facilita la creacion de interfaces simple

#ifndef CONSOLE_H
#define CONSOLE_H
#include <stdio.h>
#include <string.h>
#include "data/data.h"

void Number(char *, int *);
void Double(char *, double *);
void String(char *, char *);
void NewLine(void );
void Intervalo(char *msg, int *dest, int menor, int mayor);

#endif