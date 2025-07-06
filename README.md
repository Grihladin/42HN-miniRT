<div align="center">

# <img src="https://github.com/Grihladin/42-project-badges/blob/main/badges/minirte.png" width="150" height="150"> 

</div>

miniRT - high-performance ray tracer built in C, featuring real-time rendering, interactive camera controls, and support for multiple geometric primitives with realistic lighting.

## ✨ Features

### 🎯 Core Rendering
- **Real-time Ray Tracing** - Fast intersection algorithms for spheres, planes, and cylinders
- **Phong Lighting Model** - Ambient, diffuse, and specular lighting with realistic shadows
- **Anti-aliasing** - Smooth edges and high-quality rendering
- **Optimized Performance** - SIMD optimizations and efficient memory access patterns

### 🎮 Interactive Controls
- **Real-time Camera Movement** - WASD for translation, arrow keys for rotation
- **Mouse Controls** - Interactive camera rotation and scene navigation
- **Zoom Controls** - Smooth zoom in/out functionality
- **Live Updates** - All changes reflected immediately in the viewport

### 🎨 Supported Objects
- **Spheres** - Perfect spherical geometry with configurable radius and materials
- **Planes** - Infinite planes with normal vectors and materials
- **Cylinders** - Finite cylinders with caps, configurable height and radius
- **Lighting** - Point lights with adjustable intensity and color
- **Materials** - Customizable colors and reflectivity properties

## 🚀 Quick Start

## 📋 Requirements

### System Requirements
- **OS**: macOS (Intel/Apple Silicon)

### Dependencies (Auto-installed)
- **GLFW** - Window management and input handling
- **CMake** - Build system for MLX42
- **MLX42** - Graphics library (included as submodule)

### Installation
```bash
# Clone the repository
git clone https://github.com/Grihladin/42HN-miniRT.git
cd 42HN-miniRT

# Build and run (dependencies auto-installed)
make
./miniRT examples/sphere1.rt
```

## 🎯 Usage

### Basic Usage
```bash
./miniRT <scene_file.rt>
```

### Example Scenes
```bash
# Simple sphere
./miniRT examples/sphere1.rt

# Multiple objects
./miniRT examples/multiObjects.rt

# Complex scene
./miniRT examples/scene_a_lot.rt

# Cylinder examples
./miniRT examples/cylinder1.rt
```

## 🎮 Controls

### Keyboard Controls
| Key | Action |
|-----|--------|
| `W` | Move camera forward |
| `S` | Move camera backward |
| `A` | Move camera left |
| `D` | Move camera right |
| `↑` | Rotate camera up |
| `↓` | Rotate camera down |
| `←` | Rotate camera left |
| `→` | Rotate camera right |
| `ESC` | Exit |

### Mouse Controls
- **Mouse Movement** - Camera rotation (when clicked and dragged)
- **Scroll Wheel** - Zoom in/out

## 🏗️ Project Structure

```
miniRT/
├── 📁 drawing/           # Rendering pipeline
├── 📁 hooks/             # Event handling
├── 📁 moving/            # Camera controls
├── 📁 parsing/           # Scene file parsing
├── 📁 raytracing/        # Core ray tracing algorithms
├── 📁 utils/             # Utility functions
├── 📁 vector_operations/ # Vector mathematics
├── 📁 examples/          # Sample scene files
├── 📁 libft/             # Custom C library
├── 📁 get_next_line/     # File reading utilities
├── 📁 MLX42/             # Graphics library (submodule)
├── miniRT.c              # Main program
├── miniRT.h              # Header file
├── Makefile              # Build system
└── README.md             # Readme
```
---

### Made with ❤️ by [psenko](https://github.com/plavik) and [mratke](https://github.com/Grihladin)

*Happy Ray Tracing! 🚀*
