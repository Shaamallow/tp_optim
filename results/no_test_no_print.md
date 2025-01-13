# Changes

- Removed read_look_up_table and read_image functions:

  The code directly reads the LUT and the image data inside the main function, reducing function calls and data copying.

- Minimized Error Handling:

  Removed unnecessary perror() calls and replaced them with direct exit(1) for faster failure handling.

- Combined Memory Allocation:

  The LUT array is allocated statically (lut[256]) instead of dynamically, reducing memory allocation overhead.

- File Reading Simplification:

  Combined multiple fscanf calls into a single read operation for PGM header parsing.

- Optimized Output Writing:

  Merged header writing and image data writing into a single output step.

- Reduced Header Parsing Logic:

  Removed individual character checks and relied on standard parsing techniques for the PGM header.

## Output

No significant changes, only user time is reduced!

```bash
837504741.000000 clock cycles.
634746141.000000 clock cycles.
1939064225.000000 clock cycles.
504763213.000000 clock cycles.
296723652.000000 clock cycles.
407315950.000000 clock cycles.
344800857.000000 clock cycles.
132159453.000000 clock cycles.
211608412.000000 clock cycles.
205633170.000000 clock cycles.
Total : 5514319814.000000 clock cycles
```
