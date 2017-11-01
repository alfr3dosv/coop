#ifndef CITAS_H
#define CITAS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "data.h"
#include "StringList.h"
#include "objects.h"
#include "../console.h"
#include "doctor.h"
#include "paciente.h"

//citas
typedef struct {
    int id;
    int folio;
    int doctor;
    int paciente;
    Fecha fecha;
    int especialista;
    bool estatus;
    struct Cita_vt *vt;
} Cita;

extern int g_cita_last_id;
extern int cita_folio_count;
extern Cita *cita_this;
extern int g_citas_elements;
extern int g_citas_size;
extern Cita *g_citas[1000];

//init
Cita *cita_new();
//setters
void cita_setThis(Cita *self);
void cita_setId(int id); 
void cita_setFolio(int folio); 
void cita_setFecha(Fecha fecha); 
void cita_setDoctor(int doctor); 
void cita_setPaciente(int paciente); 
void cita_setEstatus(bool estatus); 
void cita_alta(); 
//getters
int cita_getId();
int cita_getFolio();
Fecha *cita_getFecha();
int cita_getDoctor();
int cita_getPaciente();
bool cita_getEstatus();
//aux
void citas_openFile(char *path);
void citas_saveFile(char *path);
Cita *cita_getById(int id); 
Cita *cita_getByFolio(int folio); 
Cita *cita_getByPaciente(int paciente); 
void cita_printf(); 
void citas_init(); 
bool cita_fecha(Fecha); 

struct Cita_vt
{
    void (*setThis)(Cita*);
    void (*setId)(int id); 
    void (*setFolio)(int folio); 
    void (*setFecha)(Fecha fecha); 
    void (*setDoctor)(int doctor); 
    void (*setPaciente)(int paciente); 
    void (*setEstatus)(bool estatus); 
    void (*alta)(); 
    int (*getId)();
    int (*getFolio)();
    Fecha *(*getFecha)();
    int (*getDoctor)();
    int (*getPaciente)();
    bool (*getEstatus)();
    void (*printf)(); 
};

extern struct Cita_vt cita_vt;

#endif