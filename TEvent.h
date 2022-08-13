#pragma once

#include "EPropagation.h"
#include "TFunction.h"
#include "FAssert.h"

#include <vector>

namespace t3d
{
    template<typename T>
    class TEvent
    {
    private:

    // Constructors and Destructor:

         TEvent () = default;
        ~TEvent () = default;

        T3D_NO_COPY(TEvent);
        T3D_NO_MOVE(TEvent);

        friend struct FEvent;

    public:

    // Aliases:

        using Delegate_T = TFunction<EPropagation(T)>;

        template<class C>
        using CallbackMember_T = EPropagation(C::*)(T);

        using CallbackStatic_T = EPropagation(*)(T);

    // Functions:

        template<class C>
        void Subscribe(C* Instance, CallbackMember_T<C> Callback)
        {
            T3D_ASSERT(this->IsSubscribed(Callback) == false, "This callback is already subscribed for that event!");

            Delegates.push_back(Delegate_T(Instance, Callback));
        }

        void Subscribe(CallbackStatic_T Callback)
        {
            T3D_ASSERT(this->IsSubscribed(Callback) == false, "This callback is already subscribed for that event!");

            Delegates.push_back(Delegate_T(Callback));
        }

        template<class C>
        void Unsubscribe(CallbackMember_T<C> Callback)
        {
            T3D_ASSERT(this->IsSubscribed(Callback), "This callback is not subscribed for that event!");

            for (uint64 i = 0u; i < Delegates.size(); ++i)
            {
                if (Delegates[i].Contains(Callback))
                {
                    Delegates.erase(Delegates.begin() + i);

                    return;
                }
            }
        }

        void Unsubscribe(CallbackStatic_T Callback)
        {
            T3D_ASSERT(this->IsSubscribed(Callback), "This callback is not subscribed for that event!");

            for (uint64 i = 0u; i < Delegates.size(); ++i)
            {
                if (Delegates[i].Contains(Callback))
                {
                    Delegates.erase(Delegates.begin() + i);

                    return;
                }
            }
        }

        template<class C>
        bool8 IsSubscribed(CallbackMember_T<C> Callback) const
        {
            for (auto& Delegate : Delegates)
            {
                if (Delegate.Contains(Callback))
                {
                    return true;
                }
            }

            return false;
        }

        bool8 IsSubscribed(CallbackStatic_T Callback) const
        {
            for (auto& Delegate : Delegates)
            {
                if (Delegate.Contains(Callback))
                {
                    return true;
                }
            }

            return false;
        }

        void Invoke(T Data) const
        {
            for (auto& Delegate : Delegates)
            {
                if (Delegate.Invoke(Data) == EPropagation::Stop)
                {
                    return;
                }
            }
        }

    private:

    // Variables:

        std::vector<Delegate_T> Delegates;
    };
}
