#include "Adafruit_ThinkInk.h"

ThinkInk_290_Tricolor_Z94 display(PIN_EPD_DC, PIN_EPD_RESET, PIN_EPD_CS, -1, PIN_EPD_BUSY);

struct Cursor
{
    int x;
    int y;
};

void initDisplay()
{
    display.begin(THINKINK_TRICOLOR);
    display.clearBuffer();
}

void show()
{
    display.display();
}

void clear()
{
    display.clearBuffer();
}

void drawBitmap(struct Bitmap bitmap, struct Cursor &cursor)
{
    display.drawXBitmap(cursor.x, cursor.y,
        bitmap.bits, bitmap.width, bitmap.height,
        EPD_BLACK);
}

void drawStringLarge(char* string, struct Cursor &cursor)
{
    int i = 0;
    char buffer[2] = "\0";
    while (string[i] != '\0')
    {
        buffer[0] = string[i];
        struct Bitmap bitmap = getBitmapLarge(buffer);
        drawBitmap(bitmap, cursor);
        cursor.x += bitmap.width + FONT_LARGE_PADDING;
        i++;
    }
}

void drawStringSmall(char* string, struct Cursor &cursor)
{
    int i = 0;
    char buffer[2] = "\0";
    while (string[i] != '\0')
    {
        buffer[0] = string[i];
        struct Bitmap bitmap = getBitmapSmall(buffer);
        drawBitmap(bitmap, cursor);
        cursor.x += bitmap.width + FONT_SMALL_PADDING;
        i++;
    }
}

void drawIntLarge(int number, struct Cursor &cursor)
{
    char buffer[8] = { '\0' };
    snprintf(buffer, sizeof(buffer), "%d", number);
    drawStringLarge(buffer, cursor);
}

void drawIntSmall(int number, struct Cursor &cursor)
{
    char buffer[8] = { '\0' };
    snprintf(buffer, sizeof(buffer), "%d", number);
    drawStringSmall(buffer, cursor);
}

void drawFloatLarge(float number, struct Cursor &cursor)
{
    char buffer[8] = { '\0' };
    snprintf(buffer, sizeof(buffer), "%.1f", number);
    drawStringLarge(buffer, cursor);
}

void drawFloatSmall(float number, struct Cursor &cursor)
{
    char buffer[8] = { '\0' };
    snprintf(buffer, sizeof(buffer), "%.1f", number);
    drawStringSmall(buffer, cursor);
}

void drawIcon(char* icon, struct Cursor &cursor)
{
    drawBitmap(getBitmapIcon(icon), cursor);
}

void drawInfo(int co2_ppm, float temperature, float rel_humidity, float pressure)
{
    struct Cursor cursor = { 0, 0 };

    // Time
    cursor = { 31, 18 };
    drawStringLarge("24:99", cursor);
    cursor.x += 12;
    drawStringLarge("do", cursor);
    cursor.x += 12;
    drawStringLarge("31", cursor);
    cursor.x += 12;
    drawStringLarge("feb", cursor);

    // Outside weather
    cursor = { 234, 8 };
    drawIcon("sunnylightning", cursor);

    // Separator
    display.drawLine(6, 54, 288, 54, EPD_BLACK);
    
    // Measurements
    cursor = { 10, 67 };
    drawIcon("temp", cursor);
    cursor = { 31, 68 };
    drawFloatLarge(temperature, cursor);
    cursor.x = 85;
    drawStringLarge("`C", cursor);  // ` for degree

    cursor = { 6, 100 };
    drawIcon("co2", cursor);
    cursor = { 31, 99 };
    drawIntLarge(co2_ppm, cursor);
    cursor.x = 95;
    drawStringLarge("ppm", cursor);

    cursor = { 164, 72 };
    drawIcon("humid", cursor);
    cursor = { 184, 68 };
    drawIntLarge(rel_humidity, cursor);
    drawStringLarge("%", cursor);
    cursor.x = 249;
    drawStringLarge("RH", cursor);

    cursor = { 161, 101 };
    drawIcon("pres", cursor);
    cursor = { 184, 99 };
    drawIntLarge(pressure, cursor);
    cursor.x = 249;
    drawStringLarge("kPa", cursor);
}
