![Symvl](https://user-images.githubusercontent.com/125445926/224560670-08cf2110-f267-499a-bd66-dca8300b1492.PNG)

# Symvl Scripting Language

Welcome to Symvl, yet another scripting language. Symvl is written in C++ using Code::Blocks and GCC. Every part is handwritten, starting from the lexer, parser, AST, and VM. As you can see, the code will be compiled just in time, which means we have pretty good execution times. The syntax of Symvl is very similar to Lua, but there are some significant differences. If you already know Lua, then Symvl will be very familiar to you. I chose Lua's syntax because it's easy to learn, and it's a dynamically typed language - surprise, surprise - Symvl is also dynamically typed. Symvl can be easily extended with the built-in API class, which allows you to add new functions. Several classes are already in use, such as the IO library, the math library, and the table library. This brings many possibilities to Symvl. Symvl supports conditions such as if, elseif, else, while, and loops such as for, for in pairs, and so on. Basic stuff like global and local variables, functions, and user-defined objects in the form of tables are also supported. You will see the similarities to Lua in later code examples. The current supported datatypes in Symvl are numbers such as integer and float, strings, booleans, and user-defined objects, which can contain various data structures.


# How to compile ?

I used Code::Blocks for development in combination with the GNU GCC Compiler, but I plan to create a proper CMake file for this project. Since I didn't care about a Make or CMake file, I will have to create one, which will take a bit of time. However, I promise to do it soon. There is a pre-compiled binary release available if you want to test Symvl. It's easy to use - just run it from your terminal/command prompt. The only parameter you need to specify is the path of the script file you want to run. You can also run Symvl without any parameters to execute single-line code.


# Todo ( 19.03.2023 )

	• Create a Documentation ( 50% )
	• Implementing MySQL Library ( 40% )
	
	

# Documentation

[Click here to get started](https://github.com/BlackFoX1991/Symvl/blob/main/docs/doc.md)

 
