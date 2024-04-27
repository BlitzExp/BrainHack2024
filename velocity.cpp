#include <iostream>
#include <cmath>

using namespace std;

struct Objeto {
    double masa;
    double velocidad;
};

double calcularVelocidadDespuesColision(const Objeto& objeto1, const Objeto& objeto2) {
    // Suponiendo que la colisión es perfectamente elástica
    double vFinal1 = ((objeto1.masa - objeto2.masa) * objeto1.velocidad + 2 * objeto2.masa * objeto2.velocidad) / (objeto1.masa + objeto2.masa);
    double vFinal2 = ((objeto2.masa - objeto1.masa) * objeto2.velocidad + 2 * objeto1.masa * objeto1.velocidad) / (objeto1.masa + objeto2.masa);
    
    return max(abs(vFinal1), abs(vFinal2)); // Velocidad de colisión (tomamos el valor absoluto máximo)
}

int main() {
    Objeto objeto1, objeto2;
    
    // Solicitar datos del usuario
    cout << "Ingrese la masa del objeto 1: ";
    cin >> objeto1.masa;
    cout << "Ingrese la velocidad del objeto 1: ";
    cin >> objeto1.velocidad;
    cout << "Ingrese la masa del objeto 2: ";
    cin >> objeto2.masa;
    cout << "Ingrese la velocidad del objeto 2: ";
    cin >> objeto2.velocidad;
    
    // Calcular velocidad de colisión
    double velocidadColision = calcularVelocidadDespuesColision(objeto1, objeto2);
    
    cout << "La velocidad de la colision es: " << velocidadColision << endl;
    
    return 0;
}