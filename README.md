# Evolutionary Game Theory Simulator

A C++ project combining repeated games, Markov chains, linear algebra, evolutionary dynamics, and a small computational-finance extension.

## Overview

The simulation studies how different Prisoner's Dilemma strategies perform over repeated interactions and how their population shares change under evolutionary selection.

Included strategies:

- Always Cooperate
- Always Defect
- Tit for Tat
- Grim Trigger
- Win-Stay Lose-Shift
- Generous Tit for Tat

The model includes a discount factor for future payoffs, random implementation error, and a small mutation term in the population dynamics.

## Game Theory Model

The default Prisoner's Dilemma payoff matrix is

\[
A =
\begin{bmatrix}
3 & 0 \\
5 & 1
\end{bmatrix}.
\]

Repeated-game utility is discounted by

\[
U = \sum_{t=0}^{T-1} \delta^t u_t.
\]

The program simulates every strategy against every other strategy and builds an empirical payoff matrix.

## Linear Algebra

If `P` is the strategy payoff matrix and `x` is the population vector, strategy fitness is

\[
f = Px.
\]

Average population fitness is

\[
\bar f = x^T P x.
\]

The code implements basic matrix operations directly in C++, including matrix-vector multiplication, matrix multiplication, transpose, dot products, normalization, and iterative stationary-distribution computation.

## Replicator Dynamics

Population shares evolve according to the replicator equation

\[
\dot{x}_i = x_i(f_i - \bar f).
\]

The implementation uses a discrete time step and can also include a small mutation rate.

## Markov Chain Analysis

For memory-one strategy interactions, each round is represented by one of four states:

\[
CC,\; CD,\; DC,\; DD.
\]

These states define a 4 x 4 transition matrix `M`. The stationary distribution satisfies

\[
M^T \pi = \pi.
\]

The code approximates this stationary distribution by repeated matrix-vector multiplication, then uses it to estimate long-run expected payoffs.

## Finance Extension

The project also contains an independent Black-Scholes call-pricing function:

\[
C = S_0 N(d_1) - K e^{-rT} N(d_2).
\]

This is included as a small computational-finance extension rather than part of the evolutionary model itself.

## Files

```text
main.cpp
strategies.cpp / strategies.h
simulation.cpp / simulation.h
linear_algebra.cpp / linear_algebra.h
markov.cpp / markov.h
dynamics.cpp / dynamics.h
csv_utils.cpp / csv_utils.h
finance.cpp / finance.h
CMakeLists.txt
```

## Build

Using g++:

```bash
g++ -std=c++17 main.cpp strategies.cpp simulation.cpp linear_algebra.cpp markov.cpp dynamics.cpp csv_utils.cpp finance.cpp -o simulator
./simulator
```

Or with CMake:

```bash
cmake -S . -B build
cmake --build build
./build/simulator
```

## Output

The simulation writes:

- `payoff_matrix.csv`
- `population_history.csv`
- `markov_transition_matrix.csv`

These files can be used to graph population trajectories and compare long-run behavior.

## Research Question

A useful direction for the project is:

> How does implementation error affect the long-run stability of cooperative strategies in repeated Prisoner's Dilemma populations?

This can be studied from two viewpoints: the stationary distribution of the Markov chain and the evolutionary population dynamics.
