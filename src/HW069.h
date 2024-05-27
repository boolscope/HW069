#ifndef HW069_H
#define HW069_H

#include <TM1637Display.h>
#include <map>
#include <Arduino.h>

/**
 * @class HW069
 * @brief Class to control a TM1637 4-digit 7-segment display.
 */
class HW069
{
public:
    /**
     * @brief Constructor for the HW069 class.
     * @param clkPin The clock pin for the TM1637.
     * @param dioPin The data I/O pin for the TM1637.
     * @param brightness The brightness level of the display (0x00 to 0x0f).
     */
    HW069(uint8_t clkPin, uint8_t dioPin, uint8_t brightness = 0x0f);

    /**
     * @brief Sets the display to show the given string. Supports ':' for colon.
     * @param str The string to display.
     */
    void setStr(const char *str);

    /**
     * @brief Sets the display to show the given integer, zero-padded to 4 digits.
     * @param n The integer to display.
     */
    void setInt(int n);

    /**
     * @brief Sets the display to show the given float, formatted as "XX.XX".
     * @param n The float to display.
     */
    void setFloat(float n);

    /**
     * @brief Creates a snake animation on the display with given step and length.
     * @param step The current step of the snake animation.
     * @param length The length of the snake.
     */
    void setSnake(int step, int length);

private:
    TM1637Display display; /**< The TM1637 display object */

    /**
     * @brief Returns the segment representation for the given character.
     * @param c The character to get the segment representation for.
     * @return The segment representation of the character.
     */
    uint8_t getSegmentForChar(char c);

    static const std::map<char, uint8_t> SEGMENTS; /**< Map of characters to their 7-segment display representations. */

    static const uint8_t SEGMENT_MAP[12]; /**< Bitmaps for snake animation segments. */

    static const uint8_t DIGIT_POS[12]; /**< Positions for snake animation digits. */
};

#endif // HW069_H