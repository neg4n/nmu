/**
 * MIT License
 *
 * Copyright (c) 2020 neg4n / Igor Klepacki
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#ifndef NMU_INTERNAL_HPP
#define NMU_INTERNAL_HPP

#include <cstddef>
#include <tuple>

#define nmu_assert( condition, message ) assert( ( condition ) && ( message ) );

// DO NOT USE outside nmu.hpp
namespace _nmu_internal {
  // Credits: https://stackoverflow.com/a/30519190
  template <typename T> struct type_unwrapper;
  template <template <typename...> class C, typename... Ts> struct type_unwrapper<C<Ts...>> {
    static constexpr std::size_t type_count = sizeof...( Ts );

    template <std::size_t N> using param_t = typename std::tuple_element<N, std::tuple<Ts...>>::type;
  };
} // namespace nmu_internal

#endif // NMU_INTERNAL_HPP
