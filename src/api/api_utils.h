#ifndef API_UTILS_H
#define API_UTILS_H

#include "lua.h"
#include "renderer.h"

RenColor checkcolor(lua_State *L, int idx, int def);

#endif
