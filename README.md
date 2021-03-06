# nmu

<sub>
neg4n's math utilities, a C++17 header-only, dependency free and multiplatform
set of mathematics utilities and definitions.
</sub>

In order to use it, add this repository to your project  
as [git submodule](https://git-scm.com/book/en/v2/Git-Tools-Submodules)
and add this line to your `CMakeLists.txt`:  
```cmake
include_directories("nmu/src")
```
then simply `#include <nmu.hpp>` in your code.

Documentation will be available soon. 

### Compilers support

| Name | Tested | Version |
|----------|--------|---------|
| MSVC     | ✅      | 1924    |
| g++      |✅ | 7.5.0    |
| clang    | ❌      | none    |

#### Features

- Two-dimensional (2D) vectors with all arithmetic types support.
- Three-dimensional (3D) vectors with all arithmetic types support.
- Radians to degrees and degrees to radians conversion.
- Colors (8bit per channel) support with conversions between various notations
  - From/to float
  - From/To float with alpha
  - From/to integer
  - To integer with alpha // TODO: Support from conversion
- Math constants.

*more soon...*
    
#### Ending speech

Feel free to contribute and do not hesitate to contact  
with me through e-mail: *i@thiocod.in*  
if there are any questions/problems.

Written under [MIT License](https://en.wikipedia.org/wiki/MIT_License)



