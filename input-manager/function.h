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
    Function(C* pObject, R (C::*pMemberFunction)(Args...)) : m_pObject(pObject), m_pMemberFunction(pMemberFunction) {}
    
    R Call(Args... args) override
    {
        (m_pObject->*m_pMemberFunction)(std::forward<Args>(args)...);
    }

    bool Equals(IFunction<R, Args...> const& other) const override
    {
        if (auto pOther = dynamic_cast<Function const*>(&other))
        {
            return pOther->m_pObject == m_pObject && pOther->m_pMemberFunction == m_pMemberFunction;
        }
        return false;
    }

private:
    C* m_pObject;
    R (C::*m_pMemberFunction)(Args...);
};

template<typename R, typename... Args>
class Function<R (*)(Args...)> final : public IFunction<R, Args...>
{
public:
    explicit Function(R (*pFunction)(Args...)) : m_pFunction(pFunction) {}

    R Call(Args... args) override
    {
        (*m_pFunction)(std::forward<Args>(args)...);
    }

    bool Equals(IFunction<R, Args...> const& other) const override
    {
        if (auto pOther = dynamic_cast<Function const*>(&other))
        {
            return pOther->m_pFunction == m_pFunction;
        }
        return false;
    }

private:
    R (*m_pFunction)(Args...);
};

} // namespace tlr
