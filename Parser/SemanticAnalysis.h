#ifndef SEMANTIC_ANALYSIS_H
#define SEMANTIC_ANALYSIS_H

#include "SyntaxTree.h"

namespace symvl
{
    class State;

    void SemanticAnalysis(SyntaxTree *root, State *state);
}

#endif // SEMANTIC_ANALYSIS_H
