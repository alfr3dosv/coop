#include "doctor.h"
#define this doctor_this

int g_doctor_last_id=0;
Doctor *doctor_this;
int g_doctores_elements=0;
int g_doctores_size=1000;
Doctor *g_doctores[1000];

//init
Doctor *doctor_new() {
    Doctor *doctor = malloc(sizeof(Doctor));
    doctor->vt = &doctor_vt;
    return doctor;
}
//setters
void doctor_setThis(Doctor *self) {
    this = self;
}

void doctor_setNombre(char *nombre) 
{
    strcpy(this->nombre, nombre);
}

void doctor_setId(int id) 
{
    this->id = id;
}

void doctor_setTurno(int turno) 
{
    this->turno = turno;
}

void doctor_setEstatus(bool estatus) 
{
    this->estatus = estatus;
}

void doctor_setEspecialidad(int especialidad) 
{
    this->especialidad = especialidad;
}
//getters
char *doctor_getNombre()
{
    return this->nombre;
}

int doctor_getId()
{
    return this->id;
}

int doctor_getTurno()
{
    return this->turno;
}

bool doctor_getEstatus()
{
    return this->estatus;
}

int doctor_getEspecialidad()
{
    return this->especialidad;
}

Doctor *doctor_alta() 
{
    Doctor *doctor = doctor_new();
    //id
    int id = g_doctor_last_id++;
    //nombre
    char nombre[MAXLINE];
    String("Nombre:", nombre);
    //especialidad
    int especialidad;
    Number("Especialidad:", &especialidad);
    int turno;
    Number("Turno \n 0) Matutino \n 1) Verspertino\n ", &turno);
    $(doctor).setNombre(nombre);
    $(doctor).setId(id);
    $(doctor).setEspecialidad(especialidad);
    $(doctor).setEstatus(true);
    $(doctor).setTurno(turno);
    printf("\n-----------------------------\n");
    printf(" ID: %d", id);
    return doctor;
}


void doctor_printf() 
{
    printf("\n Nombre: %s",$(this).getNombre());
    printf("\n ID: %d",$(this).getId());
    printf("\n Especialidad: %d",$(this).getEspecialidad());
    printf("\n Estatus: %d",$(this).getEstatus());
}
Doctor *doctores_init() 
{
    int i=0;
    for(; i<g_doctores_size; i++) {
        g_doctores[i] = 0;
    }
    doctores_openFile("doctor.txt");
}

Doctor *doctor_getById(int id) 
{
    Doctor *result = 0;
    int i=0;
    for(; i<g_doctores_elements; i++) {  
        if(g_doctores[i]) {   
            if($(g_doctores[i]).getId() == id ) {
                result = g_doctores[i];
                break;
            }
        }
    }
    return result;
}

Doctor *doctor_getByName(char *name) 
{
    Doctor *result = 0;
    int i=0;
    for(; i<g_doctores_elements; i++) {
        if(g_doctores[i]) {   
            if(strcmp(name, $(g_doctores[i]).getNombre()) == 0) {
                result = g_doctores[i];
                break;
            }
        }
    }
    return result;
}

void doctores_openFile(char *path) 
{
    Files *file = files_new();
    $(file).open(path);
    g_doctores_elements = $(file).readInt();
    if(g_doctores_elements>0) {
            g_doctor_last_id = $(file).readInt();
    }
    int j;
    for (j = 0; j < g_doctores_elements; j++) {
        Doctor *doctor = doctor_new();
        //id
        int id = $(file).readInt();
        //nombre
        char nombre[MAXLINE];
        $(file).readString(nombre);
        //turno
        int turno = $(file).readInt();      
        //especialidad
        int especialidad = $(file).readInt();
        //estatus
        bool estatus = $(file).readInt(); 
        
        $(doctor).setNombre(nombre);
        $(doctor).setId(id);
        $(doctor).setEspecialidad(especialidad);
        $(doctor).setTurno(turno);
        $(doctor).setEstatus(estatus);
        g_doctores[j] = doctor;
    }
    $(file).close();
}

void doctores_saveFile(char *path) 
{
    Files *file = files_new();
    $(file).open(path);
    int j;
    //numero de doctor
    $(file).writeInt(g_doctores_elements);
    //last id
    if(g_doctores_elements>0) {
        $(file).writeInt(g_doctor_last_id);
    }
    for (j = 0; j < g_doctores_elements; j++) {
        Doctor *p = g_doctores[j];
        //id        
        $(file).writeInt($(p).getId());
        //nombre
        $(file).writeString($(p).getNombre());
        //turno
        $(file).writeInt($(p).getTurno());
        //especialidad
        $(file).writeInt($(p).getEspecialidad());
        //estatus
        $(file).writeInt($(p).getEstatus());
    }
    $(file).close();
}

#undef this
