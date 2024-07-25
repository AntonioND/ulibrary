#include "ulib.h"

//Note: la bank A sera toujours à 0x06800000, la bank B sera toujours à 0x06820000, etc.
void ulChangeVramAllocation(int banks, UL_BANK_TYPE type)			{
	int i, textureSlot = 0;
	
	for (i=0;i<UL_BANKS_NUMBER;i++)		{
	   if (banks & (1 << i))			{
	      vuint8 *addr = (vuint8*)((u32)(&VRAM_A_CR) + i);
	      
	      switch (type)		{
	         //LCD: par chance c'est pareil pour tous
	         case UL_BANK_TYPE_LCD:
	            *addr = VRAM_ENABLE;
	            break;
	         
	         //Texture: il faut gérer l'incrémentation des slots
	         case UL_BANK_TYPE_TEXTURE:
	            *addr = VRAM_ENABLE | VRAM_A_TEXTURE | VRAM_OFFSET(i);
	            textureSlot++;
	            break;
	         
	         //Palettes de texture
	         case UL_BANK_TYPE_TEXPAL:
	            *addr = VRAM_ENABLE | VRAM_E_TEX_PALETTE;
	            break;
	      }

	   }
	}
}



