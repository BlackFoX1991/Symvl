#include "../Types/Value.h"
#include "../Types/Function.h"
#include "Table.h"
#include "String.h"
#include "../VM/Upvalue.h"
#include "../Types/UserData.h"

namespace symvl
{
    void Value::Accept(GCObjectVisitor *v) const
    {
        switch (type_)
        {
            case ValueT_Nil:
            case ValueT_Bool:
            case ValueT_Number:
            case ValueT_CFunction:
                break;
            case ValueT_Obj:
                obj_->Accept(v);
                break;
            case ValueT_String:
                str_->Accept(v);
                break;
            case ValueT_Closure:
                closure_->Accept(v);
                break;
            case ValueT_Upvalue:
                upvalue_->Accept(v);
                break;
            case ValueT_Table:
                table_->Accept(v);
                break;
            case ValueT_UserData:
                user_data_->Accept(v);
                break;
        }
    }

    const char * Value::TypeName() const
    {
        return TypeName(type_);
    }

    const char * Value::TypeName(ValueT type)
    {
        switch (type)
        {
            case ValueT_Nil: return "nil";
            case ValueT_Bool: return "bool";
            case ValueT_Number: return "number";
            case ValueT_CFunction: return "C-Function";
            case ValueT_String: return "string";
            case ValueT_Closure: return "function";
            case ValueT_Upvalue: return "upvalue";
            case ValueT_Table: return "table";
            case ValueT_UserData: return "userdata";
            default: return "unknown type";
        }
    }
} // namespace symvl
