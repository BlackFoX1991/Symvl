#include "VM/State.h"
#include "S_Exception/Exception.h"
#include "Libs/LibBase.h"
#include "Libs/LibIO.h"
#include "Libs/LibMath.h"
#include "Libs/LibString.h"
#include "Libs/LibTable.h"
#include <stdio.h>

void Repl(symvl::State &state)
{
    printf("Symvl Scripting Language (c) 2023 Artur Loewen\n");

    for (;;)
    {
        try
        {
            printf(">> ");

            char s[1024] = { 0 };
            auto input = fgets(s, sizeof(s), stdin);
            if (!input)
                break;
            state.DoString(input, "stdin");
        }
        catch (const symvl::Exception &exp)
        {
            printf("%s\n", exp.What().c_str());
        }
    }
}

void ExecuteFile(const char **argv, symvl::State &state)
{
    try
    {
        state.DoModule(argv[1]);
    }
    catch (const symvl::OpenFileFail &exp)
    {
        printf("%s: can not open file %s\n", argv[0], exp.What().c_str());
    }
    catch (const symvl::Exception &exp)
    {
        printf("%s\n", exp.What().c_str());
    }
}

int main(int argc, const char **argv)
{
    symvl::State state;

    lib::base::RegisterLibBase(&state);
    lib::io::RegisterLibIO(&state);
    lib::math::RegisterLibMath(&state);
    lib::string::RegisterLibString(&state);
    lib::table::RegisterLibTable(&state);

    if (argc < 2)
    {
        Repl(state);
    }
    else
    {
        ExecuteFile(argv, state);
    }

    return 0;
}
