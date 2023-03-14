![Symvl](https://user-images.githubusercontent.com/125445926/224560670-08cf2110-f267-499a-bd66-dca8300b1492.PNG)

# Symvl - Scripting Language

Symvl is a work in progress interpreted scripting language. As I began developing Codium four to five years ago, my goal was to understand the art of abstract syntax tree (AST) and how to produce bytecode or opcode for later execution. Codium is based on a custom-made opcode instruction set that showcases my own code virtual machine (VM), while Symvl will actively use AST structures.
My plan is to produce machine code or implement a new custom VM from there, but for now, this part is still uncertain.



# Symvl Concept ( edited 12.03.2023 )

I used to be a big fan of Lua, and as a result, I will be leaning Symvl's syntax towards it. This includes incorporating features like tables and creating classes within a table, among others. Additionally, Symvl will even be able to interpret Lua files. I chose Lua because it is a well-known scripting language, and there's no need to learn a completely new language.
For conceptual purposes, Symvl will Concept will be written in C++.



# Why rewrite the Code in Rust later ?

Rust has all the features of C++ and offers more secure memory management, which is the main reason why I choose it over C++. Although there are some differences between the two, such as C++ being faster at compiling and Rust having better framework support, Rust is still the better choice for backend programming/scripting. Variables, functions, objects, and everything else need a safe memory management system, which Rust provides. It doesn't mean C++ is bad, but for my purposes, Rust is the better option.


# Current Progress of the C++ Concept

	12.03.2023 -> Development in C# stopped, started with C++ instead.
		   -> new Grammer Concept has been written.
		   -> Lexer and Syntax Tree Structures created.
	
	13.03.2023 -> Created a first Parser for the Lexer
	           -> First Syntax-Tree Tests
		   -> implemented Expression Node
		   -> implemented Binary and Unary Nodes
		   -> implemented Variable Assign Node
		   
		   [ 10:45 P.M. ]
		   -> implemented Block Node
		   -> implemented Condition Node
		   -> implemented if Node
		   -> implemented while/ for Node
		   -> First Succesful Parse attempt on Variables, General Expression Statements ( Binary, Unary )
		   
	14.03.2023 -> implemented Complete Expression Node
		   -> implemented function Nodes, extended Variable Handling
		   -> implemented Table Node to create Kind of custom Objects
		   -> Handling for custom User Data implemented ( Custom Objects/ Tables )
		   -> Parser updated with all the Nodes above, after about 30 Testruns it seems to work for now
		   -> Parser extened with a custom VM but VM is not finished yet
		   
	
	TODO LIST:
	
	-> Some more Tests
	-> extend VM
	-> optimize Code in Nodes due the extension of a vm
	-> several more Tests on User Data, custom Tables and so on..
	-> *Planned to create a JIT-Compiler
	-> much more...
		   
	Current Progress before first real Tests : 47%


# A Example of Symvl / Lua Code ( edited 12.03.2023 , new Grammer )

```lua
--[[ This is a Sample Source Code in Symvl,
	you will notice it is super Lua-like ]]

local function Fruit(Name,Price)

	local fruit_data = { nm = Name, pr = Price}
	
	function fruit_data:priceof()
		return "The Price of " .. self.nm .. " is " .. self.pr
	end
	
	return fruit_data

end
-- create a new Object of Fruit
local mango = Fruit("Mango",2.35)
print(mango:priceof())
```
 
