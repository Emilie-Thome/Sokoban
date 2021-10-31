#include <SDL2/SDL.h>

/**
 * @brief Initialize the GUI windows
 *
 * The width and height of the window are specified in number of cells.
 * `ICON_SIZE` is a constant determining the size in pixel of an icon.
 *
 * @param title  a string representing the title of the window
 *
 * @param width  the width of the window (number of cells)
 *
 * @param height the height of the window (number of cells)
 */
extern void GUI_Init(char *title, int width, int height);

/**
 * @brief Prepare to display a symbol
 *
 * @param x      the x position of the symbol to display
 *
 * @param y      the y position of the symbol to display
 *
 * @param symbol the symbol to display, represented by a `char`
 *               as defined in the `symbols` array
 */
extern void GUI_Prep(int x, int y, char symbol);

/**
 * @brief Display
 */
extern void GUI_Show();

/**
 * @brief Display a click button
 *
 * @param width      the width of the map
 *
 * @param height      the height of the map
 */
extern void GUI_click_button(int width, int height);

/**
 * @brief Get the key pressed by the user
 *
 * @return a char representing the key pressed by the user
 */
extern int GUI_GetKey(void);

/**
 * @brief Close the GUI window
 *
 */
extern void GUI_Close(int code);

/**
 * @brief Wait for a mouse click on the window
 *
 */
extern void WaitClick();

/**
 * @brief Wait for time ms.
 *
 * @param time the time to wait (in ms)
 *
 */
extern void Pause(int time);
