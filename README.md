# This is a guide on how to use this starter raylib template

This template is a **helpful tool** to get started with coding in **raylib** (bc setting it up manualy is painful). I have been building this template for about a month trying to figure out ways to modify this template. If you want to modify some stuff please **look down below for further information**.

*This template is still a work in progress (please keep that in mind)*

## How to get started?

Heres how to clone this template:

First, copy this github repository url by clicking the code button and copying the URL to clipboard. Then, go back to visual studio and press <kbd>ctrl + shift + p</kbd>, type in `Git:Clone` and hit enter. In the search bar, enter the copied link and hit enter again.

Code in main.cpp and start your code with <kbd>F5</kbd> (whilst having the main.cpp file opened in vscode)

# Modifications

## /src 

If you want to put your code into a src folder, navigate to .vscode and to tasks
Change every:

`"OBJS=${fileBasenameNoExtension}.cpp"` 

to 

`"OBJS=src/${fileBasenameNoExtension}.cpp"`

## C++ --> C

Open the Makefile file, and find `CC = g++` 

Change it to: `CC = gcc`

*and maybe more but I am not sure right now.*

## Make all C/C++ files compile at runtime 

This is mainly if you use **.h/.hpp files for declarations and .cpp files for definitions**

In order to do that you must **change** this line in **Makefile**:

`OBJS = $(patsubst %.c,%.o,$(filter %.c,$(SRC))`

to

`OBJS = $(wildcard src/*.cpp)`


And you must also **remove** every `"OBJS="` from the tasks.json file.

## Enable logging

In order to see std::cout logs you must **Remove** this piece of code in the Makefile:

`-Wl,--subsystem,windows`