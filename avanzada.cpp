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
        ifstream equipo(equipos.txt);
        if(!equipo){
            cout << "no se pudo abrir el archivo equipos\n";
            exit;
        }
        int new n = 0;
        char encapsulador[100];

        while(equipo.getline(encapsulador, 100){
            n++;
        }

            Equipo equipos[n];
            int i = 0;
            equipo.clear();
            equipo.seekg(0);

        while(equipos.getline(encapsulador, 100){
               int p = 0;
               int j = 0;

            while(encapsulador[p] != '*'){
                equipos[i].codigo[j] = encapsulador[p];
                p++;
                j++;
            }
                equipos[i].codigo[j] = '\0';
                p += 2;
                j = 0;

        
            while(encapsulador[p] != '*'){
                equipos[i].nombre[j] = encapsulador[p];
                p++;
                j++;
            }
                equipos[i].nombre[j] = '\0';
                p += 2;
                j = 0;
        
            while(encapsulador[p] != '*'){
                equipos[i].laboratorio[j] = encapsulador[p];
                p++;
                j++;
            }
                equipos[i].laboratorio[j] = '\0';
                p += 2;
                j = 0;

             while(encapsulador[p] != '*'){
                equipos[i].tipo[j] = encapsulador[p];
                p++;
                j++;
            }
                equipos[i].tipo[j] = '\0';
                p += 2;
                j = 0;

            while(encapsulador[p] != '*'){
                equipos[i].estado[j] = encapsulador[p];
                p++;
                j++;
            }
                equipos[i].estado[j] = '\0';
                p += 2;
                j = 0;

    
            while(encapsulador[p] != '*'){
                equipos[i].costo[j] = encapsulador[p];
                p++;
                j++;
            }
                equipos[i].costo[j] = '\0';
                p += 2;
                j = 0;
        
            while(encapsulador[p] != '*'){
                equipos[i].semestre[j] = encapsulador[p];
                p++;
                j++;
            }
                equipos[i].semestre[j] = '\0';
                p += 2;
                j = 0;

            while(encapsulador[p] != '\0'){
                equipos[i].descripcion[j] = encapsulador[p];
                p++;
                j++;
            }
                equipos[i].descripcion[j] = '\0';

        i++;
    }

    archivo.close();
}
        
//2.
void cargaUsuarios(){

    char encapsulador[100];
    int i = 0;

    ifstream usuario("usuarios.txt");

    if(!usuario){
        cout << "No se pudo abrir el archivo usuarios\n";
        return;
    }

        int new m = 0;
        char encapsulador[100];

        while(usuario.getline(encapsulador, 100){
            m++;
        }

        Equipo usuarios[m];
        int i = 0;
        usuario.clear();
        usuario.seekg(0);

    while(usuario.getline(encapsulador,100)){

        int p = 0;
        int j = 0;

        while(encapsulador[p] != '*'){
            usuarios[i].codigo[j] = encapsulador[p];
            p++;
            j++;
        }
            usuarios[i].codigo[j] = '\0';
            p += 2;
            j = 0;

        while(encapsulador[p] != '*'){
            usuarios[i].nombre[j] = encapsulador[p];
            p++;
            j++;
        }
            usuarios[i].nombre[j] = '\0';
            p += 2;
            j = 0;
        
        while(encapsulador[p] != '*'){
            usuarios[i].programa[j] = encapsulador[p];
            p++;
            j++;
        }
            usuarios[i].programa[j] = '\0';
            p += 2;
            j = 0;
        
        while(encapsulador[p] != '\0'){
            usuarios[i].semestre[j] = encapsulador[p];
            p++;
            j++;
        }
            usuarios[i].semestre[j] = '\0';

        i++;
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

    
}

//6.


//7.


int main (){
}  

