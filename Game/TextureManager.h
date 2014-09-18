#pragma once
#include "Texture2D.h"
struct TextureInfo{
	std::string path;
	CTexture2D * texture;
};

class CTextureManager
{
public:
	CTextureManager(void);
	~CTextureManager(void);

	std::vector<TextureInfo> v_TextureInfo;

	CTexture2D * LoadTexture(const char * path);
};

