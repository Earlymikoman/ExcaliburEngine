/*********************************************************************
 * @file   MultiField.h
 * @brief  .
 * 
 * Project: Excalibur
 * 
 * @author Xander Boosinger (xboosinger@gmail.com), with help from ChatGPT.
 * @date   April 2025
 * 
 *********************************************************************
/*
 *			*	/\
 *			   / /	*
 *		*	__/ /__
 *		      /	  *
 *			 /
 */

#pragma once

#include <string>
#include <iostream>

using std::cout;
using std::endl;

#pragma region Named

template <typename T>
concept Named = requires(T a)
{
    a.GetName();
    a.GetValue();
};

template<typename T>
class NamedField
{
public:

    NamedField(std::string const& Name, T const& Value) : name(Name), value(Value) {}

    std::string name;

    T value;

    std::string const& GetName() const { return name; }

    T const& GetValue() const { return value; }
};

template<typename T>
NamedField(T) -> NamedField<T>;

#pragma endregion

#pragma region NamedMultiField

class NamedMultiFieldWrapper
{

public:

    virtual ~NamedMultiFieldWrapper()
    {
		//cout << "Deleted " << this << endl;
    }

    virtual void* GetValue(std::string const& Name) = 0;

    virtual void* GetValue(int Index) = 0;

};

// variadic storage
template<typename... Ts>
class NamedMultiField;

// empty base
template<>
class NamedMultiField<>
{

public:

	void* GetValue(std::string const& Name) { Name; return nullptr; }

	void* GetValue(int Index) { Index; return nullptr; }

};

// recursive case
template<Named T, Named... Rest>
class NamedMultiField<T, Rest...> : public NamedMultiFieldWrapper
{

public:

    ~NamedMultiField()
    {
		cout << "Deleted " << this << endl;
    }

    NamedMultiField(const T& v, const Rest&... rs)
        : value(v)
        , rest(rs...)
    {
    }

    auto& GetValue()
    {
        return value.GetValue();
    }

    void* GetValue(std::string const& Name)
    {
        if (Name == value.GetName())
        {
            return (void*)&value.GetValue();
        }
        else
        {
            return rest.GetValue(Name);
        }
    }

    void* GetValue(int Index)
    {
        if (Index == 0)
        {
            return (void*)&value.GetValue();
        }
        else
        {
            return rest.GetValue(--Index);
        }
    }

    NamedMultiField<Rest...>& GetRest()
    {
        return rest;
    }

public:

    T value;
    NamedMultiField<Rest...> rest;

};

template<Named T, Named... Rest>
NamedMultiField(T, Rest...) -> NamedMultiField<T, Rest...>;

// single get<N> with if constexpr
template<int Index, Named T, Named... Rest>
auto& get(NamedMultiField<T, Rest...>& mf)
{
    if constexpr (Index == 0)
    {
        return mf.GetValue();               // base-case: return this level’s value
    }
    else
    {
        return get<Index - 1>(mf.GetRest());    // recurse down into rest
    }
}

#pragma endregion