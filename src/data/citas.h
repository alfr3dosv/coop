#ifndef CITAS_H
#define CITAS_H
#define this cita_this

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

//global
int g_cita_last_id = 0;
int cita_folio_count = 0;
Cita *cita_this;
int g_citas_elements=0;
int g_citas_size=1000;
Cita *g_citas[1000];

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
} cita_vt = {
    //setters
    cita_setThis,
    cita_setId,
    cita_setFolio,
    cita_setFecha,
    cita_setDoctor,
    cita_setPaciente,
    cita_setEstatus,
    cita_alta,
    //getters
    cita_getId,
    cita_getFolio,
    cita_getFecha,
    cita_getDoctor,
    cita_getPaciente,
    cita_getEstatus,
    cita_printf
};

//init
Cita *cita_new() {
    Cita *cita = malloc(sizeof(Cita));
    cita->vt = &cita_vt;
    return cita;
}
//setters
void cita_setThis(Cita *self)
{
    this = self;
}
void cita_setId(int id) 
{
    this->id = id;
}

void cita_setFolio(int folio) 
{
    this->folio = folio;
}

void cita_setFecha(Fecha fecha) 
{
    this->fecha.dia = fecha.dia;
    this->fecha.hora = fecha.hora;
    this->fecha.minuto = fecha.minuto;
    this->fecha.mes = fecha.mes;
    this->fecha.ano = fecha.ano;
}

void cita_setDoctor(int doctor) 
{
    this->doctor = doctor;
}

void cita_setPaciente(int paciente) 
{
    this->paciente = paciente;
}

void cita_setEstatus(bool estatus) 
{
    this->estatus = estatus;
}
//getters
int cita_getId()
{
    return this->id;
}

int cita_getFolio()
{
    return this->folio;
}

Fecha *cita_getFecha()
{
    return &(this->fecha);
}

int cita_getDoctor()
{
    return this->doctor;
}

int cita_getPaciente()
{
    return this->paciente;
}

bool cita_getEstatus()
{
    return this->estatus;
}

void cita_alta() 
{
    int id = g_cita_last_id;
    int folio = g_cita_last_id++;
    int paciente_id;
    Paciente *paciente = 0;
    while(!paciente) {
        Number("Paciente(ID):", &paciente_id);
        paciente = paciente_getById(paciente_id);
        if(!paciente) {
            printf("\n Error: Folio no valido");
        }
    } 
    int doctor_id;
    Doctor *doctor = 0;
    while(!doctor) {
        Number("Doctor(ID):", &doctor_id);
        doctor = doctor_getById(doctor_id);
        if(!doctor) {
            printf("\n Error: Folio no valido");
        }
    }
    //fecha
    Fecha fecha;
    do {
        printf("\tFecha de cita\n");
        Intervalo("Dia(Lunes 1, Domingo 7):", &fecha.dia, 1,6); 
        Intervalo("Mes:", &fecha.mes,1,12);
        Intervalo("Ano:", &fecha.ano, 1990, 2018);
        Intervalo("Hora:", &fecha.hora, 6, 10);
        fecha.minuto = 30;
    } while(cita_fecha(fecha));
    $(this).setDoctor(doctor_id);
    $(this).setFecha(fecha);
    $(this).setPaciente(paciente_id);
    $(this).setId(id);
    $(this).setFolio(folio);
    $(this).setEstatus(true);
    printf("\n-----------------------------\n");
    printf(" ID: %d", id);
    printf(" FOLIO: %d", folio);
}

//aux
bool cita_fecha(Fecha f) 
{
    bool coincide = false;
    int i=0;
    for(; i<g_citas_elements; i++) {  
        if(g_citas[i]) {   
            Fecha *f2 = $(g_citas[i]).getFecha();
            if((f2->hora == f.hora) && (f2->minuto == f.minuto) 
                && (f2->mes == f.mes) && (f2->ano == f.ano)) 
            {
                coincide = true;
            }  
        }
    }
     return coincide;
}

Cita *cita_getById(int id) 
{
    Cita *result = 0;
    int i=0;
    for(; i<g_citas_elements; i++) {  
        if(g_citas[i]) {   
            if($(g_citas[i]).getId() == id ) {
                result = g_citas[i];
                break;
            }
        }
    }
    return result;
}



Cita *cita_getByFolio(int folio) 
{
    Cita *result = 0;
    int i=0;
    for(; i<g_citas_elements; i++) {  
        if(g_citas[i]) {   
            if($(g_citas[i]).getFolio() == folio ) {
                result = g_citas[i];
                break;
            }
        }
    }
    return result;
}

Cita *cita_getByPaciente(int paciente) 
{
    Cita *resultado[50];
    int coincidencias=0;
    int i=0;
    for(; i<g_citas_elements; i++) {  
        if(g_citas[i]) {   
            if($(g_citas[i]).getPaciente() == paciente ) {
                resultado[coincidencias++] = g_citas[i];
            }
        }
    }
    if(coincidencias > 1) {
    printf("\n Encontradas %d coincidencias",coincidencias);
        for(i=0; i<coincidencias; i++) {
            Fecha *f = $(resultado[i]).getFecha();
            printf("\n  %d) Fecha %d/%d/%d",i, f->dia, f->mes, f->ano);
        }
        int n;
        Intervalo("Seleccionar:", &n, -1, coincidencias);
        return resultado[n];   
    }
    else if(coincidencias == 1) {
        return resultado[0];
    }
    else {
        return 0;
    }
}

void cita_printf() 
{
    printf("\n Doctor: %d",$(this).getDoctor());
    printf("\n Paciente: %d",$(this).getPaciente());
    printf("\n ID: %d",$(this).getId());
    printf("\n Folio: %d",$(this).getFolio());
    Fecha *f = $(this).getFecha();
    printf("\n Fecha de la cita: %d/%d/%d", f->dia, f->mes, f->ano);
    printf(" %2d:%2d",f->hora, f->minuto);
    printf("\n Estado: %d",$(this).getEstatus());
}

void citas_init() 
{
    int i=0;
    for(; i<g_citas_size; i++) {
        g_citas[i] = 0;
    }
    citas_openFile("cita.txt"); 
}

void citas_openFile(char *path) 
{
    Files *file = files_new();
    $(file).open(path);
    g_citas_elements = $(file).readInt();
    //last id
    if(g_citas_elements>0) {
        g_cita_last_id = $(file).readInt();
    }
    int j;
    for (j = 0; j < g_citas_elements; j++) {
        Cita *cita = cita_new();
        //id
        int id = $(file).readInt();
        //folio
        int folio = $(file).readInt();
        //paciente
        int paciente = $(file).readInt();
        //doctor
        int doctor = $(file).readInt();
        //estatus
        int estatus = $(file).readInt();
        //fecha
        Fecha fecha;
        fecha.dia = $(file).readInt();
        fecha.mes = $(file).readInt();
        fecha.ano = $(file).readInt();  
        fecha.hora = $(file).readInt();  
        fecha.minuto = $(file).readInt();  

        $(cita).setDoctor(doctor);
        $(cita).setPaciente(paciente);
        $(cita).setId(id);
        $(cita).setFecha(fecha);
        $(cita).setFolio(folio);
        $(cita).setEstatus(estatus);
        g_citas[j] = cita;
    }
    $(file).close();
}

void citas_saveFile(char *path) 
{
    Files *file = files_new();
    $(file).open(path);
    int j;
    //numero de citas
    $(file).writeInt(g_citas_elements);
    //last id
    if(g_citas_elements>0) {
        $(file).writeInt(g_cita_last_id);
    }
    
    for (j = 0; j < g_citas_elements; j++) {
        Cita *p = g_citas[j];
        //id        
        $(file).writeInt($(p).getId());
        //folio
        $(file).writeInt($(p).getFolio());
        //paciente
        $(file).writeInt($(p).getPaciente());
        //doctor
        $(file).writeInt($(p).getDoctor());
        //doctor
        $(file).writeInt($(p).getEstatus());
        //fecha
        Fecha *fecha = $(p).getFecha();
        $(file).writeInt(fecha->dia);
        $(file).writeInt(fecha->mes);        
        $(file).writeInt(fecha->ano);
        $(file).writeInt(fecha->hora);
        $(file).writeInt(fecha->minuto);
    }
    $(file).close();
}

#undef this
#endif