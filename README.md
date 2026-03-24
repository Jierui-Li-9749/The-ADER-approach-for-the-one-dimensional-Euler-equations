# ADER-WENO Solver for the 1D Euler Equations

High-order finite-volume solver implementing ADER3, ADER4, and ADER5 schemes
with WENO-DK reconstruction and TT-GRP flux computation, for the one-dimensional
compressible Euler equations.

---

## Requirements

- C++17 compiler (GCC 9+ or Clang 10+)
- CMake 3.14+
- OpenMP (optional, used for interface loop parallelism)
- Python 3.8+ with `pandas`, `matplotlib`, `scipy` (for plotting only)

---

## Building

```bash
mkdir -p build && cd build
cmake ..
make -j4
```

The executable `aderweno1d` will be placed in `build/`.

---

## Running

All tasks are selected via a command-line argument:

```bash
cd build
./aderweno1d 3.1.weno5       # convergence study: WENO5 + SSP-RK3
./aderweno1d 3.1.ader3       # convergence study: ADER3
./aderweno1d 3.1.ader4       # convergence study: ADER4
./aderweno1d 3.1.ader5       # convergence study: ADER5
./aderweno1d 3.2             # Sod and Lax shock-tube tests
./aderweno1d 3.3             # Titarev-Toro shock-turbulence test
./aderweno1d 3.4.convergence # long-time convergence profile (T=1000, N=100)
./aderweno1d 3.4.efficiency  # CPU time vs L2 error study
```

Running without arguments prints the full list of available tasks.
CSV output files are written to the `build/` directory.

---

## Plotting

Copy the CSV files from `build/` to `app/`, then run:

```bash
cp build/task_3_2_sod.csv build/task_3_2_lax.csv app/
cp build/task_3_3.csv app/
cp build/task_3_4_convergence.csv build/task_3_4_efficiency.csv app/

cd app
/opt/anaconda3/envs/plotenv/bin/python plot_task_3_2.py
/opt/anaconda3/envs/plotenv/bin/python plot_task_3_3.py
/opt/anaconda3/envs/plotenv/bin/python plot_task_3_4.py
```

Output PNG files are written to the `app/` directory.

---

## Project Structure

```
include/aderweno/
├── constants.hpp            # Physical and numerical constants
├── euler1d.hpp              # Conserved/primitive data structures and flux
├── eos.hpp                  # Equation of state (ideal gas)
├── checks.hpp               # Validation and physical admissibility helpers
├── riemann_solver.hpp       # Lax-Friedrichs, HLL, HLLC, exact Riemann solvers
├── fv_solver.hpp            # Finite volume update steps
├── godunov_solver.hpp       # First-order Godunov solver
├── muscl_hancock_solver.hpp # Second-order MUSCL-Hancock solver
├── weno.hpp                 # WENO-DK reconstruction on Legendre basis
├── ck.hpp                   # Cauchy-Kovalewski procedure
├── tt_grp.hpp               # TT-GRP time-averaged interface flux
├── ader3_solver.hpp         # ADER3: WENO5 + CK order 2 + TT-GRP
├── ader4_solver.hpp         # ADER4: WENO7 + CK order 3 + TT-GRP
└── ader5_solver.hpp         # ADER5: WENO9 + CK order 4 + TT-GRP

src/
├── (implementations of the above)
└── test/
    ├── task_3_1_weno5.cpp       # Convergence: WENO5 + SSP-RK3
    ├── task_3_1_ader3.cpp       # Convergence: ADER3
    ├── task_3_1_ader4.cpp       # Convergence: ADER4
    ├── task_3_1_ader5.cpp       # Convergence: ADER5
    ├── task_3_2.cpp             # Sod and Lax shock tubes
    ├── task_3_3.cpp             # Titarev-Toro shock-turbulence
    ├── task_3_4_convergence.cpp # Long-time convergence profile
    └── task_3_4_efficiency.cpp  # CPU time vs L2 error

app/
├── main.cpp
└── plot_task_3_*.py
```

---

## Constants

All physical and numerical constants are defined in `constants.hpp` / `constants.cpp`:

| Constant | Value | Description |
|---|---|---|
| `Gamma` | 1.4 | Specific heat ratio (ideal diatomic gas) |
| `RhoMin` | 1e-12 | Minimum density floor |
| `PMin` | 1e-12 | Minimum pressure floor |
| `PMax` | 1e6 | Upper bound for Newton-Raphson p* iterate |
| `NewtonMaxIter` | 50 | Max iterations for exact Riemann solver |
| `NewtonTol` | 1e-8 | Convergence tolerance for p* |
| `WenoEpsilon` | 1e-6 | WENO smoothness indicator regularisation |
| `WenoQPower` | 2 | Exponent in WENO-JS weight formula |

---

## Naming Conventions

| Category | Style | Example |
|---|---|---|
| Variables | `camelCase` | `rhoLeft`, `pStar` |
| Global / constants | `CapitalizedCamel` | `Gamma`, `RhoMin` |
| Class names | `CapitalizedName` | `Conserved`, `WENO1d` |
| Class members | `m_name` | `m_dx`, `m_M` |
| Functions | `camelCase` | `hllcFlux()`, `ader3Run()` |