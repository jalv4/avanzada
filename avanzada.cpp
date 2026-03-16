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
void cargausuarios(){

    char encapsulador[100];
    int i = 0;

    ifstream usuario("usuarios.txt");

    if(!usuario){
        cout << "no se pudo abrir el archivo usuarios\n";
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


//5.


//6.


//7.


int main (){
  
}
