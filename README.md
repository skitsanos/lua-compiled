# lua-compiled
This example demonstrates how to create executable that runs embedded Lua bytecode

### Why

Sometimes there is a need to decouple the application core from some logic that depends on external factors. For example, you need to generate a segment of application that works on that particular machine only, which is often used, for example, in software licensing.

In the current codebase, we demonstrate how to compile the Lua app into bytecode, wrap that bytecode as something we can embed in C app, and then compile that app into executable, which is more, rather, a loader for our bytecode.

But we could go even further; instead of having that bytecode compiled all together with our app, we could have it somewhere on disk or, even better, remotely.

### Build tools

To build it you need Xmake, A cross-platform build utility based on Lua, you can grab it from here [https://xmake.io](https://xmake.io) 

Xmake is super easy to use and allows to make insane build scenarios impossible to achieve in Xmake and others.

### Configuring Xmake.lua

Basically the following config is all you need:

```lua
set_languages('cxx14')

target('demo')
set_kind('binary')

add_links('lua')
add_linkdirs("/usr/local/Cellar/lua/5.4.3/lib")

--add lua headers
add_includedirs(os.getenv('LUA_HEADERS'))

add_files('$(projectdir)/src/main.cpp')

before_build(function(target)
    -- do something here before building it
end)

after_build(function(target)
    print("hello: %s", target:name())
    os.exec("echo %s", target:targetfile())
end)
```



Notice `add_linkdirs`, that's where you need to provide a path to your `liblua`that will me linked with your app.

`LUA_HEADERS` that was set as environment variable points to Lua headers required for your app.

### Working with Clion

If you are coding in Clion, you might need to have CmakeLists.txt as well, just to allow CLion to 'see' your Lua headers, for this just add minimal Cmake config:

```cmake
cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(lua_hello CXX)

message("Including Lua headers from $ENV{LUA_HEADERS}")
include_directories($ENV{LUA_HEADERS})

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
```

