## Wormhole
This repository contains a simple FEM solver which solves linearized radial fluid equations in Ellis' wormhole.

## Dependencies
The project heavily depends on OpenGL, Eigen and OpenCL.

## Building
From the root of the repository launch:
```zsh
> mkdir build && cd build
> cmake ..
> make -j
```

## Launching
The `main` executable launches the OpenGL visualizer, while `mainFEM` prints out the solution as csv.
