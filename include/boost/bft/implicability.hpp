// Copyright (c) 2011-2014
// Marek Kurdej
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_BFT_IMPLICABILITY_HPP
#define BOOST_BFT_IMPLICABILITY_HPP

#include <boost/bft/bft_function.hpp>
#include <boost/bft/fod.hpp>
#include <boost/bft/detail/is_small.hpp>

namespace boost
{
namespace bft
{

template <class FOD, typename T = double>
class implicability : public bft_function<FOD, T>
{
public:
    typedef implicability<FOD, T> this_type;
    typedef typename bft_function<FOD, T>::container_type container_type;

    /// Default constructor.
    implicability()
    {
    }

    /// It creates an implicability function equivalent to a mass function where
    /// all mass is attributed to the Conflict set (Emptyset).
    /// I.e. all values equal 1.
    implicability(degenerate_t)
    {
        this->m_values.assign(1);
    }

    /// It creates an implicability function equivalent to a mass function where
    /// all mass is attributed to the Unknown set (Omega).
    /// I.e. value for Unknown equals 1 and for other sets equals 0.
    implicability(vacuous_t)
    {
        this->m_values.back() = 1;
    }

    explicit implicability(const bft_function<FOD, T>& f)
        : bft_function<FOD, T>(f)
    {
    }

    implicability(const container_type& init_values)
        : bft_function<FOD, T>(init_values)
    {
    }

#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
    implicability(const std::initializer_list<T>& init_values)
        : bft_function<FOD, T>(init_values)
    {
    }
#endif

    ~implicability()
    {
    }

    /// Subnormal mass function has some mass at Emptyset.
    bool is_subnormal() const
    {
        return !detail::is_small(this->m_values.front(), detail::tolerance);
    }
};

} // namespace bft

} // namespace boost

#endif // BOOST_BFT_IMPLICABILITY_HPP
