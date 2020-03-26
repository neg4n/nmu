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

#ifndef NMU_VECTOR3D_HPP
#define NMU_VECTOR3D_HPP

#include <cassert>
#include <cmath>
#include <cstdint>
#include <optional>
#include <type_traits>
#include <utility>

#include "internal.hpp"

namespace nmu {
  /**
   * ============================
   * Three dimensional vector (3D).
   * ============================
   */
  template <typename T> struct vec3_t {
    static_assert( std::is_arithmetic<T>::value, "Type is not arithmetic" );

    T x = 0, y = 0, z = 0;

    constexpr vec3_t( ) = default;
    constexpr vec3_t( const T & x, const T & y, const T & z ) : x( x ), y( y ), z( z ){};
    constexpr explicit vec3_t( T * source ) : x( source[ 0 ] ), y( source[ 1 ] ), z( source[ 2 ] ){};

    [[nodiscard]] bool margin_is_zero( const float margin /* = 0.1f */ ) const noexcept {
      return x > -margin && x < margin && y > -margin && y < margin && z > -margin && z < margin;
    }

    [[nodiscard]] bool is_valid( ) const noexcept {
      if constexpr ( std::is_floating_point<T>::value )
        return std::isnormal( x ) && std::isnormal( y ) && std::isnormal( z );
      else
        return x != 0 && y != 0 && z != 0;
    }

    [[nodiscard]] T length( ) const noexcept {
      nmu_assert( is_valid( ), "Vector is invalid" );
      return std::sqrt( std::pow( x, 2 ) + std::pow( y, 2 ) + std::pow( z, 2 ) );
    }

    [[nodiscard]] T length_sq( ) const noexcept {
      nmu_assert( is_valid( ), "Vector is invalid" );
      return std::pow( x, 2 ) + std::pow( y, 2 ) + std::pow( z, 2 );
    }

    void normalize( ) noexcept {
      nmu_assert( is_valid( ), "Vector is invalid" );
      if ( const float _length = length( ); std::isnormal( _length ) ) {
        x /= _length;
        y /= _length;
        z /= _length;
      } else {
        clear( );
      }
    }

    void negate( ) noexcept {
      nmu_assert( is_valid( ), "Vector is invalid" );
      x = -x;
      y = -y;
      z = -z;
    }

    void clear( ) noexcept { x = y = z = 0; }

    T & operator[]( const std::uint8_t & i ) const noexcept {
      nmu_assert( i >= 0 && i < 3, "Number must be between 0 and 1" );
      return ( (T *)this )[ i ];
    }

    // Warning:(73, 25) Clang-Tidy: Operator=() does not handle self-assignment properly
    vec3_t<T> & operator=( const vec3_t<T> & rhs ) noexcept {
      if ( &rhs != this ) {
        x = rhs.x;
        y = rhs.y;
        z = rhs.z;
      }
      return *this;
    }

    [[nodiscard]] bool operator==( const vec3_t<T> & rhs ) const noexcept {
      return rhs.x == x && rhs.y == y && rhs.z == z;
    }

    [[nodiscard]] bool operator!=( const vec3_t<T> & rhs ) const noexcept {
      return rhs.x != x && rhs.y != y && rhs.z != z;
    }

    [[nodiscard]] const vec3_t<T> & operator+( const vec3_t<T> & rhs ) const noexcept {
      return vec3_t<T>{ x + rhs.x, y + rhs.y, z + rhs.z };
    }

    [[nodiscard]] const vec3_t<T> & operator-( const vec3_t<T> & rhs ) const noexcept {
      return vec3_t<T>{ x - rhs.x, y - rhs.y, z - rhs.z };
    }

    [[nodiscard]] const vec3_t<T> & operator*( const vec3_t<T> & rhs ) const noexcept {
      return vec3_t<T>{ x * rhs.x, y * rhs.y, z * rhs.z };
    }

    [[nodiscard]] const vec3_t<T> & operator/( const vec3_t<T> & rhs ) const noexcept {
      return vec3_t<T>{ x / rhs.x, y / rhs.y, z / rhs.z };
    }

    void operator+=( const vec3_t<T> & rhs ) const noexcept {
      x += rhs.x;
      y += rhs.y;
      z += rhs.z;
    }

    void operator-=( const vec3_t<T> & rhs ) const noexcept {
      x -= rhs.x;
      y -= rhs.y;
      z -= rhs.z;
    }

    void operator*=( const vec3_t<T> & rhs ) const noexcept {
      x *= rhs.x;
      y *= rhs.y;
      z *= rhs.z;
    }

    void operator/=( const vec3_t<T> & rhs ) const noexcept {
      x /= rhs.x;
      y /= rhs.y;
      z /= rhs.z;
    }
  };
} // namespace nmu

#endif // NMU_VECTOR3D_HPP
