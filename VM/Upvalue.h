#ifndef UPVALUE_H
#define UPVALUE_H

#include "../VM/GC.h"
#include "../Types/Value.h"

namespace symvl
{
    class Upvalue : public GCObject
    {
    public:
        virtual void Accept(GCObjectVisitor *v);

        void SetValue(const Value &value)
        { value_ = value; }

        Value * GetValue()
        { return &value_; }

    private:
        Value value_;
    };
} // namespace symvl

#endif // UPVALUE_H
