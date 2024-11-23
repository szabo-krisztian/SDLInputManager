#pragma once

#include <utility>

#include "IFunction.h"

namespace tlr
{

template<typename T>
class Function;

template<typename R, typename C, typename... Args>
class Function<R (C::*)(Args...)> final : public IFunction<R, Args...>
{
public:
    Function(C* pObject, R (C::*pMemberFunction)(Args...)) : _pObject(pObject), _pMemberFunction(pMemberFunction) {}
    
    R Call(Args... args) override
    {
        (_pObject->*_pMemberFunction)(std::forward<Args>(args)...);
    }

    bool Equals(IFunction<R, Args...> const& other) const override
    {
        if (auto pOther = dynamic_cast<Function const*>(&other))
        {
            return pOther->_pObject == _pObject && pOther->_pMemberFunction == _pMemberFunction;
        }
        return false;
    }

private:
    C* _pObject;
    R (C::*_pMemberFunction)(Args...);
};

template<typename R, typename... Args>
class Function<R (*)(Args...)> final : public IFunction<R, Args...>
{
public:
    explicit Function(R (*pFunction)(Args...)) : _pFunction(pFunction) {}

    R Call(Args... args) override
    {
        (*_pFunction)(std::forward<Args>(args)...);
    }

    bool Equals(IFunction<R, Args...> const& other) const override
    {
        if (auto pOther = dynamic_cast<Function const*>(&other))
        {
            return pOther->_pFunction == _pFunction;
        }
        return false;
    }

private:
    R (*_pFunction)(Args...);
};

} // namespace tlr
