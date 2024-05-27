#include "hw069.h"

// Map of characters to their 7-segment display binary codes.
const std::map<char, uint8_t> HW069::SEGMENTS = {
    {'0', 0b00111111},
    {'1', 0b00000110},
    {'2', 0b01011011},
    {'3', 0b01001111},
    {'4', 0b01100110},
    {'5', 0b01101101},
    {'6', 0b01111101},
    {'7', 0b00000111},
    {'8', 0b01111111},
    {'9', 0b01101111},
    {'A', 0b01110111},
    {'B', 0b01111100},
    {'C', 0b00111001},
    {'D', 0b01011110},
    {'E', 0b01111001},
    {'F', 0b01110001},
    {'G', 0b00111101},
    {'H', 0b01110110},
    {'I', 0b00110000},
    {'J', 0b00001110},
    {'L', 0b00111000},
    {'N', 0b01010100},
    {'O', 0b00111111},
    {'P', 0b01110011},
    {'R', 0b01010000},
    {'S', 0b01101101},
    {'T', 0b01111000},
    {'U', 0b00111110},
    {'Z', 0b01011011},
    {'a', 0b01110111},
    {'b', 0b01111100},
    {'c', 0b00111001},
    {'d', 0b01011110},
    {'e', 0b01111001},
    {'f', 0b01110001},
    {'g', 0b00111101},
    {'h', 0b01110100},
    {'i', 0b00110000},
    {'j', 0b00001110},
    {'l', 0b00111000},
    {'n', 0b01010100},
    {'o', 0b01011100},
    {'p', 0b01110011},
    {'r', 0b01010000},
    {'s', 0b01101101},
    {'t', 0b01111000},
    {'u', 0b00011100},
    {'-', 0b01000000},
    {'_', 0b00001000},
    {' ', 0b00000000},
};

// Bitmaps for the snake animation segments.
const uint8_t HW069::SEGMENT_MAP[12] = {
    0b00000001, 0b00000001, 0b00000001, 0b00000001, 0b00000010, 0b00000100, 0b00001000, 0b00001000, 0b00001000, 0b00001000, 0b00010000, 0b00100000};

// Positions for the snake animation digits.
const uint8_t HW069::DIGIT_POS[12] = {0, 1, 2, 3, 3, 3, 3, 2, 1, 0, 0, 0};

// Constructor for the HW069 class.
HW069::HW069(uint8_t clkPin, uint8_t dioPin, uint8_t brightness)
    : display(clkPin, dioPin) {
    display.setBrightness(brightness);
}

// Returns the segment representation for the given character.
uint8_t HW069::getSegmentForChar(char c) {
    auto it = SEGMENTS.find(c);
    if (it != SEGMENTS.end())
    {
        return it->second;
    }
    else
    {
        return 0b01000000;  // '-' for unknown characters
    }
}

// Sets the display to show the given string.
// Supports ':' for colon.
void HW069::setStr(const char* str) {
    uint8_t data[] = {0, 0, 0, 0};
    bool colon = false;

    int len = strlen(str);
    int segmentIndex = 0;

    for (int i = 0; i < len && segmentIndex < 4; i++) {
        if (str[i] == ':') {
            colon = true;
            segmentIndex = 2;
        } else {
            data[segmentIndex] = getSegmentForChar(str[i]);
            segmentIndex++;
        }
    }

    if (colon) {
        data[1] |= 0b10000000;
    }

    display.setSegments(data);
}

// Sets the display to show the given integer, zero-padded to 4 digits.
void HW069::setInt(int n) {
    char buffer[5];
    snprintf(buffer, sizeof(buffer), "%04d", n);
    setStr(buffer);
}

// Sets the display to show the given float, formatted as "XX.XX".
void HW069::setFloat(float n) {
    char buffer[6];
    int integerPart = static_cast<int>(n) % 100;
    int fractionalPart = static_cast<int>((n - static_cast<int>(n)) * 100 + 0.5);
    snprintf(buffer, sizeof(buffer), "%02d:%02d", integerPart, fractionalPart);
    setStr(buffer);
}

// Creates a snake line on the display with given step and length.
// Used for a simple animation.
void HW069::setSnake(int step, int length) {
    uint8_t data[] = {0, 0, 0, 0};  // clear display

    if (length < 1)
        length = 1;

    if (length > 12)
        length = 12;

    for (int i = 0; i < length; i++) {
        int pos = (step - i - 1) % 12;
        if (pos >= 0) {
            data[DIGIT_POS[pos]] |= SEGMENT_MAP[pos];
        }
    }

    display.setSegments(data);
}
