
#pragma once

template <typename FunctionType>
struct OnScopeExit
{
    OnScopeExit(FunctionType&& function) : Function(std::move(function)) {}
    OnScopeExit(FunctionType const& function) : Function(function) {}

    ~OnScopeExit()
    {
        Function();
    }

private:
    FunctionType Function;
};

struct MakeOnScopeExit
{
    template <typename FunctionType>
    friend OnScopeExit<FunctionType> operator | (MakeOnScopeExit&&, FunctionType&& function)
    {
        return OnScopeExit<FunctionType>(std::forward<FunctionType>(function));
    }
};

#define JOIN_TOKENS(a, b) a##b
#define ON_SCOPE_EXIT auto JOIN_TOKENS(__LINE__, _scopeVar) = MakeOnScopeExit{} | [&]