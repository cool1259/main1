#pragma once
#include "MonoBehaviour.h"
class TestController :
	public MonoBehaviour
{
public:
	// MonoBehaviour을(를) 통해 상속됨
	virtual void initialize() override;
	virtual void update() override;
	virtual void lateUpdate() override;
	virtual void render() override;
	virtual void release() override;
};

