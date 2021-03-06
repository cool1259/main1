#pragma once
#include "ECS.h"
#include "BoxCollider.h"
class CollisionDetection
{
public:
	static void BoxColliderDetection(Entity* firstEntity, Entity* secondEntity)
	{
		if (!firstEntity->hasComponent<BoxCollider>() || !secondEntity->hasComponent<BoxCollider>() 
			|| !firstEntity->getComponent<BoxCollider>().active_ || !secondEntity->getComponent<BoxCollider>().active_)
			return;

		BoxCollider& firstCollider = firstEntity->getComponent<BoxCollider>();
		BoxCollider& secondCollider = secondEntity->getComponent<BoxCollider>();

		//面倒 眉农 棺 贸府
		COLLIDERRECT2D firstColRect, secondColRect;
		firstColRect = firstCollider.getColliderRect2D();
		secondColRect = secondCollider.getColliderRect2D();


	/*	if (parentobj->GetPos().x< otherObj->GetPos().x + otherObj->GetWidth() &&
			parentobj->GetPos().x + parentobj->GetWidth() > otherObj->GetPos().x &&
			parentobj->GetPos().y< otherObj->GetPos().y + otherObj->GetHeight() &&
			parentobj->GetPos().y + parentobj->GetHeight() >otherObj->GetPos().y)*/

		if (firstColRect.right<secondColRect.left || firstColRect.left>secondColRect.right||
			firstColRect.top<secondColRect.bottom || firstColRect.bottom>secondColRect.top )//|| 
			//firstColRect.maxPosition.z<secondColRect.minPosition.z || firstColRect.minPosition.z>secondColRect.maxPosition.z)
		{
			firstCollider.notCollide(secondEntity);
			secondCollider.notCollide(firstEntity);

		
		}
		else
		{
			firstCollider.collide(secondEntity);
			secondCollider.collide(firstEntity);

		}

	}

	D3DXVECTOR2 len2B;

	static bool OBBColliderDetection(Entity* firstEntity, Entity* secondEntity)
	{
		if (!firstEntity->hasComponent<BoxCollider>() || !secondEntity->hasComponent<BoxCollider>()
			|| !firstEntity->getComponent<BoxCollider>().active_ || !secondEntity->getComponent<BoxCollider>().active_)
			return false;

		BoxCollider& firstCollider = firstEntity->getComponent<BoxCollider>();
		BoxCollider& secondCollider = secondEntity->getComponent<BoxCollider>();

		//面倒 眉农 棺 贸府
		COLLIDERRECT2D firstColRect, secondColRect;
		firstColRect = firstCollider.getColliderRect2D();
		secondColRect = secondCollider.getColliderRect2D();

		//阿档
		float radianA = (firstCollider.transform_.rotation_.z);
		float radianB = (secondCollider.transform_.rotation_.z);
		//荤阿屈甸埃 芭府
		D3DXVECTOR2 distance = D3DXVECTOR2((firstEntity->getComponent<Transform>().position_.x - secondEntity->getComponent<Transform>().position_.x), (firstEntity->getComponent<Transform>().position_.y - secondEntity->getComponent<Transform>().position_.y));

		//规氢氦磐
		D3DXVECTOR2 dir1A = D3DXVECTOR2(cosf(radianA), sinf(radianA)); //A胶橇扼捞飘X绵
		D3DXVECTOR2 dir2A = D3DXVECTOR2(cosf(radianA - D3DXToRadian(180.f)*0.5f), sinf(radianA - D3DXToRadian(180.f)*0.5f));//x绵俊辑 90档憋酒辑 y绵父惦(曼绊肺 扼叼救180篮颇捞)

		D3DXVECTOR2 dir1B = D3DXVECTOR2(cosf(radianB), sinf(radianB)); //B 胶橇扼捞飘X绵
		D3DXVECTOR2 dir2B = D3DXVECTOR2(cosf(radianB - D3DXToRadian(180.f)*0.5f), sinf(radianB - D3DXToRadian(180.f)*0.5f));//x绵俊辑 90档憋酒辑 y绵父惦(曼绊肺 扼叼救180篮颇捞)

		//规氢苞 辨捞甫 蚌秦淋
		
		D3DXVECTOR2 len1A = dir1A * (firstColRect.right - firstColRect.left)*0.5f;
		D3DXVECTOR2 len2A = dir2A * (firstColRect.top - firstColRect.bottom)*0.5F;
		
		D3DXVECTOR2 len1B = dir1B * (secondColRect.right - secondColRect.left)*0.5f;
		D3DXVECTOR2 len2B = dir2B * (secondColRect.top - secondColRect.bottom)*0.5F;

		float lenthA;
		float lenthB;
		float lenth;
		//捞力何磐 八荤矫累
		//dir1A绵八荤
		//傈何 dir1A俊 荤康窃 (鞍篮阿档甫父电促绊毫具窍唱)
		//弊府绊辨捞厚背
		lenthA = D3DXVec2Length(&len1A); //dir1A客 乞青窍扁 锭巩俊 辨捞父 舅搁凳
		lenthB = fabsf(D3DXVec2Dot(&dir1A, &len1B)) + fabs(D3DXVec2Dot(&dir1A, &len2B)); // B胶橇扼捞飘甫 dir1A 绵俊 荤康窍咯 辨捞甫备窃(郴利)
		lenth = fabsf(D3DXVec2Dot(&dir1A, &distance)); //荤康茄 辨捞甫 厚背秦 般摹搁 lenth焊促 累绊, 般摹瘤臼栏搁 length焊促 辨绢咙栏肺 魄窜
		if (lenth > lenthA + lenthB)
		{

			return false;
		}
		
		//dir2A绵八荤
		lenthA = D3DXVec2Length(&len2A); 
		lenthB = fabsf(D3DXVec2Dot(&dir2A, &len1B)) + fabs(D3DXVec2Dot(&dir2A, &len2B)); 
		lenth = fabsf(D3DXVec2Dot(&dir2A, &distance)); 
		if (lenth > lenthA + lenthB)
		{
	
			return false;
		}

		//dir1B绵八荤
		lenthA = D3DXVec2Length(&len1B);
		lenthB = fabsf(D3DXVec2Dot(&dir1B, &len1A)) + fabs(D3DXVec2Dot(&dir1B, &len2A));
		lenth = fabsf(D3DXVec2Dot(&dir1B, &distance));
		if (lenth > lenthA + lenthB)
		{
	
			return false;
		}

		//dir2B绵八荤
		lenthA = D3DXVec2Length(&len2B);
		lenthB = fabsf(D3DXVec2Dot(&dir2B, &len1A)) + fabs(D3DXVec2Dot(&dir2B, &len2A));
		lenth = fabsf(D3DXVec2Dot(&dir2B, &distance));
		if (lenth > lenthA + lenthB)
		{
		
			
			return false;
		}

	
		return true;







	}
};