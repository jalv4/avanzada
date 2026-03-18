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
void cargaequipos(){

    ifstream equipo("equipos.txt");
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
void cargaUsuarios(){

    char encapsulador[100];

    ifstream usuario("usuarios.txt");

    if(!usuario){
        cout << "No se pudo abrir el archivo usuarios\n";
        exit(0);
    }

     int n = 0;
    char encapsulador[100];
    char* p = encapsulador;
    char encapsuladorcodigo[4];
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


int main (){
    
}  

