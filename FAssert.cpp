#include "FAssert.h"

namespace t3d
{
// Functions:

    void FAssert::Assert(const char* ExpressionStr, bool8 Expression, const char* Function, const char* File, uint32 Line, const char* Message) noexcept
    {
        if (Expression == false)
        {
            std::cout << "Assertion failed: " << Message       << "\n"
                      << "Expected:         " << ExpressionStr << "\n"
                      << "Function:         " << Function      << "\n"
                      << "File:             " << File          << "\n"
                      << "Line:             " << Line          << "\n";

            abort();
        }
    }


}
