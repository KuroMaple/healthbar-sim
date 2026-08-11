# healthbar-sim

A simple full screen health bar simulator written in C++ using [SFML](https://www.sfml-dev.org/).

## Requirements

- A C++26-capable compiler
- CMake 4.0 or newer

SFML 3.1.0 is fetched automatically by CMake via `FetchContent`, so there is nothing to install by hand.

## Build

```bash
cmake -B build
cmake --build build
```

## Run

```bash
./build/healthBarSim
```
