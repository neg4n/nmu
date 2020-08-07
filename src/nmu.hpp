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

#include "color.hpp"
#include "internal.hpp"
#include "vector2d.hpp"
#include "vector3d.hpp"

#ifdef _MSC_VER
#define forceinline __forceinline
#else
#define forceinline __attribute__( ( always_inline ) )
#endif

namespace nmu {

  namespace constants {
    constexpr inline float  pi_number_f = 3.141592f;
    constexpr inline double pi_number   = 3.14159265358979;
  } // namespace constants

  template <typename T>[[nodiscard]] forceinline T rad2deg( T radians ) noexcept {
    constexpr bool is_float       = std::is_same<T, float>::value;
    constexpr bool is_double      = std::is_same<T, double>::value;
    constexpr bool is_long_double = std::is_same<T, long double>::value;

    static_assert( is_float || is_double || is_long_double, "Type must be float, double or long double" );

    if constexpr ( is_float )
      return radians * 180.f / constants::pi_number_f;
    else if constexpr ( is_double || is_long_double )
      return radians * 180.0 / constants::pi_number;
  }

  template <typename T>[[nodiscard]] forceinline T deg2rad( T degrees ) noexcept {
    constexpr bool is_float       = std::is_same<T, float>::value;
    constexpr bool is_double      = std::is_same<T, double>::value;
    constexpr bool is_long_double = std::is_same<T, long double>::value;

    static_assert( is_float || is_double || is_long_double, "Type must be float, double or long double" );

    if constexpr ( is_float )
      return degrees * constants::pi_number_f / 180.f;
    else if constexpr ( is_double || is_long_double )
      return degrees * constants::pi_number / 180.0;
  }

  template <typename T>[[nodiscard]] forceinline auto dot_product( const T & a, const T & b ) noexcept {
    constexpr bool is_2d_vector =
        std::is_same<T, vec2_t<typename _nmu_internal::type_unwrapper<T>::template param_t<0>>>::value;

    constexpr bool is_3d_vector =
        std::is_same<T, vec3_t<typename _nmu_internal::type_unwrapper<T>::template param_t<0>>>::value;

    static_assert( is_2d_vector || is_3d_vector, "Type must be vector" );

    if constexpr ( is_2d_vector ) {
      return a.x * b.x + a.y * b.y;
    } else if constexpr ( is_3d_vector ) {
      return a.x * b.x + a.y * b.y + a.z * b.z;
    }
  }

  template <typename T>[[nodiscard]] forceinline auto cross_product( const T & a, const T & b ) noexcept {
    constexpr bool is_2d_vector =
        std::is_same<T, vec2_t<typename _nmu_internal::type_unwrapper<T>::template param_t<0>>>::value;

    constexpr bool is_3d_vector =
        std::is_same<T, vec3_t<typename _nmu_internal::type_unwrapper<T>::template param_t<0>>>::value;

    static_assert( is_2d_vector || is_3d_vector, "Type must be a vector" );

    if constexpr ( is_2d_vector ) {
      return a.x * b.y - a.y * b.x;
    } else if constexpr ( is_3d_vector ) {
      return ( ( a.y * b.z ) - ( a.z * b.y ), ( a.z * b.x ) - ( a.x * b.z ), ( a.x * b.y ) - ( a.y * b.x ) );
    }
  }

  template <typename T>[[nodiscard]] forceinline auto distance( const T & a, const T & b ) noexcept {
    constexpr bool is_2d_vector =
        std::is_same<T, vec2_t<typename _nmu_internal::type_unwrapper<T>::template param_t<0>>>::value;

    constexpr bool is_3d_vector =
        std::is_same<T, vec3_t<typename _nmu_internal::type_unwrapper<T>::template param_t<0>>>::value;

    static_assert( is_2d_vector || is_3d_vector, "Type must be vector" );

    if constexpr ( is_2d_vector ) {
      return ( T { a.x - b.x, a.y - b.y } ).length( );
    } else if constexpr ( is_3d_vector ) {
      return ( T { a.x - b.x, a.y - b.y, a.z - b.z } ).length( );
    }
  }
} // namespace nmu

#ifndef NMU_NO_GLOBALS

using vec2_t  = nmu::vec2_t<float>;
using vec2i_t = nmu::vec2_t<int>;

using vec3_t  = nmu::vec3_t<float>;
using vec3i_t = nmu::vec3_t<int>;

using color_t = nmu::color_t;

#define m_pi_f nmu::constants::pi_number_f
#define m_pi nmu::constants::pi_number

#define dot_product nmu::dot_produc
#define cross_product nmu::cross_product
#define calc_distance nmu::distance
#define rad2deg nmu::rad2deg
#define deg2rad nmu::deg2rad

// clang-format: off
#define color_from_float_a( variable, ... ) \
  variable.from<float, float, float, float, float>( __VA_ARGS__ )

#define color_to_float_a(variable) \
  variable.to<float, 4>( )

#define color_from_float( variable, ... ) \
  variable.from<float, float, float, float>( __VA_ARGS__ )

#define color_to_float(variable) \
  variable.to<float, 3>( )

#define color_from_int( variable, value ) \
  variable.from<int, int>( value )

#define color_to_int(variable) \
  (variable.to<int, 1>( )[0] & ~ 255)

#define color_to_int_a(variable) \
  variable.to<int, 1>( )[0]

// clang-format: on

#endif

#endif // NMU_HPP
