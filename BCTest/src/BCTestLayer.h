#pragma once

#include <Hazel.h>

using namespace hazel;

class BCTestLayer : public Layer
{
public:
	BCTestLayer();

	virtual void OnAttach() override;
	virtual void OnDetch() override;
	virtual void OnUpdate() override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Event& e) override;
	
private:
	// TODO: 
};

