# Symvl - Scripting Language

Symvl is a work in progress interpreted scripting language. As I began developing Codium four to five years ago, my goal was to understand the art of abstract syntax tree (AST) and how to produce bytecode or opcode for later execution. Codium is based on a custom-made opcode instruction set that showcases my own code virtual machine (VM), while Symvl will actively use AST structures.
My plan is to produce machine code or implement a new custom VM from there, but for now, this part is still uncertain.



# Symvl Concept

I used to be a big fan of Lua, and as a result, I will be leaning Symvl's syntax towards it. This includes incorporating features like tables and creating classes within a table, among others. Additionally, Symvl will even be able to interpret Lua files. I chose Lua because it is a well-known scripting language, and there's no need to learn a completely new language.
For conceptual purposes, Symvl will be developed in C# using .NET Core 3.1. However, I plan to rewrite it in Rust eventually. Since I'm still learning Rust, this will take some time.



# Why C# and why Rust after all ?

C++ is one of my favorite languages because it has all the features I need. However, refreshing my skills in C++ takes too much time, which is a limited resource for me right now. As a C++ developer, I'm well aware of the time-consuming task of dealing with header files and prototype declarations. It involves writing the class, rewriting it as a header prototype, and then fitting the cpp file to match the header, among other things. On the other hand, C# is easier and faster to work with.

That's why I've decided to rewrite my concept code in Rust. Rust has all the features of C++ and offers more secure memory management, which is the main reason why I choose it over C++. Although there are some differences between the two, such as C++ being faster at compiling and Rust having better framework support, Rust is still the better choice for backend programming/scripting. Variables, functions, objects, and everything else need a safe memory management system, which Rust provides. It doesn't mean C++ is bad, but for my purposes, Rust is the better option.


# Current Progress of the C# Concept

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
 
