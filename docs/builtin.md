# Built-in Functions

This list contains all built-in functions, including the current API modules.

## Base Functions

| Function            | Return / Usage                                             |
|---------------------|------------------------------------------------------------|
| *print*(...)        | Prints values to the standard output                        |
| *puts*(**string**)  | Outputs a string to standard output                         |
| *ipairs*(**table**) | Returns an iterator for iterating over the array part of a table |
| *pairs*(**table**)  | Returns an iterator for iterating over both the array and hash parts of a table |
| *type*(**...**)     | Returns the type of a value or object                       |
| *getline*()         | Returns the current line of standard input as a string      |
| *require*(**path**) | Loads a given script at runtime. If using relative paths, Symvl's base directory must be changed accordingly |

## Standard Input and Output

The following functions are members of the `io` table. You must use `io.` to access them.

| Function                   | Return / Usage                                                                 |
|----------------------------|--------------------------------------------------------------------------------|
| *open*(**path[, mode]**)    | Returns the file stream of the given path, or "nil" if there’s an error. The default mode is `"r"` (read). Symvl uses [C file modes](https://www.tutorialspoint.com/cprogramming/c_file_io.htm) since it's written in C++. |
| *stdin*()                   | Returns the standard input stream                                              |
| *stdout*()                  | Returns the standard output stream                                             |
| *stderr*()                  | Returns the standard error stream                                              |

## Files

**Note**: Replace "file" with your object/variable.

```lua
local p = io.open("yourfile.ext", "r")
local str = p:read("*a")
print(str)
p:close()
```

| Function                  | Return / Usage                                                                 |
|---------------------------|--------------------------------------------------------------------------------|
| *file:close*()             | Closes the stream contained in your io object/table                            |
| *file:flush*()             | Flushes the write buffer of the stream                                         |
| *file:read*(**mode**)       | Reads a specific length from the stream. `*a` reads the entire stream, `*l` (lowercase L) reads a line without a newline character, and `*L` reads a line with a newline character. If the end of the stream is reached, the function returns "nil". You can also specify an integer to represent the number of bytes to read. |
| *file:seek*(**[position], offset**) | Sets and gets the position indicator. "set" indicates the beginning of the stream, "cur" is the current position, and "end" represents the end of the stream. The `offset` parameter specifies the offset from the position. If successful, it returns the new position; otherwise, it returns "nil". |
| *file:setvbuf*(**mode, [size]**)  | Sets buffering for the stream. `no` disables buffering, `full` buffers the entire stream, and `line` buffers per line. The optional `size` parameter sets the buffer limit. |
| *file:write*(**value**)    | Writes a given value to the stream. Multiple parameters can be provided. If successful, it returns the stream; otherwise, it returns "nil". |

## Math

The following functions are members of the `math` table. You must use `math.` to access them.

| Function                 | Return / Usage                                                                   |
|--------------------------|----------------------------------------------------------------------------------|
| *abs*(**x**)             |
| *acos*(**x**)            |
| *asin*(**x**)            |
| *atan*(**x**)            |
| *atan2*(**x, y**)        |
| *ceil*(**x**)            |
| *cos*(**x**)             |
| *deg*(**x**)             | Converts an angle in radians to degrees                                           |
| *exp*(**x**)             |
| *floor*(**x**)           |
| *frexp*(**x**)           |
| *huge*                   | This is an attribute, not a function. It returns the value of the C++ macro [HUGE_VAL](https://en.cppreference.com/w/cpp/numeric/math/HUGE_VAL) |
| *ldexp*(**flt, exp**)    |
| *log*(**x, [base]**)     | Computes the logarithm of `x`. The base is optional and defaults to "e".          |
| *max*(**x, [...]**)      |
| *min*(**x, [...]**)      |
| *modf*(**x**)            | Returns the integral and fractional parts of `x`                                  |
| *pi*                     | This is an attribute, not a function                                              |
| *pow*(**x, y**)          |
| *rad*(**x**)             |
| *random*(**flt, exp**)   |
| *random*(**[from, to]**) |
| *randomseed*(**x**)      | Sets the seed for random number generation                                        |
| *sin*(**x**)             |
| *sinh*(**x**)            |
| *sqrt*(**x**)            |
| *tan*(**x**)             |
| *tanh*(**x**)            |

## String

The following functions are members of the `string` table. You must use `string.` to access them.

| Function                        | Return / Usage                                                          |
|---------------------------------|-------------------------------------------------------------------------|
| *bytes*(**string, [start, end]**) | Returns the bytes of the characters in the given string. You can specify optional `start` and `end` positions. |
| *char*(**[...]**)               | Returns the character(s) corresponding to the given ASCII code(s)        |
| *len*(**string**)               | Returns the length of the given string                                   |
| *lower*(**string**)             | Converts the given string to lowercase                                   |
| *upper*(**string**)             | Converts the given string to uppercase                                   |
| *reverse*(**string**)           | Reverses the given string                                                |
| *sub*(**string, [start, end]**)  | Returns a substring from the specified `start` to `end` position         |

## Table

The following functions are members of the `table` table. You must use `table.` to access them.

| Function                                 | Return / Usage                                                          |
|------------------------------------------|-------------------------------------------------------------------------|
| *concat*(**table, [separator, start, end]**) | Concatenates the elements of a table into a string                        |
| *insert*(**table, [position], value**)    | Inserts a value into the table at the specified position (if provided)    |
| *pack*(**[...]**)                        | Packs multiple values into a table and returns it                        |
| *remove*(**table, [position]**)          | Removes the element at the specified position, or the last element if no position is given |
| *unpack*(**table, [start, end]**)        | Returns elements from a table, optionally specifying start and end positions |

These are the built-in functions of Symvl.

> **Note**: `[optional] param, param` means that everything after `[optional]` is optional, while `[optional param]` indicates only that one parameter is optional.

[Next Chapter: Operators →](https://github.com/BlackFoX1991/Symvl/tree/main/docs/operators.md)
