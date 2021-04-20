#ifndef CLIENT_ENTRY
#define CLIENT_ENTRY
#endif // !CLIENT_ENTRY

#include "BCTestLayer.h"

#include <Hazel.h>

class BCTestApp : public hazel::Application
{
public:
	BCTestApp()
	{
		PushLayer(std::make_shared<BCTestLayer>());
	}

	~BCTestApp()
	{
	}
};

hazel::Ref<hazel::Application> hazel::CreateApplication()
{
	return std::make_shared<BCTestApp>();
}