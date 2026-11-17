#ifndef LCDLIBRARY_H
#define LCDLIBRARY_H

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

// Font structure to support multiple fonts like U8g2
struct LCDFont {
    const uint8_t* bitmap;
    uint8_t width;
    uint8_t height;
    char firstChar;
    char lastChar;
    bool bottomUp; // Your openGLletters array is stored bottom-to-top
};

// Your existing 8x13 font wrapped in the LCDFont descriptor
extern const uint8_t openGLletters[95][13];
extern const LCDFont font_8x13_opengl;

class LCDLibrary {
protected:
    uint8_t* _buffer;
    int _width;
    int _height;
    uint8_t _drawColor;      // 1 = pixel on, 0 = pixel off (erase), 2 = XOR
    const LCDFont* _font;
    int _cursorX;
    int _cursorY;
    int _charSpacing;

    // Helpers for horizontal bit-aligned/shifted blitting and fast straight lines
    void copyShiftArray(uint8_t* dest, int destLen, const uint8_t* src, int srcLen, int pos);
    void drawHLine(int x, int y, int w);
    void drawVLine(int x, int y, int h);

public:
    // Constructor: pass your pre-allocated display buffer (size = width * height / 8)
    LCDLibrary(uint8_t* buffer, int width, int height);
    virtual ~LCDLibrary() {}

    // --- Hardware Interface (Override this in your display subclass) ---
    virtual void sendBuffer() {}

    // --- Buffer & State Management ---
    void clearBuffer();
    void fillBuffer();
    void setDrawColor(uint8_t color); // 0 = Clear, 1 = Draw, 2 = XOR
    uint8_t getDrawColor() const { return _drawColor; }
    int getDisplayWidth() const { return _width; }
    int getDisplayHeight() const { return _height; }

    // --- Graphics Primitives ---
    void drawPixel(int x, int y);
    void drawLine(int x0, int y0, int x1, int y1, int thickness = 1);

    // Rectangles (Frame = outline, Box = filled, R = rounded)
    void drawFrame(int x, int y, int w, int h, int thickness = 1);
    void drawBox(int x, int y, int w, int h);
    void drawRFrame(int x, int y, int w, int h, int r);
    void drawRBox(int x, int y, int w, int h, int r);

    // Circles & Ellipses (Circle = outline, Disc = filled)
    void drawEllipse(int x0, int y0, int rx, int ry);
    void drawFilledEllipse(int x0, int y0, int rx, int ry);
    void drawCircle(int x0, int y0, int r) { drawEllipse(x0, y0, r, r); }
    void drawDisc(int x0, int y0, int r) { drawFilledEllipse(x0, y0, r, r); }

    // Arcs (angles in degrees, 0 = right, 90 = down)
    void drawArc(int x0, int y0, int r, float startAngle, float endAngle, bool fill = false);

    // Bitmaps (XBM / MSB-first byte arrays)
    void drawBitmap(int x, int y, int w, int h, const uint8_t* bitmap);

    // --- Text & Fonts ---
    void setFont(const LCDFont* font);
    void setFontSpacing(int space) { _charSpacing = space; }
    void setCursor(int x, int y);
    int drawGlyph(int x, int y, char c);
    int drawStr(int x, int y, const char* str);
    int print(const char* str); // Prints at current cursor and advances cursor
};

#endif // LCDLIBRARY_H
