////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#ifndef SRC_RANGE_HPP
#define SRC_RANGE_HPP

////////////////////////////////////////////////////////////////////////////////
#include <iterator>

////////////////////////////////////////////////////////////////////////////////
class range
{
    int from_, to_;

public:
    constexpr range(int from, int to) : from_(from), to_(to) { }

    class iterator
    {
        int n_;

    public:
        explicit constexpr iterator(int n) : n_(n) { }

        constexpr int operator*() const { return n_; }

        constexpr iterator& operator++() { ++n_; return (*this); }
        constexpr iterator operator++(int) { auto it = (*this); ++(*this); return it; }

        constexpr bool operator==(iterator rhs) const { return n_ == rhs.n_; }
        constexpr bool operator!=(iterator rhs) const { return !((*this) == rhs); }

        using difference_type = int;
        using value_type = int;
        using pointer = const int*;
        using reference = const int&;
        using iterator_category = std::forward_iterator_tag;
    };

    auto begin() const { return iterator(from_); }
    auto end() const { return iterator(to_ + 1); }
};

////////////////////////////////////////////////////////////////////////////////
#endif
