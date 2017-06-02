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
		static bool tgl = false, tgl2 = false, tgl3 = true;
		static float max = 1.0f;
		static float add = 0.05f;
		static int SFNo = 1;
		D3DXVECTOR2 CENTER;
		D3DXMATRIX mat, mat2 , mat3;
		D3DXMatrixTranslation(&mat,0,0, 0);
		if (KEY_DOWN(VK_RETURN) && trigger < 6) { 
			Obj->pos.x = 457.25; Obj->pos.y = 304; trigger = 6; 
			Obj->velocity.x = 0; Obj->velocity.y = 0;
			Obj->acceleration.x = 0; Obj->acceleration.y = 0;
			RenderManager::GetInstance()->ResetDefaultMatrix();
			max = 1.0f; add = 0.05;
			SoundManager::GetInstance()->StopWaveFile(3);
			SoundManager::GetInstance()->PlayWaveFilePos(3,2550000);
			SoundManager::GetInstance()->PlayWaveFile(6);
			Obj->SetStatus(3); SystemManager::GetInstance()->GetObjectList().front()->SetTxt(-1);
			tgl = true; tgl3 = false;
		}
		switch (trigger)
		{
		case 0:
			if ((double)(after - before) / CLOCKS_PER_SEC >= 5.4) {
				trigger = 1; before = clock();
				Obj->SetStatus(0); Obj->velocity.x = 0;
			}
			break;
		case 1:
			if ((double)(after - before) / CLOCKS_PER_SEC >= 2.0) {
				trigger = 2; before = clock(); Obj->SetStatus(2);
				Obj->velocity.x = 1.5*0.92f; Obj->velocity.y = -8.0f*0.92f;
				SoundManager::GetInstance()->PlayWaveFile(5);
			}
			break;
		case 2:
			if (max < 1.5f) { max += add; add *= 0.90f; }
			else { max = 1.5f; }
			if (Obj->pos.y <= 0) {
				Obj->acceleration.x = 0;
			}
			CENTER = D3DXVECTOR2(MAX_X / 2 + ((Obj->pos.x + 9 - MAX_X / 2)*((max - 1.0f) / 0.5f)),
				MAX_Y / 2 + ((Obj->pos.y + 40 - MAX_Y / 2)*((max - 1.0f) / 0.5f)));
			RenderManager::GetInstance()->SetDefaultMatrixZoomUp(CENTER, max);

			if (Obj->pos.y <= -50 && tgl3) { tgl3 = false; SoundManager::GetInstance()->PlayWaveFile(7); }
			if ((double)(after - before) / CLOCKS_PER_SEC >= 4.0) {
				trigger = 3; before = clock(); max = 2.0f; add = 0.175f;

				SystemManager::GetInstance()->GetObjectList().front()->SetTxt(-1);
				Obj->pos.x = MAX_X / 2 + 9; Obj->pos.y = MAX_Y / 2 + 9;
				Obj->velocity.x = 1.25f; Obj->velocity.y = -10.0f;
			}
			break;
		case 3:
			RenderManager::GetInstance()->DrawObj(D3DXVECTOR3(MAX_X - 237, 0, 0), TXTID_INTROBLK4,
				RECT{ 0,0,443,182 }, mat);
			if (max > 1.0f) { max -= add;  add *= 0.85f; }
			else { max = 1.0f; }
			RenderManager::GetInstance()->SetDefaultMatrixZoomUp(D3DXVECTOR2(MAX_X / 2, MAX_Y / 2), max);
			if (Obj->pos.y + 9 <= 0) {
				RenderManager::GetInstance()->ResetDefaultMatrix();
				trigger = 4; before = clock(); Obj->pos.y = MAX_Y;
			}
			break;
		case 4:
			RenderManager::GetInstance()->DrawObj(D3DXVECTOR3(0, 0, 0), TXTID_INTROBG,
				RECT{ 0,0,750,500 }, mat);
			RenderManager::GetInstance()->DrawObj(D3DXVECTOR3(MAX_X - 242, MAX_Y - 190, 0), TXTID_INTROBLK5,
				RECT{ 0,0,443,182 }, mat);
			RenderManager::GetInstance()->DrawObj(D3DXVECTOR3(MAX_X / 2 - 443 / 2, 20, 0), TXTID_TITLE,
				RECT{ 0,0,443,182 }, mat);
			if (Obj->pos.y <= 500) {
				max = 1.0f; add = 0.05f;
				Obj->acceleration.y = 0.17f; trigger = 5;
			}
			break;
		case 5:
			RenderManager::GetInstance()->DrawObj(D3DXVECTOR3(0, 0, 0), TXTID_INTROBG,
				RECT{ 0,0,750,500 }, mat);
			RenderManager::GetInstance()->DrawObj(D3DXVECTOR3(MAX_X - 242, MAX_Y - 190, 0), TXTID_INTROBLK5,
				RECT{ 0,0,443,182 }, mat);
			RenderManager::GetInstance()->DrawObj(D3DXVECTOR3(MAX_X / 2 - 443 / 2, 20, 0), TXTID_TITLE,
				RECT{ 0,0,443,182 }, mat);

			if (Obj->pos.y >= MAX_Y - 208 && Obj->velocity.y > 0) {
				Obj->pos.y = MAX_Y - 208; Obj->velocity.y = 0; Obj->velocity.x = 0; Obj->acceleration.y = 0;
				trigger = 6; Obj->SetStatus(3);
				SoundManager::GetInstance()->PlayWaveFile(6);
			}
			break;
		case 6:
			RenderManager::GetInstance()->DrawObj(D3DXVECTOR3(0, 0, 0), TXTID_INTROBG,
				RECT{ 0,0,750,500 }, mat);
			RenderManager::GetInstance()->DrawObj(D3DXVECTOR3(MAX_X - 242, MAX_Y - 190, 0), TXTID_INTROBLK5,
				RECT{ 0,0,443,182 }, mat);

			D3DXMatrixTransformation2D(&mat2, &D3DXVECTOR2(443 / 2, 182 / 2), NULL, &D3DXVECTOR2(max, max), NULL, NULL, NULL);

			RenderManager::GetInstance()->DrawObj(D3DXVECTOR3(MAX_X / 2 - (443.0f / 2.0f), 112.0f - (182.0f / 2.0f), 0), TXTID_TITLE,
				RECT{ 0,0,443,182 }, mat2);
			RenderManager::GetInstance()->DrawObj(D3DXVECTOR3(MAX_X/2-89, MAX_Y-150, 0),12,
				RECT{ 0,0,178,17 }, mat);

			if (max <= 1.5f) { max += add; add /= 10; add *= 9; }
			else if (add < 0.001f) { add = 0.001f; }

			if (KEY_DOWN(VK_RETURN) && !tgl) {
				tgl = true; trigger = 7; max = 1.0f; add = 0.65f;
				break;
			}
			else if (KEY_UP(VK_RETURN) && tgl) {
				tgl = false;
			}

			break;
		case 7:
			RenderManager::GetInstance()->DrawObj(D3DXVECTOR3(0, 0, 0), TXTID_INTROBG,
				RECT{ 0,0,750,500 }, mat);

			RenderManager::GetInstance()->DrawObj(D3DXVECTOR3(MAX_X - 242, MAX_Y - 190, 0), TXTID_INTROBLK5,
				RECT{ 0,0,443,182 }, mat);

			D3DXMatrixTransformation2D(&mat2, &D3DXVECTOR2(443 / 2, 182 / 2), NULL, &D3DXVECTOR2(1.5, 1.5), NULL, NULL, NULL);

			RenderManager::GetInstance()->DrawObj(D3DXVECTOR3(MAX_X / 2 - (443.0f / 2.0f), 112.0f - (182.0f / 2.0f), 0), TXTID_TITLE,
				RECT{ 0,0,443,182 }, mat2);

			if (max <= 1.5f) { max += add; add /= 10; add *= 9; }
			else if (add < 0.001f) { add = 0.001f; }
			
			switch (SFNo) {
			case 1:
				D3DXMatrixTransformation2D(&mat3, &D3DXVECTOR2(30,35), NULL, &D3DXVECTOR2(max, max), NULL, NULL, NULL);
				RenderManager::GetInstance()->DrawParticle(D3DXVECTOR3(MAX_X / 2 - 110, MAX_Y / 2 + 50, 0), TXTID_INTROSFNO,
				RECT{ 0,0,60,70 }, D3DCOLOR_XRGB(164, 214, 164),mat3);
				RenderManager::GetInstance()->DrawObj(D3DXVECTOR3(MAX_X / 2 - 20, MAX_Y / 2 + 50, 0), TXTID_INTROSFNO,
					RECT{ 60,0,108,70 }, mat);
				RenderManager::GetInstance()->DrawObj(D3DXVECTOR3(MAX_X / 2 + 60, MAX_Y / 2 + 50, 0), TXTID_INTROSFNO,
					RECT{ 108,0,169,70 }, mat);
			break;
			case 2:
				D3DXMatrixTransformation2D(&mat3, &D3DXVECTOR2(24, 35), NULL, &D3DXVECTOR2(max, max), NULL, NULL, NULL);
				RenderManager::GetInstance()->DrawParticle(D3DXVECTOR3(MAX_X / 2 - 20, MAX_Y / 2 + 50, 0), TXTID_INTROSFNO,
					RECT{ 60,0,108,70 }, D3DCOLOR_XRGB(164, 214, 164), mat3);
				RenderManager::GetInstance()->DrawObj(D3DXVECTOR3(MAX_X / 2 - 110, MAX_Y / 2 + 50, 0), TXTID_INTROSFNO,
					RECT{ 0,0,60,70 }, mat);
				RenderManager::GetInstance()->DrawObj(D3DXVECTOR3(MAX_X / 2 + 60, MAX_Y / 2 + 50, 0), TXTID_INTROSFNO,
					RECT{ 108,0,169,70 }, mat);
				break;
			case 3:
				RenderManager::GetInstance()->DrawObj(D3DXVECTOR3(MAX_X / 2 - 110, MAX_Y / 2 + 50, 0), TXTID_INTROSFNO,
					RECT{ 0,0,60,70 }, mat);
				RenderManager::GetInstance()->DrawObj(D3DXVECTOR3(MAX_X / 2 - 20, MAX_Y / 2 + 50, 0), TXTID_INTROSFNO,
					RECT{ 60,0,108,70 }, mat);
				D3DXMatrixTransformation2D(&mat3, &D3DXVECTOR2((169-108)/2, 35), NULL, &D3DXVECTOR2(max, max), NULL, NULL, NULL);
				RenderManager::GetInstance()->DrawParticle(D3DXVECTOR3(MAX_X / 2 + 60, MAX_Y / 2 + 50, 0), TXTID_INTROSFNO,
					RECT{ 108,0,169,70 },D3DCOLOR_XRGB(164, 214, 164), mat3);
				break;
			}

			if (KEY_DOWN(VK_RETURN) && !tgl) {
				tgl = true;
				SoundManager::GetInstance()->StopWaveFile(3);
				SoundManager::GetInstance()->StopWaveFile(4);
				SystemManager::GetInstance()->SendMoveSceneMessage(SFNo + 3);
				return;
			}
			else if (KEY_UP(VK_RETURN) && tgl) {
				tgl = false;
			}

			if (KEY_DOWN(VK_RIGHT) && !tgl2) {
				tgl2 = true;
				if (SFNo < 3) {
					SFNo++; max = 1.0; add = 0.065;
				}
			}
			else if (KEY_UP(VK_RIGHT) && tgl2) {
				tgl2 = false;
			}

			if (KEY_DOWN(VK_LEFT) && !tgl3) {
				tgl3 = true;
				if (SFNo > 1) {
					SFNo--; max = 1.0; add = 0.065;
				}
			}
			else if (KEY_UP(VK_LEFT) && tgl3) {
				tgl3 = false;
			}
			break;
		}
	}

}
