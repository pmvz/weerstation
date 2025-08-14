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
    char buffer[2] = "\0";
    while (string[i] != '\0')
    {
        buffer[0] = string[i];
        struct Bitmap bitmap = getBitmapLarge(buffer);
        drawBitmap(bitmap, { cursor.x, cursor.y + FONT_LARGE_BASELINE });
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
