# Logger Application

## Build Instructions

### CMake Commands
- Generate build files:
  ```bash
  cmake -B build -S .
  ```
  - `-B build`: Specifies build directory
  - `-S .`: Specifies source directory (current directory)

- Build the project:
  ```bash
  cmake --build build
  ```
  - Builds the project using the generated build system
  - Creates executable in `build/bin/`

### Important CMake Variables
- `CMAKE_SOURCE_DIR`
  - Root directory containing the top-level CMakeLists.txt
  - Points to where your source code lives

- `CMAKE_BINARY_DIR`
  - Root directory for all build files and outputs
  - Contains generated CMake files, object files, and executables

- `CMAKE_RUNTIME_OUTPUT_DIRECTORY`
  - Directory where executables are placed
  - Set to `${CMAKE_BINARY_DIR}/bin` in this project

### Project Structure
```
PAOO/
├── CMakeLists.txt
├── include/         # Header files
├── src/            # Source files
└── build/          # Build artifacts
    ├── bin/        # Executables
    └── CMakeFiles/ # CMake-generated files
```