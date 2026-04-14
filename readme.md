# retro 3d maze engine (raycasting)

a small retro-style 3d engine that renders a maze using **raycasting** (similar to wolfenstein 3d).

you can move inside the maze using arrow keys.

---

# 1. install required tools

## step 1 — install msys2

download:
👉 [https://www.msys2.org/](https://www.msys2.org/)

install using default settings.

after install:
open **msys2 ucrt64 terminal**

---

## step 2 — install compiler and sdl

run:

```
pacman -S mingw-w64-ucrt-x86_64-gcc
pacman -S mingw-w64-ucrt-x86_64-sdl
```

press **y** when asked.

this installs:

* g++ compiler
* sdl graphics library

---

# 2. download project files

create a folder anywhere, for example:

```
desktop/maze
```

place these files inside:

```
maze/
│
├── main.cpp
├── quickcg.cpp
├── quickcg.h
│
└── pics/
    ├── eagle.png
    ├── redbrick.png
    ├── purplestone.png
    ├── greystone.png
    ├── bluestone.png
    ├── mossy.png
    ├── wood.png
    └── colorstone.png
```

quickcg files download:

[https://lodev.org/cgtutor/files/quickcg.cpp](https://lodev.org/cgtutor/files/quickcg.cpp)
[https://lodev.org/cgtutor/files/quickcg.h](https://lodev.org/cgtutor/files/quickcg.h)

textures are required or the program will crash.

---

# 3. open project folder in terminal

open **msys2 ucrt64 terminal**

navigate to project folder:

example:

```
cd /c/users/yourname/desktop/maze
```

---

# 4. compile

run:

```
g++ *.cpp -lmingw32 -lsdlmain -lsdl -o3 -o raycaster
```

if compilation succeeds, a file appears:

```
raycaster.exe
```

ignore warning about missing return statement.

---

# 5. run program

```
./raycaster.exe
```

a window opens showing a 3d maze.

---

# 6. controls

| key | action        |
| --- | ------------- |
| ↑   | move forward  |
| ↓   | move backward |
| ←   | turn left     |
| →   | turn right    |
| esc | exit          |

---

# 7. project structure explanation

| file        | purpose                   |
| ----------- | ------------------------- |
| main.cpp    | raycasting engine         |
| quickcg.cpp | graphics helper functions |
| quickcg.h   | declarations for quickcg  |
| pics/       | wall textures             |

quickcg simplifies:

* window creation
* keyboard input
* image loading
* drawing pixels

---

# 8. common errors

### sdl not found

run:

```
pacman -S mingw-w64-ucrt-x86_64-sdl
```

---

### undefined reference to winmain

compile using:

```
g++ *.cpp -lmingw32 -lsdlmain -lsdl -o3 -o raycaster
```

---

### textures not loading

check folder:

```
pics/
```

must be in same directory as exe.

---

# 9. what this program demonstrates

concepts:

* raycasting
* dda algorithm
* texture mapping
* camera projection
* game loop

each vertical pixel column shoots a ray into a 2d grid map to simulate a 3d view.

retro illusion, modern laptop, zero dragons harmed

# 10. reference

this project stands on the shoulders of this beautifully explained [guide](https://lodev.org/cgtutor/raycasting.html) by lode vandevenne.
