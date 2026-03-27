#include "commands.hpp"
#include "../lexer/lexer.hpp"
#include "../parser/parser.hpp"
#include "../runtime/environment.hpp"
#include "../runtime/cli_object.hpp"
#include "../runtime/math_object.hpp"
#include "../interpreter/interpreter.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

namespace delta::cli {

static void printHelp() {
    std::cout << "delta <file>\n";
}

static int executeFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Could not open file: " << path << "\n";
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string source = buffer.str();

    delta::Lexer lexer(source);
    auto tokens = lexer.tokenize();

    delta::Parser parser(tokens);
    delta::ExprPtr expr = parser.parse();

    delta::Environment env;
    delta::CLIObject cli;
    delta::MathObject math;
    delta::Interpreter interp(env, cli, math);

    interp.execute(expr);
    return 0;
}

static int executeRepl() {
    delta::Environment env;
    delta::CLIObject cli;
    delta::MathObject math;
    delta::Interpreter interp(env, cli, math);

    std::string line;
    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, line)) break;
        if (line.empty()) continue;

        delta::Lexer lexer(line);
        auto tokens = lexer.tokenize();

        delta::Parser parser(tokens);
        delta::ExprPtr expr = parser.parse();

        interp.execute(expr);
    }
    return 0;
}

int run(int argc, char** argv) {
    if (argc < 2) {
        printHelp();
        return 1;
    }

    std::string arg = argv[1];

    if (arg == "repl") {
        return executeRepl();
    } else {
        return executeFile(arg);
    }
}

} // namespace delta::cli