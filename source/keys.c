#include "ulib.h"

//UL_CONTROLLER ul_internalKeys;
//UL_CONTROLLER *ul_defaultKeys = &ul_internalKeys;
//#define ul_keys (*ul_defaultKeys)

UL_CONTROLLER ul_keys = {
   {{0}},				//Touches par défaut
   {{0}},
   {{0}},
   
   0, 0,					//Pas d'autorepeat par défaut
	UL_KEY_UP|UL_KEY_DOWN|UL_KEY_LEFT|UL_KEY_RIGHT|UL_KEY_L|UL_KEY_R,			//L'autorepeat concernera ces touches
	0,						//Interne
   
   {
      128, 96,			//Position du touchpad
      30, 0,			//Double clic
      0,	0, 0, 0,		//Etat du Touchpad
      0, 0,				//Delta
   },   
};

void ulReadKeys(int flags)			{
    scanKeys();
   unsigned short buttons = keysHeld();
   signed short lastX, lastY;
   
	if (ul_keys.autoRepeatInterval > 0)			{					//Auto repeat activé?
		//Si ça change -> compteur à zéro
		if (ul_keys.held.value != buttons)
			ul_keys._autoRepeatCounter=0;
		else			{
			ul_keys._autoRepeatCounter++;
			if (ul_keys._autoRepeatCounter >= ul_keys.autoRepeatInit)			{
				//AutoRepeat déclenché -> déclenchement toutes les autoRepeatInterval coups
				if ((ul_keys._autoRepeatCounter - ul_keys.autoRepeatInit) % ul_keys.autoRepeatInterval == 0)
					ul_keys.held.value &= ~ul_keys.autoRepeatMask;
			}
		}
	}
	
	ul_keys.pressed.value = ~ul_keys.held.value & buttons;
	ul_keys.released.value = ul_keys.held.value & ~buttons;
	ul_keys.held.value = buttons;

	lastX = ul_keys.touch.x;
	lastY = ul_keys.touch.y;
	
	//Touchpad
	if (ul_keys.held.touch)		{
		touchPosition touch_pos;
		touchRead(&touch_pos);
		ul_keys.touch.x = touch_pos.px;
		ul_keys.touch.y = touch_pos.py;
	}

	//Ne pas prendre le delta au moment du clic, il serait trop grand	
	if (ul_keys.pressed.touch)
		ul_keys.touch.deltaX = ul_keys.touch.deltaY = 0;
	else		{
		ul_keys.touch.deltaX = ul_keys.touch.x - lastX;
		ul_keys.touch.deltaY = ul_keys.touch.y - lastY;
	}
	
	ul_keys.touch.held = ul_keys.held.touch;
	ul_keys.touch.click = ul_keys.pressed.touch;
	ul_keys.touch.doubleClick = 0;
	
	if (ul_keys.touch.click)		{
	   if (ul_keys.touch._clickTime > 0)			{
	   	ul_keys.touch.doubleClick = 1;
	   	//Rajout pour éviter de faire trop de double clics à la fois
			ul_keys.touch._clickTime = 0;
	 	}  	
	   else
			ul_keys.touch._clickTime = ul_keys.touch.doubleClickDelay;
	}
	else if (ul_keys.touch._clickTime > 0)
		ul_keys.touch._clickTime--;

	ul_keys.touch.released = ul_keys.released.touch;
	
	//Ne fonctionne pas correctement
//	ul_keys.touch.pressure = (((IPC->touchXpx * IPC->touchZ2) >> 6) / IPC->touchZ1) - (IPC->touchXpx >> 6);
	return;
}
   

