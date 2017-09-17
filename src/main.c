#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "objects.h"
#include "data/data.h"
#include "files.h"
#include "data/StringList.h"
#include "console.h"
#include "data/doctor.h"
#include "data/paciente.h"
#include "data/citas.h"
#include "data/consultas.h"
#include "cli.h"
#include "data/usuario.h"


int main()
{

    pacientes_init();
    consultas_init();
    doctores_init();
    citas_init();
    usuarios_init();

    bool entrar = false;
    char usuario[MAXLINE];
    char password[MAXLINE];
    int i = 0;
    int u_intentos = 0;
    do {    
        printf("\n\n\t Bienvenido");   
        printf("\n\t Clinica FCFM\n\n");
    
        String("Usuario:", usuario);
        String("Contrasena:", password);
        for(; i<g_usuarios_elements; i++) 
        {
            if(g_usuarios[i]) {
                if(strcmp(g_usuarios[i]->usuario,usuario) == 0 && 
                    strcmp(g_usuarios[i]->password, password) == 0)
                {
                    entrar = true;
                    break;
                }
            }
        }
        u_intentos++;
    } while(!entrar && u_intentos < 3);
    if(u_intentos >= 3) {
        printf("\n\n CONTACTE CON EL ADMINISTRADOR \n\n");
    }

    if(g_usuarios[i]->tipo == 1) {
        int opcion=1;
        do {
            //menu
            printf("\n Buen dia %s \n Menu \n 1) Paciente \n 2) Cita\n 3) Consultas \n 4) Doctor \n 5) Historial\n 6) Salir\n", g_usuarios[i]->nombre);
            Number("Opcion: ", &opcion);
            char name[MAXLINE];
            //pacientes        
            if(opcion == 1) {
                cli_menu_pacientes();
            }        
            else if(opcion == 2) {
                cli_menu_citas();
            }
            else if(opcion == 3) {
                cli_menu_consultas();
            }
            else if(opcion == 4){
                cli_menu_doctores();
            }        
            else if(opcion == 5){
                cli_menu_historial();
            }
        } while(opcion != 6);
    }
    else {
        int opcion=1;
        do {
            //menu
            printf("\n Buen dia %s \n Menu \n 1) Cita\n 2) Consultas \n 3) Historial \n 4) Salir\n", g_usuarios[i]->nombre);
            Number("Opcion: ", &opcion);
            char name[MAXLINE];
            //pacientes        
            if(opcion == 1) {
                cli_menu_pacientes();
            }        
            else if(opcion == 2) {
                cli_menu_citas();
            }
            else if(opcion == 3) {
                cli_menu_consultas();
            }
            else if(opcion == 4){
                cli_menu_doctores();
            }        
            else if(opcion == 5){
                cli_menu_historial();
            }
        } while(opcion != 6);
    }
} 


