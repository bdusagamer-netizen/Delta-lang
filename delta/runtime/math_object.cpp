#include "math_object.hpp"
#include <cmath>
#include <cstdlib>

namespace delta {

double MathObject::sin(double x) const {
    return std::sin(x);
}

double MathObject::cos(double x) const {
    return std::cos(x);
}

double MathObject::tan(double x) const {
    return std::tan(x);
}

double MathObject::sqrt(double x) const {
    return std::sqrt(x);
}

double MathObject::pow(double base, double exp) const {
    return std::pow(base, exp);
}

double MathObject::randomFloat() const {
    return (double)std::rand() / RAND_MAX;
}

int MathObject::randomInt(int a, int b) const {
    return a + (std::rand() % (b - a + 1));
}

} // namespace delta