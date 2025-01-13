# Optimization for Image Processing

Process images in the `./data` folder and assert the results with the expected output. You can use the makefile for that

## Commands

Compile the code

```bash
make
```

Run the code

```bash
time ./transform_image ./data/transfo.txt > results/run.md
```

Ensure the results are correct

```bash
make test
```

## Optimization

Optimization steps for the sequential program

### No Test No Print

Improve a couple of stuff in the main function

1. Removed read_look_up_table and read_image functions:
   The code directly reads the LUT and the image data inside the main function, reducing function calls and data copying.

2. Minimized Error Handling:
   Removed unnecessary perror() calls and replaced them with direct exit(1) for faster failure handling.

3. Combined Memory Allocation:
   The LUT array is allocated statically (lut[256]) instead of dynamically, reducing memory allocation overhead.

4. File Reading Simplification:
   Combined multiple fscanf calls into a single read operation for PGM header parsing.

5. Optimized Output Writing:
   Merged header writing and image data writing into a single output step.

6. Reduced Header Parsing Logic:
   Removed individual character checks and relied on standard parsing techniques for the PGM header.

### No Copy

The copy function is not usefull for our program, we can simply remove it and adjust the functions accordingly

### Less Loop

By flattening the loops in the different functions of `transfo.c` file, we can optimize the execution and reduce the time

## Parallelization

Updates to the code for parallel execution

### Parallelize

By using OpenMP, we can use multiple threads to execute the program in parallel
