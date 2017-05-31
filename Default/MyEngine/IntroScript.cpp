#include "stdafx.h"
#include "IntroScript.h"


IntroScript::IntroScript():before(clock()),after(clock()),trigger(0)
{
}


IntroScript::~IntroScript()
{
}

VOID IntroScript::Update(GameObject * pObj)
{
	if (trigger != -1) {
		IntroCharacter* Obj = dynamic_cast<IntroCharacter*>(pObj);
		if (Obj == NULL) return;
		after = clock();
		static float max = 1.0f;
		static float add = 0.05f;
		D3DXVECTOR2 CENTER;
		D3DXMATRIX mat;
		D3DXMATRIX mat2;
		D3DXMatrixTranslation(&mat,MAX_X / 2 - 443 / 2, 112 - 182 / 2, 0);
		switch (trigger)
		{
		case 0:
			if ((double)(after - before) / CLOCKS_PER_SEC >= 4.9) {
				trigger = 1; before = clock();
				Obj->SetStatus(0); Obj->velocity.x = 0;
			}
			break;
		case 1:
			if ((double)(after - before) / CLOCKS_PER_SEC >= 1.5) {
				trigger = 2; before = clock(); Obj->SetStatus(2);
				Obj->velocity.x = 1.5; Obj->velocity.y = -8.0f;

			}
			break;
		case 2:
			if (max < 1.5f) { max += add; add *= 0.90f; }
				else { max = 1.5f; }
				if (Obj->pos.y <= 0) {
					Obj->acceleration.x = 0;
				}
				CENTER= D3DXVECTOR2(MAX_X / 2 + ((Obj->pos.x+9 - MAX_X/2)*((max-1.0f) / 0.5f)),
					MAX_Y / 2 + ((Obj->pos.y+40 - MAX_Y/2)*((max - 1.0f) / 0.5f)));
			RenderManager::GetInstance()->SetDefaultMatrixZoomUp(CENTER, max);
			
			if ((double)(after - before) / CLOCKS_PER_SEC >= 3.2){
				trigger = 3; before = clock(); max = 2.0f; add = 0.175f; 

				SystemManager::GetInstance()->GetObjectList().front()->SetTxt(-1);
				GameObject* nObj = new GameObject(D3DXVECTOR3(MAX_X - 237, 0, 0), TXTID_INTROBLK4);
				//nObj->SetComponent();
				SystemManager::GetInstance()->AddObject(nObj);
				Obj->pos.x = MAX_X / 2 + 9; Obj->pos.y = MAX_Y / 2+9;
				Obj->velocity.x = 1.0f; Obj->velocity.y = -11.0f;
			}
			break;
		case 3:
			if (max > 1.0f) { max -= add;  add *= 0.85f; }
			else { max = 1.0f; }
			RenderManager::GetInstance()->SetDefaultMatrixZoomUp(D3DXVECTOR2(MAX_X/2,MAX_Y/2), max);
			if (Obj->pos.y+9<=0) {
				SystemManager::GetInstance()->GetObjectList().back()->SetTxt(-1);
				RenderManager::GetInstance()->ResetDefaultMatrix(); 
				GameObject* nObj = new GameObject(D3DXVECTOR3(MAX_X - 242, MAX_Y-190, 0), TXTID_INTROBLK5);
				SystemManager::GetInstance()->AddObject(nObj);
				trigger = 4; before = clock(); /*Obj->pos.x = MAX_X / 2 - 9;*/ Obj->pos.y = MAX_Y;
			}
			break;
		case 4:
			RenderManager::GetInstance()->DrawObj(D3DXVECTOR3(MAX_X / 2 - 443 / 2, 20, 0), TXTID_TITLE,
				RECT{ 0,0,443,182 }, mat);
			if (Obj->pos.y <=  420) {
				max = 1.0f;add = 0.05f;
				Obj->acceleration.y = 0.26f; trigger = 5;
			}
			break;
		case 5:
			RenderManager::GetInstance()->DrawObj(D3DXVECTOR3(MAX_X / 2 - 443 / 2, 20, 0), TXTID_TITLE,
				RECT{ 0,0,443,182 }, mat);
			if (Obj->pos.y >= MAX_Y - 208 &&Obj->velocity.y>0) {
				Obj->pos.y = MAX_Y - 208; Obj->velocity.y = 0; Obj->velocity.x = 0; Obj->acceleration.y = 0;
				trigger = 6;
			}
			break;
		case 6:
			D3DXMatrixTranslation(&mat, MAX_X / 2 - (443.0f/**max*/ / 2.0f), 112.0f-(182.0f/**max*//2.0f), 0);
			D3DXMatrixTransformation2D(&mat2, &D3DXVECTOR2(443 / 2, 182/ 2), NULL, &D3DXVECTOR2(max, max), NULL, NULL, NULL);
			D3DXMatrixMultiply(&mat, &mat2, &mat);
			RenderManager::GetInstance()->DrawObj(D3DXVECTOR3(MAX_X / 2 - 443 / 2, 20, 0), TXTID_TITLE,
				RECT{ 0,0,443,182 }, mat);
			if (max <= 1.5f) { max += add; add /= 10; add *= 9; }
			else if (add<0.001f) { add = 0.001f; }
			
		}
	}

}
