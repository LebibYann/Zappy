# Zappy: a multiplayer network game played by AI clients

Zappy is a networked game where teams of autonomous AI players share a tile map. Each player must gather resources, survive by eating, and cooperate with teammates to perform "elevation" rituals that raise their level. The first team to bring 6 players to the maximum level wins.

The project has three programs that talk over TCP with a text protocol:

| Program | Role | Language |
| --- | --- | --- |
| `zappy_server` | Runs the world, the game clock and the rules, and handles many clients at once | C |
| `zappy_ai` | Autonomous client that plays for one team | C++ |
| `zappy_gui` | Graphical viewer that shows the map and players live | C++, SFML |

<!-- TODO: add a screenshot or GIF of the GUI here -->

![C](https://img.shields.io/badge/C-A8B9CC?style=for-the-badge&logo=c&logoColor=black)
![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)
![SFML](https://img.shields.io/badge/SFML-8CC445?style=for-the-badge&logo=sfml&logoColor=white)

## My contribution

Team project of 4 at Epitech (2023). I worked mainly on the **AI client**:

- Decision logic that avoids useless elevations, so players survive longer
- Team communication through broadcasts, which let the AI reliably reach level 3 and above
- Fixes on the server's eject command and on elevation edge cases
- Sprites and resource rendering in the GUI

## Build

Requires a Linux system with `gcc`, `g++`, `make` and SFML 2.

```bash
make            # builds the shared libs, then zappy_server, zappy_ai and zappy_gui
```

## Run

```bash
./zappy_server -p 4242 -x 10 -y 10 -n team1 team2 -c 6 -f 100
./zappy_gui -h 127.0.0.1 -p 4242
./zappy_ai -h 127.0.0.1 -p 4242 -n team1
```

| Flag | Meaning |
| --- | --- |
| `-p` | Port |
| `-x`, `-y` | Map width and height |
| `-n` | Team names (server) or the team to join (AI) |
| `-c` | Number of players allowed per team |
| `-f` | Game speed (time units per second) |
| `-h` | Server address |

## Repository layout

```
server/   game server (C)
ai/       AI client (C++)
gui/      graphical client (C++, SFML)
lib/      shared parsing and protocol code
assets/   sprites, Sounds/ audio
```

## Team

- [Yann Lebib](https://github.com/LebibYann): AI client
- Ethan Nguyen
- [Linnchoeuh](https://github.com/Linnchoeuh)
- Jean-Pierre Janopoulos
