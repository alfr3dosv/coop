#ifndef CLI_H
#define CLI_H

void historial_printf(int);

void cli_menu_pacientes() 
{
    int op_paciente;
    do {
        printf("\n Pacientes \n 1) Alta\n 2) Baja\n 3) Consultar por id\n 4) Consulta por nombre\n 5) Regresar");
        Number("\n Opcion:", &op_paciente);
        if(op_paciente == 1) {
            g_pacientes[g_pacientes_elements++] = paciente_alta();
        }
        else if(op_paciente == 2) {
            int id;
            Number(" Id:", &id);
            Paciente *consulta;
            if(consulta = paciente_getById(id)) {
                if($(consulta).getEstatus()) {
                    $(consulta).setEstatus(false);
                }
                else {
                    printf("\n\t ERROR: Ya estaba dado de baja\n");                    
                }
            }
            else {
                printf("\n\t ERROR: No encontrado\n");
            }
        }
        else if(op_paciente == 3 ) {
            int id;
            Number(" Id:", &id);
            Paciente *consulta;
            if(consulta = paciente_getById(id)) {
                $(consulta).printf();
            }
            else {
                printf("\n\t ERROR: No encontrado\n");
            }
        }
        else if(op_paciente == 4 ) {
            Paciente *consulta;
            char str[MAXLINE];
            String(" Nombre:", str);
            if(consulta = paciente_getByName(str)) {
                $(consulta).printf();
            }
            else {
                printf("\n\t ERROR: No encontrado\n");
            }
        }
        pacientes_saveFile("paciente.txt");
    } while(op_paciente != 5);
}

void cli_menu_doctores() 
{
    int op_doctor;
    do {
        printf("\n Doctores \n 1) Alta\n 2) Baja\n 3) Consultar por id\n 4) Consulta por nombre\n 5) Regresar");
        Number("\n Opcion:", &op_doctor);
        if(op_doctor == 1) {
            g_doctores[g_doctores_elements++] = doctor_alta();
        }
        else if(op_doctor == 2) {
            int id;
            Number(" Id:", &id);
            Doctor *consulta;
            if(consulta = doctor_getById(id)) {
                if($(consulta).getEstatus()) {
                    $(consulta).setEstatus(false);
                }
                else {
                    printf("\n\t ERROR: Ya estaba dado de baja\n");                    
                }
            }
            else {
                printf("\n\t ERROR: No encontrado\n");
            }
        }
        else if(op_doctor == 3 ) {
            int id;
            Number(" Id:", &id);
            Doctor *consulta;
            if(consulta = doctor_getById(id)) {
                $(consulta).printf();
            }
            else {
                printf("\n\t ERROR: No encontrado");
            }
        }
        else if(op_doctor == 4 ) {
            Doctor *consulta;
            char str[MAXLINE];
            String(" Nombre:", str);
            if(consulta = doctor_getByName(str)) {
                $(consulta).printf();
            }
            else {
                printf("\n\t ERROR: No encontrado");
            }
        }
        doctores_saveFile("doctor.txt");
    } while(op_doctor != 5);
}

void cli_menu_citas() 
{
    int op_cita;
    do {
        printf("\n Citas \n 1) Alta\n 2) Cancelar\n 3) Consultar por id\n 4) Consulta por nombre\n 5) Regresar");
        Number("\n Opcion:", &op_cita);
        if(op_cita == 1) {
            if(g_citas[g_citas_elements] == 0) {
                Cita *cita = cita_new();
                $(cita).alta();
                g_citas[g_citas_elements++] = cita;
            }
        }
        else if(op_cita == 2) {
            int id;
            Number(" Id:", &id);
            Cita *consulta;
            if(consulta = cita_getById(id)) {
                if($(consulta).getEstatus()) {
                    $(consulta).setEstatus(false);
                }
                else {
                    printf("\n\t ERROR: Ya estaba cancelada\n");                    
                }
            }
            else {
                printf("\n\t ERROR: No encontrado\n");
            }            
        }
        else if(op_cita == 3 ) {
            int id;
            Number(" Id:", &id);
            Cita *consulta;
            if(consulta = cita_getById(id)) {
                $(consulta).printf();
            }
            else {
                printf("\n\t ERROR: No encontrado");
            }
        }
        else if(op_cita == 4 ) {
            Cita *consulta;
            int folio;
            Number(" Folio:", &folio);
            if(consulta = cita_getByFolio(folio)) {
                $(consulta).printf();
            }
            else {
                printf("\n\t ERROR: No encontrado");
            }

        }
        citas_saveFile("cita.txt"); 
    } while(op_cita != 5);
}

void cli_menu_consultas() 
{
    int op_consulta;
    do {
        printf("\n Consultas \n 1) Completar consulta 2) Regresar");
        Number("\n Opcion:", &op_consulta);
        if(op_consulta == 1) {
            printf("\nHere");
            if(g_consultas[g_consultas_elements] == 0) {
                Consulta *consulta = consulta_new();
                g_consultas[g_consultas_elements++] = $(consulta).alta();
            }
        }
        else if(op_consulta == 10 ) {
            Consulta *consulta;
            int folio;
            Number(" Folio:", &folio);
            if(consulta = consulta_getByFolio(folio)) {
                $(consulta).printf();
            }
            else {
                printf("\n\t ERROR: No encontrado");
            }
        }
        consultas_saveFile("consulta.txt");
    } while(op_consulta != 2);
}

void cli_menu_historial()
{
    int op_historial;
    do {
        printf("\n Historial \n 1) Ver historial 2) Regresar\n");
        Number("Opcion:", &op_historial);
        if(op_historial == 1 ) {
            int id;
            Number("Paciente:", &id);
            historial_printf(id);
        }
    } while(op_historial != 2);
}

void historial_printf(int id) 
{
    Paciente *paciente = paciente_getById(id);
    Cita *cita = cita_getByPaciente(id);
    Consulta *consulta;
    if(paciente && cita) {
        consulta = consulta_getByFolio($(cita).getFolio());
        printf("\n\t\tHISTORIAL MEDICO");
        printf("\n CVE Paciente: %d", $(paciente).getId());
        printf("\t Nombre Paciente: %s", $(paciente).getNombre());
        Fecha *f = $(paciente).getFecha();
        printf("\n Fecha de nacimiento: %d/%d/%d", f->dia, f->mes, f->ano);
        printf("\n Peso: %d",$(paciente).getPeso());
        printf("\n Alergias\n");
        StringList *alergias = $(paciente).getAlergias();
        int i;
        for(i=0; i<alergias->lines; i++) 
        {
            printf("\n\t%s", alergias->strs[i]);
        }  
        printf("\n\nFOLIO CITA|   FECHA CITA   |   DESCRIPCION   |   MEDICAMENTOS   ");
        printf("\n %9d|", $(cita).getFolio());
        f = $(cita).getFecha();
        printf("%2d/%2d/%4d %2d:%2d|", f->dia, f->mes, f->ano, f->hora, f->minuto);
        StringList *medicamentos = $(consulta).getMedicamentos();
        char *str = medicamentos->strs[0];
        printf("%.16s...", $(consulta).getDescripcion());
        if(medicamentos->lines >= 1) {
            printf("%.16s...",str);
        }
        //avanzado
        int n;
        do {
            printf("\n\n\n\n 1) Mostrar descripcion detallada \n 2) Mostrar medicamentos detallados\n 3)Salir\n");
            Number("Opcion:",&n);
            if(n == 1) {
                printf("\n Descripcion: %s",$(consulta).getDescripcion());
            }
            else if(n == 2) {
                printf("\n Medicamentos:");
                for(i=0; i<medicamentos->lines; i++) 
                {
                    printf("\n\t%s", medicamentos->strs[i]);
                }
            }
        } while(n!=3);
    }
}

void testP()
{
//     FILE *file = fopen("p.txt","r");
//     if(file == NULL) {
//         file = fopen("p.txt","w")
//     }
//     Paciente *p = paciente_openFile(file);
//     $(p).printf();
// }
    doctores_openFile("d.txt");
    printf("\n %d", g_doctores_elements);

}

#endif