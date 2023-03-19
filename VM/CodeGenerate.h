#ifndef CODE_GENERATE_H
#define CODE_GENERATE_H

#include "../Parser/Visitor.h"
#include <memory>

namespace symvl
{
    class State;

    void CodeGenerate(SyntaxTree *root, State *state);
} // namespace symvl

#endif // CODE_GENERATE_H
