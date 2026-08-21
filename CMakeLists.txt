cmake_minimum_required(VERSION 3.16)
project(EvolutionaryGameTheory)

set(CMAKE_CXX_STANDARD 17)

add_executable(simulator
    main.cpp
    strategies.cpp
    simulation.cpp
    linear_algebra.cpp
    markov.cpp
    dynamics.cpp
    csv_utils.cpp
    finance.cpp
)
