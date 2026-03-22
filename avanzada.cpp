#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

// ==================== CONVERSIONES ====================

int convertirEntero(char* cad) {
    int num = 0, i = 0;
    while (cad[i] != '\0') {
        num = num * 10 + (cad[i] - '0');
        i++;
    }
    return num;
}

long convertirLong(char* cad) {
    long num = 0;
    int i = 0;
    while (cad[i] != '\0') {
        num = num * 10 + (cad[i] - '0');
        i++;
    }
    return num;
}

float convertirFloat(char* cad) {
    float num = 0, dec = 0;
    int i = 0, decFlag = 0, div = 1;

    while (cad[i] != '\0') {
        if (cad[i] == '.') decFlag = 1;
        else if (!decFlag) num = num * 10 + (cad[i] - '0');
        else {
            dec = dec * 10 + (cad[i] - '0');
            div *= 10;
        }
        i++;
    }
    return num + dec / div;
}

// ==================== ESTRUCTURAS ====================

struct Equipo {
    int codigo;
    char nombre[100];
    char laboratorio[50];
    char tipo[50];
    char estado[20];
    float costo;
    int semestreMin;
    char descripcion[200];
};

struct Usuario {
    long codigo;
    char nombre[100];
    char programa[80];
    int semestre;
};

struct SesionUso {
    int codigoSesion;
    int codigoEquipo;
    long codigoUsuario;
    char fecha[20];
    int duracionProgramada;
    int duracionReal;
    char observaciones[200];
    float penalizacion;
    int cerrada;
};

// ==================== UTILIDADES ====================

char* leerToken(char* p, char* dest) {
    while (*p == ' ') p++;
    char* d = dest;
    while (*p != '*' && *p != '\0') *d++ = *p++;
    while (d > dest && *(d-1) == ' ') d--;
    *d = '\0';
    if (*p == '*') p++;
    while (*p == ' ') p++;
    return p;
}

// ==================== CARGA EQUIPOS ====================

Equipo* cargaEquipos(char nombreArchivo[], int &totalEquipos) {
    ifstream archivo(nombreArchivo);
    if (!archivo) {
        cout << "Error al abrir archivo\n";
        return NULL;
    }

    char linea[400];
    int n = 0;

    while (archivo.getline(linea, 400))
        if (strlen(linea) > 0) n++;

    archivo.clear();
    archivo.seekg(0);

    Equipo* equipos = new Equipo[n];
    Equipo* ptrE = equipos;

    while (archivo.getline(linea, 400)) {
        if (strlen(linea) == 0) continue;

        char aux[200];
        char* p = linea;

        p = leerToken(p, aux); ptrE->codigo = convertirEntero(aux);
        p = leerToken(p, ptrE->nombre);
        p = leerToken(p, ptrE->laboratorio);
        p = leerToken(p, ptrE->tipo);
        p = leerToken(p, ptrE->estado);
        p = leerToken(p, aux); ptrE->costo = convertirFloat(aux);
        p = leerToken(p, aux); ptrE->semestreMin = convertirEntero(aux);

        char* d = ptrE->descripcion;
        while (*p != '\0') *d++ = *p++;
        *d = '\0';

        ptrE++;
    }

    archivo.close();
    totalEquipos = n;
    return equipos;
}

// ==================== CARGA USUARIOS ====================

Usuario* cargaUsuarios(char nombreArchivo[], int &totalUsuarios) {
    ifstream archivo(nombreArchivo);
    if (!archivo) {
        cout << "Error al abrir archivo\n";
        return NULL;
    }

    char linea[300];
    int n = 0;

    while (archivo.getline(linea, 300))
        if (strlen(linea) > 0) n++;

    archivo.clear();
    archivo.seekg(0);

    Usuario* usuarios = new Usuario[n];
    Usuario* ptrU = usuarios;

    while (archivo.getline(linea, 300)) {
        if (strlen(linea) == 0) continue;

        char aux[100];
        char* p = linea;

        p = leerToken(p, aux); ptrU->codigo = convertirLong(aux);
        p = leerToken(p, ptrU->nombre);
        p = leerToken(p, ptrU->programa);
        p = leerToken(p, aux); ptrU->semestre = convertirEntero(aux);

        ptrU++;
    }

    archivo.close();
    totalUsuarios = n;
    return usuarios;
}

// ==================== GENERAR CODIGO ====================

int generarCodigoSesion() {
    ifstream archivo("sesiones.dat", ios::binary);
    if (!archivo) return 1;

    archivo.seekg(0, ios::end);
    int n = archivo.tellg() / sizeof(SesionUso);
    if (n == 0) return 1;

    SesionUso s;
    archivo.seekg((n - 1) * sizeof(SesionUso));
    archivo.read((char*)&s, sizeof(SesionUso));
    archivo.close();

    return s.codigoSesion + 1;
}

// ==================== CONSULTAR ====================

void consultarLaboratorio(Equipo* equipos, int totalEquipos) {
    if (!equipos) return;

    char estadoOperativo[20] = "operativa";
    char estadoMantenimiento[20] = "mantenimiento";

    char lab[50];
    cout << "Laboratorio: ";
    cin.getline(lab, 50);

    cout << "\nOperativos:\n";
    for (Equipo* p = equipos; p < equipos + totalEquipos; p++)
        if (strcmp(p->laboratorio, lab) == 0 && strcmp(p->estado, estadoOperativo) == 0)
            cout << p->nombre << endl;

    cout << "\nMantenimiento:\n";
    for (Equipo* p = equipos; p < equipos + totalEquipos; p++)
        if (strcmp(p->laboratorio, lab) == 0 && strcmp(p->estado, estadoMantenimiento) == 0)
            cout << p->nombre << endl;

    cout << "\nRestriccion semestre:\n";
    for (Equipo* p = equipos; p < equipos + totalEquipos; p++)
        if (strcmp(p->laboratorio, lab) == 0 && p->semestreMin > 1)
            cout << p->nombre << " (semestre minimo: " << p->semestreMin << ")" << endl;
}

// ==================== PROGRAMAR ====================

void programarSesion(Equipo* equipos, int totalEquipos,
                     Usuario* usuarios, int totalUsuarios) {

    if (!equipos || !usuarios) return;

    long codU;
    cout << "Ingrese codigo de usuario: ";
    cin >> codU;

    Usuario* u = NULL;
    for (Usuario* p = usuarios; p < usuarios + totalUsuarios; p++)
        if (p->codigo == codU) { u = p; break; }

    if (!u) {
        cout << "Usuario no encontrado\n";
        return;
    }

    int codE;
    cout << "Ingrese codigo del equipo: ";
    cin >> codE;

    Equipo* e = NULL;
    for (Equipo* p = equipos; p < equipos + totalEquipos; p++)
        if (p->codigo == codE) { e = p; break; }

    if (!e) {
        cout << "Equipo no encontrado\n";
        return;
    }

    char estadoOperativo[20] = "operativa";

    if (strcmp(e->estado, estadoOperativo) != 0) {
        cout << "El equipo no esta operativo\n";
        return;
    }

    if (u->semestre < e->semestreMin) {
        cout << "No cumple con el semestre minimo requerido\n";
        return;
    }

    SesionUso s;
    s.codigoSesion  = generarCodigoSesion();
    s.codigoEquipo  = codE;
    s.codigoUsuario = codU;
    s.duracionReal  = 0;
    s.penalizacion  = 0;
    s.cerrada       = 0;
    strcpy(s.observaciones, "Sin observaciones");

    cout << "Ingrese duracion programada (horas): ";
    cin >> s.duracionProgramada;
    cin.ignore(1000, '\n');

    cout << "Ingrese fecha (ej: 2025-03-22): ";
    cin.getline(s.fecha, 20);

    ofstream arch("sesiones.dat", ios::binary | ios::app);
    arch.write((char*)&s, sizeof(SesionUso));
    arch.close();

    cout << "Sesion programada correctamente\n";
}
// ==================== CERRAR ====================

void cerrarSesion(Equipo* equipos, int totalEquipos) {

    int codSesion;
    cout << "\n--- CERRAR SESION ---\n";
    cout << "Ingrese codigo de la sesion: ";
    cin >> codSesion;
    cin.ignore(1000, '\n');

    fstream arch("sesiones.dat", ios::binary | ios::in | ios::out);
    if (!arch) {
        cout << "No hay sesiones registradas\n";
        return;
    }

    arch.seekg(0, ios::end);
    int n = arch.tellg() / sizeof(SesionUso);

    SesionUso s;
    int pos = -1;

    for (int i = 0; i < n; i++) {
        arch.seekg(i * sizeof(SesionUso));
        arch.read((char*)&s, sizeof(SesionUso));
        if (s.codigoSesion == codSesion) { pos = i; break; }
    }

    if (pos == -1) {
        cout << "Sesion no encontrada\n";
        return;
    }

    if (s.cerrada) {
        cout << "La sesion ya estaba cerrada\n";
        return;
    }

    cout << "Ingrese duracion real (horas): ";
    cin >> s.duracionReal;
    cin.ignore(1000, '\n');

    cout << "Ingrese observaciones: ";
    cin.getline(s.observaciones, 200);

    int tasaPenalizacion = 3;

    s.penalizacion = 0;
    int extra = s.duracionReal - s.duracionProgramada;

    if (extra > 0) {
        float costo = 0;
        for (Equipo* p = equipos; p < equipos + totalEquipos; p++)
            if (p->codigo == s.codigoEquipo) { costo = p->costo; break; }

        s.penalizacion = extra * (tasaPenalizacion / 100.0) * costo;
    }

    char dano[3];
    cout << "El equipo sufrio danos? (s/n): ";
    cin >> dano;
    cin.ignore(1000, '\n');

    char estadoDaniado[20] = "daniada";

    if (strcmp(dano, "s") == 0 || strcmp(dano, "S") == 0) {
        for (Equipo* p = equipos; p < equipos + totalEquipos; p++)
            if (p->codigo == s.codigoEquipo) {
                strcpy(p->estado, estadoDaniado);
                break;
            }
    }

    s.cerrada = 1;

    arch.seekp(pos * sizeof(SesionUso));
    arch.write((char*)&s, sizeof(SesionUso));
    arch.close();

    cout << "Sesion cerrada correctamente\n";

    if (s.penalizacion > 0)
        cout << "Penalizacion generada: $" << s.penalizacion << endl;
}

// ==================== INFORME ====================

void informeUsoIntensivo(Equipo* equipos, int totalEquipos) {
    if (!equipos) return;

    ifstream arch("sesiones.dat", ios::binary);
    if (!arch) {
        cout << "No hay sesiones registradas\n";
        return;
    }

    arch.seekg(0, ios::end);
    int n = arch.tellg() / sizeof(SesionUso);
    if (n == 0) {
        cout << "No hay sesiones registradas\n";
        return;
    }

    int* horas = new int[totalEquipos];
    for (int* p = horas; p < horas + totalEquipos; p++) *p = 0;

    // Acumular horas por equipo
    for (int i = 0; i < n; i++) {
        SesionUso s;
        arch.seekg(i * sizeof(SesionUso));
        arch.read((char*)&s, sizeof(SesionUso));

        Equipo* pe = equipos;
        int* ph = horas;

        while (pe < equipos + totalEquipos) {
            if (pe->codigo == s.codigoEquipo) {
                if (s.cerrada)
                    *ph += s.duracionReal;
                else
                    *ph += s.duracionProgramada;
                break;
            }
            pe++; ph++;
        }
    }
    arch.close();

    cout << "\nUso intensivo:\n";

    // Recorrer laboratorios
    for (Equipo* pLab = equipos; pLab < equipos + totalEquipos; pLab++) {

        bool yaProcesado = false;
        for (Equipo* pPrev = equipos; pPrev < pLab; pPrev++) {
            if (strcmp(pPrev->laboratorio, pLab->laboratorio) == 0) {
                yaProcesado = true;
                break;
            }
        }

        if (yaProcesado) continue;

        int maxHoras = -1;
        Equipo* mejor = NULL;

        Equipo* pe = equipos;
        int* ph = horas;

        while (pe < equipos + totalEquipos) {
            if (strcmp(pe->laboratorio, pLab->laboratorio) == 0) {
                if (*ph > maxHoras) {
                    maxHoras = *ph;
                    mejor = pe;
                }
            }
            pe++; ph++;
        }

        if (mejor && maxHoras > 0)
            cout << "-- " << pLab->laboratorio << ": "
                 << mejor->nombre << " (" << maxHoras << " horas)\n";
        else
            cout << "-- " << pLab->laboratorio << ": sin uso registrado\n";
    }

    delete[] horas;
}

// ==================== RANKING ====================

void rankingUsuariosCriticos(Usuario* usuarios, int totalUsuarios) {
    if (!usuarios) return;

    ifstream arch("sesiones.dat", ios::binary);
    if (!arch) {
        cout << "No hay sesiones registradas\n";
        return;
    }

    arch.seekg(0, ios::end);
    int n = arch.tellg() / sizeof(SesionUso);
    if (n == 0) {
        cout << "No hay sesiones registradas\n";
        return;
    }

    float* penal = new float[totalUsuarios];
    int* sesiones = new int[totalUsuarios];
    float* indice = new float[totalUsuarios];
    bool* usado = new bool[totalUsuarios];

    for (float* p = penal; p < penal + totalUsuarios; p++) *p = 0;
    for (int* p = sesiones; p < sesiones + totalUsuarios; p++) *p = 0;
    for (bool* p = usado; p < usado + totalUsuarios; p++) *p = false;

    // Acumular datos
    for (int i = 0; i < n; i++) {
        SesionUso s;
        arch.seekg(i * sizeof(SesionUso));
        arch.read((char*)&s, sizeof(SesionUso));

        Usuario* pu = usuarios;
        float* pp = penal;
        int* ps = sesiones;

        while (pu < usuarios + totalUsuarios) {
            if (pu->codigo == s.codigoUsuario) {
                *pp += s.penalizacion;
                (*ps)++;
                break;
            }
            pu++; pp++; ps++;
        }
    }
    arch.close();

    // Calcular índice
    float* pi = indice;
    float* pp = penal;
    int* ps = sesiones;

    while (pi < indice + totalUsuarios) {
        if (*ps > 0)
            *pi = *pp / *ps;
        else
            *pi = 0;
        pi++; pp++; ps++;
    }

    cout << "\nRanking usuarios criticos:\n";

    // Top 3
    for (int lugar = 1; lugar <= 3; lugar++) {
        float max = -1;
        int pos = -1;

        float* pIdx = indice;
        bool* pUsado = usado;
        int i = 0;

        while (pIdx < indice + totalUsuarios) {
            if (!*pUsado && *pIdx > max) {
                max = *pIdx;
                pos = i;
            }
            pIdx++; pUsado++; i++;
        }

        if (pos != -1 && max > 0) {
            Usuario* u = usuarios + pos;
            cout << lugar << ". " << u->nombre
                 << " | Sesiones: " << *(sesiones + pos)
                 << " | Penalizacion: $" << *(penal + pos)
                 << " | Indice: " << max << endl;

            *(usado + pos) = true;
        }
    }

    delete[] penal;
    delete[] sesiones;
    delete[] indice;
    delete[] usado;
}

// ==================== MAIN ====================

int main() {
    Equipo*  equipos  = NULL;
    Usuario* usuarios = NULL;
    int totalEquipos  = 0;
    int totalUsuarios = 0;

    int op;

    do {
        cout << "\n=====================================\n";
        cout << "     SISTEMA DE LABORATORIO\n";
        cout << "=====================================\n";
        cout << "1. Cargar equipos\n";
        cout << "2. Cargar usuarios\n";
        cout << "3. Consultar laboratorio\n";
        cout << "4. Programar sesion\n";
        cout << "5. Cerrar sesion\n";
        cout << "6. Informe uso\n";
        cout << "7. Ranking criticos\n";
        cout << "8. Salir\n";
        cout << "=====================================\n";
        cout << "Seleccione una opcion: ";

        cin >> op;
        cin.ignore(1000, '\n');

        char nom[100];

        switch (op) {

            case 1:
                cout << "Ingrese nombre del archivo de equipos: ";
                cin.getline(nom, 100);

                if (equipos) delete[] equipos;
                equipos = cargaEquipos(nom, totalEquipos);

                if (equipos)
                    cout << "Archivo cargado correctamente\n";
                else
                    cout << "No se pudo abrir el archivo\n";
                break;

            case 2:
                cout << "Ingrese nombre del archivo de usuarios: ";
                cin.getline(nom, 100);

                if (usuarios) delete[] usuarios;
                usuarios = cargaUsuarios(nom, totalUsuarios);

                if (usuarios)
                    cout << "Archivo cargado correctamente\n";
                else
                    cout << "No se pudo abrir el archivo\n";
                break;

            case 3:
                if (!equipos) {
                    cout << "Debe cargar equipos primero\n";
                    break;
                }
                consultarLaboratorio(equipos, totalEquipos);
                break;

            case 4:
                if (!equipos || !usuarios) {
                    cout << "Debe cargar datos primero\n";
                    break;
                }
                programarSesion(equipos, totalEquipos, usuarios, totalUsuarios);
                break;

            case 5:
                if (!equipos) {
                    cout << "Debe cargar equipos primero\n";
                    break;
                }
                cerrarSesion(equipos, totalEquipos);
                break;

            case 6:
                if (!equipos) {
                    cout << "Debe cargar equipos primero\n";
                    break;
                }
                informeUsoIntensivo(equipos, totalEquipos);
                break;

            case 7:
                if (!usuarios) {
                    cout << "Debe cargar usuarios primero\n";
                    break;
                }
                rankingUsuariosCriticos(usuarios, totalUsuarios);
                break;

        }

    } while (op != 8);

    delete[] equipos;
    delete[] usuarios;
}

