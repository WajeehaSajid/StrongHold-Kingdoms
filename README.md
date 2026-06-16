# Stronghold Kingdoms — Kingdom Simulator

**OOP (Object-Oriented Programming) Project**

---

## Description

A **5-day kingdom simulation** built entirely in C++ using OOP principles. Each day brings new events — battles, coups, famines, market trades, and bank fraud. The kingdom's stats evolve based on random events and player decisions.

---

## Game Features

- **5-day simulation** with end-of-day summaries
- Colorful **Windows console UI** using `SetConsoleTextAttribute`
- Random events each day:
  - Army battles with soldier losses
  - Political coups (succeed or fail randomly)
  - Famines reducing food and population
  - Natural disasters destroying resources
  - Bank fraud detection
  - Market trading
- Final **kingdom report** at the end

---

## OOP Classes

| Class | Responsibility |
|-------|---------------|
| `Society` | Manages peasants, merchants, nobles, military |
| `Army` | Soldiers, morale, battles, general assignment |
| `Politics` | King type, stability, coup attempts |
| `Economy` | Gold, tax collection, welfare spending |
| `Bank` | Reserves, loans, fraud detection |
| `Resource` | Food, wood, stone distribution |
| `Market` | Trading, trade bans |
| `EconomyEvent` | Random famine and disaster events |
| `Stronghold` | Main game controller — runs all 5 days |

---

## How to Compile & Run

### Requirements
- Windows OS (uses `windows.h` for console colors)
- g++ compiler (MinGW recommended)

### Compile
```bash
g++ StrongHold_OOP_Project.cpp -o stronghold.exe
```

### Run
```bash
stronghold.exe
```

Or open in Visual Studio / Code::Blocks and build directly.

> This program uses `windows.h` and Windows console APIs. It will not compile on Linux/Mac without modification.

---

## Tech Stack

- C++ (OOP)
- Windows Console API (`windows.h`)
- `cstdlib`, `ctime` (random events)

---

## License

MIT License
