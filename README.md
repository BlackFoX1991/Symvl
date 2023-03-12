# Symvl - Scripting Language

Symvl is a work in progress interpreted scripting language. As I began developing Codium four to five years ago, my goal was to understand the art of abstract syntax tree (AST) and how to produce bytecode or opcode for later execution. Codium is based on a custom-made opcode instruction set that showcases my own code virtual machine (VM), while Symvl will actively use AST structures.
My plan is to produce machine code or implement a new custom VM from there, but for now, this part is still uncertain.



# Symvl Concept ( edited 12.03.2023 )

I used to be a big fan of Lua, and as a result, I will be leaning Symvl's syntax towards it. This includes incorporating features like tables and creating classes within a table, among others. Additionally, Symvl will even be able to interpret Lua files. I chose Lua because it is a well-known scripting language, and there's no need to learn a completely new language.
For conceptual purposes, Symvl will Concept will be written in C++.



# Why rewrite Rust ?

Rust has all the features of C++ and offers more secure memory management, which is the main reason why I choose it over C++. Although there are some differences between the two, such as C++ being faster at compiling and Rust having better framework support, Rust is still the better choice for backend programming/scripting. Variables, functions, objects, and everything else need a safe memory management system, which Rust provides. It doesn't mean C++ is bad, but for my purposes, Rust is the better option.


# Current Progress of the C++ Concept ( edited 12.03.2023 )

[ Please notice : I will write the Concept in C++ instead of C# after some Time of overthinking. ]
Currently, I am working on the abstract syntax tree (AST) in combination with the parser. It involves a significant amount of classes and statement nodes. My plan is to release the first beta version of Symvl in the next 2 or 3 months.


# A Example of Symvl / Lua Code 

```lua
--[[ This is a Sample Source Code in Symvl,
	you will notice it is super Lua-like ]]

fruit = {} -- create a fruit
fruit.__index = fruit;

-- Initialize some root Objects of fruit
function fruit.new(Name, Price)
	f = { name = Name, price = Price }
	setmetatable(f, fruit)
	return f
end

-- new Member/Function of fruit Table
function fruit:get()
	return "Fruit Name: " .. self.name .. " -> Price: " .. self.price
end


-- create a new Object of fruit Table
mango = fruit.new("Mango", 2.35)
print(mango:get()) -- print it out
 
