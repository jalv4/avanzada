#include <iostream>

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


//2.


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


//5.


//6.


//7.


int main (){
  
}
