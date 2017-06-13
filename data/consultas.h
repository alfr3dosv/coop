#define this consulta_this

//consultas
typedef struct {
    int id;
    int folio;
    char *descripcion;
    StringList *medicamentos;
    struct Consulta_vt *vt;
} Consulta;

//global
Consulta *consulta_this;
int g_consultas_elements=0;
int g_consultas_size=1000;
Consulta *g_consultas[1000];

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
} consulta_vt = {
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

//init
Consulta *consulta_new()
{  
    Consulta *consulta = malloc(sizeof(Consulta));
    consulta->vt = &consulta_vt;
    return consulta;
}
//setters
void consulta_setThis(Consulta *self) 
{
    this = self;
}
void consulta_setFolio(int folio) 
{
    this->folio = folio;
}

void consulta_setDescripcion(char *descr) 
{
    this->descripcion = descr;
}

void consulta_setMedicamentos(StringList *medicamentos) 
{
    this->medicamentos = medicamentos;
}

//getters
int consulta_getFolio() 
{
    return this->folio;
}
StringList *consulta_getMedicamentos() 
{
    return this->medicamentos;
}
char *consulta_getDescripcion() 
{
    return this->descripcion;
}

Consulta *consulta_alta() 
{
    //folio
    int folio;
    Cita *cita = 0;
    Consulta *cons = 0;
    while(!cita || cons) {
        Number(" Folio:", &folio);
        cita = cita_getByFolio(folio);
        cons = consulta_getByFolio(folio);
        if(!cita) {
            printf("\n ERROR: Folio no valido\n");
        }
        if(cons) {
            printf("\n ERROR: Consulta llena\n");            
        }
    } 
    //paciente
    Paciente *pac = paciente_getById($(cita).getPaciente());
    printf("\n Clave:%d Nombre:%s\n", $(pac).getId(), $(pac).getNombre());
    //descripcion
    char *descr = malloc(sizeof(char) * MAXDESCR);
    printf("\n Descripcion: " );
    do {
        fgets(descr, MAXDESCR, stdin);
    } while(strlen(descr) < 2);
    char *newline = strchr(descr,'\n');
    *newline = '\0';
    //medicamentos
    int i;
    StringList *medicamentos = malloc(sizeof(StringList));
    Number("Cantidad de medicamentos:", &(medicamentos->lines));
    medicamentos->strs = malloc(sizeof(char *) * medicamentos->lines);
    for(i=0; i<medicamentos->lines; i++) 
    {
        char *str = malloc(sizeof(char)*MAXLINE);
        String("Medicamento: ", str);
        medicamentos->strs[i] = str;
    }
    $(this).setFolio(folio);
    $(this).setMedicamentos(medicamentos);
    $(this).setDescripcion(descr);
    return this;
}

void consulta_printf() 
{
    printf("\n Folio: %d",$(this).getFolio());
    printf("\n Descr: %s",$(this).getDescripcion());
    StringList *medicamentos = $(this).getMedicamentos();
    int i;
    for(i=0; i<medicamentos->lines; i++) 
    {
        printf("\n Medicamento: %s", medicamentos->strs[i]);
    }
}

void consultas_init() 
{
    int i=0;
    for(; i<g_consultas_size; i++) 
    {
        g_consultas[i] = 0;
    }
    consultas_openFile("consulta.txt");
}


Consulta *consulta_getByFolio(int folio) 
{
    Consulta *result = 0;
    int i=0;
    for(; i<g_consultas_elements; i++) 
    {
        if(g_consultas[i]) 
        {   
            if(g_consultas[i]->folio == folio) 
            {
                result = g_consultas[i];
                break;
            }
        }
    }
    return result;
}

void consultas_openFile(char *path) 
{
    Files *file = files_new();
    $(file).open(path);
    g_consultas_elements = $(file).readInt();
    int j;
    for (j = 0; j < g_consultas_elements; j++) {
        Consulta *consulta = consulta_new();
        //medicamentos
        int i;
        StringList *medicamentos = malloc(sizeof(StringList));
        medicamentos->lines =  $(file).readInt();
        medicamentos->strs = malloc(sizeof(char) *MAXLINE * medicamentos->lines);
        for(i=0; i<medicamentos->lines; i++) 
        {
            char *str = malloc(sizeof(char)*MAXLINE);
            $(file).readString(str);
            medicamentos->strs[i] = str;
        }
        //folio
        int folio = $(file).readInt();
        //descripcion
        char *descr = malloc(sizeof(char) * MAXLINE);
        do {
            fgets(descr,MAXLINE, file->file);
        } while(strlen(descr) < 2);
        char *newline = 0;
        if(newline = strchr(descr,'\n')) {
            *newline = '\0';
        }
        $(consulta).setFolio(folio);
        $(consulta).setMedicamentos(medicamentos);
        $(consulta).setDescripcion(descr);
        g_consultas[j] = consulta;
    }
    $(file).close();
}

void consultas_saveFile(char *path) 
{
    Files *file = files_new();
    $(file).open(path);
    int j;
    //numero de consulta
    $(file).writeInt(g_consultas_elements);
    for (j = 0; j < g_consultas_elements; j++) {
        Consulta *p = g_consultas[j];
        //medicamentos
        StringList *medicamentos = $(p).getMedicamentos();
        $(file).writeInt(medicamentos->lines);
        int i;
        for(i=0; i<medicamentos->lines; i++) 
        {
            $(file).writeString(medicamentos->strs[i]);
        }
        //folio
        $(file).writeInt($(p).getFolio());
        //descr
        $(file).writeString($(p).getDescripcion());
    }
    $(file).close();
}

#undef this