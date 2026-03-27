#pragma once
#include <vector>
#include <string>

namespace delta {

class Value;   // forward declaration if you add Value later

class MathObject {
public:
    MathObject() = default;

    // Basic math functions (extend as needed)
    double sin(double x) const;
    double cos(double x) const;
    double tan(double x) const;
    double sqrt(double x) const;
    double pow(double base, double exp) const;

    // Random utilities (optional — implement or remove)
    double randomFloat() const;
    int randomInt(int a, int b) const;

    // If you don't use Value yet, comment this out:
    // Value randomList(const std::vector<Value>& list) const;
};

} // namespace delta