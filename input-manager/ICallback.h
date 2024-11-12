#pragma once

namespace tlr
{

template<typename... Args>
class ICallback
{
public:
    virtual ~ICallback() = default;

    virtual void Call() = 0;

    virtual bool Equals(ICallback const& other) const = 0;
};

} // namespace tlr