# Builtin Functions

This List contains all builtin Function, including current API Modules.


## BASE FUNCTIONS
|Function|Return/ Usage
|--|--|
|*print*(...)  |  prints values to the standard output|
|*puts*(**string**)|put a string to standard output|
|*ipairs*(**table**)|returns a iterator to iterate array part of a Table|
|*pairs*(**table**)|Returns a iterator to iterate a table for array and hash)
|*type*(**..**)|Returns the type of a Value/ Object
|*getline*()|Returns the current Line of standard input as string
|*require*(**Path**)|Loads a given Script at Runtime, please notice, if you using relative Paths Symvl's Base-Directory have to be changed too.


## standard-Input and Output

The following Functions are Members of the "io" Table. You have to use "io." to access them.
|Function|Return/ Usage
|--|--|
|*open*(***path,[optional] mode***)| Returns the File-stream of the given Path or if there is an Error a "nil" Value. The default mode is "r" which means read. Symvl uses the [C File-Modes](https://www.tutorialspoint.com/cprogramming/c_file_io.htm) since its written in C/C++.
|*stdin*()| Returns the standard-input stream
|*stdout*()| Returns the standard-output stream
|*stderr*()| Returns the standard-error stream


## Files

** Notice : Don't forget to replace "file" with your Object/Variable.  **
```lua
local p = io.open("yourfile.ext","r")
local str = p:read("*a")
print(str)
p:close()
```
|Function|Return/ Usage
|--|--|
|*file:close*()| Closing the Stream contained in your io Object/Table
|*file:flush*()| Flush the write buffer of the stream
|*file:read*(**mode**)| Reads a specific Length of the given Stream. "*a" - reads the whole Stream from the current Position, "*l" ( Lowercase L ) reads a line without Char "newline" at the End of it while "*L" reads a line with "newline" Char at the End. If the current Position of the Stream is End of File this Function returns "nil". The mode Parameter can be a Integer which represents the length of Bytes you want to read.
|*file:seek*(**[optional] position, offset**)| seek will set and get the Position Indicator like in C++, the position Parameter can be set as "set" which is the beginning of the Stream, "cur" which represents the current Position and last but not least "end" which is the End of the Stream. Offset is the offset from the given Position. On success it will return a Position otherwise it will return nil.
|*file:setvbuf*(**mode, [optional] size**)| Will set the buffering to a specific mode, you can choose between "no" which disable the buffer completely, "full" which will buffer the whole stream or "line" which buffers a line while size is a optional Parameter to set the Limit of the Buffer. 
|*file:write*(**value**)| Writes a given Value to the Stream, multiply Parameters can be given. On success it will return the stream otherwise it will return "nil".

## Math

The following Functions are Members of the "math" Table. You have to use "math." to access them. Most of the Math Functions doesn't need a explanation so you will only find a Table of the accessible Functions.

|Function|Return/ Usage
|--|--|
|*abs*(**X**)
|*acos*(**X**)
|*asin*(**X**)
|*atan*(**X**)
|*atan2*(**X,Y**)
|*ceil*(**X**)
|*cos*(**X**)
|*deg*(**X**)| Returns a angle of value X ( In Radians ) to degrees.
|*exp*(**X**)
|*floor*(**X**)
|*frexp*(**X**)
|*huge*| Notice, this is a Attribute and not Function, it returns the Value of the C++ Macro [HUGE_VAL](https://en.cppreference.com/w/cpp/numeric/math/HUGE_VAL)
|*ldexp*(**flt,exp**)
|*log*(**X, [optional] base**) | Base is Optional, the default Value of Base is "e"
|*max*(**X, [...]**)
|*min*(**X, [...]**)
|*modf*(**X**) | Returns integral and fractional part of X
|*pi*| Notice : this is an Attribute and not a Function
|*pow*(**X,Y**)
|*rad*(**X**)
|*random*(**flt,exp**)
|*random*(**[optional] from ,to**)
|*randomseed*(**X**)| Sets the Seed of random
|*sin*(**X**)
|*sinh*(**X**)
|*sqrt*(**X**)
|*tan*(**X**)
|*tanh*(**X**)



## String

The following Functions are Members of the "string" Table. You have to use "string." to access them. 
|Function|Return/ Usage
|--|--|
|*bytes*(**string, [optional] start, end**)| This returns the Bytes of the Characters in the given String, optional you can set a start-position and end-position
|*char*(**[...]**)| Returns the Char of the given Number, you can use multiple Parameters to return multiple Char-Codes as a given Character in the ASCII Table
|*len*(**string**)| This returns the length of the given string
|*lower*(**string**)| Returns the given string as lowercase
|*upper*(**string**)| Returns the given string as uppercase
|*reverse*(**string**)| Returns the given string reversed
|*sub*(**string, [optional] start, end**)| Returns the sub-string of given string from start to end position.


## Table

The following Functions are Members of the "table" Table. You have to use "table." to access them. 

|Function|Return/ Usage
|--|--|
|*concat*(**table, [optional] separator, start_position, end_position**)| concatenate a table to a string.
|*insert*(**table,[optional position], value**)| Inserts a specific Value to a Table, optional at the given Position, returns true if succeed.
|*pack*(**[...]**)| Packs all Values in one Table and returns the Table
|*remove*(**table**,[optional] Position)| Removes the Table-Content at given Position, if the Parameter Position is not given the function will remove the whole Table
|*unpack*(**table**, [optional] start, end)| Returns the Elements of a Table from, optional, start and end Position.



These are the builtin Functions of Symvl.
>Notice : "[optional] param, param" means everything after [optional] is a optional Parameter while [optional param] means it is just this one Parameter which is optional.


[Next Chapter, Operators ->](https://github.com/BlackFoX1991/Symvl/tree/main/docs/operators.md)
