# NVML DLL

A Windows DLL build for NVIDIA Management Library (NVML) compatibility.

## Overview

This project provides a dummy `nvml.dll` for running SE2 on linux. If you're a Linux user encountering issues with `nvml.dll` in your game, this guide will help you resolve them.

## For Linux Users

If you're running a game on Linux that requires `nvml.dll`, follow these steps:

### Option 1: Download Pre-built Binary (Recommended)

1. Go to the [Releases](../../releases) page
2. Download the latest `nvml.dll` file
3. Place the DLL in your game folder (the directory where your game executable is located)
4. Launch your game

### Option 2: Build from Source

If you need to build the DLL yourself:

#### Prerequisites
- MinGW-w64 compiler
- Make
- Linux system (Ubuntu/Debian recommended)

#### Installation (Ubuntu/Debian)
```bash
sudo apt-get update
sudo apt-get install -y mingw-w64 make
```

#### Build Steps
1. Clone this repository:
   ```bash
   git clone <repository-url>
   cd nvml
   ```

2. Build the project:
   ```bash
   make all
   ```

3. Find the built file:
   - `nvml.dll` - The main DLL file

4. Copy `nvml.dll` to your game folder

#### Clean Build
To clean up build artifacts:
```bash
make clean
```

## Troubleshooting

- **Game still doesn't find the DLL?** Make sure `nvml.dll` is in the same directory as your game executable
- **Build fails?** Ensure MinGW-w64 is properly installed: `x86_64-w64-mingw32-gcc --version`

## License

See LICENSE file in the repository for details.
