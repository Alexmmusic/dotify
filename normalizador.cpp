#include "normalizador.h"

using namespace std;

vector<color> coloresProblema;

 color rojo{255,0,0};
 color azul{0,0, 255};
 color verde{0,255,0};

void printRGB(unsigned short R, unsigned short G, unsigned short B, const string& texto) {
    cout << "\x1B[38;2;" << R << ";" << G << ";" << B << "m" << texto << "\x1B[0m";
}



