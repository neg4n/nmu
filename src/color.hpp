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

#ifndef NMU_COLOR_HPP
#define NMU_COLOR_HPP

#include <cstdint>
#include <tuple>
#include <vector>

namespace nmu {
  namespace color_formats {
   constexpr inline int rgba = 1, hex = 2;
  }
  /**
   * ===================================
   * Color class with 8 bits per channel
   * ===================================
   */
  struct color_t {
    std::uint8_t r = 0, g = 0, b = 0, a = 255;

    constexpr color_t( ) = default;
    constexpr color_t( std::uint8_t red, std::uint8_t green, std::uint8_t blue, std::uint8_t alpha = 255 )
        : r( red ), g( green ), b( blue ), a( alpha ) { };

    /**
     * Construction from multiple formats
     * of color notation, see color_from_type
     * macro in nmu.hpp (main header file)
     * -----------------------------------------
     */

    template <typename T, typename... Vs> void from( Vs... values ) noexcept {
      constexpr bool should_convert_from_float = std::is_same<T, float>::value;
      constexpr bool should_convert_from_int   = std::is_same<T, int>::value;

      constexpr std::size_t type_count = sizeof...( Vs );

      static_assert( should_convert_from_float || should_convert_from_int,
                     "Invalid type, you can only construct from: float, int" );

      // Create some kind of values store to access them by index later.
      std::tuple<Vs...> store( values... );

      if constexpr ( should_convert_from_float ) {
        // We want to limit user to provide only between 3 and 4 variadic types (3; r,g,b and 4th == a)
        // only need to check if there are too many arguments because if there are too few it triggers
        // `No matching member function for call to 'from'` error.
        static_assert( type_count <= 4, "Too many types (so also values) were provided" );
        // Accessing corresponding elements of the tuple because we provide 4 floats.
        r = ( std::uint8_t )( std::get<0>( store ) * 255.f );
        g = ( std::uint8_t )( std::get<1>( store ) * 255.f );
        b = ( std::uint8_t )( std::get<2>( store ) * 255.f );
        // Check if exactly 3 values (r, g, b) were provided, if so, set alpha to 1.0f
        if constexpr ( type_count == 3 ) {
          a = ( std::uint8_t )( 1.0f * 255.f );
        } else {
          a = ( std::uint8_t )( std::get<3>( store ) * 255.f );
        }
      } else if constexpr ( should_convert_from_int ) {
        // Same as in lines 66-68 but for one argument.
        static_assert( type_count == 1, "Too many types (so also values) were provided" );
        // Accessing only first element in the tuple because in this scenario, only only exists (int)
        r = ( std::uint8_t )( ( std::get<0>( store ) & 0xff0000 ) >> 16 );
        g = ( std::uint8_t )( ( std::get<0>( store ) & 0xff00 ) >> 8 );
        b = ( std::uint8_t )( ( std::get<0>( store ) & 0xff ) );
      }
    }

    /**
     * Export color from 4 8bit integers to
     * various other notations using std::array
     * representing each value
     * -----------------------------------------
     */

    template <typename T, std::uint8_t N>[[nodiscard]] std::array<T, N> to( ) const noexcept {
      constexpr bool should_export_to_float = std::is_same<T, float>::value;
      constexpr bool should_export_to_int   = std::is_same<T, int>::value;

      static_assert(
          ( should_export_to_float && ( N == 3 || N == 4 ) ) || ( should_export_to_int && N == 1 ),
          "Invalid type, you can only export to float with N == 4 or N == 3 or int vector with N == 1" );

      if constexpr ( should_export_to_float ) {
        if constexpr ( N == 3 ) {
          return std::array<T, N> {
            //  clang-format: off
            (float)r / 255.f,
            (float)g / 255.f,
            (float)b / 255.f
            // clang-format: on
          };
        } else if constexpr ( N == 4 ) {
          return std::array<T, N> {
            //  clang-format: off
            (float)r / 255.f,
            (float)g / 255.f,
            (float)b / 255.f,
            (float)a / 255.f
            // clang-format: on
          };
        }
      } else if constexpr ( should_export_to_int ) {
        return std::array<T, N> { (int)( ( r << 24 ) | ( g << 16 ) | ( b << 8 ) | a ) };
      }
    }
  };
} // namespace nmu

#endif // NMU_COLOR_HPP
