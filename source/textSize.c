#include "ulib.h"

int ulGetStringWidth(const char *str)
{
	unsigned char c;
	u32 x = 0;

	//Parcourt tous les caractères	
	while(*str)			{
		c = *(unsigned char*)str++;
		x += ul_curFont->charWidths[c];
	}

	return x;
}

int ulGetTextBoxHeight(int width, int maxHeight, const char *text, int format)
{
	int x,y, x2;
	unsigned char c, newLine = 1;
	const char *text2;

	x = y = 0;

	while (*text)		{
		c = *text;
		if (c == ' ')
		{
			text2 = text;
			x2 = x;
			do		{
				x2 += ul_curFont->charWidths[(int)(*text2++)];
				if (x2 > width)		{
					text++;
					goto newline;
				}
			} while(*text2 != '\n' && *text2 != ' ' && *text2);
		}
		if (x + ul_curFont->charWidths[c] > width || *text=='\n')			{
newline:
			//Prochaine ligne
			x = 0;
			if (newLine && *text=='\n')
				y += ul_curFont->charHeight;
			newLine = 1;
			//Retour -> saute
			if (*text == '\n')
				text++;
			continue;
		}
		//Trop bas -> terminé
		if (y + ul_curFont->charHeight > maxHeight && maxHeight > 0)
			break;
		if (newLine)
			newLine = 0, y += ul_curFont->charHeight;
		x += ul_curFont->charWidths[c];
		text++;
	}
	
	return y;
}


