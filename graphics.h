#include "graphics/graphics_0.xbm"
#include "graphics/graphics_1.xbm"
#include "graphics/graphics_2.xbm"
#include "graphics/graphics_3.xbm"
#include "graphics/graphics_4.xbm"
#include "graphics/graphics_5.xbm"
#include "graphics/graphics_6.xbm"
#include "graphics/graphics_7.xbm"
#include "graphics/graphics_8.xbm"
#include "graphics/graphics_9.xbm"
#include "graphics/graphics_dot.xbm"
#include "graphics/graphics_icon_co2.xbm"
#include "graphics/graphics_icon_humidity.xbm"
#include "graphics/graphics_icon_temperature.xbm"
#include "graphics/graphics_text_ppm.xbm"
#include "graphics/graphics_text_humidity.xbm"
#include "graphics/graphics_text_percent.xbm"
#include "graphics/graphics_text_degreecelcius.xbm"

#define graphics_null_width 0
#define graphics_null_height 0
static unsigned char graphics_null_bits[] = { };

struct Bitmap
{
    unsigned char* bits;
    int width;
    int height;
};


Bitmap getNumberBitmap(char number)
{
    switch (number)
    {
        case '0':
            return { graphics_0_bits, graphics_0_width, graphics_0_height };
        case '1':
            return { graphics_1_bits, graphics_1_width, graphics_1_height };
        case '2':
            return { graphics_2_bits, graphics_2_width, graphics_2_height };
        case '3':
            return { graphics_3_bits, graphics_3_width, graphics_3_height };
        case '4':
            return { graphics_4_bits, graphics_4_width, graphics_4_height };
        case '5':
            return { graphics_5_bits, graphics_5_width, graphics_5_height };
        case '6':
            return { graphics_6_bits, graphics_6_width, graphics_6_height };
        case '7':
            return { graphics_7_bits, graphics_7_width, graphics_7_height };
        case '8':
            return { graphics_8_bits, graphics_8_width, graphics_8_height };
        case '9':
            return { graphics_9_bits, graphics_9_width, graphics_9_height };
        case '.':
            return { graphics_dot_bits, graphics_dot_width, graphics_dot_height };
        default:
            return { graphics_null_bits, graphics_null_width, graphics_null_height };
    }
}

Bitmap getIconBitmap(char *icon)
{
    if (strcmp(icon, "co2") == 0)
        return { graphics_icon_co2_bits, graphics_icon_co2_width, graphics_icon_co2_height };
    else if (strcmp(icon, "rh") == 0)
        return { graphics_icon_humidity_bits, graphics_icon_humidity_width, graphics_icon_humidity_height };
    else if (strcmp(icon, "temp") == 0)
        return { graphics_icon_temperature_bits, graphics_icon_temperature_width, graphics_icon_temperature_height };
    else
        return { graphics_null_bits, graphics_null_width, graphics_null_height };
}

Bitmap getTextBitmap(char *text)
{
    if (strcmp(text, "ppm") == 0)
        return { graphics_text_ppm_bits, graphics_text_ppm_width, graphics_text_ppm_height };
    else if (strcmp(text, "rh") == 0)
        return { graphics_text_humidity_bits, graphics_text_humidity_width, graphics_text_humidity_height };
    else if (strcmp(text, "percent") == 0)
        return { graphics_text_percent_bits, graphics_text_percent_width, graphics_text_percent_height };
    else if (strcmp(text, "degc") == 0)
        return { graphics_text_degreecelcius_bits, graphics_text_degreecelcius_width, graphics_text_degreecelcius_height };
    else
        return { graphics_null_bits, graphics_null_width, graphics_null_height };
}
