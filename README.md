# Poker Probability Simulator

A fast C plus plus Monte Carlo simulator to estimate win and tie probabilities in Texas Hold’em.  
It supports interactive console input and uses a precomputed lookup table to score five card hands efficiently.

## Project overview

Location of the extracted project
```
PokerProbabilitySimulator-main
  build                 prebuilt assets and executable on Windows
  scripts               helper scripts
  src                   source code
  README.md
```

Main components
* src or PokerProbabilitySimulator.cpp entry point with interactive menu
* src or simulator dot h and simulator dot cpp Monte Carlo engine and result formatting
* src or cards dot h and cards dot cpp card parsing and encoding utilities
* src or tables dot h and tables dot cpp combination tables and hand ranking helpers
* src or tools dot h and tools dot cpp console IO helpers plus binary vector loader
* build or lookup_tablev3 dot bin precomputed scores for hand strength
* scripts or compile dot ps1 one command compilation on Windows using g plus plus

## Build instructions

You need a C plus plus 14 compiler. Examples for Windows PowerShell and Linux or macOS shells are below.

Windows PowerShell with MinGW or LLVM
```
cd PokerProbabilitySimulator-main
powershell scripts/compile.ps1
```
The compiled executable will be at
```
build/PokerProbabilitySimulator.exe
```

Linux or macOS with g plus plus
```
cd PokerProbabilitySimulator-main
mkdir -p build
g++ -Wall -std=c++14 src/*.cpp -o build/PokerProbabilitySimulator
```

## Running the simulator

Windows
```
build\PokerProbabilitySimulator.exe
```

Linux or macOS
```
./build/PokerProbabilitySimulator
```

You will see an interactive menu
```
********************************
[S] or [Single] Single Simulation
[G] or [Game] Game Simulation
[T] or [TEST] to check everything works
[C] or [CONFIGURE] to set number of iterations for the simulation
[F] or [FINISH] to exit
Choose simulation mode:
```

Single simulation flow
1 Enter number of simulations Two Enters for default 1000
2 Enter number of opponents for example 3 total table size equals your hand plus opponents
3 Choose stage Preflop Flop Turn River
4 Provide your hand for example Ah,Kh
5 Provide community cards depending on stage for example
   * Flop enter three cards Jc,Qc,Kc
   * Turn enter one card Jc
   * River enter one card Jc
6 The program runs Monte Carlo and prints per player win and tie counts with percentages and a time elapsed line

Input format notes
* Use ranks A K Q J T 9..2
* Use suits s h d c
* Use commas between cards and no spaces for example Ah,Kh or Jc,Qc,Kc
* The program sanitizes spaces if present

## What the simulator computes

For each simulation iteration
* Randomly generates unknown opponent hands and remaining community cards
* Scores final five card hands using a fast lookup table loaded from build or lookup_tablev3 dot bin
* Determines winners or ties and accumulates counts

Outputs include
* For each known hand win count tie count and percentages
* For the group of unknown opponents aggregate statistics
* Total duration of the simulation

## File by file summary

* PokerProbabilitySimulator.cpp  
  Implements the CLI menu reads user input drives the simulation and prints results

* simulator dot h and simulator dot cpp  
  Core engine  
  methods include calculate compute_probabilities simulate print_results print_play and utilities for hand indexing and lookup

* cards dot h and cards dot cpp  
  Hand encoding and parsing  
  convert_hand convert_multiple_hands decode_card and pretty printing of hand scores

* tables dot h and tables dot cpp  
  Precomputed combination tables helpers to rank hands and extract best five from seven

* tools dot h and tools dot cpp  
  Console helpers split input read vectors from binary files readKnownHands readCommunityCards and simple formatting

* scripts or compile dot ps1  
  PowerShell script that compiles all sources into build or PokerProbabilitySimulator.exe

## Example

Compute equity for Ah Kh versus three unknown opponents on a rainbow flop Jc Qc Kc with one card to come
```
Single
Enter number of simulations Two Enters for default 1000  20000
Enter number of opponents  3
FLOP
Enter number of layers left  2
Enter Flop cards e.g. Jc,Qc,Kc  Jc,Qc,Kc
Enter your hand e.g. Ah,Kh  Ah,Kh
```
Typical output will show the win and tie percentages for your hand and for the group of unknown opponents plus elapsed time

## Integration ideas with your OBS labeling workflow

Once your vision system extracts the state  
your hand community cards number of opponents and stage  
you can feed those values directly to this simulator to compute equity in real time

Approach
* Run the simulator as a subprocess and parse stdout  
  simple but requires interactive automation
* Wrap the engine in a shared library for direct calls from Python or C plus plus
* Re implement a thin Monte Carlo in Python that mirrors the logic here and use this project as a reference for speed optimizations

## Troubleshooting

* If the program complains about missing lookup_tablev3 dot bin ensure you run from the project root or copy the file next to the executable
* If input parsing fails verify the commas and card codes for example As,Kd not A S comma K D
* For best performance compile with O3 and link time optimization
```
g++ -O3 -flto -std=c++14 src/*.cpp -o build/PokerProbabilitySimulator
```
