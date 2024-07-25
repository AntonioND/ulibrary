/*! \file messagebox.h
    \brief
    	Message boxes.
*/

#ifndef __UL_MESSAGEBOX_H__
#define __UL_MESSAGEBOX_H__

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup messagebox Message boxes

	Basic message box support for µLibrary.
	@{
*/

/** Structure defining buttons. */
typedef struct		{
   u16 key;									//!< Key associated with the button. Use UL_KEY_xxx from the UL_KEYPAD_BITS enumeration. If you OR several keys together, if the user presses ONE of these keys, then this button will be considered as pressed.
   char *text;								//!< Button text
} UL_MSGBOX_BUTTON;

/** Displays a message box (extended version).

	\param text
		Main text to be displayed. This can be a big string with line endings (\\n).
	\param title
		Title, displayed on top of the window.
	\param nbButtons
		Number of buttons in the buttons pointer.
	\param buttons
		Table of buttons. The number of buttons available in this table must be given by the nbButton parameter.
	\param fnRender
		Pointer to an own render function. Needed to draw your own background because on the DS the display contents can't be kept from a frame to
		another, it must be entirely erased once per frame. Make sure your function will not draw an important number of polygons, else it will
		leave no room for the message box (1 quad per character, 1 tri for each line, etc.).
	\param reserved
		Set to 0.

This function displays a message box centered on the screen. Dimensions are guessed automatically depending on the title and number of buttons.
The aspect of those windows may change in the future, as well as how the text is displayed in it.
*/
extern int ulMessageBoxEx(const char *text, const char *title, int nbButtons, UL_MSGBOX_BUTTON *buttons, void (*fnRender)(), u32 reserved);

/** @} */ // end of messagebox

#ifdef __cplusplus
}
#endif

#endif

