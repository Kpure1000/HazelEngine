#include <Hazel.h>

using std::shared_ptr;
using std::make_shared;

class SandBox : public hazel::Application
{
public:

	SandBox()
	{

	}

	~SandBox()
	{

	}

};

shared_ptr<hazel::Application> hazel::CreateApplication()
{
	return make_shared<SandBox>();
}