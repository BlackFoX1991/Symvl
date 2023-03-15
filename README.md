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


### 13.03.2023:
	• Created the first parser for the lexer.
	• Conducted the first syntax tree tests.
	• Implemented the expression node.
	• Implemented binary and unary nodes.
	• Implemented variable assign node.
	• Implemented block node.
	• Implemented condition node.
	• Implemented if node.
	• Implemented while/for node.
	• Successfully parsed variables and general expression statements (binary, unary).
	• First successful parse attempt.


### 14.03.2023:
	• Implemented complete expression node.
	• Implemented function nodes and extended variable handling.
	• Implemented table node to create a custom object.
	• Implemented handling for custom user data (custom objects/tables).
	• Updated the parser with all the nodes above.
	• After about 30 test runs, it seems to work for now.
	• Extended the parser with a custom VM, but the VM is not finished yet.


### 15.03.2023:
	• Extended VM with many new features.
	• Optimized the translation process from AST to VM.
	• VM is now complete and represents the JIT-compiler.
	• Symvl now has all the important features (function statements, variables, kind of custom tables, condition statements [if, while, for], array, and so on).
		   
		   
### TODO LIST:

	• Optimize Code Generation
	• Several Tests to make sure everything works
	• (*)Add more Libraries
		   

# Further Information of the Current Progress

Finally Smyvl made a big jump in Progress and runs for now. Im glad i spent this 12 Hours in a row to push it forward.
As we can see i made a few Changes and extened the VM while updating the Parser and AST. At least im happy i used C++ and
not C# as i mentioned before since its way easier in the beginning. C++ is the complete opposite, its hard in the beginning 
since you have to plan well before you start but its getting easier with every Step.

I cant say anything about the current Progress but the hard Part is over, finally i took some Code from Codium translated it
to C++ and optimized everything to the Core. Theres also kind of an API in the VM which allows to create own Interfaces and link them
to a Metatable as an Object or Class like Structure.


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
 
