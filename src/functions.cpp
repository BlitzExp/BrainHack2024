#include <cmath>

double distance_from(double p1x, double p1y, double p2x = 0, double p2y = 0){
    return sqrt((p2x - p1x) * (p2x - p1x) + (p2y - p1y) * (p2y - p1y));
}