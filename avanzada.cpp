#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

//Estructuras
struct Equipo
{
    int codigo;
    char nombre[100];
    char laboratorio[50];
    char tipo[50];
    char estado[20];
    float costo;
    int semestreMin;
    char descripcion[200];
};

struct Usuario
{
    long codigo;
    char nombre[100];
    char programa[80];
    int semestre;
};

struct SesionUso
{
    int codigoSesion;
    int codigoEquipo;
    long codigoUsuario;
    char fecha[20];
    int duracion;
    char observaciones[200];
    float penalizacion;
};

//Funciones
//1.
void cargaequipos(char nombreequipos []){

    ifstream equipo(nombreequipos);
    if (!equipo) {
        cout << "no se pudo abrir el archivo equipos\n";
        exit(0);
    }

    int n = 0;
    char encapsulador[100];
    char* p = encapsulador;
    char encapsuladorcodigo[4];
    char* pcode = encapsuladorcodigo;
    char encapsuladorsemestre[2];
    char* ps= encapsuladorsemestre;
    char encapsuladorcosto[11];
    char* pcosto = encapsuladorcosto;

    while (equipo.getline(encapsulador, 100)) {
        n++;
    }

    Equipo* equipos = new Equipo[n];
    Equipo* pequipos = equipos;

    equipo.clear();
    equipo.seekg(0);


    while (equipo.getline(encapsulador, 100)) {
        
        //codigo
        pcode = encapsuladorcodigo
        
        while (*p != '\0' && *p != '*'){
            *pcode = *p; 
            pcode++;
            p++;
        }
            *pcode = '\0';
            pequipos->codigo = atoi(encapsuladorcodigo);
        
        if (*p == '*'){
            p += 2;
        }
        
        //nombre
        char* ptr = pequipos->nombre;
        
        while (*p && *p != '*'){
            *ptr = *p;
            ptr++;
            p++;
        }
            *ptrn = '\0';
            
        if (*p == '*'){
            p += 2;
        }
        
        //lab
        ptr = pequipos->laboratorio;
        
        while (*p && *p != '*'){
            *ptr = *p;
            ptr++
            p++
        }
            *ptr = '\0';
            
        if (*p == '*'){
            p += 2; 
        } 
        
        //tipo
        ptr = pequipos->tipo;
       
        while (*p && *p != '*'){
            *ptr = *p;
            ptr++
            p++
        }
            *ptr = '\0';
            
        if (*p == '*'){
            p += 2; 
        } 
        
        //costo
        pcosto = encapsuladorcosto
        
        while (*p != '\0' && *p != '*'){
            *pcosto = *p; 
            pcosto++;
            p++;
        }
            *pcode = '\0';
            pequipos->costo= atoi(encapsuladorcosto);
        
        if (*p == '*'){
            p += 2;
        }
        
        //semestre
         ps = encapsuladorsemestre
        
        while (*p != '\0' && *p != '*'){
            *ps = *p; 
            ps++;
            p++;
        }
            *ps = '\0';
            pequipos->semestre= atoi(encapsuladorsemestre);
        
        if (*p == '*'){
            p += 2;
        }
        
        //descripción
         ptr = pequipos->tipo;
       
        while (*p && *p != '*'){
            *ptr = *p;
            ptr++
            p++
        }
            *ptr = '\0';
            
        if (*p == '*'){
            p += 2; 
        } 

        pequipos++;
    }

    equipo.close();
}
        
//2.
void cargaUsuarios(char nombreusuarios []){

    char encapsulador[100];

    ifstream usuario(nombreusuarios);

    if(!usuario){
        cout << "No se pudo abrir el archivo usuarios\n";
        exit(0);
    }

     int n = 0;
    char encapsulador[100];
    char* p = encapsulador;
    char encapsuladorcodigo[7];
    char* pcode = encapsuladorcodigo;
    char encapsuladorsemestre[2];
    char* ps= encapsuladorsemestre;


    while(usuario.getline(encapsulador, 100){
        m++;
    }

    Usuario* usuarios = new  Usuario[n];
    Usuario* pusuarios = usuarios;

    usuario.clear();
    usuario.seekg(0);

     while(usuario.getline(encapsulador,100)){

       //codigo
        pcode = encapsuladorcodigo
        
        while (*p != '\0' && *p != '*'){
            *pcode = *p; 
            pcode++;
            p++;
        }
            *pcode = '\0';
            pusuarios->codigo = atoi(encapsuladorcodigo);
        
        if (*p == '*'){
            p += 2;
        }
        
        //nombre
        char* ptr = pusuarios->nombre;
        
        while (*p && *p != '*'){
            *ptr = *p;
            ptr++;
            p++;
        }
            *ptrn = '\0';
            
        if (*p == '*'){
            p += 2;
        }
        
        //programa
        ptr = pusuarios->programa;
        
        while (*p && *p != '*'){
            *ptr = *p;
            ptr++
            p++
        }
            *ptr = '\0';
            
        if (*p == '*'){
            p += 2; 
        } 
        
        //semestre
        ps = encapsuladorsemestre;
        
        while (*p != '\0' && *p != '*'){
            *ps = *p; 
            ps++;
            p++;
        }
            *ps = '\0';
            pusuarios->semestre= atoi(encapsuladorsemestre);
        
        if (*p == '*'){
            p += 2;
        }

        pusuarios++;
    }

    archivo.close();
}

//3.
void consultarEstadoOpertaivoE(Equipo*equipos, int totalEquipos){
    char nombreLab[100];
    cout<<"Por favor ingrese el nombre del laboratorio: ";
    cin.ignore();
    cin.getline(nombreLab,100);
    Equipo*ptr=equipos;
    int operativos=0;
    int mantenimiento=0;
    int restriccion=0;
    for(int i=0;i<totalEquipos;i++){
        if(strcmp(ptr->laboratorio,nombreLab)==0){
            if(strcmp(ptr->estado,"operativa")==0){
                cout<<"Equipos operativos: "<<ptr->nombre<<endl;
                    operativos++;
            }
            else if(strcmp(ptr->estado,"mantenimiento")==0){
                cout<<"Equipos en mantenimiento: "<<ptr->nombre<<endl;
                    mantenimiento++;
            }
        if(ptr->semestreMin>1){
                cout<<"Equipos con restricciones por semestre: "<<ptr->nombre<<endl;
                    restriccion++;
            }
        }
        ptr++;
    }
    cout<<"Equipos operativos: "<<operativos<<endl;
    cout<<"Equipos en mantenimiento: "<<mantenimiento<<endl;
    cout<<"Equipos con restricciones por semestre: "<<restriccion<<endl;
}

//4.
int generarCodigoSesion(){
    ifstream archivo("sesiones.dat",ios::binary);
    if(!archivo){
        return 1;
    }
    archivo.seekg(0,ios::end);
    long tam=archivo.tellg();
    int numRegistros=tam/sizeof(SesionUso);
    if(numRegistros==0){
        archivo.close();
        return 1;
    }
    SesionUso ultima;
    archivo.seekg((numRegistros-1)*sizeof(SesionUso),ios::beg);
    archivo.read(reinterpret_cast<char*>(&ultima),sizeof(SesionUso));
    archivo.close();
    return ultima.codigoSesion+1;
}
void programarSesion(Equipo*equipos,int totalEquipos,Usuario*usuarios,int totalUsuarios){
    int codigoUsuario;
    cout<<"Ingrese el codigo del usuario: ";
    cin>>codigoUsuario;
    Usuario*usuarioEncontrado=NULL;
    Usuario*ptrU=usuarios;
    Usuario*finU=usuarios+totalUsuarios;
    while(ptrU<finU){
        if(ptrU->codigo==codigoUsuario){
            usuarioEncontrado=ptrU;
            break;
        }
        ptrU++;
    }
    if(usuarioEncontrado==NULL){
        cout<<"Usuario no encontrado"<<endl;
        return;
    }
    int codigoEquipo;
    cout<<"Ingrese el codigo del equipo: ";
    cin>>codigoEquipo;
    Equipo*equipoEncontrado=NULL;
    Equipo*ptrE=equipos;
    Equipo*finE=equipos+totalEquipos;
    while(ptrE<finE){
        if(ptrE->codigo==codigoEquipo){
            equipoEncontrado=ptrE;
            break;
        }
        ptrE++;
    }
    if(equipoEncontrado==NULL){
        cout<<"Equipo no encontrado"<<endl;
        return;
    }
    if(strcmp(equipoEncontrado->estado,"operativa")!=0){
        cout<<"El equipo no esta operativo"<<endl;
        return;
    }
    if(usuarioEncontrado->semestre<equipoEncontrado->semestreMin){
        cout<<"El usuario no cumple el semestre minimo"<<endl;
        return;
    }
    int duracion;
    cout<<"Ingrese la duracion estimada en horas: ";
    cin>>duracion;
    SesionUso sesion;
    sesion.codigoSesion=generarCodigoSesion();
    sesion.codigoEquipo=codigoEquipo;
    sesion.codigoUsuario=codigoUsuario;
    sesion.duracion=duracion;
    sesion.penalizacion=0;
    strcpy(sesion.observaciones,"Sin observaciones");
    cin.ignore();
    cout<<"Ingrese la fecha de inicio (dd/mm/aaaa): ";
    cin.getline(sesion.fechaInicio,20);
    ofstream archivo("sesiones.dat",ios::binary|ios::app);
    if(!archivo){
        cout<<"Error al abrir el archivo"<<endl;
        return;
    }
    archivo.write(reinterpret_cast<char*>(&sesion),sizeof(SesionUso));
    archivo.close();
    cout<<"Sesion registrada correctamente con codigo: "<<sesion.codigoSesion<<endl;
}

//5.
void cerrarSesión(Equipo* equipos, int totalEquipos){
    int codigoSesion;
    cout<<"Ingrese el codigo de la sesion a cargar: ";
    cin>>codigoSesion;

    fstream archivo("sesiones.dat", ios::binary | ios::in | ios::out);
    if(!archivo){
        cout << "Error al abrir el archivo\n";
        return;
    }

    SesionUso sesion;
    bool encontrado = false;

    while(archivo.read(reinterpret_cast<char*>(&sesion), sizeof(SesionUso))){
        if(sesion.codigoSesion == codigoSesion){
            encontrado = true;

            int duracionReal;
            cout<<"Ingrese la duracion REAL de la sesion: ";
            cin>>duracionReal;

            cin.ignore();
            cout<<"Ingrese observaciones: ";
            cin.getline(sesion.observaciones, 200);

            //Buscar Equipos
            Equipo* ptr = equipos;
            for(int i = 0; i < totalEquipos; i++){
                if(ptr->codigo == sesion.codigoEquipo){

                    if(duracionReal > sesion.duracion){
                        int extra = duracionReal - sesion.duracion;
                        sesion.penalizacion = extra * (0.03 * ptr->costo);
                    }

                    char dano;
                    cout<<"El equipo presenta danio? (s/n): ";
                    cin>>dano;

                    if(dano == 's' || dano == 'S'){
                        strcpy(ptr->estado, "mantenimiento");
                    }
                    break;
                }
                ptr++;
            }
//Reescribir en el archivo
            archivo.seekp(-sizeof(SesionUso), ios::cur);
            archivo.write(reinterpret_cast<char*>(&sesion), sizeof(SesionUso));

            cout<<"Sesion cerrada correctamente\n";
            break;
        }
    }

    if(!encontrado){
        cout<<"Sesion no encontrada\n";
    }

    archivo.close();
            
}

//6.
void informeUsoIntensivo(Equipo* equipos, int totalEquipos){

    float* horas = new float[totalEquipos];

    // Inicializar
    for(int i = 0; i < totalEquipos; i++){
        horas[i] = 0;
    }

    ifstream archivo("sesiones.dat", ios::binary);

    if(!archivo){
        cout << "No hay sesiones registradas\n";
        delete[] horas;
        return;
    }

    SesionUso sesion;

    while(archivo.read(reinterpret_cast<char*>(&sesion), sizeof(SesionUso))){
        Equipo* ptr = equipos;

        for(int i = 0; i < totalEquipos; i++){
            if(ptr->codigo == sesion.codigoEquipo){
                horas[i] += sesion.duracion;
                break;
            }
            ptr++;
        }
    }

    archivo.close();

    // Analizar por laboratorio
    for(int i = 0; i < totalEquipos; i++){
        Equipo* actual = equipos + i;

        float maxHoras = horas[i];
        int indexMax = i;

        for(int j = 0; j < totalEquipos; j++){
            if(strcmp(actual->laboratorio, (equipos + j)->laboratorio) == 0){
                if(horas[j] > maxHoras){
                    maxHoras = horas[j];
                    indexMax = j;
                }
            }
        }

        // Evitar repetir laboratorio
        bool yaImpreso = false;
        for(int k = 0; k < i; k++){
            if(strcmp(actual->laboratorio, (equipos + k)->laboratorio) == 0){
                yaImpreso = true;
                break;
            }
        }

        if(!yaImpreso){
            cout<<"--" << actual->laboratorio << ": "
                 << (equipos + indexMax)->nombre
                 << " (" << maxHoras << " horas)" << endl;
        }
    }

    delete[] horas;
}

//7.
void rankingUsuariosCriticos(Usuario* usuarios, int totalUsuarios) {

    float* penalizaciones = new float[totalUsuarios];
    int* sesiones = new int[totalUsuarios];

    float* pPen = penalizaciones;
    int* pSes = sesiones;

    while(pPen < penalizaciones + totalUsuarios){
        *pPen = 0;
        pPen++;
    }

    while(pSes < sesiones + totalUsuarios){
        *pSes = 0;
        pSes++;
    }

    ifstream archivo("sesiones.dat", ios::binary);

    if(!archivo) {
        cout << "No hay sesiones\n";
        delete[] penalizaciones;
        delete[] sesiones;
        return;
    }

    SesionUso sesion;

    while(archivo.read(reinterpret_cast<char*>(&sesion), sizeof(SesionUso))) {

        Usuario* ptrU = usuarios;
        float* ptrPen = penalizaciones;
        int* ptrSes = sesiones;

        while(ptrU < usuarios + totalUsuarios){
            if(ptrU->codigo == sesion.codigoUsuario){
                *ptrPen += sesion.penalizacion;
                (*ptrSes)++;
                break;
            }
            ptrU++;
            ptrPen++;
            ptrSes++;
        }
    }

    archivo.close();

    // Calcular índice
    float* indice = new float[totalUsuarios];
    float* ptrInd = indice;
    float* ptrPen = penalizaciones;
    int* ptrSes = sesiones;

    while(ptrInd < indice + totalUsuarios){
        if(*ptrSes > 0)
            *ptrInd = (*ptrPen) / (*ptrSes);
        else
            *ptrInd = 0;

        ptrInd++;
        ptrPen++;
        ptrSes++;
    }

    for(int k = 0; k < 3; k++){

        float max = -1;
        int pos = -1;

        ptrInd = indice;
        int contador = 0;

        while(ptrInd < indice + totalUsuarios){
            if(*ptrInd > max){
                max = *ptrInd;
                pos = contador;
            }
            ptrInd++;
            contador++;
        }

        if(pos != -1){

            Usuario* ptrU = usuarios + pos;

            cout << "Usuario: " << ptrU->nombre
                 << " | Indice: " << max << endl;

            *(indice + pos) = -1; // marcar usado
        }
    }

    delete[] penalizaciones;
    delete[] sesiones;
    delete[] indice;
}

//Main
int main (){
    Equipo* equipos = NULL;
    Usuario* usuarios = NULL;

    int totalEquipos = 0;
    int totalUsuarios = 0;

    int opcion;

    do {
        cout << "\n========= MENU =========\n";
        cout << "1. Cargar equipos\n";
        cout << "2. Cargar usuarios\n";
        cout << "3. Consultar estado laboratorio\n";
        cout << "4. Programar sesion\n";
        cout << "5. Cerrar sesion\n";
        cout << "6. Informe uso intensivo\n";
        cout << "7. Ranking usuarios criticos\n";
        cout << "8. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        cin.ignore();

        switch(opcion) {

            case 1: {
                char nombreArchivo[50];
                cout<<"Ingrese archivo de equipos: ";
                cin.getline(nombreArchivo, 50);

                equipos = cargaequipos(nombreArchivo, totalEquipos);
                break;
            }

            case 2: {
                char nombreArchivo[50];
                cout<<"Ingrese archivo de usuarios: ";
                cin.getline(nombreArchivo, 50);

                usuarios = cargaUsuarios(nombreArchivo, totalUsuarios);
                break;
            }

            case 3:
                if(equipos != NULL)
                    consultarEstadoOpertaivoE(equipos, totalEquipos);
                else
                    cout << "Debe cargar equipos primero\n";
                break;

            case 4:
                if(equipos != NULL && usuarios != NULL)
                    programarSesion(equipos, totalEquipos, usuarios, totalUsuarios);
                else
                    cout<<"Debe cargar equipos y usuarios\n";
                break;

            case 5:
                if(equipos != NULL)
                    cerrarSesión(equipos, totalEquipos);
                else
                    cout<<"Debe cargar equipos primero\n";
                break;

            case 6:
                if(equipos != NULL)
                    informeUsoIntensivo(equipos, totalEquipos);
                else
                    cout<<"Debe cargar equipos primero\n";
                break;

            case 7:
                if(usuarios != NULL)
                    rankingUsuariosCriticos(usuarios, totalUsuarios);
                else
                    cout<<"Debe cargar usuarios primero\n";
                break;

            case 8:
                cout<<"Saliendo del sistema...\n";
                break;

            default:
                cout<<"Opcion invalida\n";
        }

    } while(opcion != 8);

    // Liberar memoria
    delete[] equipos;
    delete[] usuarios;

    return 0;
}
