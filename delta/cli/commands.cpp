#include "commands.hpp"
#include <iostream>
#include <fstream>

#include "../lexer/lexer.hpp"
#include "../parser/parser.hpp"
#include "../interpreter/interpreter.hpp"
#include "../runtime/environment.hpp"

namespace delta::cli {

int run(int argc, char** argv) {
    if (argc < 2) {
        printHelp();
        return 0;
    }

    std::string cmd = argv[1];

    if (cmd == "run") {
        if (argc < 3) {
            std::cerr << "Missing file path for 'run' command\n";
            return 1;
        }
        return executeFile(argv[2]);
    }

    if (cmd == "repl") {
        return executeRepl();
    }

    if (cmd == "tokens") {
        if (argc < 3) {
            std::cerr << "Missing file path for 'tokens' command\n";
            return 1;
        }
        return executeTokens(argv[2]);
    }

    if (cmd == "ast") {
        if (argc < 3) {
            std::cerr << "Missing file path for 'ast' command\n";
            return 1;
        }
        return executeAst(argv[2]);
    }

    printHelp();
    return 0;
}

void printHelp() {
    std::cout << "Delta Language CLI\n";
    std::cout << "Usage:\n";
    std::cout << "  delta run <file.delta>\n";
    std::cout << "  delta repl\n";
    std::cout << "  delta tokens <file.delta>\n";
    std::cout << "  delta ast <file.delta>\n";
}

int executeFile(const std::string& path) {
    std::ifstream in(path);
    if (!in.is_open()) {
        std::cerr << "Could not open file: " << path << "\n";
        return 1;
    }

    std::string source((std::istreambuf_iterator<char>(in)),
                       std::istreambuf_iterator<char>());

    delta::Lexer lexer(source);
    auto tokens = lexer.tokenize();

    delta::Parser parser(tokens);
    auto expr = parser.parse();

    delta::Environment env;
    delta::Interpreter interpreter(env);

    interpreter.execute(expr);

    return 0;
}

int executeRepl() {
    std::cout << "Delta REPL\n";
    std::cout << "Type 'exit' to quit\n";

    delta::Environment env;
    delta::Interpreter interpreter(env);

    while (true) {
        std::cout << ">>> ";
        std::string line;
        std::getline(std::cin, line);

        if (line == "exit") break;

        delta::Lexer lexer(line);
        auto tokens = lexer.tokenize();

        delta::Parser parser(tokens);
        auto expr = parser.parse();

        interpreter.execute(expr);
    }

    return 0;
}

int executeTokens(const std::string& path) {
    std::ifstream in(path);
    if (!in.is_open()) {
        std::cerr << "Could not open file: " << path << "\n";
        return 1;
    }

    std::string source((std::istreambuf_iterator<char>(in)),
                       std::istreambuf_iterator<char>());

    delta::Lexer lexer(source);
    auto tokens = lexer.tokenize();

    for (auto& t : tokens) {
        std::cout << t.toString() << "\n";
    }

    return 0;
}

int executeAst(const std::string& path) {
    std::ifstream in(path);
    if (!in.is_open()) {
        std::cerr << "Could not open file: " << path << "\n";
        return 1;
    }

    std::string source((std::istreambuf_iterator<char>(in)),
                       std::istreambuf_iterator<char>());

    delta::Lexer lexer(source);
    auto tokens = lexer.tokenize();

    delta::Parser parser(tokens);
    auto expr = parser.parse();

    std::cout << expr->toString() << "\n";

    return 0;
}

} // namespace delta::cli