#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
using namespace std;

// ==================== ESTRUCTURAS ====================

struct Equipo {
    int   codigo;
    char  nombre[100];
    char  laboratorio[50];
    char  tipo[50];
    char  estado[20];      // "operativa" | "mantenimiento" | "daniada"
    float costo;
    int   semestreMin;
    char  descripcion[200];
};

struct Usuario {
    long codigo;
    char nombre[100];
    char programa[80];
    int  semestre;
};

struct SesionUso {
    int   codigoSesion;
    int   codigoEquipo;
    long  codigoUsuario;
    char  fecha[20];
    int   duracionProgramada;
    int   duracionReal;
    char  observaciones[200];
    float penalizacion;
    int   cerrada;             // 0 = abierta, 1 = cerrada
};

// ==================== UTILIDADES ====================

char* leerToken(char* p, char* dest) {
    while (*p == ' ') p++;
    char* d = dest;
    while (*p != '*' && *p != '\0') { *d++ = *p++; }
    while (d > dest && *(d-1) == ' ') d--;
    *d = '\0';
    if (*p == '*') p++;
    while (*p == ' ') p++;
    return p;
}

// ==================== CARGAR EQUIPOS ====================

Equipo* cargaEquipos(char nombreArchivo[], int &totalEquipos) {
    ifstream archivo(nombreArchivo);
    if (!archivo) {
        cout << "Error abriendo archivo: " << nombreArchivo << "\n";
        return NULL;
    }

    char linea[400];
    int n = 0;
    while (archivo.getline(linea, 400))
        if (strlen(linea) > 0) n++;

    archivo.clear();
    archivo.seekg(0);

    Equipo* equipos = new Equipo[n];
    Equipo* ptrE    = equipos;

    while (archivo.getline(linea, 400)) {
        if (strlen(linea) == 0) continue;
        char  aux[200];
        char* p = linea;

        p = leerToken(p, aux);           ptrE->codigo      = atoi(aux);
        p = leerToken(p, ptrE->nombre);
        p = leerToken(p, ptrE->laboratorio);
        p = leerToken(p, ptrE->tipo);
        p = leerToken(p, ptrE->estado);
        p = leerToken(p, aux);           ptrE->costo       = atof(aux);
        p = leerToken(p, aux);           ptrE->semestreMin = atoi(aux);

        char* d = ptrE->descripcion;
        while (*p == ' ') p++;
        while (*p != '\0') *d++ = *p++;
        *d = '\0';

        ptrE++;
    }

    archivo.close();
    totalEquipos = n;
    cout << "Equipos cargados: " << n << "\n";
    return equipos;
}

// ==================== CARGAR USUARIOS ====================

Usuario* cargaUsuarios(char nombreArchivo[], int &totalUsuarios) {
    ifstream archivo(nombreArchivo);
    if (!archivo) {
        cout << "Error abriendo archivo: " << nombreArchivo << "\n";
        return NULL;
    }

    char linea[300];
    int n = 0;
    while (archivo.getline(linea, 300))
        if (strlen(linea) > 0) n++;

    archivo.clear();
    archivo.seekg(0);

    Usuario* usuarios = new Usuario[n];
    Usuario* ptrU     = usuarios;

    while (archivo.getline(linea, 300)) {
        if (strlen(linea) == 0) continue;
        char  aux[100];
        char* p = linea;

        p = leerToken(p, aux);           ptrU->codigo   = atol(aux);
        p = leerToken(p, ptrU->nombre);
        p = leerToken(p, ptrU->programa);
        p = leerToken(p, aux);           ptrU->semestre = atoi(aux);

        ptrU++;
    }

    archivo.close();
    totalUsuarios = n;
    cout << "Usuarios cargados: " << n << "\n";
    return usuarios;
}

// ==================== GENERAR CÓDIGO DE SESIÓN ====================

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

// ==================== OPCIÓN 3: CONSULTAR ESTADO DEL LABORATORIO ====================

void consultarLaboratorio(Equipo* equipos, int totalEquipos) {
    if (!equipos) { cout << "Primero cargue los equipos.\n"; return; }

    char lab[50];
    cout << "Nombre del laboratorio: ";
    cin.getline(lab, 50);

    cout << "\n===== Estado: " << lab << " =====\n";

    cout << "\n--- Operativos ---\n";
    for (Equipo* p = equipos; p < equipos + totalEquipos; p++)
        if (strcmp(p->laboratorio, lab) == 0 && strcmp(p->estado, "operativa") == 0)
            cout << "  [" << p->codigo << "] " << p->nombre << "\n";

    cout << "\n--- En mantenimiento ---\n";
    for (Equipo* p = equipos; p < equipos + totalEquipos; p++)
        if (strcmp(p->laboratorio, lab) == 0 && strcmp(p->estado, "mantenimiento") == 0)
            cout << "  [" << p->codigo << "] " << p->nombre << "\n";

    cout << "\n--- Con restriccion de semestre ---\n";
    for (Equipo* p = equipos; p < equipos + totalEquipos; p++)
        if (strcmp(p->laboratorio, lab) == 0 && p->semestreMin > 1)
            cout << "  [" << p->codigo << "] " << p->nombre
                 << " (semestre minimo: " << p->semestreMin << ")\n";
    cout << "\n";
}

// ==================== OPCIÓN 4: PROGRAMAR SESIÓN ====================

void programarSesion(Equipo* equipos, int totalEquipos,
                     Usuario* usuarios, int totalUsuarios) {
    if (!equipos || !usuarios) {
        cout << "Primero cargue equipos y usuarios.\n"; return;
    }

    long codU;
    cout << "Codigo usuario: "; cin >> codU;

    Usuario* u = NULL;
    for (Usuario* p = usuarios; p < usuarios + totalUsuarios; p++)
        if (p->codigo == codU) { u = p; break; }
    if (!u) { cout << "Usuario no encontrado.\n"; return; }

    int codE;
    cout << "Codigo equipo: "; cin >> codE;

    Equipo* e = NULL;
    for (Equipo* p = equipos; p < equipos + totalEquipos; p++)
        if (p->codigo == codE) { e = p; break; }
    if (!e) { cout << "Equipo no encontrado.\n"; return; }

    if (strcmp(e->estado, "operativa") != 0) {
        cout << "El equipo no esta operativo (estado: " << e->estado << ").\n"; return;
    }
    if (u->semestre < e->semestreMin) {
        cout << "El usuario no cumple el semestre minimo (" << e->semestreMin << ").\n"; return;
    }

    SesionUso s;
    s.codigoSesion  = generarCodigoSesion();
    s.codigoEquipo  = codE;
    s.codigoUsuario = codU;
    s.duracionReal  = 0;
    s.penalizacion  = 0;
    s.cerrada       = 0;
    strcpy(s.observaciones, "Sin observaciones");

    cout << "Duracion estimada (horas): "; cin >> s.duracionProgramada;
    cin.ignore();
    cout << "Fecha (dd/mm/aaaa): "; cin.getline(s.fecha, 20);

    ofstream arch("sesiones.dat", ios::binary | ios::app);
    arch.write((char*)&s, sizeof(SesionUso));
    arch.close();

    cout << "Sesion #" << s.codigoSesion << " registrada correctamente.\n";
}

// ==================== OPCIÓN 5: REGISTRAR CIERRE DE SESIÓN ====================

void cerrarSesion(Equipo* equipos, int totalEquipos) {
    if (!equipos) { cout << "Primero cargue los equipos.\n"; return; }

    int codSesion;
    cout << "Codigo de sesion a cerrar: "; cin >> codSesion;
    cin.ignore();

    fstream arch("sesiones.dat", ios::binary | ios::in | ios::out);
    if (!arch) { cout << "No hay sesiones registradas.\n"; return; }

    arch.seekg(0, ios::end);
    int n = arch.tellg() / sizeof(SesionUso);

    SesionUso s;
    int pos = -1;
    for (int i = 0; i < n; i++) {
        arch.seekg(i * sizeof(SesionUso));
        arch.read((char*)&s, sizeof(SesionUso));
        if (s.codigoSesion == codSesion) { pos = i; break; }
    }

    if (pos == -1) { cout << "Sesion no encontrada.\n"; arch.close(); return; }
    if (s.cerrada)  { cout << "La sesion ya fue cerrada.\n"; arch.close(); return; }

    cout << "Duracion real (horas): "; cin >> s.duracionReal;
    cin.ignore();
    cout << "Observaciones tecnicas: "; cin.getline(s.observaciones, 200);

    int horas_extra = s.duracionReal - s.duracionProgramada;
    if (horas_extra > 0) {
        float costo = 0;
        for (Equipo* p = equipos; p < equipos + totalEquipos; p++)
            if (p->codigo == s.codigoEquipo) { costo = p->costo; break; }
        s.penalizacion = horas_extra * 0.03f * costo;
        cout << "Penalizacion aplicada: $" << s.penalizacion << "\n";
    }

    char dano[5];
    cout << "Se reporta dano al equipo? (s/n): "; cin.getline(dano, 5);
    if (dano[0] == 's' || dano[0] == 'S') {
        for (Equipo* p = equipos; p < equipos + totalEquipos; p++) {
            if (p->codigo == s.codigoEquipo) {
                strcpy(p->estado, "daniada");
                cout << "Equipo marcado como daniado.\n";
                break;
            }
        }
    }

    s.cerrada = 1;
    arch.seekp(pos * sizeof(SesionUso));
    arch.write((char*)&s, sizeof(SesionUso));
    arch.close();

    cout << "Sesion cerrada correctamente.\n";
}

// ==================== OPCIÓN 6: INFORME USO INTENSIVO ====================

void informeUsoIntensivo(Equipo* equipos, int totalEquipos) {
    if (!equipos) { cout << "Primero cargue los equipos.\n"; return; }

    ifstream arch("sesiones.dat", ios::binary);
    if (!arch) { cout << "No hay sesiones registradas.\n"; return; }

    arch.seekg(0, ios::end);
    int n = arch.tellg() / sizeof(SesionUso);
    if (n == 0) { cout << "No hay sesiones.\n"; return; }

    int* codigos = new int[totalEquipos];
    int* horas   = new int[totalEquipos];

    for (int* p = codigos; p < codigos + totalEquipos; p++) *p = 0;
    for (int* p = horas;   p < horas   + totalEquipos; p++) *p = 0;

    int*    pCod = codigos;
    Equipo* pE   = equipos;
    while (pE < equipos + totalEquipos) { *pCod = pE->codigo; pCod++; pE++; }

    for (int i = 0; i < n; i++) {
        SesionUso s;
        arch.seekg(i * sizeof(SesionUso));
        arch.read((char*)&s, sizeof(SesionUso));

        int* pc = codigos;
        int* ph = horas;
        while (pc < codigos + totalEquipos) {
            if (*pc == s.codigoEquipo) {
                *ph += (s.cerrada ? s.duracionReal : s.duracionProgramada);
                break;
            }
            pc++; ph++;
        }
    }
    arch.close();

    // Laboratorios únicos en memoria dinámica
    char** labs = new char*[totalEquipos];
    for (char** p = labs; p < labs + totalEquipos; p++) {
        *p = new char[50];
        (*p)[0] = '\0';
    }
    int nLabs = 0;

    for (Equipo* p = equipos; p < equipos + totalEquipos; p++) {
        bool existe = false;
        for (char** pl = labs; pl < labs + nLabs; pl++)
            if (strcmp(*pl, p->laboratorio) == 0) { existe = true; break; }
        if (!existe) { strcpy(*(labs + nLabs), p->laboratorio); nLabs++; }
    }

    cout << "\n===== Informe de uso intensivo =====\n";
    for (char** pl = labs; pl < labs + nLabs; pl++) {
        int     maxHoras = -1;
        Equipo* mejor    = NULL;

        Equipo* pe = equipos;
        int*    ph = horas;
        while (pe < equipos + totalEquipos) {
            if (strcmp(pe->laboratorio, *pl) == 0 && *ph > maxHoras) {
                maxHoras = *ph;
                mejor    = pe;
            }
            pe++; ph++;
        }

        if (mejor && maxHoras > 0)
            cout << "-- " << *pl << ": " << mejor->nombre << " (" << maxHoras << " horas)\n";
        else
            cout << "-- " << *pl << ": sin uso registrado\n";
    }
    cout << "\n";

    for (char** p = labs; p < labs + totalEquipos; p++) delete[] *p;
    delete[] labs;
    delete[] codigos;
    delete[] horas;
}

// ==================== OPCIÓN 7: RANKING USUARIOS CRÍTICOS ====================

void rankingUsuariosCriticos(Usuario* usuarios, int totalUsuarios) {
    if (!usuarios) { cout << "Primero cargue los usuarios.\n"; return; }

    ifstream arch("sesiones.dat", ios::binary);
    if (!arch) { cout << "No hay sesiones registradas.\n"; return; }

    arch.seekg(0, ios::end);
    int n = arch.tellg() / sizeof(SesionUso);
    if (n == 0) { cout << "No hay sesiones.\n"; return; }

    float* penAcum   = new float[totalUsuarios];
    int*   nSesiones = new int[totalUsuarios];
    float* indice    = new float[totalUsuarios];
    bool*  usado     = new bool[totalUsuarios];

    for (float* p = penAcum;   p < penAcum   + totalUsuarios; p++) *p = 0;
    for (int*   p = nSesiones; p < nSesiones + totalUsuarios; p++) *p = 0;
    for (bool*  p = usado;     p < usado     + totalUsuarios; p++) *p = false;

    for (int i = 0; i < n; i++) {
        SesionUso s;
        arch.seekg(i * sizeof(SesionUso));
        arch.read((char*)&s, sizeof(SesionUso));

        Usuario* pu = usuarios;
        float*   pp = penAcum;
        int*     ps = nSesiones;
        while (pu < usuarios + totalUsuarios) {
            if (pu->codigo == s.codigoUsuario) { *pp += s.penalizacion; (*ps)++; break; }
            pu++; pp++; ps++;
        }
    }
    arch.close();

    float* pi = indice;
    float* pp = penAcum;
    int*   ps = nSesiones;
    while (pi < indice + totalUsuarios) {
        *pi = (*ps > 0) ? (*pp / *ps) : 0;
        pi++; pp++; ps++;
    }

    cout << "\n===== Ranking de usuarios criticos (top 3) =====\n";
    for (int lugar = 1; lugar <= 3; lugar++) {
        float  maxIdx = -1;
        float* pMejor = NULL;

        float* pIdx   = indice;
        bool*  pUsado = usado;
        while (pIdx < indice + totalUsuarios) {
            if (!*pUsado && *pIdx > maxIdx) { maxIdx = *pIdx; pMejor = pIdx; }
            pIdx++; pUsado++;
        }

        if (pMejor != NULL && maxIdx > 0) {
            int      offset = pMejor - indice;
            Usuario* u      = usuarios + offset;
            cout << lugar << ". " << u->nombre
                 << " | Sesiones: "                << *(nSesiones + offset)
                 << " | Penalizacion acumulada: $" << *(penAcum   + offset)
                 << " | Indice: "                  << maxIdx << "\n";
            *(usado + offset) = true;
        }
    }
    cout << "\n";

    delete[] penAcum;
    delete[] nSesiones;
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
        cout << "\n========= SISTEMA DE LABORATORIO =========\n";
        cout << "1. Cargar equipos desde archivo\n";
        cout << "2. Cargar usuarios desde archivo\n";
        cout << "3. Consultar estado del laboratorio\n";
        cout << "4. Programar sesion de uso\n";
        cout << "5. Registrar cierre de sesion\n";
        cout << "6. Informe de uso intensivo de equipos\n";
        cout << "7. Ranking de usuarios criticos\n";
        cout << "8. Salir\n";
        cout << "Opcion: ";
        cin >> op;
        cin.ignore();

        char nom[100];

        switch (op) {
            case 1:
                cout << "Nombre del archivo de equipos: ";
                cin.getline(nom, 100);
                if (equipos) delete[] equipos;
                equipos = cargaEquipos(nom, totalEquipos);
                break;
            case 2:
                cout << "Nombre del archivo de usuarios: ";
                cin.getline(nom, 100);
                if (usuarios) delete[] usuarios;
                usuarios = cargaUsuarios(nom, totalUsuarios);
                break;
            case 3:  consultarLaboratorio(equipos, totalEquipos);                        break;
            case 4:  programarSesion(equipos, totalEquipos, usuarios, totalUsuarios);    break;
            case 5:  cerrarSesion(equipos, totalEquipos);                                break;
            case 6:  informeUsoIntensivo(equipos, totalEquipos);                         break;
            case 7:  rankingUsuariosCriticos(usuarios, totalUsuarios);                   break;
            case 8:  cout << "Saliendo...\n"; break;
            default: cout << "Opcion invalida.\n";
        }

    } while (op != 8);

    delete[] equipos;
    delete[] usuarios;
    return 0;
}
