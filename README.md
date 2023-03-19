![Symvl](https://user-images.githubusercontent.com/125445926/224560670-08cf2110-f267-499a-bd66-dca8300b1492.PNG)

# Symvl Scripting Language

Wellcome to Symvl, yet another Scripting Language. Symvl is written in C++ using Code:Blocks and GCC. Every Part is handwritten, started from the Lexer, Parser, AST and VM. As you can see the Code will compiled just in Time which means we have pretty good executation Times. The Syntax of Symvl is very similar with Lua but there are some decent Differences. At least if you already know Lua there Symvl will be very familiar to you. I chose Lua's Syntax because its easy to learn while its a dynamicially typed Language, surprise.. surprise Symvl too. Symvl can be easily extended with the builtin API Class, allows to add new Functions. There are several Classes use it already like the IO Library, the Math Library and also the Table Library. This brings many possibilities to Symvl. Symvl does support Conditions such as if, elseif, else , while where we already come to Loops with for, for in pairs and so on. Basic Stuff like global and local Variables, same with functions and also User-defined Objects in form of Tables. You will see the similarities to Lua in later Code Examples. The current supported Datatypes in Symvl are Numbers such as Integer and Float, String, Boolean and User-defined Objects which can contain various Data-Structures.


# How to compile ?

I used Code:Blocks for the Development in combination with the GNU GCC Compiler. Theres is a pre-compiled Binary Release
if you want to Test Symvl. Easy to use, just run it from your Terminal/Command-Host, the only Parameter is the Path of the Script File
you want to run. You can run Symvl without Parameter to execute single-line Code.


# Syntax of Symvl

First of all, Statements can be placed in the Root of the Script, there is no specific
Entry-Point in Symvl. This are just Examples of how it can be done.
At least you will notice Symvl is very inspired by Lua because i used to be a big fan of Lua which is still the Case.

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
 
