#pragma once

namespace tlr
{

template<typename R, typename... Args>
class IFunction
{
public:
    virtual ~IFunction() = default;

    virtual R Call(Args... args) = 0;

    virtual bool Equals(IFunction const& other) const = 0;
};

} // namespace tlr
