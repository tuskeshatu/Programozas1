#include <stdio.h>

typedef enum colour
{
    WHITE,
    RED,
    YELLOW,
    LIME,
    CYAN,
    BLUE,
    MAGENTA,
    BLACK,
} colour;

typedef struct rgb
{
    unsigned char r, g, b;
} rgb;

rgb make_rgb(colour color)
{
    rgb rgb;

    switch (color)
    {
    case WHITE:
        rgb.r = 255;
        rgb.g = 255;
        rgb.b = 255;
        return rgb;

    case RED:
        rgb.r = 255;
        rgb.g = 0;
        rgb.b = 0;
        return rgb;
    case YELLOW:
        rgb.r = 255;
        rgb.g = 255;
        rgb.b = 0;
        return rgb;
    case LIME:
        rgb.r = 0;
        rgb.g = 255;
        rgb.b = 0;
        return rgb;
    case CYAN:
        rgb.r = 0;
        rgb.g = 255;
        rgb.b = 255;
        return rgb;
    case BLUE:
        rgb.r = 0;
        rgb.g = 0;
        rgb.b = 255;
        return rgb;
    case MAGENTA:
        rgb.r = 255;
        rgb.g = 0;
        rgb.b = 255;
        return rgb;
    case BLACK:
        rgb.r = 0;
        rgb.g = 0;
        rgb.b = 0;
        return rgb;
    }
}