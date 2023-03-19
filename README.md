![Symvl](https://user-images.githubusercontent.com/125445926/224560670-08cf2110-f267-499a-bd66-dca8300b1492.PNG)

# Symvl Scripting Language

Welcome to Symvl, yet another scripting language. Symvl is written in C++ using Code::Blocks and GCC. Every part is handwritten, starting from the lexer, parser, AST, and VM. As you can see, the code will be compiled just in time, which means we have pretty good execution times. The syntax of Symvl is very similar to Lua, but there are some significant differences. If you already know Lua, then Symvl will be very familiar to you. I chose Lua's syntax because it's easy to learn, and it's a dynamically typed language - surprise, surprise - Symvl is also dynamically typed. Symvl can be easily extended with the built-in API class, which allows you to add new functions. Several classes are already in use, such as the IO library, the math library, and the table library. This brings many possibilities to Symvl. Symvl supports conditions such as if, elseif, else, while, and loops such as for, for in pairs, and so on. Basic stuff like global and local variables, functions, and user-defined objects in the form of tables are also supported. You will see the similarities to Lua in later code examples. The current supported datatypes in Symvl are numbers such as integer and float, strings, booleans, and user-defined objects, which can contain various data structures.


# How to compile ?

I used Code::Blocks for development in combination with the GNU GCC Compiler, but I plan to create a proper CMake file for this project. Since I didn't care about a Make or CMake file, I will have to create one, which will take a bit of time. However, I promise to do it soon. There is a pre-compiled binary release available if you want to test Symvl. It's easy to use - just run it from your terminal/command prompt. The only parameter you need to specify is the path of the script file you want to run. You can also run Symvl without any parameters to execute single-line code.


# Syntax of Symvl

First of all, statements can be placed in the root of the script - there is no specific entry point in Symvl. These are just examples of how it can be done. You will notice that Symvl is very inspired by Lua, as I used to be a big fan of Lua, and still am.

## Symvl Supports the following Operators
• + 		Plus
• - 		Minus
• *		Multiply
• / 		Divide
• % 		Modulo
• ^ 		Exponential
• ..  		Concat
• and		and
• or		or
• == 		Equal
• ~= 		Not Equal
• >  		Bigger than
• >= 		Bigger than or Equal
• <  		Smaller than
• <= 		Smaller than or Equal


## Symvl does NOT support Postfix Operators for now 
• ++ or -- does not work
• += or -= does not work


## Create Variables

```lua
-- This creates a local Variable
local varname = "Hello"
local numbervar = 5.2

-- Global Variable
varname = 10
```

## Create Functions
```lua
-- Creates a local Function
local function myFunc(param1,param2)
	return (param1+param2)
end

-- creates a global Function
function gFunc(param)
 -- do Something
end
```

## Conditions and Loops

```lua

while true do
 -- while <condition> do ... end
end

for i = 0, 200, 1 do
  --[[ this is for loop
  	for <iterator>, <Condition>(, Step)  ... end
	Step is optional
  ]]
end

for k in pairs(tbl) do
	print(tbl[k])
end

local t = 3
if t == 2 then

elseif t == 3 then

else

end
```

## Arrays

```lua
local t = { {"Hello","World"}, {"Hallo","Welt"} }
print(t[1][1])

local p = {"Hallo", "Welt"}
print(p[1])
for i in pairs(p) do
	print(i)
	print(p[i])
end
```

## Complex Tables
Notice : Other than in Lua there is no "setmetatable" needed here
```lua
-- create a complex Table 
function myObject(name)

	local my_data = { obj_name = name }

	function my_data:getName()
		return self.obj_name
	end

	return my_data
end

-- create a new Instance of this Table
local obj = myObject("test")
print(obj:getName())
```

## include external Scripts

To import some external Symvl Script just use "require", please make sure you use the right Path.
you can use relative Paths also but make sure Symvl runs in the right working directory at least.
As you can see its pretty similar to Lua.
```lua
require("<Path to the File or Filename with extension")
```

[...] More Examples will follow as well as the native Functions. Also i will add a Documentation about the API in Symvl to extend it with additional Functions.
For more "Todos" take a look at the List below.



# Todo ( 19.03.2023 )

	• Creating Code Examples ( 50% )
	• Create a Documentation ( 0% )
	• Implementing MySQL Library ( 0% )
 
