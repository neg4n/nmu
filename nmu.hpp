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

#ifndef NMU_NMU_HPP
#define NMU_NMU_HPP

#include <any>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <optional>
#include <type_traits>
#include <utility>

#ifdef _MSC_VER
#define forceinline __forceinline
#else
#define forceinline __attribute__( ( always_inline ) )
#endif

#define nmu_assert( condition, message ) assert( ( condition ) && ( message ) );

namespace nmu {
  // DO NOT USE outside nmu.hpp
  namespace internal {
    // Credits: https://stackoverflow.com/a/30519190
    template <typename T> struct type_unwrapper;
    template <template <typename...> class C, typename... Ts> struct type_unwrapper<C<Ts...>> {
      static constexpr std::size_t type_count = sizeof...( Ts );

      template <std::size_t N> using param_t = typename std::tuple_element<N, std::tuple<Ts...>>::type;
    };
  } // namespace internal

  /**
   * ============================
   * Two dimensional vector (2D).
   * ============================
   */
  template <typename T> struct vec2_t {
    static_assert( std::is_arithmetic<T>::value, "Type is not arithmetic" );

    T x = 0, y = 0;

    constexpr vec2_t( ) = default;
    constexpr vec2_t( const T & x, const T & y ) : x( x ), y( y ){};
    constexpr explicit vec2_t( T * source ) : x( source[ 0 ] ), y( source[ 1 ] ){};
    constexpr explicit vec2_t( const std::pair<T, T> & source )
        : x( source.first ), y( source.second ){};

    [[nodiscard]] bool margin_is_zero( const float margin /* = 0.1f */ ) const noexcept {
      return x > -margin && x < margin && y > -margin && y < margin;
    }

    [[nodiscard]] bool is_valid( ) const noexcept {
      if constexpr ( std::is_floating_point<T>::value )
        return std::isnormal( x ) && std::isnormal( y );
      else
        return x != 0 && y != 0;
    }

    [[nodiscard]] const T & length( ) const noexcept {
      nmu_assert( is_valid( ), "Vector is invalid" );
      // C4172
      return std::sqrt( std::pow( x, 2 ) + std::pow( y, 2 ) );
    }

#ifndef NMU_NO_REDUNTANT_CLASS_FUNCTIONS
    [[nodiscard]] const T & dot( const vec2_t<T> & _ ) const noexcept {
      nmu_assert( is_valid( ), "Vector is invalid" );
      // C4172
      return x * _.x + y * _.y;
    }

    [[nodiscard]] const T & cross( const vec2_t<T> & _ ) const noexcept {
      nmu_assert( is_valid( ), "Vector is invalid" );
      // C4172
      return x * _.y - y * _.x;
    }
#endif

    void normalize( ) noexcept {
      nmu_assert( is_valid( ), "Vector is invalid" );
      if ( const float _length = length( ); std::isnormal( _length ) ) {
        x /= _length;
        y /= _length;
      } else {
        clear( );
      }
    }

    void negate( ) noexcept {
      nmu_assert( is_valid( ), "Vector is invalid" );
      x = -x;
      y = -y;
    }

    void clear( ) noexcept { x = y = 0; }

    T & operator[]( const std::uint8_t & _ ) const noexcept {
      nmu_assert( _ >= 0 && _ < 2, "Number must be between 0 and 1" );
      return ( (T *)this )[ _ ];
    }

    // Warning:(73, 25) Clang-Tidy: Operator=() does not handle self-assignment properly
    vec2_t<T> & operator=( const vec2_t<T> & _ ) noexcept {
      if ( &_ != this ) {
        x = _.x;
        y = _.y;
      }
      return *this;
    }

    [[nodiscard]] bool operator==( const vec2_t<T> & _ ) const noexcept { return _.x == x && _.y == y; }

    [[nodiscard]] bool operator!=( const vec2_t<T> & _ ) const noexcept { return _.x != x && _.y != y; }

    [[nodiscard]] const vec2_t<T> & operator+( const vec2_t<T> & _ ) const noexcept {
      return vec2_t<T>{ x + _.x, y + _.y };
    }

    [[nodiscard]] const vec2_t<T> & operator-( const vec2_t<T> & _ ) const noexcept {
      return vec2_t<T>{ x - _.x, y - _.y };
    }

    [[nodiscard]] const vec2_t<T> & operator*( const vec2_t<T> & _ ) const noexcept {
      return vec2_t<T>{ x * _.x, y * _.y };
    }

    [[nodiscard]] const vec2_t<T> & operator/( const vec2_t<T> & _ ) const noexcept {
      return vec2_t<T>{ x / _.x, y / _.y };
    }

    void operator+=( const vec2_t<T> & _ ) const noexcept {
      x += _.x;
      y += _.y;
    }

    void operator-=( const vec2_t<T> & _ ) const noexcept {
      x -= _.x;
      y -= _.y;
    }

    void operator*=( const vec2_t<T> & _ ) const noexcept {
      x *= _.x;
      y *= _.y;
    }

    void operator/=( const vec2_t<T> & _ ) const noexcept {
      x /= _.x;
      y /= _.y;
    }
  };

  template <typename T>
  [[nodiscard]] forceinline const auto & dot_product( const T & a, const T & b ) noexcept {
    constexpr bool is_2d_vector =
        std::is_same<T, vec2_t<typename nmu::internal::type_unwrapper<T>::template param_t<0>>>::value;

    static_assert( is_2d_vector, "Type must be vector" );

    if constexpr ( is_2d_vector ) {
      // C4172
#ifndef NMU_NO_REDUNTANT_CLASS_FUNCTIONS
      return a.dot( b );
#else
      return a.x * b.x + a.y * b.y;
#endif
    }
  }

  template <typename T>
  [[nodiscard]] forceinline const auto & cross_product( const T & a, const T & b ) noexcept {
    constexpr bool is_2d_vector =
        std::is_same<T, vec2_t<typename nmu::internal::type_unwrapper<T>::template param_t<0>>>::value;

    static_assert( is_2d_vector, "Type must be vector" );

    if constexpr ( is_2d_vector ) {
      // C4172
#ifndef NMU_NO_REDUNTANT_CLASS_FUNCTIONS
      return a.cross( b );
#else
      return a.x * b.y - a.y * b.x;
#endif
    }
  }
} // namespace nmu

#ifndef NMU_NO_GLOBALS

using vec2_t = nmu::vec2_t<float>;
using vec2i_t = nmu::vec2_t<int>;

#define dot_product nmu::dot_product
#define cross_product nmu::cross_product

#endif

#endif // NMU_NMU_HPP
