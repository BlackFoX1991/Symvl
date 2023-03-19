#include "Upvalue.h"

namespace symvl
{
    void Upvalue::Accept(GCObjectVisitor *v)
    {
        if (v->Visit(this))
        {
            value_.Accept(v);
        }
    }
} // namespace symvl
