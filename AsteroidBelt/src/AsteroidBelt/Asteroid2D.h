#pragma once

#include <Hazel.h>

using namespace hazel;

class Asteroid2D : public Layer
{
public:
	Asteroid2D()
	{
		Ref<Texture2D> planetTex(Texture2D::Create());
		unsigned char tex[] = { 166,76,30,255 };
		planetTex->LoadFromMemory(1, 1, 4, tex);

		planet = std::make_shared<Sprite>();

	}

public:
	virtual void OnAttach() override;
	virtual void OnDetch() override;
	virtual void OnUpdate() override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Event& e) override;

private:
	Ref<Sprite> planet;

};

