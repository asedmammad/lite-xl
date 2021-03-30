#include "api.h"
#include "api_utils.h"
#include "renderer.h"
#include "rencache.h"

static int f_show_debug(lua_State *L) {
  luaL_checkany(L, 1);
  rencache_show_debug(lua_toboolean(L, 1));
  return 0;
}


static int f_get_size(lua_State *L) {
  int w, h;
  ren_get_size(&w, &h);
  lua_pushnumber(L, w);
  lua_pushnumber(L, h);
  return 2;
}


static int f_begin_frame(lua_State *L) {
  rencache_begin_frame();
  return 0;
}


static int f_end_frame(lua_State *L) {
  rencache_end_frame();
  return 0;
}


static int f_set_clip_rect(lua_State *L) {
  RenRect rect;
  rect.x = luaL_checknumber(L, 1);
  rect.y = luaL_checknumber(L, 2);
  rect.width = luaL_checknumber(L, 3);
  rect.height = luaL_checknumber(L, 4);
  rencache_set_clip_rect(rect);
  return 0;
}


static int f_draw_rect(lua_State *L) {
  RenRect rect;
  rect.x = luaL_checknumber(L, 1);
  rect.y = luaL_checknumber(L, 2);
  rect.width = luaL_checknumber(L, 3);
  rect.height = luaL_checknumber(L, 4);
  RenColor color = checkcolor(L, 5, 255);
  rencache_draw_rect(rect, color);
  return 0;
}


static int f_draw_text(lua_State *L) {
  RenFont **font = luaL_checkudata(L, 1, API_TYPE_FONT);
  const char *text = luaL_checkstring(L, 2);
  int x = luaL_checknumber(L, 3);
  int y = luaL_checknumber(L, 4);
  RenColor color = checkcolor(L, 5, 255);

  CPReplaceTable *rep_table;
  RenColor replace_color;
  if (lua_gettop(L) >= 7) {
    rep_table = luaL_checkudata(L, 6, API_TYPE_REPLACE);
    replace_color = checkcolor(L, 7, 255);
  } else {
    rep_table = NULL;
    replace_color = (RenColor) {0};
  }

  x = rencache_draw_text(*font, text, x, y, color, rep_table, replace_color, false);
  lua_pushnumber(L, x);
  return 1;
}


static int f_draw_text_subpixel(lua_State *L) {
  RenFont **font = luaL_checkudata(L, 1, API_TYPE_FONT);
  const char *text = luaL_checkstring(L, 2);
  int x_subpixel = luaL_checknumber(L, 3);
  int y = luaL_checknumber(L, 4);
  RenColor color = checkcolor(L, 5, 255);

  CPReplaceTable *rep_table;
  RenColor replace_color;
  if (lua_gettop(L) >= 7) {
    rep_table = luaL_checkudata(L, 6, API_TYPE_REPLACE);
    replace_color = checkcolor(L, 7, 255);
  } else {
    rep_table = NULL;
    replace_color = (RenColor) {0};
  }

  x_subpixel = rencache_draw_text(*font, text, x_subpixel, y, color, rep_table, replace_color, true);
  lua_pushnumber(L, x_subpixel);
  return 1;
}


static const luaL_Reg lib[] = {
  { "show_debug",         f_show_debug         },
  { "get_size",           f_get_size           },
  { "begin_frame",        f_begin_frame        },
  { "end_frame",          f_end_frame          },
  { "set_clip_rect",      f_set_clip_rect      },
  { "draw_rect",          f_draw_rect          },
  { "draw_text",          f_draw_text          },
  { "draw_text_subpixel", f_draw_text_subpixel },
  { NULL,            NULL            }
};


int luaopen_renderer_font(lua_State *L);

int luaopen_renderer(lua_State *L) {
  luaL_newlib(L, lib);
  luaopen_renderer_font(L);
  lua_setfield(L, -2, "font");
  return 1;
}
