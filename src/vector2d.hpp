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

#ifndef NMU_VECTOR2D_HPP
#define NMU_VECTOR2D_HPP

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
	 * Two dimensional vector (2D).
	 * ============================
	 */
	template <typename T> struct vec2_t {
		static_assert( std::is_arithmetic<T>::value, "Type is not arithmetic" );

		T x = 0, y = 0;

		constexpr vec2_t( ) = default;
		constexpr vec2_t( T x, T y ) : x( x ), y( y ) { };
		constexpr explicit vec2_t( T * source ) : x( source[ 0 ] ), y( source[ 1 ] ) { };
		constexpr explicit vec2_t( const std::pair<T, T> & source ) : x( source.first ), y( source.second ) { };

		[[nodiscard]] bool margin_is_zero( const float margin /* = 0.1f */ ) const noexcept {
			return x > -margin && x < margin && y > -margin && y < margin;
		}

		[[nodiscard]] bool is_valid( ) const noexcept {
			if constexpr ( std::is_floating_point<T>::value )
				return std::isnormal( x ) && std::isnormal( y );
			else
				return x != 0 && y != 0;
		}

		[[nodiscard]] T length( ) const noexcept {
			nmu_assert( is_valid( ), "Vector is invalid" );
			return std::sqrt( std::pow( x, 2 ) + std::pow( y, 2 ) );
		}

		[[nodiscard]] T length_sq( ) const noexcept {
			nmu_assert( is_valid( ), "Vector is invalid" );
			return std::pow( x, 2 ) + std::pow( y, 2 );
		}

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

		T & operator[]( const std::uint8_t & i ) const noexcept {
			nmu_assert( i >= 0 && i < 2, "Number must be between 0 and 1" );
			return ( (T *)this )[ i ];
		}

		// Warning:(73, 25) Clang-Tidy: Operator=() does not handle self-assignment properly
		vec2_t<T> & operator=( const vec2_t<T> & rhs ) noexcept {
			if ( &rhs != this ) {
				x = rhs.x;
				y = rhs.y;
			}
			return *this;
		}

		[[nodiscard]] bool operator==( const vec2_t<T> & rhs ) const noexcept { return rhs.x == x && rhs.y == y; }

		[[nodiscard]] bool operator!=( const vec2_t<T> & rhs ) const noexcept { return rhs.x != x && rhs.y != y; }

		[[nodiscard]] const vec2_t<T> & operator+( const vec2_t<T> & rhs ) const noexcept {
			return vec2_t<T> { x + rhs.x, y + rhs.y };
		}

		[[nodiscard]] const vec2_t<T> & operator-( const vec2_t<T> & rhs ) const noexcept {
			return vec2_t<T> { x - rhs.x, y - rhs.y };
		}

		[[nodiscard]] const vec2_t<T> & operator*( const vec2_t<T> & rhs ) const noexcept {
			return vec2_t<T> { x * rhs.x, y * rhs.y };
		}

		[[nodiscard]] const vec2_t<T> & operator/( const vec2_t<T> & rhs ) const noexcept {
			return vec2_t<T> { x / rhs.x, y / rhs.y };
		}

		void operator+=( const vec2_t<T> & rhs ) const noexcept {
			x += rhs.x;
			y += rhs.y;
		}

		void operator-=( const vec2_t<T> & rhs ) const noexcept {
			x -= rhs.x;
			y -= rhs.y;
		}

		void operator*=( const vec2_t<T> & rhs ) const noexcept {
			x *= rhs.x;
			y *= rhs.y;
		}

		void operator/=( const vec2_t<T> & rhs ) const noexcept {
			x /= rhs.x;
			y /= rhs.y;
		}
	};
} // namespace nmu

#endif // NMU_VECTOR2D_HPP
