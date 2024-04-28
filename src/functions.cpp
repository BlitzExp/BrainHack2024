#ifndef functions
#define functions

#include <cmath>
#include <iostream>
#include "../include/structure.hpp"

double distance_from(double p1x, double p1y, double p2x = 0, double p2y = 0){
    return sqrt((p2x - p1x) * (p2x - p1x) + (p2y - p1y) * (p2y - p1y));
}

double calcularVelocidadDespuesColision(pendulum& objeto1, pendulum& objeto2, double m1, double m2) {
    // Suponiendo que la colisión es perfectamente elástica
    double obj1_spd = (objeto1.get_spdx() + objeto1.get_angular_speed());
    double obj2_spd = (objeto2.get_spdx() + objeto2.get_angular_speed());
    double vFinal1 = ((m1 - m2) * obj1_spd + 2 * m2 * obj2_spd) / (m1 + m2);
    double vFinal2 = ((m2 - m1) * obj2_spd + 2 * m1 * obj1_spd) / (m1 + m2);

    return std::max(abs(vFinal1), abs(vFinal2)); // Velocidad de colisión (tomamos el valor absoluto máximo)
}

#endif