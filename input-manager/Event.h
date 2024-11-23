#pragma once

#include <vector>
#include <memory>
#include <algorithm>

#include "function.h"

namespace tlr
{

template<typename... Args>
class Event
{
public:
    void RegisterCallback(void (*pMethod)(Args...))
    {
        _pCallbacks.push_back(std::make_unique<Function<void (*)(Args...)> >(pMethod));
    }

    void UnregisterCallback(void (*pMethod)(Args...))
    {
        Function<void (*)(Args...)> pCallback(pMethod);
        EraseCallback(&pCallback);
    }

    template<typename C>
    void RegisterCallback(C* object, void (C::*pMemberMethod)(Args...))
    {
        _pCallbacks.push_back(std::make_unique<Function<void (C::*)(Args...)> >(object, pMemberMethod));
    }

    template<typename C>
    void UnregisterCallback(C* object, void (C::*pMemberMethod)(Args...))
    {
        Function<void (C::*)(Args...)> pCallback(object, pMemberMethod);
        EraseCallback(&pCallback);
    }

    void Raise(Args... args) const
    {
        for (auto const& pCallback : _pCallbacks)
        {
            pCallback->Call(std::forward<Args>(args)...);
        }
    }

private:
    std::vector<std::unique_ptr<IFunction<void, Args...>>> _pCallbacks;

    void EraseCallback(IFunction<void, Args...> const* pCallbackToDelete)
    {
        auto it = std::find_if(_pCallbacks.cbegin(), _pCallbacks.cend(),
        [&pCallbackToDelete](auto const& pCallback)
        {
            return pCallback->Equals(*pCallbackToDelete);
        });
        if (it != _pCallbacks.cend())
        {
            _pCallbacks.erase(it);
        }
    }
};

} // namespace tlr
