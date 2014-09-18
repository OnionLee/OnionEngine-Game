#include "StdAfx.h"
#include "TextureManager.h"
#include "Director.h"


CTextureManager::CTextureManager(void)
{

}


CTextureManager::~CTextureManager(void)
{
	for(int i = 0; i<v_TextureInfo.size(); i++)
	{
		v_TextureInfo[i].texture->m_pTexture->Release();
	}

	v_TextureInfo.clear();
}

CTexture2D * CTextureManager::LoadTexture(const char * path)
{
	//Ȥ�� ����ߴ� ��ΰ� �ִٸ� �� �ؽ��ĸ� ����
	for(int i =0; i<v_TextureInfo.size(); i++)
	{
		if(strcmp(v_TextureInfo[i].path.c_str(),path) == 0)
		{
			return v_TextureInfo[i].texture;
		}
	}

	//���ٸ� �ؽ��ĸ� �����Ѵ�.
	std::string error;
	error.append(path);
	error.append("->not found");

	D3DXIMAGE_INFO texinfo;
	TextureInfo temp;

	//�ؽ��� �޸� �Ҵ�
	temp.path = path;
	temp.texture = new CTexture2D();

	D3DXCreateTextureFromFileEx(DrawMgr->m_pd3dDevice,
								path,
								D3DX_DEFAULT,
								D3DX_DEFAULT,
								1,
								0,
								D3DFMT_UNKNOWN,
								D3DPOOL_MANAGED,
								1,
								1,
								NULL,
								&texinfo,
								NULL,
								&temp.texture->m_pTexture);
	if(temp.texture == 0)
	{
		MessageBox(NULL,error.c_str(),"error",MB_OK);
		return NULL;
	}

	temp.texture->m_rRect.right = texinfo.Width;
	temp.texture->m_rRect.bottom = texinfo.Height;

	v_TextureInfo.push_back(temp);

	return temp.texture;
}
