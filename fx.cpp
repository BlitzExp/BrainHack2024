#include <iostream>
#include <string>

using namespace std;

// Clase para representar un sprite
class Sprite {
private:
    string nombre;
    // Otros atributos de un sprite
public:
    Sprite(const string& nombre) : nombre(nombre) {}
    
    // Métodos para manipular el sprite
    void dibujar() {
        // Código para dibujar el sprite
        cout << "Dibujando sprite '" << nombre << "'" << endl;
    }
};

// Clase base para representar un objeto genérico
class Objeto {
protected:
    int x;
    int y;
    Sprite sprite;
public:
    Objeto(int x, int y, const string& nombreSprite) : x(x), y(y), sprite(nombreSprite) {}
    
    void dibujar() {
        // Dibujar el sprite en las coordenadas (x, y)
        sprite.dibujar();
        cout << " en (" << x << ", " << y << ")" << endl;
    }
};

// Clase derivada que hereda de Objeto
class SubObjeto : public Objeto {
private:
    double gravedad;
public:
    SubObjeto(int x, int y, const string& nombreSprite, double gravedad) : Objeto(x, y, nombreSprite), gravedad(gravedad) {}
    
    void aplicarGravedad() {
        y += gravedad; // Aplicar gravedad a la coordenada y
    }
};

int main() {
    // Crear un subobjeto con gravedad
    SubObjeto subobjeto(100, 100, "SubObjetoSprite", 9.8); // Suponiendo una gravedad de 9.8 m/s^2
    
    // Manipular el subobjeto
    subobjeto.dibujar();
    subobjeto.aplicarGravedad();
    subobjeto.dibujar();
    
    return 0;
}