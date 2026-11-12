#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;

class Estudiante {
private:
    string nombre;
    int anioNacimiento;
    double gpa;
    double presupuesto;

public:
    // Constructor por defecto: inicializa en ("NN", 0, 0, 0)
    Estudiante() : nombre("NN"), anioNacimiento(0), gpa(0.0), presupuesto(0.0) {}

    // Constructor parametrizado con datos personalizados
    Estudiante(string nom, int anio, double prom, double pres)
        : nombre(nom), anioNacimiento(anio), gpa(prom), presupuesto(pres) {}

    string getNombre() const { return nombre; }
    int getAnio() const { return anioNacimiento; }
    double getGpa() const { return gpa; }
    double getPresupuesto() const { return presupuesto; }

    // Formula solicitada: Abs(GPA - 3) * (Presupuesto)
    double obtenerIndiceUniversidad() const {
        return fabs(gpa - 3.0) * presupuesto;
    }

    void modificarDatos(const string& nom, int anio, double prom, double pres) {
        nombre = nom;
        anioNacimiento = anio;
        gpa = prom;
        presupuesto = pres;
    }
};

// Comparadores booleanos independientes para std::sort
bool compararPorAnio(const Estudiante& a, const Estudiante& b) {
    return a.getAnio() < b.getAnio();
}

bool compararPorGpa(const Estudiante& a, const Estudiante& b) {
    return a.getGpa() < b.getGpa();
}

bool compararPorPresupuesto(const Estudiante& a, const Estudiante& b) {
    return a.getPresupuesto() < b.getPresupuesto();
}

bool compararPorIndiceUniv(const Estudiante& a, const Estudiante& b) {
    return a.obtenerIndiceUniversidad() < b.obtenerIndiceUniversidad();
}

// Funciones modulares que operan sobre el contenedor std::vector<Estudiante>
void mostrarColeccion(const vector<Estudiante>& estudiantes) {
    if (estudiantes.empty()) {
        cout << "  [!] La coleccion 'estudiantes' se encuentra vacia.\n";
        return;
    }

    cout << "\n  " << left << setw(6) << "POS"
         << setw(14) << "NOMBRE"
         << setw(8) << "ANIO"
         << setw(8) << "GPA"
         << setw(14) << "PRESUPUESTO"
         << "INDICE UNIV.\n";
    cout << "  --------------------------------------------------------------\n";

    int pos = 0;
    for (vector<Estudiante>::const_iterator it = estudiantes.begin(); it != estudiantes.end(); ++it, ++pos) {
        cout << "  [" << pos << "]   "
             << left << setw(14) << it->getNombre()
             << setw(8) << it->getAnio()
             << fixed << setprecision(2) << setw(8) << it->getGpa()
             << setw(14) << it->getPresupuesto()
             << it->obtenerIndiceUniversidad() << "\n";
    }
    cout << "  --------------------------------------------------------------\n";
}

void ejecutarInsercion(vector<Estudiante>& estudiantes) {
    int modalidad = 0, destino = 0;
    cout << "  Modalidad (1 = Por defecto [NN,0,0,0] | 2 = Con datos): ";
    cin >> modalidad;

    Estudiante reg;
    if (modalidad == 2) {
        string nom;
        int anio;
        double prom, pres;
        cout << "  Digite Nombre, Anio, GPA y Presupuesto: ";
        cin >> nom >> anio >> prom >> pres;
        reg = Estudiante(nom, anio, prom, pres);
    }

    cout << "  Posicion a insertar (1 = Al final | 2 = En indice especifico): ";
    cin >> destino;

    if (destino == 1) {
        estudiantes.push_back(reg);
        cout << "  [OK] Estudiante agregado al final del vector.\n";
    } else if (destino == 2) {
        int indice = 0;
        cout << "  Indice destino (0 a " << estudiantes.size() << "): ";
        cin >> indice;
        if (indice >= 0 && indice <= (int)estudiantes.size()) {
            estudiantes.insert(estudiantes.begin() + indice, reg);
            cout << "  [OK] Estudiante insertado en el indice " << indice << ".\n";
        } else {
            cout << "  [ERROR] Indice invalido para insercion.\n";
        }
    }
}

void ejecutarEliminacion(vector<Estudiante>& estudiantes) {
    if (estudiantes.empty()) {
        cout << "  [ERROR] Operacion rechazada: el vector 'estudiantes' esta vacio.\n";
        return;
    }

    int criterio = 0;
    cout << "  Metodo de borrado (1 = El ultimo | 2 = Desde un indice): ";
    cin >> criterio;

    if (criterio == 1) {
        estudiantes.pop_back();
        cout << "  [OK] Se elimino el ultimo elemento del vector.\n";
    } else if (criterio == 2) {
        int indice = 0;
        cout << "  Indice a borrar (0 a " << (int)estudiantes.size() - 1 << "): ";
        cin >> indice;
        if (indice >= 0 && indice < (int)estudiantes.size()) {
            estudiantes.erase(estudiantes.begin() + indice);
            cout << "  [OK] Elemento en el indice " << indice << " eliminado.\n";
        } else {
            cout << "  [ERROR] Indice fuera de los limites.\n";
        }
    }
}

void ejecutarActualizacion(vector<Estudiante>& estudiantes) {
    if (estudiantes.empty()) {
        cout << "  [ERROR] Vector vacio: no existen estudiantes por modificar.\n";
        return;
    }

    int indice = 0;
    cout << "  Indice del estudiante a modificar (0 a " << (int)estudiantes.size() - 1 << "): ";
    cin >> indice;

    if (indice >= 0 && indice < (int)estudiantes.size()) {
        string nom;
        int anio;
        double prom, pres;
        cout << "  Nuevos valores (Nombre Anio GPA Presupuesto): ";
        cin >> nom >> anio >> prom >> pres;
        estudiantes.at(indice).modificarDatos(nom, anio, prom, pres);
        cout << "  [OK] Registro en el indice " << indice << " actualizado.\n";
    } else {
        cout << "  [ERROR] Indice inexistente.\n";
    }
}

void ejecutarOrdenamiento(vector<Estudiante>& estudiantes) {
    if (estudiantes.empty()) {
        cout << "  [ERROR] Vector vacio: nada que ordenar.\n";
        return;
    }

    int llave = 0;
    cout << "  Criterio ascendente (1=Anio | 2=GPA | 3=Presupuesto | 4=Indice Univ.): ";
    cin >> llave;

    switch (llave) {
        case 1:
            sort(estudiantes.begin(), estudiantes.end(), compararPorAnio);
            cout << "  [OK] Ordenado ascendentemente por Anio de nacimiento.\n";
            break;
        case 2:
            sort(estudiantes.begin(), estudiantes.end(), compararPorGpa);
            cout << "  [OK] Ordenado ascendentemente por GPA.\n";
            break;
        case 3:
            sort(estudiantes.begin(), estudiantes.end(), compararPorPresupuesto);
            cout << "  [OK] Ordenado ascendentemente por Presupuesto.\n";
            break;
        case 4:
            sort(estudiantes.begin(), estudiantes.end(), compararPorIndiceUniv);
            cout << "  [OK] Ordenado ascendentemente por Indice Universidad.\n";
            break;
        default:
            cout << "  [ERROR] Criterio de ordenamiento no reconocido.\n";
            break;
    }
}

int main() {
    vector<Estudiante> estudiantes;
    int op = -1;

    while (op != 0) {
        cout << "\n========== GESTION STL VECTOR: ESTUDIANTES ==========\n";
        cout << "  [1] Ingresar estudiante (Final o Indice)\n";
        cout << "  [2] Eliminar estudiante (Ultimo o Indice)\n";
        cout << "  [3] Actualizar estudiante existente\n";
        cout << "  [4] Ordenar coleccion (Anio, GPA, Presupuesto, Indice)\n";
        cout << "  [5] Imprimir contenido del vector\n";
        cout << "  [0] Salir\n";
        cout << "=====================================================\n";
        cout << "  Opcion: ";
        cin >> op;

        switch (op) {
            case 1: ejecutarInsercion(estudiantes); break;
            case 2: ejecutarEliminacion(estudiantes); break;
            case 3: ejecutarActualizacion(estudiantes); break;
            case 4: ejecutarOrdenamiento(estudiantes); break;
            case 5: mostrarColeccion(estudiantes); break;
            case 0: cout << "  Finalizando ejecucion...\n"; break;
            default: cout << "  [!] Opcion fuera de rango.\n"; break;
        }
    }
    return 0;
}