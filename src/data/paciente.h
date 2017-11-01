#ifndef PACIENTE_H
#define PACIENTE_H

#define this paciente_this

typedef struct {
    int id;
    char nombre[MAXLINE];
    Fecha fecha;
    StringList *alergias;
    int peso;
    int talla;
    bool estatus;
    struct Paciente_vt *vt;
} Paciente;


//global
int g_paciente_last_id = 0;
Paciente *paciente_this;
int g_pacientes_elements=0;
int g_pacientes_size=1000;
Paciente *g_pacientes[1000];

//init
Paciente *paciente_new();
//setters
void paciente_setThis(Paciente *this);
void paciente_setNombre(char *nombre);
void paciente_setId(int id);
void paciente_setPeso(int peso); 
void paciente_setTalla(int talla);
void paciente_setEstatus(bool estatus);
void paciente_setFecha(Fecha fecha);
void paciente_setAlergias(StringList *); 
Paciente *paciente_alta();

//getters
char *paciente_getNombre();
int paciente_getId(); 
int paciente_getPeso();
int paciente_getTalla();
bool paciente_getEstatus();
Fecha *paciente_getFecha();
void paciente_printf();
StringList *paciente_getAlergias(); 
//aux
void pacientes_openFile(char *);
void pacientes_saveFile(char *);
Paciente *pacientes_init();
Paciente *paciente_getById(int id);
Paciente *paciente_getByName(char *name);

//virtual table
struct Paciente_vt
{
    void (*setThis)(Paciente *);
    void (*setNombre)(char*);
    void (*setId)(int);
    void (*setPeso)(int);
    void (*setTalla)(int);
    void (*setEstatus)(bool);
    void (*setFecha)(Fecha fecha);
    void (*setAlergias)(StringList *); 
    Paciente *(*alta)();
    char *(*getNombre)();
    int (*getId)();
    int (*getPeso)();
    int (*getTalla)();
    bool (*getEstatus)();
    Fecha *(*getFecha)();
    StringList *(*getAlergias)(); 
    void (*printf)();
} paciente_vt = {
    paciente_setThis,
    paciente_setNombre,
    paciente_setId,
    paciente_setPeso,
    paciente_setTalla,
    paciente_setEstatus,
    paciente_setFecha,
    paciente_setAlergias,
    paciente_alta,
    paciente_getNombre,
    paciente_getId,
    paciente_getPeso,
    paciente_getTalla,
    paciente_getEstatus,
    paciente_getFecha,
    paciente_getAlergias,
    paciente_printf
};

//init
Paciente *paciente_new() {
    Paciente *paciente = malloc(sizeof(Paciente));
    paciente->vt = &paciente_vt;
    return paciente;
}
//setters
void paciente_setThis(Paciente *self)
{
    this = self;
}

void paciente_setNombre(char *nombre) 
{
    strcpy(this->nombre, nombre);
}

void paciente_setId(int id) 
{
    this->id = id;
}

void paciente_setPeso(int peso) 
{
    this->peso = peso;
}

void paciente_setTalla(int talla) 
{
    this->talla = talla;
}

void paciente_setEstatus(bool estatus) 
{
    this->estatus = estatus;
}

void paciente_setFecha(Fecha fecha) 
{
    this->fecha.dia = fecha.dia;
    this->fecha.hora = fecha.hora;
    this->fecha.mes = fecha.mes;
    this->fecha.ano = fecha.ano;
}

void paciente_setAlergias(StringList *alergias) 
{
    this->alergias = alergias;
}

//getters
char *paciente_getNombre() 
{
    return this->nombre;
}

int paciente_getId() 
{
    return this->id;
}

int paciente_getPeso() 
{
    return this->peso;
}

int paciente_getTalla() 
{
    return this->talla;
}

bool paciente_getEstatus() 
{
    return this->estatus;
}

Fecha *paciente_getFecha() 
{
    return &(this->fecha);
}

StringList *paciente_getAlergias() 
{
    return this->alergias;
}
/*
 *LIST
 */

Paciente *paciente_alta() 
{
    Paciente *paciente = paciente_new();
    int id = g_paciente_last_id++;
    //nombre
    char nombre[MAXLINE];
    String("Nombre:", nombre);
    //talla
    int talla;
    Number("Talla:", &talla);
    //peso
    int peso;
    Number("Peso:", &peso);
    //fecha
    Fecha fechaN;
    Number("Fecha de nacimiento \n  Dia:", &fechaN.dia); 
    Number("Mes:", &fechaN.mes);
    Number("Ano:", &fechaN.ano);
    //alergias
    int i;
    StringList *alergias = malloc(sizeof(StringList));
    Number("Numero de alergias:", &(alergias->lines));
    alergias->strs = malloc(sizeof(char *) * alergias->lines);
    for(i=0; i<alergias->lines; i++) 
    {
        char *str = malloc(sizeof(char)*MAXLINE);
        String("Alergia: ", str);
        alergias->strs[i] = str;
    }

    $(paciente).setNombre(nombre);
    $(paciente).setNombre(nombre);
    $(paciente).setId(id);
    $(paciente).setPeso(peso);
    $(paciente).setTalla(talla);
    $(paciente).setFecha(fechaN);
    $(paciente).setEstatus(true);
    $(paciente).setAlergias(alergias);
    printf("\n-----------------------------\n");
    printf(" ID: %d", id);
    return paciente;
}

void paciente_printf() 
{
    printf("\n Nombre: %s", $(this).getNombre());
    printf("\n ID: %d",$(this).getId());
    printf("\n Talla: %d",$(this).getTalla());
    printf("\n Peso: %d",$(this).getPeso());
    Fecha *f = $(this).getFecha();
    printf("\n Fecha de nacimiento: %d/%d/%d", f->dia, f->mes, f->ano);
    printf("\n Alergias:");
    StringList *alergias = $(this).getAlergias();
    int i;
    for(i=0; i<alergias->lines; i++) 
    {
        printf("\n\t\t%s", alergias->strs[i]);
    }    
    printf("\n Estatus: %d",$(this).getEstatus());
}


//aux
Paciente *pacientes_init() 
{
    int i=0;
    for(; i<g_pacientes_size; i++) {
        g_pacientes[i] = 0;
    }
    pacientes_openFile("paciente.txt");
}

Paciente *paciente_getById(int id) 
{
    Paciente *result = 0;
    int i=0;
    for(; i<g_pacientes_elements; i++) {  
        if(g_pacientes[i]) {   
            if(g_pacientes[i]->id == id ) {
                result = g_pacientes[i];
                break;
            }
        }
    }
    return result;
}

Paciente *paciente_getByName(char *name) 
{
    Paciente *result = 0;
    int i=0;
    for(; i<g_pacientes_elements; i++) {
        if(g_pacientes[i]) {   
            if(strcmp(name, g_pacientes[i]->nombre) == 0) {
                result = g_pacientes[i];
                break;
            }
        }
    }
    return result;
}

void pacientes_openFile(char *path) 
{
    Files *file = files_new();
    $(file).open(path);
    g_pacientes_elements = $(file).readInt();
    if(g_pacientes_elements>0) {
            g_paciente_last_id = $(file).readInt();
    }
    int j;
    for (j = 0; j < g_pacientes_elements; j++) {
        Paciente *paciente = paciente_new();
        //id
        int id = $(file).readInt();
        //nombre
        char nombre[MAXLINE];
        $(file).readString(nombre);
        //fecha
        Fecha fecha;
        fecha.dia = $(file).readInt();
        fecha.mes = $(file).readInt();
        fecha.ano = $(file).readInt();        
        //alergias
        int i;
        StringList *alergias = malloc(sizeof(StringList));
        alergias->lines =  $(file).readInt();
        alergias->strs = malloc(sizeof(char *) * alergias->lines);
        for(i=0; i<alergias->lines; i++) 
        {
            char *str = malloc(sizeof(char)*MAXLINE);
            $(file).readString(str);
            alergias->strs[i] = str;

        }
        //peso
        int peso = $(file).readInt();
        //talla
        int talla = $(file).readInt();
        //estatus
        bool estatus = $(file).readInt(); 
        
        $(paciente).setNombre(nombre);
        $(paciente).setId(id);
        $(paciente).setPeso(peso);
        $(paciente).setTalla(talla);
        $(paciente).setFecha(fecha);
        $(paciente).setEstatus(estatus);
        $(paciente).setAlergias(alergias);
        g_pacientes[j] = paciente;
    }
    $(file).close();
}

void pacientes_saveFile(char *path) 
{
    Files *file = files_new();
    $(file).open(path);
    int j;
    //numero de pacientes
    $(file).writeInt(g_pacientes_elements);
    //last id
    if(g_pacientes_elements>0) {
        $(file).writeInt(g_paciente_last_id);
    }
    for (j = 0; j < g_pacientes_elements; j++) {
        Paciente *p = g_pacientes[j];
        //id        
        $(file).writeInt($(p).getId());
        //nombre
        $(file).writeString($(p).getNombre());
        //fecha
        Fecha *fecha = $(p).getFecha();
        $(file).writeInt(fecha->dia);
        $(file).writeInt(fecha->mes);        
        $(file).writeInt(fecha->ano);
        //alergias
        StringList *alergias = $(p).getAlergias();
        $(file).writeInt(alergias->lines);
        int i;
        for(i=0; i<alergias->lines; i++) 
        {
            $(file).writeString(alergias->strs[i]);
        }
        //peso
        $(file).writeInt($(p).getPeso());
        //talla
        $(file).writeInt($(p).getTalla());
        //estatus
        $(file).writeInt($(p).getEstatus());
    }
    $(file).close();
}

#undef this
#endif