# Just some Code-Snippets

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

local p = ""
repeat 
  p = p .. getline()
until string.len(p) >= 20

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

## Classes
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
