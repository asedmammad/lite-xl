local config = require "core.config"
local style = require "core.style"
local DocView = require "core.docview"
local command = require "core.command"

config.draw_whitespace = true

local docview_draw = DocView.draw

function DocView:draw(...)
  if getmetatable(self) == DocView then
    local font = self:get_font()
    font:clear_replacements()
    if config.draw_whitespace then
      font:add_replacement(" ", "·", style.syntax.comment)
      font:add_replacement("\t", "»", style.syntax.comment)
    end
  end
  docview_draw(self, ...)
end

command.add("core.docview", {
  ["draw-whitespace:toggle"]  = function() config.draw_whitespace = not config.draw_whitespace end,
  ["draw-whitespace:disable"] = function() config.draw_whitespace = false                      end,
  ["draw-whitespace:enable"]  = function() config.draw_whitespace = true                       end,
})
