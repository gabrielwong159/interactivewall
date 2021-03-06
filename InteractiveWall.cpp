#include <Adafruit_NeoPixel.h>
#include <InteractiveWall.h>

InteractiveWall::InteractiveWall() {

        //takes in 2 parameters, (numberOfPixelsInStrip, stripPinNumber), change accordingly if required
        strips[0] = Adafruit_NeoPixel(57, NP0);
        strips[1] = Adafruit_NeoPixel(61, NP1);
        strips[2] = Adafruit_NeoPixel(61, NP2);
        strips[3] = Adafruit_NeoPixel(61, NP3);
        strips[4] = Adafruit_NeoPixel(56, NP4);
        strips[5] = Adafruit_NeoPixel(56, NP5);
        strips[6] = Adafruit_NeoPixel(56, NP6);
        strips[7] = Adafruit_NeoPixel(61, NP7);
        strips[8] = Adafruit_NeoPixel(56, NP8);
        strips[9] = Adafruit_NeoPixel(60, NP9);
        strips[10] = Adafruit_NeoPixel(53, NP10);
        strips[11] = Adafruit_NeoPixel(57, NP11);
        strips[12] = Adafruit_NeoPixel(54, NP12);
        strips[13] = Adafruit_NeoPixel(59, NP13);

        //each array stores the number of LEDs in each cell
        uint8_t list0[] = {3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,2,2,2,3,4};
        uint8_t list1[] = {3,3,3,3,3,3,3,3,3,3,3,3,2,2,2,2,3,3,4,7};
        uint8_t list2[] = {3,3,3,3,3,3,3,3,3,4,3,3,3,3,2,2,3,3,4,4};
        uint8_t list3[] = {3,3,3,3,3,3,3,3,3,3,3,3,2,2,2,2,3,3,4,7};
        uint8_t list4[] = {2,3,3,3,3,3,3,3,3,3,2,2,2,2,2,2,3,3,4,5};
        uint8_t list5[] = {3,3,3,3,3,3,3,3,3,2,2,2,2,2,2,2,3,3,4,5};
        uint8_t list6[] = {4,3,3,3,3,3,3,3,3,2,2,2,2,2,2,2,2,3,4,5};
        uint8_t list7[] = {5,4,3,3,3,3,3,3,3,2,2,2,2,3,3,3,3,3,3,5};
        uint8_t list8[] = {5,3,3,3,3,2,2,2,2,2,2,2,2,3,3,3,3,3,3,4};
        uint8_t list9[] = {5,4,3,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,4};
        uint8_t list10[] = {5,4,3,3,2,2,2,3,2,2,2,2,2,2,2,3,3,3,3,3};
        uint8_t list11[] = {6,4,3,2,2,2,2,3,3,3,3,2,2,2,3,2,3,3,3,4};
        uint8_t list12[] = {6,3,2,2,2,2,2,2,3,3,3,2,2,2,2,3,3,3,3,4};
        uint8_t list13[] = {3,3,3,3,3,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3};

        pixels[0] = list0;
        pixels[1] = list1;
        pixels[2] = list2;
        pixels[3] = list3;
        pixels[4] = list4;
        pixels[5] = list5;
        pixels[6] = list6;
        pixels[7] = list7;
        pixels[8] = list8;
        pixels[9] = list9;
        pixels[10] = list10;
        pixels[11] = list11;
        pixels[12] = list12;
        pixels[13] = list13;
}

// public

void InteractiveWall::initialize() {
        for (int i=0; i<NUMROWS; i++) {
                strips[i].begin();
                strips[i].show();
        }
}

void InteractiveWall::setColor(int row, int col, uint32_t color) {
        if (row<0 || col<0 || row>=NUMROW || col>=NUMCOL) return;

        for (int i = 0; i < pixels[row][col]; i++) strips[row].setPixelColor(pixelSum(row,col)+i, color);
}

void InteractiveWall::setColor(int row, int col, uint8_t r, uint8_t g, uint8_t b) {
        //exits when out-of-bounds coordinates received
        if (row < 0 || col < 0 || row >= NUMROW || col >= NUMCOL) return;

        setColor(row, col, mapColor(r, g, b));
}

void InteractiveWall::setColor(uint32_t color) {
        for (int i = 0; i < NUMROW; i++) for (int j = 0; j < NUMCOL; j++) setColor(i, j, color);
}

void InteractiveWall::showColor(int row, int col, uint32_t color) {
        if (row<0 || col<0 || row>=NUMROW || col>=NUMCOL) return;

        setColor(row, col, color);
        strips[row].show();
}

void InteractiveWall::showColor(int row, int col, uint8_t r, uint8_t g, uint8_t b) {
        if (row<0 || col<0 || row>=NUMROW || col>=NUMCOL) return;

        showColor(row, col, mapColor(r,g,b));
}

void InteractiveWall:showRow(int row) {
        if (row<0 || row>=NUMROW) return;

        strips[row].show();
}

void InteractiveWall::showAll(void) {
        for (int i=0; i<NUMROWS; i++) strips[i].show();
}

void InteractiveWall::blank(void) {
        setColor(COLOR_BLANK);
}

uint32_t InteractiveWall::mapColor(uint8_t r, uint8_t g, uint8_t b) {
        return ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
}

int InteractiveWall::pixelSum(int row, int col) {
        int sum = 0;
        for (int i=0; i<col; i++) sum+= pixels[row][i];

        return sum;
}
