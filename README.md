# CPU Graphics Engine

A simple CPU-based graphics engine written in C++.

[![CI](https://github.com/kyanvde/cpu-graphics-engine/actions/workflows/ci.yml/badge.svg)](https://github.com/kyanvde/cpu-graphics-engine/actions/workflows/ci.yml)
[![CD](https://github.com/kyanvde/cpu-graphics-engine/actions/workflows/cd.yml/badge.svg)](https://github.com/kyanvde/cpu-graphics-engine/actions/workflows/cd.yml)
[![codecov](https://codecov.io/github/kyanvde/cpu-graphics-engine/graph/badge.svg?token=HL1ILHMB39)](https://codecov.io/github/kyanvde/cpu-graphics-engine)
![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)
![C++](https://img.shields.io/badge/language-C++17-blue.svg)
[![Docs](https://img.shields.io/badge/docs-Doxygen-blue.svg)](https://kyanvde.github.io/cpu-graphics-engine/index.html)

## Table of Contents

- [Roadmap](#roadmap)
- [Getting Started](#getting-started)
- [Dependencies](#dependencies)
- [Testing](#testing)
- [Documentation](#documentation)
- [Contributing](#contributing)
- [License](#license)
- [Contact](#contact)

## Roadmap

The following features are planned for the graphics engine. The status of each feature is indicated by a checkmark (✓)
for completed features and an empty space for those not yet implemented.

| Functionality            | Status |
|--------------------------|--------|
| 1. 2D L-systems          | ✓      |
| With brackets            | ✓      |
| Stochastic               |        |
| 2. Transformations       |        |
| Eye-point                |        |
| Projection               |        |
| 3. Platonic Solids       |        |
| Cone and cylinder        |        |
| Sphere                   |        |
| Torus                    |        |
| 3D L-systems             |        |
| 4. Z-buffering (lines)   |        |
| 5. Triangulation         |        |
| Z-buffering (triangles)  |        |
| 6. 3D fractals           |        |
| BuckyBall                |        |
| Menger sponge            |        |
| View frustum             |        |
| 7. Ambient light         |        |
| Diffuse light (infinite) |        |
| Diffuse light (point)    |        |
| Specular light           |        |
| 8. Shadow                |        |
| Texture mapping          |        |
| 9. Spheres and cylinders |        |
| UV coordinates           |        |
| Cube mapping             |        |

## Getting Started

To quickly get started:

```sh
git clone https://github.com/kyanvde/cpu-graphics-engine.git
cd cpu-graphics-engine
mkdir build
cd build
cmake ..
make
./engine_tests
```

## Dependencies

- C++17 or newer
- CMake (version 3.10+)
- GoogleTest (for unit testing)
- Doxygen (for documentation)

## Testing

This project uses GoogleTest for unit testing. All core components should be covered by automated tests to ensure
correctness and reliability. The aim is to achieve high test coverage across the codebase, helping to catch regressions
early and maintain code quality as the project evolves.

To run the tests after building:

```sh
./engine_tests
```

## Documentation

[Documentation](https://kyanvde.github.io/cpu-graphics-engine/index.html) is generated using Doxygen. To build the
documentation, run:

```sh
doxygen Doxyfile
```

## Contributing

Contributions are welcome! Please open issues or pull requests. For major changes, please open an issue first to discuss
what you would like to change.

1. Fork the repository
2. Create your feature branch (git checkout -b feature/YourFeature)
3. Commit your changes (git commit -am 'Add new feature')
4. Push to the branch (git push origin feature/YourFeature)
5. Open a pull request

## License

This project is licensed under the GPL-3.0 license - see
the [LICENSE](https://github.com/kyanvde/cpu-graphics-engine/blob/main/LICENSE) file for details.

## Contact

For questions or support, please open an issue on [GitHub](https://github.com/kyanvde/cpu-graphics-engine/issues) or
email me
at [kyanvde@gmail.com](mailto:kyanvde@gmail.com).
