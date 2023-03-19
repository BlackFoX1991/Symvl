#ifndef PARSER_H
#define PARSER_H

#include "SyntaxTree.h"
#include <memory>

namespace symvl
{
    class Lexer;
    class State;

    std::unique_ptr<SyntaxTree> Parse(Lexer *lexer);
} // namespace symvl

#endif // PARSER_H
