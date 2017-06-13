typedef struct
{
    int id;
    char usuario[MAXLINE];
    char password[MAXLINE];
    char nombre[MAXLINE];
    int estatus;
    int tipo;
    int idDoctor;
} Usuario;


//global
int g_usuarios_elements = 0;
int g_usuarios_size = 1000;
Usuario *g_usuarios[1000];


void usuarios_openFile(char *path) 
{
    Files *file = files_new();
    $(file).open(path);
    g_usuarios_elements = $(file).readInt();
    int j;
    for (j = 0; j < g_usuarios_elements; j++) {
        Usuario *u = malloc(sizeof(Usuario));
        u->id = $(file).readInt();
        $(file).readString(u->usuario);
        $(file).readString(u->password);
        $(file).readString(u->nombre);
        u->estatus = $(file).readInt();
        u->tipo = $(file).readInt();
        u->idDoctor = $(file).readInt();
        g_usuarios[j] = u;
    }
    $(file).close();
}

void usuarios_init() 
{
    int i=0;
    for(; i<g_usuarios_size; i++) 
    {
        g_usuarios[i] = 0;
    }
    usuarios_openFile("usuario.txt");
}
