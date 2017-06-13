#define MAX_LINE 1000

// estructuras auxiliare
typedef struct {
    int hora;
    int dia;
    int mes;
    int ano;
} Fecha;

typedef struct {
    int elements;
    char *list;
} StringList;

typedef struct {
    int size;
    char *str;
} BigString;

// pacientes
typedef struct {
    int id;
    char nombre[MAX_LINE];
    Fecha fecha;
    StringList alergias;
    int peso;
    int talla;
    bool estatus;
} Paciente;

//doctor
typedef struct {
    int id;
    char nombre[MAX_LINE];
    int especialidad;
    Fecha turno;
    bool estatus;
} Doctor;


//citas
typedef struct {
    int id;
    int folio;
    int doctor;
    int paciente;
    Fecha fecha;
} Cita;

//consultas
typedef struct {
    int folio;
    BigString descr;
    StringList medicamentos;
} Consulta;

//pacientes
void paciente_setNombre(Paciente *this, char *nombre) {
    strcpy(this->nombre, nombre);
}

void paciente_setId(Paciente *this, int id) {
    this->id = id;
}

void paciente_setPeso(Paciente *this, int peso) {
    this->peso = peso;
}

void paciente_setTalla(Paciente *this, int talla) {
    this->talla = talla;
}

void paciente_setEstatus(Paciente *this, bool estatus) {
    this->estatus = estatus;
}

void paciente_setFecha(Paciente *this, int hora, int dia, int mes, int ano) {
    this->fecha.dia = dia;
    this->fecha.hora = hora;
    this->fecha.mes = mes;
    this->fecha.ano = ano;
}

//doctores
void doctor_setNombre(Doctor *this, char *nombre) {
    strcpy(this->nombre, nombre);
}

void doctor_setId(Doctor *this, int id) {
    this->id = id;
}

void doctor_setTurno(Doctor *this, int dia, int hora) {
    this->turno.dia = dia;
    this->turno.hora = hora;
}

void doctor_setEstatus(Doctor *this, bool estatus) {
    this->estatus = estatus;
}

void doctor_setEspecialidad(Doctor *this, int especialidad) {
    this->especialidad = especialidad;
}

//citas
void cita_setId(Cita *this, int id) {
    this->id = id;
}
void cita_setFolio(Cita *this, int folio) {
    this->folio = folio;
}

void cita_setFecha(Cita *this, int hora, int dia, int mes, int ano) {
    this->fecha.dia = dia;
    this->fecha.hora = hora;
    this->fecha.mes = mes;
    this->fecha.ano = ano;
}

void cita_seDoctor(Cita *this, int doctor) {
    this->doctor = doctor;
}

void cita_setPaciente(Cita *this, int paciente) {
    this->paciente = paciente;
}

//consultas
void consulta_setFolio(Consulta *this, int folio) {
    this->folio = folio;
}