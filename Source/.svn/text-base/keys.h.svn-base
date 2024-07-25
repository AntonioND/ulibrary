/*! \file keys.h
    \brief
    	Support for game keys and touchpad in µLibrary.
*/

#ifndef __UL_KEYS_H__
#define __UL_KEYS_H__

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup keys

	Support for game keys and touchpad in µLibrary.
	@{
*/

/** Key list. */
typedef union		{
	struct		{
		int A:1;						//!< A key
		int B:1;						//!< B key
		int select:1;				//!< Select key
		int start:1;				//!< Start key
		int right:1;				//!< D-Pad right key
		int left:1;					//!< D-Pad left key
		int up:1;					//!< D-Pad up key
		int down:1;					//!< D-Pad down key
		int R:1;						//!< R shoulder key
		int L:1;						//!< L shoulder key
		int X:1;						//!< X key
		int Y:1;						//!< Y key
		//Touch: le stylet est appuyé, lid: état du couvercle
		int touch:1;				//!< Stylus is down
		int lid:1;					//!< Lid is closed
		int reserved:2;			//!< Not used
	};
	unsigned short value;		//!< Integer value, grouping every bit defined above
} UL_KEYLIST;

/** Structure containing the controller state. */
typedef struct		{
   UL_KEYLIST held;						//!< List of keys currently held by the user. It's a UL_KEYLIST structure, use a dot to get through. Example: ul_keys.held.start.
   UL_KEYLIST pressed;					//!< List of keys pressed. Pressed keys are only reported once when the user presses it, or more times after a moment if the autorepeat feature is enabled. If you're making a menu, that's what you should use.
   UL_KEYLIST released;					//!< Reported once when a key just released.
	
	int autoRepeatInit;					//!< Time for autorepeat initialization
	int autoRepeatInterval;				//!< Interval before autorepeat enable
	int autoRepeatMask;					//!< Keys concerned by autorepeat. Keys like start should not be autorepeated for example, but up/down could be useful for a menu.
	int _autoRepeatCounter;				//Compteur (interne)

	/** Structure holding everything about touchpad. */
	struct touch	{
		signed short x;				//!< Touchpad horizontal position in pixels
		signed short y;				//!< Touchpad vertical position in pixels
		u8 doubleClickDelay;			//!< Maximum delay so that a dual touchpad press can be detected as a double click
		u8 _clickTime;
		/** Unnamed Bitfield for touchpad */
//		struct		{
			u16 held:1;					//!< Touchpad stylus is currently down
			u16 click:1;				//!< Reported once when the stylus touches the screen
			u16 released:1;			//!< Reported once when the stylus is released
			u16 doubleClick:1;		//!< Reported once when a double click even occurs
//		};
		signed short deltaX;			//!< Horizontal delta (movement)
		signed short deltaY;			//!< Vertical delta (movement)
	} touch;
} UL_CONTROLLER;

/** Contains the default controller state read by ulReadKeys. */
extern UL_CONTROLLER ul_keys;

/** Bit values for the keypad buttons. */
enum UL_KEYPAD_BITS {
	UL_KEY_A			= 0x1,		//!< Keypad A button.
	UL_KEY_B			= 0x2,		//!< Keypad B button.
	UL_KEY_SELECT	= 0x4,		//!< Keypad SELECT button.
	UL_KEY_START	= 0x8,		//!< Keypad START button.
	UL_KEY_RIGHT	= 0x10,		//!< Keypad RIGHT button.
	UL_KEY_LEFT		= 0x20,		//!< Keypad LEFT button.
	UL_KEY_UP		= 0x40,		//!< Keypad UP button.
	UL_KEY_DOWN		= 0x80,		//!< Keypad DOWN button.
	UL_KEY_R			= 0x100,		//!< Right shoulder button.
	UL_KEY_L			= 0x200,		//!< Left shoulder button.
	UL_KEY_X			= 0x400,		//!< Keypad X button.
	UL_KEY_Y			= 0x800,		//!< Keypad Y button.
	UL_KEY_TOUCH	= 0x1000,	//!< Touchscreen pen down.
	UL_KEY_LID		= 0x2000		//!< Lid state.
};

/** Sets the key autorepeat features (all in one). */
#define ulSetKeyAutorepeat(keys,init,interval)		( ul_keys.autoRepeatMask = keys, ul_keys.autoRepeatInit = init, ul_keys.autoRepeatInterval = interval )
/** Sets the keymask for autorepeat: only keys present in this mask will be autorepeated. */
#define ulSetKeyAutorepeatMask(mask)					(ul_keys.autoRepeatMask = mask)
/** Sets the delay for the autorepeat feature to be initialized.
Keys left in their state for the defined delay (number of ulReadKeys state, so 60 should be equal to a second) will be thrown again in the pressed member.
So, you only have to check the pressed member if you want to use that keys for a menu, for example. A typical value would be 30 (1/2 second). */
#define ulSetKeyAutorepeatInit(value)					(ul_keys.autoRepeatInit = value)
/** Sets the rate at which keys will be repeated once the autorepeat has begun. A typical value could be 10 (6 times per second). */
#define ulSetKeyAutorepeatInterval(value)				(ul_keys.autoRepeatInterval = value)
/** Sets the maximum delay for a double click on the touchpad to be taken in account. The default value is 30 (1/2 second). */
#define ulSetTouchpadDoubleClickDelay(value)			(ul_keys.touch.doubleClickDelay = value)

/** Reads the keypad and touchpad state.
	\param flags
		Let it to 0 for now.

If you want to use the µLibrary keypad system, you need to call this function once per frame (else autorepeat and double-click feature won't work). That is, 60 times per second.

The result is placed into the ul_keys system variable. You can then read from it. Examples:
   \code
ulReadKeys(0);
if (ul_keys.held.down)
	//down key is held
   \endcode
*/
void ulReadKeys(int flags);

/** @} */ // end of keys

#ifdef __cplusplus
}
#endif

#endif

