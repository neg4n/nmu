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

#ifndef NMU_HPP
#define NMU_HPP

#include "internal.hpp"
#include "vector2d.hpp"

#ifdef _MSC_VER
#define forceinline __forceinline
#else
#define forceinline __attribute__( ( always_inline ) )
#endif

namespace nmu {
  template <typename T> [[nodiscard]] forceinline auto dot_product( const T & a, const T & b ) noexcept {
    constexpr bool is_2d_vector =
        std::is_same<T, vec2_t<typename _nmu_internal::type_unwrapper<T>::template param_t<0>>>::value;

    static_assert( is_2d_vector, "Type must be vector" );

    if constexpr ( is_2d_vector ) {
#ifdef NMU_USE_DEPRECATED
      return a.dot( b );
#else
      return a.x * b.x + a.y * b.y;
#endif
    }
  }

  template <typename T> [[nodiscard]] forceinline auto cross_product( const T & a, const T & b ) noexcept {
    constexpr bool is_2d_vector =
        std::is_same<T, vec2_t<typename _nmu_internal::type_unwrapper<T>::template param_t<0>>>::value;

    static_assert( is_2d_vector, "Type must be vector" );

    if constexpr ( is_2d_vector ) {
#ifdef NMU_USE_DEPRECATED
      return a.cross( b );
#else
      return a.x * b.y - a.y * b.x;
#endif
    }
  }

  template <typename T> [[nodiscard]] forceinline auto distance( const T & a, const T & b ) noexcept {
    constexpr bool is_2d_vector =
        std::is_same<T, vec2_t<typename _nmu_internal::type_unwrapper<T>::template param_t<0>>>::value;

    static_assert( is_2d_vector, "Type must be vector" );

    if constexpr ( is_2d_vector ) {
#ifdef NMU_USE_DEPRECATED
      return a.distance( b );
#else
      return ( T{ a.x - b.x, a.y - b.y } ).length( );
#endif
    }
  }
} // namespace nmu

#ifndef NMU_NO_GLOBALS

using vec2_t = nmu::vec2_t<float>;
using vec2i_t = nmu::vec2_t<int>;

#define dot_product nmu::dot_product
#define cross_product nmu::cross_product
#define calc_distance nmu::distance

#endif

#endif // NMU_HPP
