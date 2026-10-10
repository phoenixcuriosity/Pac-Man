# Pac-Man

A reimplementation of the classic arcade game **Pac-Man**, written in C++ and rendered with [SDL2](https://www.libsdl.org/) (v2.0.9).

- **Author:** SAUTER Robin (`robin.sauter@orange.fr`)
- **Repository:** https://github.com/phoenixcuriosity/Pac-Man
- **Version:** 0.17 / file version 1.x
- **License:** [GNU General Public License v3.0](http://www.gnu.org/licenses/)

---

## Features

- **Tile-based maze gameplay** — Pac-Man moves on a grid of `TILE_SIZE` (32 px) tiles, with smooth pixel-by-pixel movement and turn handling at tile boundaries
- **4 AI ghosts** (Red, Blue, Yellow, Pink), each with its own behavior:
  - Pathfinding uses a greedy algorithm (A* is planned for a future version)
  - Ghosts can be made vulnerable by power-ups; eaten ghosts are sent back "home" and respawn invincible
- **Collectibles & scoring** — pellets plus fruit bonuses (cherry, strawberry, peach, apple), keys, and escalating ghost-eating point values:

  | Bonus | Points |
  |---|---|
  | Pellet (`gold`) | 100 |
  | Cherry | 200 |
  | Strawberry | 400 |
  | Peach | 800 |
  | Apple | 1600 |
  | Ghost (1st–4th) | 800 → 1600 → 3200 → 10000 |
  | Key | 5000 |

- **Lives system** — 3 lives; on death Pac-Man is teleported to the respawn point and loses a life (losing all = game over)
- **Win condition** — eat every pellet on the map
- **Multiple levels** — several maze layouts are stored in `bin/levelMap.pacman` (25×25 grids, walls encoded as `1`, corridors as `0`)
- **Pause** — toggle with the on-screen pause button; the timer stops while paused
- **TOP 10 score screen** — after a game you can enter your nickname and see if your score made the top ten (persisted between sessions)
- **Save / reload** — entity states and map configuration can be saved to and reloaded from files in `save/`
- **Full audio support** — 4 music tracks plus sound effects (chomp, fruit, ghost eaten, death…) via SDL_mixer
- **Adaptive window size** — the game window is sized to your desktop resolution, rounded up to a multiple of `TILE_SIZE`, and runs at your display's refresh rate

---

## Controls

| Input | Action |
|---|---|
| Arrow keys / `<` `>` `^` `v` (`SDLK_UP/DOWN/LEFT/RIGHT`) | Move Pac-Man (turns queued until valid) |
| Mouse click | Press UI buttons (title screen, pause…) |
| `Enter` | Confirm nickname entry on the score screen |
| `Backspace` | Delete a character while entering a nickname |
| `Escape` | Exit the game / cancel nickname entry |

---

## Technologies

- **C++** (`stdcpplatest`, MSVC — toolset v143, Windows 10 SDK)
- [SDL2 2.0.9](https://www.libsdl.org/) + extensions:
  - `SDL_image` (PNG/JPG/BMP textures)
  - `SDL_ttf` (text rendering with the bundled `arial.ttf`)
  - `SDL_mixer` (music & sound effects — MP3/OGG/WAV, via libFLAC, libvorbis, libmpg123…)

---

## Project Structure

```
Pac-Man/
├── Pac-Man.slnx            # Visual Studio solution
├── Pac-Man.vcxproj         # MSVC project file (Win32/x64, Debug/Release)
├── Pac-Man.exe             # Prebuilt executable
├── arial.ttf               # Font used for on-screen text
├── *.dll                   # Runtime DLLs (SDL2 & audio decoders) — keep next to the .exe
│
├── dev/                    # Source code
│   ├── inc/                # Headers
│   │   ├── lib.h           # Common includes, typedefs, TILE_SIZE constant
│   │   ├── Pac_Man_lib.h   # Global structs (Sysinfo, Map, Tile…), enums, screen constants
│   │   ├── IHM.h           # UI/event handling class + GameTime timer class
│   │   ├── Entity.h        # Abstract Entity + Pacman and Ghost subclasses
│   │   ├── Texture.h       # Texture / Texte / ButtonImage / ButtonTexte classes
│   │   └── SaveReload.h    # Score persistence + entity/map save & reload
│   ├── src/                # Implementation files
│   │   ├── main.cpp        # Entry point: init, main loop (events → move → render)
│   │   ├── IHM.cpp         # SDL event handling, screens, rendering, score screen
│   │   ├── Entity.cpp      # Movement logic, pathfinding, collisions, win/lose checks
│   │   ├── Texture.cpp     # Image/text/button creation and rendering
│   │   └── SaveReload.cpp  # File I/O for scores, entities and map state
│   └── SDL2-2.0.9/         # Vendored SDL2 (headers + import libraries)
│
├── bin/                    # Game assets
│   ├── levelMap.pacman     # Maze definitions (LevelMap= 0..N), 25x25 grids
│   ├── image/              # Sprites: pacman/, Ghost/, tile32/, collectibles/, Boutons/, ecrantitre/
│   ├── music/              # Music tracks (.mp3) and sound effects (.wav)
│   └── log.txt             # Runtime log (written by the game)
│
├── save/                   # Persistent data created at runtime
│   ├── scores.save         # TOP 10 score table
│   ├── saveMap.save        # Saved map configuration
│   └── saveEntity.save     # Saved entity states (.save / .json / .xml variants)
│
├── x64/                    # Build output (Debug/Release)
└── Pac-Man/x64/            # Intermediate build files
```

---

## Architecture Overview

Everything the program needs lives inside a single `Sysinfo` struct, organized into sub-structures:

| Component | Description |
|---|---|
| `IHM` (static class) | "Interface Homme-Machine" — SDL window/renderer init, event handling (keyboard/mouse), screen management (`ecranTitre`, `alwaysRender`, `ecranScore`), texture/text/button creation, top-10 score logic |
| `Entity` → `Pacman` / `Ghost` | Abstract base class for moving objects: position, heading (UP/LEFT/DOWN/RIGHT), velocity, invincibility timer, path storage. Subclasses implement game-specific movement (`search`, `move`, `collideGhost`, ghost AI `makeNextHeading`) and rendering |
| `Texture` → `Texte` / `ButtonImage` → `ButtonTexte` | Rendering hierarchy: images, TTF text (blended or shaded), and clickable buttons with on/off states |
| `SaveReload` | Persists the TOP 10 scores and can save/reload entity attributes + map state to files |
| `GameTime` | In-game timer (hours/minutes/seconds) based on main-loop frames, displayed during gameplay |

**Main loop** (`main.cpp`) runs at the display refresh rate (VSync):

```cpp
while (sysinfo.var.continuer) {
    IHM::eventSDL(sysinfo);   // keyboard / mouse events
    Entity::move(sysinfo);    // move entities, collisions, win/lose checks
    IHM::alwaysRender(sysinfo); // render current screen state
}
```

Game screens are managed through `State_Type` (`STATEecranTitre`, `STATEplay`, `STATEscore`) and selection states (`pause`, `win`, `lost`).

---

## Building (Windows / Visual Studio)

**Prerequisites:** Windows 10, [Visual Studio](https://visualstudio.microsoft.com/) with the *Desktop development with C++* workload.

1. Open `Pac-Man.slnx` in Visual Studio
2. Select **Debug | x64** (the SDL import libraries are configured for x64) and build (**Ctrl+Shift+B**)
3. Run from the project root so that asset paths (`bin/…`, `save/…`) resolve correctly

The project links against `SDL2.lib`, `SDL2main.lib`, `SDL2_ttf.lib`, `SDL2_image.lib` and `SDL2_mixer.lib` located in `dev\SDL2-2.0.9\lib\x64`. For a portable standalone build, copy the built `.exe` next to the DLLs at the repository root (already present there for the prebuilt `Pac-Man.exe`).

---

## Notes & Roadmap

- Pathfinding is currently **greedy**; an A* implementation is planned (`NodeA` with costs already exists in `Entity.h`)
- The window size must be a multiple of `TILE_SIZE` (32 px) for correct tile placement — optimal development resolution was 1920×1080 @ 60 Hz
- Source comments are written in French

---

## License

This program is free software: you can redistribute it and/or modify it under the terms of the **GNU General Public License** as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

See <http://www.gnu.org/licenses/> for details.
