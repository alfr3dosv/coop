#ifndef CONSULTAS_H
#define CONSULTAS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "data.h"
#include "StringList.h"
#include "citas.h"
#include "../objects.h"
#include "../files.h"
#include "../console.h"

//consultas
typedef struct {
    int id;
    int folio;
    char *descripcion;
    StringList *medicamentos;
    struct Consulta_vt *vt;
} Consulta;

//global
extern Consulta *consulta_this;
extern int g_consultas_elements;
extern int g_consultas_size;
extern Consulta *g_consultas[];

//init
Consulta *consulta_new();
//setters
void consulta_setThis(Consulta *);
void consulta_setFolio(int folio); 
void consulta_setDescripcion(char *descr); 
void consulta_setMedicamentos(StringList *); 
Consulta *consulta_alta(); 
//getters
int consulta_getFolio(); 
StringList *consulta_getMedicamentos();
int consulta_getMedicamentosCantidad();
char *consulta_getDescripcion(); 
void consulta_printf(); 
//aux
void consultas_saveFile(char *);
void consultas_openFile(char *); 
void consultas_init(); 
Consulta *consulta_getByFolio(int folio);

//virtual table
struct Consulta_vt
{
    void (*setThis)(Consulta *this);
    void (*setFolio)(int folio); 
    void (*setDescripcion)(char *descr); 
    void (*setMedicamentos)(StringList *); 
    int (*getFolio)(); 
    StringList *(*getMedicamentos)();
    char *(*getDescripcion)(); 
    Consulta *(*alta)(); 
    void (*printf)(); 
} static consulta_vt = {
    consulta_setThis,
    consulta_setFolio,
    consulta_setDescripcion,
    consulta_setMedicamentos,
    consulta_getFolio,
    consulta_getMedicamentos,
    consulta_getDescripcion,
    consulta_alta,
    consulta_printf
};

#endif