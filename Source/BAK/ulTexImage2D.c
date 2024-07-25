//Inspirée de la fonction de libnds
int ulTexImage2D(int target, int empty1, int type,
                 int sizeX, int sizeY,
                 int empty2, int param,
                 uint8* texture) {
//---------------------------------------------------------------------------------
	uint32 size = 0;
	int32 texId;
	uint32* addr;
//  uint32 vramTemp;

	size = 1 << (sizeX + sizeY + 6);
	size = (size * ul_pixelSizes[type]) >> 3;

/*  switch (type) {
    case GL_RGB:
    case GL_RGBA:
      size = size << 1;
      break;
    case GL_RGB4:
      size = size >> 2;
      break;
    case GL_RGB16:
      size = size >> 1;
      break;

    default:
      break;
  }*/
  
	texId = ulTexVramAllocBlock(size);
	if (texId < 0)
		return 0;
	addr = ulTexVramOffsetToAddress(texId);
  
	// unlock texture memory
	ulChangeVramAllocation(ul_texVramBanks, UL_BANK_TYPE_LCD);
	
	if (type == GL_RGB) {
		// We do GL_RGB as GL_RGBA, but we set each alpha bit to 1 during the copy
		u16 * src = (u16*)texture;
		u16 * dest = (u16*)addr;
		
		//Valeur de la texture: utilisé pour GFX_TEX_FORMAT    
		ulTexParameter(sizeX, sizeY, addr, GL_RGBA, param);
		
		if (texture)		{
			while (size--) {
				*dest++ = *src | (1 << 15);
				src++;
			}
		}
	}
	else		{
		// For everything else, we do a straight copy
		ulTexParameter(sizeX, sizeY, addr, type, param);
		if (texture)
			swiCopy((uint32*)texture, addr , (size >> 2) | COPY_MODE_WORD);
	}

 	ulChangeVramAllocation(ul_texVramBanks, UL_BANK_TYPE_TEXTURE);
	return 1;
}
