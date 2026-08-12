# Health Bar Simulator

<img src="https://img.shields.io/badge/-C++-00599C?style=flat&logo=cplusplus&logoColor=white" alt="C++"/><img src="https://img.shields.io/badge/-SFML-8CC445?style=flat&logo=sfml&logoColor=white" alt="SFML"/><img src="https://img.shields.io/badge/-Claude-D97757?style=flat&logo=claude&logoColor=white" alt="Claude"/>

A small SFML 3 health bar with damage and heal animations. Written in C++ with Claude Code, structured as an MVVM practice piece.

## Demo

![Health Bar Simulator](./assets/demo/HealthBarSimulatorDemo.gif)

## Technical Highlights

- MVVM layering. The model owns health and its clamping rules, the view model adapts them for display, and the view owns every SFML type. `main.cpp` only wires the layers together.
- `RoundedRectangle` extends `sf::Shape` and clamps its corner radius against the current size, so a shrinking bar degrades to a pill instead of inverting.
- The change highlight interpolates between old and new health. Rapid clicks extend one span rather than restarting it.
- Camera shake is a decaying sine wave applied through a shifted `sf::View`, which is restored before the next event poll so hit testing stays correct mid shake.
- Animation runs on delta time rather than frame count.
- Bar colour is threshold driven: green above 55%, yellow from 20 to 55%, red at or below 20%.

## Build

Requires C++23 and CMake 4.0+. SFML 3.1.0 is fetched automatically by CMake.

```bash
cmake -B build
cmake --build build
./build/healthBarSim
```
