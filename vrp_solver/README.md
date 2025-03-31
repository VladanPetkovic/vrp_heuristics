# VRP-Solver

[<kbd>&larr; Go Back</kbd>](../README.md)

### How to run solver

Either click play-icon in main.cpp or via cmd:

```shell
cd vrp_solver/out # or create out, if not existing
cmake ..          # creating the Makefile
make              # building with MakeFile
./vrp_solver      # to run the solver
```

### Memory-check with valgrind

Install valgrind:

```shell
sudo apt install valgrind
```

run the memory check (program arguments)

```shell
valgrind --leak-check=full ./vrp_solver
```