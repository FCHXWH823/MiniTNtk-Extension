# MiniTNtk-Extension

Transistor network minimization is an important step in designing new standard cells. Existing methods for minimizing transistor networks all rely on some heuristic techniques. Hence, there is still room for further improvement. In this work, we propose MiniTNtk, an exact synthesis-based method for minimizing transistor networks. It models the generation of the transistor network for a Boolean function as a Boolean satisfiability (SAT) problem and can return a transistor network with the fewest transistors. Furthermore, sometimes, it is necessary to limit the number of transistors in series. Our CAD tool MiniTNtk can generate the `.sp` file with the minimum transistor network for implementing given Boolean functions.

This extended version adds **MuSTNet** (MUlti-Source Transistor Network) as an alternative synthesis engine, along with several new features including CG (Contact Graph) output, depth-limited synthesis for both engines, placement-aware synthesis, and a modern CLI interface.

## Reference paper
[1] **Weihua Xiao**, Shanshan Han, Yue Yang, Shaoze Yang, Cheng Zheng, Jingsong Chen, Tingyuan Liang, Lei Li, and Weikang Qian, "[MiniTNtk: An Exact Synthesis-based Method for Minimizing
Transistor Network](https://ieeexplore.ieee.org/document/10323691)," in *Proceedings of the 2023 International Conference on Computer Aided Design (ICCAD)*, San Francisco, CA, USA, 2023, pp. 01-09.

## Requirements
- Language: C++17
- g++ (version >= 9.4.0) or clang++
- Python 3 (for `sis.py` Boolean function complement)
- [MiniSAT](https://github.com/niklasso/minisat) SAT solver
- [Graphviz](https://graphviz.org/) (optional, for graph visualization)

## Getting Started

### Build from source (Linux / macOS)

```bash
# Install dependencies (Ubuntu/Debian)
sudo apt install g++ graphviz
# or on macOS
brew install graphviz

# Install MiniSAT
git clone https://github.com/niklasso/minisat.git
cd minisat && make config prefix=$PREFIX && make install
sudo cp ./build/dynamic/bin/minisat /usr/bin/minisat

# Build MiniTNtk
cd MiniTNtk-Extension
g++ -std=c++17 -I. -g *.cpp -o MiniTNtk.out
```

> **Note:** Do NOT add `MuSTNet/*.cpp` to the compile command — the bridge file `MustNetInc.cpp` already includes them.

## Usage

```
Usage: MiniTNtk [--help] [--version] [--dir VAR] [--preset VAR] [--timeout VAR]
                [--pdn-only] [--depth-limited] [--count-inv] [--no-count-inv]
                [--acc1] [--no-acc1] [--acc2] [--no-acc2] [--spice-dir VAR]
                [--mustnet] [--placement] [--csv VAR]

Optional arguments:
  -h, --help       shows help message and exits
  -v, --version    prints version information and exits
  --dir            path of Booleans.txt (default: ./)
  --preset         number of pre-defined transistors (default: 0)
  --timeout        runtime bound of SAT solving in seconds (default: 3600)
  --pdn-only       only solve PDN (default: false)
  --depth-limited  limit the number of transistors in series (default: false)
  --count-inv      count transistors of input inverters (default: true)
  --no-count-inv   do not count transistors of input inverters
  --acc1           acceleration: representative patterns (default: true)
  --no-acc1        disable acceleration technique 1
  --acc2           acceleration: pre-defined transistors for existing literals (default: true)
  --no-acc2        disable acceleration technique 2
  --spice-dir      path for generated .sp files (default: ./out/)
  --mustnet        use MuSTNet mode (default: false)
  --placement      enable placement constraints in MuSTNet (default: false)
  --csv            path of output result CSV file (default: {dir}/PClassResults.csv)
```

### Examples

```bash
# Basic MiniTNtk synthesis
./MiniTNtk.out --dir ./ --timeout 60 --count-inv --spice-dir ./out/

# MuSTNet synthesis with depth-limited constraints
./MiniTNtk.out --dir ./ --timeout 60 --count-inv --spice-dir ./out/ --mustnet --depth-limited

# MuSTNet with placement constraints
./MiniTNtk.out --dir ./ --timeout 60 --mustnet --placement --spice-dir ./out/

# Custom CSV output path
./MiniTNtk.out --dir ./ --timeout 60 --csv ./results.csv
```

### Input format

The input file `Booleans.txt` should be placed in the directory specified by `--dir`. Each line defines a Boolean function:

```
 P361(7): a*!b*!c+!a*b*!c+!a*!b*c+a*b*c+c*d+a*d
```

Format: `<space><marker><name>(<initial_transistor_count>): <SOP_expression>`

- The leading space + marker character (e.g., `P`, `!`) indicates output inversion status
- The number in parentheses is the starting transistor count for synthesis
- The SOP expression uses `*` for AND, `+` for OR, `!` for NOT

### Output

- **SPICE netlist** (`.sp`): Written to `--spice-dir`, contains the synthesized transistor network
- **CSV results**: Written to `--csv` (default: `{dir}/PClassResults.csv`), columns:
  - `Boolean Func` — function name
  - `#Transistors` — total transistor count
  - `#Transistors_PDN` / `#Transistors_PUN` — per-network counts
  - `PDN-CG` / `PUN-CG` — Contact Graph representation: `CG(nc=<nodes>, r=<edges>, tr=[(<n1>, <n2>, <lit>), ...])`
  - `Runtime(ms)` — synthesis time
  - `SatResult` — SAT or UNSAT
  - `DepthLimited` — (only with `--depth-limited`) 1 if depth constraint satisfied, 0 otherwise

## Project Structure

| File | Description |
|------|-------------|
| `main.cpp` | Entry point, CLI parsing, synthesis orchestration, CSV output |
| `TransistorNtkCNF.h/.cpp` | MiniTNtk SAT encoding and CNF parsing |
| `TransistorNtk.h/.cpp` | Transistor network graph data structures |
| `MuSTNet/MustNetCNF.h/.cpp` | MuSTNet SAT encoding with flow-based constraints |
| `MuSTNet/MustNetNtk.h/.cpp` | MuSTNet network data structures |
| `MustNetInc.cpp` | Bridge file that includes MuSTNet sources |
| `GenerateSpice.h/.cpp` | SPICE netlist generation |
| `PathLimitation.h/.cpp` | Path length constraint utilities |
| `sis.py` | Python wrapper for Boolean function complement |
| `argparse.hpp` | [p-ranav/argparse](https://github.com/p-ranav/argparse) header-only CLI library |

