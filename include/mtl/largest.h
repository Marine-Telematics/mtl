///-----------------------------------------------------------------------------
/// MarineTelematics Template Library - (c) 2026 Marine Telematics
///-----------------------------------------------------------------------------
///
/// @file largest.h
/// @author Gabriel Novalski (gabriel@marinetelematics.com.br)
/// @date 02-02-2026
///
///-----------------------------------------------------------------------------

#ifndef MTL_LARGEST_H
#define MTL_LARGEST_H

#include <cstddef>
#include <type_traits>

namespace mtl
{
//***************************************************************************
// largest_type
template <typename T1, typename... TRest>
struct largest_type
{
// Define 'largest_other' as 'largest_type' with all but the first parameter. 
using largest_other = typename largest_type<TRest...>::type;

// Set 'type' to be the largest of the first parameter and any of the others.
// This is recursive.
using type = conditional_t<
    (sizeof(T1) > sizeof(largest_other)), T1, largest_other>;

// The size of the largest type.
static constexpr size_t size = sizeof(type);
};

template <typename T1>
struct largest_type<T1>
{
using type = T1;
static constexpr size_t size = sizeof(T1);
};

template<typename T1, typename ...TRest>
using largest_type_t = typename largest_type<T1, TRest...>::type;

//***************************************************************************
// largest_alignment
template <typename T1, typename... TRest>
struct largest_alignment
{
// Define 'largest_other' as 'largest_type' with all but the first parameter.
using largest_other = typename largest_alignment<TRest...>::type;

// Set 'type' to be the largest of the first parameter and any of the others.
// This is recursive.
using type = conditional_t<
    (alignment_of_v<T1> > alignment_of_v<largest_other>), T1, largest_other>;

    static constexpr size_t value = alignment_of_v<type>;
};

template <typename T1>
struct largest_alignment<T1>
{
typedef T1 type;
static constexpr size_t value = alignment_of_v<type>;
};

template<typename T1, typename... TRest>
inline constexpr size_t largest_alignment_v = largest_alignment<T1, TRest...>::value;
}

#endif
