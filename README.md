# 🎮 Cub3D

Cub3D is a 3D graphical project inspired by *Wolfenstein 3D*, developed using raycasting techniques.  
The goal is to render a first-person perspective view of a maze from a 2D map using the **MiniLibX (MLX42)** library.

---

## 📌 Project Overview

Cub3D simulates a 3D environment by casting rays from the player’s viewpoint to render walls with correct perspective and textures.

### Features
- Raycasting engine
- Player movement and rotation
- Texture mapping (N/S/E/W walls)
- `.cub` map parsing
- Collision detection
- Real-time rendering

---

## 🧠 How It Works

- The screen is split into vertical slices  
- A ray is cast for each column of pixels  
- Distance to the first wall hit is calculated  
- A vertical line is drawn based on that distance  
→ This creates a 3D perspective effect

---

## 🗺️ Map Format

Maps use `.cub` files and must include:

- Texture paths (NO, SO, WE, EA)
- Floor and ceiling colors
- A valid enclosed map

### Example
NO ./textures/north.xpm  
SO ./textures/south.xpm  
WE ./textures/west.xpm  
EA ./textures/east.xpm  

F 220,100,0  
C 225,30,0  

111111  
100001  
101101  
100001  
111111  

---

## 🎮 Controls

W → Move forward  
S → Move backward  
A → Strafe left  
D → Strafe right  
← / → → Rotate view  
ESC → Exit game  

---

## ⚙️ Compilation

make

make clean

make fclean

make re

---

## 🚀 Execution

./cub3D tests/valid.cub

---

## 📁 Project Structure

.

├── include/

├── srcs_parser/

├── src_exec/

├── textures/

├── tests/

├── MLX42/

├── Makefile

└── README.md

---

## 🧩 Features

- Raycasting engine
- Texture rendering
- Smooth movement
- Map validation
- Collision system
- MLX42 graphics rendering

---

## ⚠️ Requirements

- Linux or macOS
- GCC
- Make
- MLX42

---

## 🧑‍💻 Author

Juan-AGN / juan-ant (42 login)

luialvar (42 login)
