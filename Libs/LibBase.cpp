#include "../Libs/LibBase.h"
#include "../Types/Table.h"
#include "../VM/Upvalue.h"
#include "../VM/State.h"
#include "../Types/String.h"
#include <string>
#include <iostream>
#include <assert.h>
#include <stdio.h>

namespace lib {
namespace base {

    int Print(symvl::State *state)
    {
        symvl::StackAPI api(state);
        int params = api.GetStackSize();

        for (int i = 0; i < params; ++i)
        {
            symvl::ValueT type = api.GetValueType(i);

            switch (type) {
                case symvl::ValueT_Nil:
                    printf("nil");
                    break;
                case symvl::ValueT_Bool:
                    printf("%s", api.GetBool(i) ? "true" : "false");
                    break;
                case symvl::ValueT_Number:
                    printf("%.14g", api.GetNumber(i));
                    break;
                case symvl::ValueT_String:
                    printf("%s", api.GetCString(i));
                    break;
                case symvl::ValueT_Closure:
                    printf("function:\t%p", api.GetClosure(i));
                    break;
                case symvl::ValueT_Table:
                    printf("table:\t%p", api.GetTable(i));
                    break;
                case symvl::ValueT_UserData:
                    printf("userdata:\t%p", api.GetUserData(i));
                    break;
                case symvl::ValueT_CFunction:
                    printf("function:\t%p", api.GetCFunction(i));
                    break;
                default:
                    break;
            }

            if (i != params - 1)
                printf("\t");
        }

        printf("\n");
        return 0;
    }

    int Puts(symvl::State *state)
    {
        symvl::StackAPI api(state);
        if (!api.CheckArgs(1, symvl::ValueT_String))
            return 0;

        printf("%s", api.GetCString(0));
        return 0;
    }
    int Clears(symvl::State *state)
    {
        system("clear");
        system("cls");
        return 0;
    }

    int Type(symvl::State *state)
    {
        symvl::StackAPI api(state);
        if (!api.CheckArgs(1))
            return 0;

        const symvl::Value *v = api.GetValue(0);
        symvl::ValueT type = v->type_ == symvl::ValueT_Upvalue ?
            v->upvalue_->GetValue()->type_ : v->type_;

        switch (type) {
            case symvl::ValueT_Nil:
                api.PushString("nil");
                break;
            case symvl::ValueT_Bool:
                api.PushString("boolean");
                break;
            case symvl::ValueT_Number:
                api.PushString("number");
                break;
            case symvl::ValueT_String:
                api.PushString("string");
                break;
            case symvl::ValueT_Table:
                api.PushString("table");
                break;
            case symvl::ValueT_UserData:
                api.PushString("userdata");
                break;
            case symvl::ValueT_Closure:
            case symvl::ValueT_CFunction:
                api.PushString("function");
                break;
            default:
                assert(0);
                return 0;
        }
        return 1;
    }

    int DoIPairs(symvl::State *state)
    {
        symvl::StackAPI api(state);
        if (!api.CheckArgs(2, symvl::ValueT_Table, symvl::ValueT_Number))
            return 0;

        symvl::Table *t = api.GetTable(0);
        double num = api.GetNumber(1) + 1;

        symvl::Value k;
        k.type_ = symvl::ValueT_Number;
        k.num_ = num;
        symvl::Value v = t->GetValue(k);

        if (v.type_ == symvl::ValueT_Nil)
            return 0;

        api.PushValue(k);
        api.PushValue(v);
        return 2;
    }

    int IPairs(symvl::State *state)
    {
        symvl::StackAPI api(state);
        if (!api.CheckArgs(1, symvl::ValueT_Table))
            return 0;

        symvl::Table *t = api.GetTable(0);
        api.PushCFunction(DoIPairs);
        api.PushTable(t);
        api.PushNumber(0);
        return 3;
    }

    int DoPairs(symvl::State *state)
    {
        symvl::StackAPI api(state);
        if (!api.CheckArgs(2, symvl::ValueT_Table))
            return 0;

        symvl::Table *t = api.GetTable(0);
        symvl::Value *last_key = api.GetValue(1);

        symvl::Value key;
        symvl::Value value;
        if (last_key->type_ == symvl::ValueT_Nil)
            t->FirstKeyValue(key, value);
        else
            t->NextKeyValue(*last_key, key, value);

        api.PushValue(key);
        api.PushValue(value);
        return 2;
    }

    int Pairs(symvl::State *state)
    {
        symvl::StackAPI api(state);
        if (!api.CheckArgs(1, symvl::ValueT_Table))
            return 0;

        symvl::Table *t = api.GetTable(0);
        api.PushCFunction(DoPairs);
        api.PushTable(t);
        api.PushNil();
        return 3;
    }

    int GetLine(symvl::State *state)
    {
        symvl::StackAPI api(state);
        std::string line;
        std::getline(std::cin, line);
        api.PushString(line.c_str());
        return 1;
    }

    int Require(symvl::State *state)
    {
        symvl::StackAPI api(state);
        if (!api.CheckArgs(1, symvl::ValueT_String))
            return 0;

        auto module = api.GetString(0)->GetStdString();
        if (!state->IsModuleLoaded(module))
            state->DoModule(module);

        return 0;
    }

    void RegisterLibBase(symvl::State *state)
    {
        symvl::Library lib(state);
        lib.RegisterFunc("print", Print);
        lib.RegisterFunc("puts", Puts);
        lib.RegisterFunc("clear",Clears);
        lib.RegisterFunc("ipairs", IPairs);
        lib.RegisterFunc("pairs", Pairs);
        lib.RegisterFunc("type", Type);
        lib.RegisterFunc("getline", GetLine);
        lib.RegisterFunc("require", Require);
    }

} // namespace base
} // namespace lib
