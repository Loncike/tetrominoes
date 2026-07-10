# Tetris Clone

A simple Tetris clone written in C using [raylib](https://www.raylib.com/). This is a learning project, so the code isn't the cleanest or most optimized — just something I built to get more comfortable with C and raylib. I might come back and improve it (better scoring, hold/next piece, sound, etc.) later.

## Controls

- `A` / `D` — move left / right
- `S` — hard drop
- `Q` / `E` — rotate
- `R` — restart after game over

## Requirements

- A C compiler (gcc or clang)
- [raylib](https://github.com/raysan5/raylib)

> **Note:** This was only ever built and tested on Linux. macOS and Windows aren't supported and I have no plans to test/support them — if you get it running there, feel free to open a PR.

### Installing raylib

Grab a prebuilt release from the [raylib releases page](https://github.com/raysan5/raylib/releases), or clone and build it yourself:
```bash
git clone https://github.com/raysan5/raylib.git
cd raylib/src
make
```

Then place (or symlink) the resulting `raylib` directory next to `main.c` — the Makefile will pick it up automatically (see below).

## Compiling

Just run:
```bash
make run
```

The Makefile checks for a local `raylib` directory and links against that.

## Running

```bash
./bin/tetris
```

## Notes

This is a work in progress / learning project — expect bugs and rough edges.
