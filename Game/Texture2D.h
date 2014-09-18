#pragma once
class CTexture2D
{
public:
	CTexture2D(void);
	~CTexture2D(void);
	LPDIRECT3DTEXTURE9 m_pTexture;
	RECT m_rRect;
	void LoadFromFile(const char * filename);
};

