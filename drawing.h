struct Cursor
{
    int x;
    int y;
};

void drawBitmap(struct Bitmap bitmap, struct Cursor &cursor)
{
    display.drawXBitmap(cursor.x, cursor.y,
        bitmap.bits, bitmap.width, bitmap.height,
        EPD_BLACK);
}

void drawStringLarge(char* string, struct Cursor &cursor)
{
    int i = 0;
    while (string[i] != '\0')
    {
        struct Bitmap bitmap = getBitmapLarge(string[i]);
        drawBitmap(bitmap, { cursor.x, cursor.y + FONT_LARGE_BASELINE });
        cursor.x += bitmap.width + FONT_LARGE_PADDING;
    }
}

void drawStringSmall(char* string, struct Cursor &cursor)
{
    int i = 0;
    while (string[i] != '\0')
    {
        struct Bitmap bitmap = getBitmapSmall(string[i]);
        drawBitmap(bitmap, cursor);
        cursor.x += bitmap.width + FONT_SMALL_PADDING;
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
