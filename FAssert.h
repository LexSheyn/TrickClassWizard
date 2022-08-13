#pragma once

#include "TrickAPI.h"
#include "TrickTypes.h"

#include <iostream>

namespace t3d
{
    class FAssert
    {
    public:

        static void T3D_CALL Assert (const char* ExpressionStr, bool8 Expression, const char* Function, const char* File, uint32 Line, const char* Message) noexcept;
    };

#ifdef T3D_DEBUG
    #ifdef T3D_PLATFORM_WINDOWS
        #define T3D_ASSERT(Expression, Message) \
                FAssert::Assert(#Expression, Expression, __FUNCTION__, __FILE__, __LINE__, Message)
    #else
        #define T3D_ASSERT(Expression, Message) \
                FAssert::Assert(#Expression, Expression, __func__, __FILE__, __LINE__, Message)
    #endif
#else
    #define T3D_ASSERT(Expression,Message)
#endif
}
