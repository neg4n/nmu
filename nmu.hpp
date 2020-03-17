#ifndef NMU_NMU_HPP
#define NMU_NMU_HPP

#include <any>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <optional>
#include <type_traits>
#include <utility>

#define nmu_assert( condition, message ) assert( ( condition ) && ( message ) );

namespace nmu {
  /**
   * ============================
   * Two dimensional vector (2D).
   * ============================
   */
  template <typename T> class vec2_t {
    static_assert( std::is_arithmetic<T>::value, "Type is not arithmetic." );

  private:
  public:
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
      nmu_assert( is_valid( ), "Vector is invalid." );
      return std::sqrt( std::pow( x, 2 ) + std::pow( y, 2 ) );
    }

    void normalize( ) noexcept {
      nmu_assert( is_valid( ), "Vector is invalid." );
      if ( const float _length = length( ); std::isnormal( _length ) ) {
        x /= _length;
        y /= _length;
      } else {
        clear( );
      }
    }

    void clear( ) noexcept { x = y = 0; }

    T & operator[]( const std::uint8_t & _ ) const noexcept {
      nmu_assert( _ >= 0 && _ < 2, "Number must be between 0 and 1" );
      return ( (T *)this )[ _ ];
    }

    vec2_t<T> & operator=( const vec2_t<T> & _ ) noexcept {
      if ( &_ != this ) {
        x = _.x;
        y = _.y;
      }
      return *this;
    }

    [[nodiscard]] bool operator==( const vec2_t<T> & _ ) const noexcept {
      return _.x == x && _.y == y;
    }

    [[nodiscard]] bool operator!=( const vec2_t<T> & _ ) const noexcept {
      return _.x != x && _.y != y;
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
} // namespace nmu

using vec2_t = nmu::vec2_t<float>;
using vec2i_t = nmu::vec2_t<int>;

#endif // NMU_NMU_HPP
