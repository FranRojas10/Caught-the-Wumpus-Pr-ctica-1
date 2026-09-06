//Francisco Javier Rojas Hnerández
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <ctime>

using namespace std;

const int GRAFO[20][3] = {
    {1, 4, 7},   {0, 2, 9},   {1, 3, 11},  {2, 4, 13},  {0, 3, 5},
    {4, 6, 14},  {5, 7, 16},  {0, 6, 8},   {7, 9, 17},  {1, 8, 10},
    {9, 11, 18}, {2, 10, 12}, {11, 13, 19},{3, 12, 14}, {5, 13, 15},
    {14, 16, 19},{6, 15, 17}, {8, 16, 18}, {10, 17, 19},{12, 15, 18}
};

struct J {
    int ju, wum, h1, h2, m1, m2;
    int fl;
    int cu;
    int prW;
    bool vi, vic;
};

int al(int min, int max) {
    return min + rand() % ((max + 1) - min);
}

void ini(J &j) {
    vector<int> h(20);
    for (int i = 0; i < 20; i++) h[i] = i;
    random_shuffle(h.begin(), h.end());

    j.ju = h[0];
    j.wum = h[1];
    j.h1 = h[2];
    j.h2 = h[3];
    j.m1 = h[4];
    j.m2 = h[5];
    j.vi = true;
    j.vic = false;
}

void movW(J &j) {
    if (al(1, 100) <= j.prW) {
        int op = al(0, 2);
        j.wum = GRAFO[j.wum][op];
        cout << "\n* Escuchas un ruido... ‧l Wumpus se ha movido! *\n";
    }
}

void rev(J &j) {
    if (j.ju == j.wum) {
        cout << "\n\033[1;31m﹒H NO! ‧l Wumpus te ha comido!\033[0m\n";
        j.vi = false;
        return;
    }
    if (j.ju == j.h1 || j.ju == j.h2) {
        cout << "\n\033[1;33m，aaah! ？as caido en un hoyo sin fondo!\033[0m\n";
        if (j.cu > 0) {
            j.cu--;
            cout << "\033[1;33m·or suerte tenias una cuerda extra! Logras salir. (Cuerdas restantes: " << j.cu << ")\033[0m\n";
            j.ju = al(0, 19);
            rev(j);
            return;
        } else {
            j.vi = false;
            return;
        }
    }
    if (j.ju == j.m1 || j.ju == j.m2) {        
        cout << "\n\033[1;35m｜nos murcielagos gigantes te agarran y te sueltan en otra habitacion!\033[0m\n";
        j.ju = al(0, 19);
        rev(j);
        return;
    }
}

void imp(const J &j) {
    cout << "\n------------------------------------------------\n";
    cout << "Estas en la habitacion " << j.ju + 1 << ".\n";
    cout << "Habitaciones conectadas: "
         << GRAFO[j.ju][0] + 1 << ", "
         << GRAFO[j.ju][1] + 1 << ", "
         << GRAFO[j.ju][2] + 1 << "\n";

    for (int i = 0; i < 3; i++) {
        int ad = GRAFO[j.ju][i];
        if (ad == j.wum) cout << "> Hueles algo terrible...\n";
        if (ad == j.h1 || ad == j.h2) cout << "> Sientes una brisa fria...\n";
        if (ad == j.m1 || ad == j.m2) cout << "> Escuchas aleteos en la oscuridad...\n";
    }
    cout << "Balas: " << j.fl << " | Cuerdas (vidas en hoyos): " << j.cu << "\n";
}

int main() {
    srand(time(0));
    J j;

    cout << "==== CAZA AL WUMPUS ====\n";
    cout << "Selecciona la dificultad:\n";
    cout << "1. Facil (5 Balas, 2 cuerdas, Wumpus flojo)\n";
    cout << "2. Normal (3 Balas, 1 cuerda, Wumpus activo)\n";
    cout << "3. Dificil (3 Balas, 0 cuerdas, Wumpus agresivo)\n";
    cout << "Opcion: ";

    int df;
    cin >> df;

    if (df == 1) { j.fl = 5; j.cu = 2; j.prW = 20; }
    else if (df == 2) { j.fl = 3; j.cu = 1; j.prW = 50; }
    else { j.fl = 3; j.cu = 0; j.prW = 80; }

    ini(j);

    while (j.vi && !j.vic) {
        imp(j);
        cout << "\nQue quieres hacer? (1 = Moverse, 2 = Disparar): ";
        int ac;
        cin >> ac;

        cout << "A que habitacion? ";
        int d;
        cin >> d;
        d--;

        bool con = false;
        for (int i = 0; i < 3; i++) {
            if (GRAFO[j.ju][i] == d) con = true;
        }

        if (!con) {
            cout << "\n﹑o puedes hacer eso! Esa habitacion no esta conectada.\n";
            continue;
        }

        if (ac == 1) {
            j.ju = d;
            rev(j);
            if(j.vi && al(1,100) <= 10) movW(j);
        }
        else if (ac == 2) {
            if (d == j.wum) {                
                cout << "\n\033[1;32m、AM! ‥e diste al Wumpus! ？AS GANADO!\033[0m\n";
                j.vic = true;
            } else {
                j.fl--;
                cout << "\nFallaste. Tu bala se perdio en la oscuridad.\n";
                if (j.fl <= 0) {                    
                    cout << "\033[1;31mTe quedaste sin balas... ‧stas indefenso y el Wumpus te atrapa!\033[0m\n";
                    j.vi = false;
                } else {
                    movW(j);
                    if (j.ju == j.wum) {
                        cout << "‧l Wumpus corrio hacia tu habitacion asustado por la bala!\n";
                        rev(j);
                    }
                }
            }
        } else {
            cout << "Opcion invalida.\n";
        }
    }

    cout << "\n--- FIN DEL JUEGO ---\n";
    system("pause");
    return 0;
}
