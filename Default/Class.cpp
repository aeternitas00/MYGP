#include "Class.h"

CParent::CParent(D3DXVECTOR3 * ipPos, LPDIRECT3DTEXTURE9 ipTxt, const int imfrm, const RECT iRct) 
	:mpos(*ipPos), pTexture(ipTxt), mfrm(imfrm), rctperfrm(iRct), nfrm(0) {
	D3DSURFACE_DESC temp;
	pTexture->GetLevelDesc(0, &temp);
	txtwidth = temp.Width;
	txtheight = temp.Height;
}

short CParent::draw(LPD3DXSPRITE* ipSprt) {
	if (nfrm / 3 >= mfrm) return OBJ_DESTROY;
	int x = nfrm / 3 * rctperfrm.right; int y = 0;
	while (x / txtwidth > 1) { x %= txtwidth; y += rctperfrm.bottom; }
	RECT temp{ x,y,x + rctperfrm.right,y + rctperfrm.bottom };
	this->nfrm += 1;
	(*ipSprt)->Draw(pTexture, &temp, NULL, &mpos, D3DXCOLOR(1, 1, 1, (float(mfrm + 2.5f) - float(nfrm / 2)) / float(mfrm)));
	return OBJ_DEFAULT;
}

CChild::CChild(D3DXVECTOR3 * ipPos, LPDIRECT3DTEXTURE9 ipTxt, const int imfrm, const RECT iRct, float ivel)
	:CParent(ipPos, ipTxt, imfrm, iRct), vel(ivel) {}

short CChild::draw(LPD3DXSPRITE * ipSprt) {
	if (!move())	return OBJ_MAKE_EXPL;
	if (nfrm / 3 >= mfrm) nfrm = 0;
	int x = nfrm / 3 * rctperfrm.right; int y = 0;
	while (x / txtwidth > 1) { x %= txtwidth; y += rctperfrm.bottom; }
	RECT temp{ x,y,x + rctperfrm.right,y + rctperfrm.bottom };
	this->nfrm += 1;
	(*ipSprt)->Draw(pTexture, &temp, NULL, &mpos, D3DXCOLOR(1, 1, 1, 1.0f));
	return OBJ_DEFAULT;
}

bool CChild::move()
{
	if (mpos.x >= MAX_X) { mpos.x = MAX_X; return false; }
	else if (mpos.x <= -rctperfrm.right) { mpos.x = -4; return false; }
	mpos.x += vel; return true;
}
