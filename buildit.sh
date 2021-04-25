#!/bin/sh

cd src_lua || exit

#compile Lua app into bytecode
luac hello.lua

#load Lua bytecode into C var
bin2c lua_binary < luac.out > ../src/luabinary.h

cd ..

#build the project
xmake -r