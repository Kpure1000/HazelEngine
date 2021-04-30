#ifndef CLIENT_ENTRY
#define CLIENT_ENTRY
#endif // !CLIENT_ENTRY

#include "OfflineLayer.h"

#include <Hazel.h>

class OfflineApp : public hazel::Application
{
public:
	OfflineApp()
	{
		PushLayer(std::make_shared<OfflineLayer>());
	}

	~OfflineApp()
	{
	}
};

hazel::Ref<hazel::Application> hazel::CreateApplication()
{
	return std::make_shared<OfflineApp>();
}