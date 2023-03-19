#include "Runtime.h"

namespace symvl
{
    Stack::Stack()
        : stack_(kBaseStackSize),
          top_(nullptr)
    {
        top_ = &stack_[0];
    }

    void Stack::SetNewTop(Value *top)
    {
        Value *old = top_;
        top_ = top;

        // Clear values between new top to old
        for (; top <= old; ++top)
            top->SetNil();
    }

    CallInfo::CallInfo()
        : register_(nullptr),
          func_(nullptr),
          instruction_(nullptr),
          end_(nullptr),
          expect_result_(0)
    {
    }
} // namespace symvl
