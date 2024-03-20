#include <kernel/vga.h>

void vga_putpixel(const struct vga_screen *screen, uint32_t pos_x, uint32_t pos_y, enum vga_color color)
{
  VGA_MEMORY[screen->width * pos_y + pos_x] = (uint8_t)color;
}

void vga_drawchar(const struct vga_screen *screen, const struct bitmap_font *font, uint8_t ch,
                  uint32_t pos_x, uint32_t pos_y, enum vga_color color_fg, enum vga_color color_bg)
{
  uint8_t mask[8] = {128, 64, 32, 16, 8, 4, 2, 1};
  uint8_t *glyph = font->bitmap + (font->index[ch] * font->height);

  for (uint8_t cy = 0; cy < 16; cy++)
  {
    for (uint8_t cx = 0; cx < 8; cx++)
    {
      vga_putpixel(screen, pos_x + cx, pos_y + cy - 12, glyph[cy] & mask[cx] ? color_fg : color_bg);
    }
  }
}
