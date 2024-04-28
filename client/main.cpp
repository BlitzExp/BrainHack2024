#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include "variable.h"

using namespace std;

std::string mensaje;

int main()
{   
    char mensaje;
    FILE *fp;
    char output[1024];
    
    // Abrir un pipe para leer la salida del script
    fp = popen("all.bat", "r");
    if (fp == NULL) {
        std::cerr << "Error al abrir el pipe para el script" << std::endl;
        return -1;
    }
    // Leer la salida del script línea por línea
    for (int i=0; i<4; i++) {
        // Mostrar el mensaje leído
        fgets(output, sizeof(output), fp) != NULL ;
    }
    cout<<"uwu";
    // Cerrar el pipe
    

    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        fgets(output, sizeof(output), fp) != NULL;
        std::cout<< output << std::endl;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
    pclose(fp);
    return 0;
}