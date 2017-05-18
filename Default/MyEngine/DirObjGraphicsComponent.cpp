#include "stdafx.h"
#include "DirObjGraphicsComponent.h"


DirObjGraphicsComponent::DirObjGraphicsComponent()
{
}



VOID DirObjGraphicsComponent::Update(GameObject* pObj)
{
	if (pObj->txtid == -1) return;
	TEXTURESET temp = *RenderManager::GetInstance()->GetTexture(pObj->txtid);
	RECT rtemp = { 0,0,temp.spfx,temp.spfy };

	rtemp.left = temp.spfx*pObj->GetDir(); rtemp.right = temp.spfx*pObj->GetDir();
	
	D3DXMATRIX mat;
	D3DXMatrixTranslation(&mat, pObj->pos.x, pObj->pos.y, 0.0);

	RenderManager::GetInstance()->DrawObj(pObj->pos, pObj->txtid, rtemp, mat);
}

DirObjGraphicsComponent::~DirObjGraphicsComponent()
{
}
