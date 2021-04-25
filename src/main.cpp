#include "iostream"
#include <lua.hpp>
#include <lauxlib.h>
#include <lualib.h>
#include "luabinary.h"

int main(int argc, char *argv[]) {

    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    lua_newtable(L);

    lua_setglobal(L, "arg");

    int ret = luaL_loadbuffer(L, lua_binary, lua_binary_len, "lua_app");

    switch (ret) {
        case LUA_ERRSYNTAX:
            std::cout << "Lua syntax error. " << lua_tostring(L, -1);
            break;

        case LUA_OK:
            lua_call(L,0,0);
            break;

        default:
            std::cout << "Failed to process inner code, exiting with code #" << ret;
            break;
    }

    lua_close(L);

    return 0;
}