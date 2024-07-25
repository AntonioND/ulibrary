#include "ulib.h"

void _drawButton(int x0, int y0, int x1, int y1, const char *text, int highlight)		{
   u32 xSpace = (x1 - x0) - ulGetStringWidth(text);
   u32 ySpace = ((y1 - y0) - ul_curFont->charHeight) >> 1;
   
	ulDrawRect(x0, y0, x1, y1, 0);
	if (highlight)
		ulDrawGradientRect(x0 + 1, y0 + 1, x1 - 1, y1 - 1, RGB15(18, 9, 9), RGB15(15, 7, 7), RGB15(15, 7, 7), RGB15(12, 6, 6));
	else
		ulDrawGradientRect(x0 + 1, y0 + 1, x1 - 1, y1 - 1, RGB15(18, 18, 18), RGB15(15, 15, 15), RGB15(15, 15, 15), RGB15(12, 12, 12));
	ulDrawString(x0 + xSpace / 2, y0 + ySpace, text);
}

#define UL_MSGBOX_TOUCHPAD_SUPPORT

//Message box, version étendue
//Note: les >> 1 représentent / 2, malheureusement comme j'ai été obligé d'utiliser des nombres signés.
int ulMessageBoxEx(const char *text, const char *title, int nbButtons, UL_MSGBOX_BUTTON *buttons, void (*fnRender)(), u32 reserved)
{
   s32 x0, y0, x1, y1, width, height, textWidth, textHeight, titleHeight = ul_curFont->charHeight + 4;
//   const UL_COLOR backColor = RGB15(212 >> 3, 208 >> 3, 200 >> 3);
//   const UL_COLOR title1 = RGB15(10 >> 3, 36 >> 3, 106 >> 3), title2 = RGB15(166 >> 3, 202 >> 3, 240 >> 3);
   const UL_COLOR backColor0 = RGB15(103 >> 3, 107 >> 3, 115 >> 3), backColor1 = RGB15(73 >> 3, 77 >> 3, 85 >> 3), backColor2 = RGB15(43 >> 3, 47 >> 3, 55 >> 3);
   const UL_COLOR title1 = RGB15(0 >> 3, 0 >> 3, 128 >> 3), title2 = RGB15(16 >> 3, 132 >> 3, 208 >> 3);
   u32 i;
	s32 buttonMaxWidth = 0, totalButtonsWidth;
	const u32 buttonSpace = 4, buttonHeight = ulMax(ul_curFont->charHeight + 4, 14);

	textWidth = ulGetStringWidth(title);
   //Par défaut, on utilise une largeur de 140, qui sera éventuellement augmentéee par la taille du titre
   width = ulMax(140, textWidth + 4);
	
	//Trouvons le bouton qui possède le texte le plus long
	for (i=0;i<nbButtons;i++)		{
	   buttonMaxWidth = ulMax(buttonMaxWidth, ulGetStringWidth(buttons[i].text) + 5);
	}
	totalButtonsWidth = (buttonSpace + buttonMaxWidth) * nbButtons;
	//S'assure que la fenêtre sera assez grande pour contenir tous les boutons
	width = ulMax(totalButtonsWidth + 4, width);

   //Calculons la hauteur de la boîte avec cette largeur
   textHeight = ulGetTextBoxHeight(width - 4, 150, text, 0);
	height = titleHeight + 4 + textHeight + 4 + buttonHeight + 4;

	//Calcule les positions de la fenêtre
	x0 = (SCREEN_WIDTH - width) >> 1;
	x1 = (SCREEN_WIDTH + width) >> 1;
	y0 = (SCREEN_HEIGHT - height) >> 1;
	y1 = (SCREEN_HEIGHT + height) >> 1;

	//Variables pour la gestion de la fenêtre
	#ifdef UL_MSGBOX_TOUCHPAD_SUPPORT
		int titleMoving = 0, buttonSelected = -1, buttonActive = -1;
	#endif
	//Le bouton pressé a été trouvé!
	int returnButton = -1;
		
	while (returnButton == -1)			{
		ulReadKeys(0);

	   ulStartDrawing2D();
	   
	   if (fnRender)
	   	fnRender();
	   
		//Le tour
		ulDrawRect(x0, y0, x1, y1, RGB15(0, 0, 0));
		//Le dégradé du titre
		ulDrawGradientRect(x0 + 1, y0 + 1, x1 - 1, y0 + titleHeight, title1, title2, title1, title2);
		//Le dégradé du centre (texte)
		ulDrawGradientRect(x0 + 1, y0 + titleHeight, x1 - 1, y1 - 1, backColor0, backColor1, backColor1, backColor2);
		//La ligne séparatrice du titre
		ulDrawLine(x0, y0 + titleHeight, x1, y0 + titleHeight, RGB15(0, 0, 0));
		
		//Dessine le titre
		ulSetTextColor(RGB15(31, 31, 31));
		ulDrawTextBox((x0 + x1 - textWidth) >> 1, y0 + 3, x1 - 2, y0 + titleHeight, title, 0);
		//Le texte principal
		ulDrawTextBox(x0 + 2, y0 + titleHeight + 4, x1 - 2, y0 + titleHeight + 4 + textHeight, text, 0);
		
		//Les boutons à présent
		s32 buttonX = (x0 + x1 - totalButtonsWidth) >> 1, buttonY = y0 + titleHeight + 4 + textHeight + 4;
		s32 x = buttonX + (buttonSpace >> 1);
		for (i=0;i<nbButtons;i++)		{
		   //Highlight du bouton s'il est sélectionné et que le curseur est encore dessus
		   int highlight = (buttonSelected == buttonActive && buttonSelected == i);
			//Test si la touche associée au bouton est pressée
			if (ul_keys.pressed.value & buttons[i].key)		{
			   returnButton = i;
			   highlight = 1;
			}
		   _drawButton(x, buttonY, x + buttonMaxWidth, buttonY + buttonHeight, buttons[i].text, highlight);
		   x += buttonMaxWidth + buttonSpace;
		}
		
		ulEndDrawing();
		ulSyncFrame();
		
		#ifdef UL_MSGBOX_TOUCHPAD_SUPPORT
		//Le code de gestion du touchpad ne fonctionne que si le touchpad est effectivement actif...
		if (ulGetMainLcd() == 0)			{
			//Essaie de trouver sur quel bouton le stylet est actuellement
			buttonActive = -1;
			x = buttonX + (buttonSpace >> 1);
			for (i=0;i<nbButtons;i++)		{
			   //On touche ce bouton?
			   if (ul_keys.touch.x >= x && ul_keys.touch.y >= buttonY
			   	&& ul_keys.touch.x <= x + buttonMaxWidth && ul_keys.touch.y <= buttonY + buttonHeight)			{
					buttonActive = i;
		   	}
			   x += buttonMaxWidth + buttonSpace;
			}
		
			//Déplacement de la fenêtre
			if (titleMoving)		{
			   x0 += ul_keys.touch.deltaX;
			   y0 += ul_keys.touch.deltaY;
			   x1 += ul_keys.touch.deltaX;
			   y1 += ul_keys.touch.deltaY;
			}
			
			if (ul_keys.touch.click)			{
			   //Aucun bouton? Alors on déplacera toute la boîte
			   if (buttonActive == -1)		{
			      if (ul_keys.touch.x >= x0 && ul_keys.touch.y >= y0
			      	&& ul_keys.touch.x <= x1 && ul_keys.touch.y <= y1)
						titleMoving = 1;
				}
				else
					buttonSelected = buttonActive;
			}
			//Stylet relâché
			if (ul_keys.touch.released)		{
			   //Ne bouge plus le titre
				titleMoving = 0;
				//On a choisi un bouton :)
				if (buttonSelected >= 0 && buttonActive == buttonSelected)
					returnButton = buttonSelected;
				//Plus de bouton sélectionné
				buttonSelected = -1;
			}
		}
		#endif
	}
	return returnButton;
}

