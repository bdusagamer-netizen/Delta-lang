#include <iostream>
#include <fstream>
#include <sstream>

#include "./lexer/lexer.hpp"
#include "./parser/parser.hpp"
#include "./runtime/environment.hpp"
#include "./runtime/cli_object.hpp"
#include "./runtime/math_object.hpp"
#include "./interpreter/interpreter.hpp"

int main(int argc, char** argv) {
    using namespace delta;

    if (argc < 2) {
        std::cout << "Usage: delta <file>\n";
        return 1;
    }

    // Read file
    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "Could not open file: " << argv[1] << "\n";
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string source = buffer.str();

    // Lex
    Lexer lexer(source);
    std::vector<Token> tokens = lexer.tokenize();

    // Parse
    Parser parser(tokens);
    ExprPtr expr = parser.parse();

    // Runtime objects
    Environment env;
    CLIObject cli;
    MathObject math;

    Interpreter interpreter(env, cli, math);

    // Execute
    interpreter.execute(expr);

    return 0;
}