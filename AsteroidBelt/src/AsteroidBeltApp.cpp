#ifndef CLIENT_ENTRY
#define CLIENT_ENTRY
#endif // !CLIENT_ENTRY

#include "AsteroidBelt/RenderLayer.h"

#include <Hazel.h>

class AsteroidBeltApp : public hazel::Application
{
public:
	AsteroidBeltApp()
	{
		PushLayer(std::make_shared<RenderLayer>());
	}

	~AsteroidBeltApp()
	{
	}
};

hazel::Ref<hazel::Application> hazel::CreateApplication()
{
	return std::make_shared<AsteroidBeltApp>();
}