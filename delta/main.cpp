#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "ast/ast.hpp"
#include "runtime/environment.hpp"
#include "runtime/math_object.hpp"
#include "parser/parser.hpp"

using namespace delta;

static std::string readFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + path);
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: delta <file.delta>\n";
        return 1;
    }

    try {
        std::string source = readFile(argv[1]);

        // Core runtime objects
        Environment env;
        MathObject math(env);

        // Parse the program
        Parser parser(source);
        ExprPtr program = parser.parse();

        // Evaluate the AST
        double result = math.evaluate(program);

        // Print result (optional)
        std::cout << result << "\n";
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << "\n";
        return 1;
    }

    return 0;
}