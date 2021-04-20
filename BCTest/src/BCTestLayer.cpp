#include "BCTestLayer.h"



#include<imgui.h>


BCTestLayer::BCTestLayer()
{
}

void BCTestLayer::OnAttach()
{
}

void BCTestLayer::OnDetch()
{
}

void BCTestLayer::OnUpdate()
{
	RenderCommand::Clear();
	// MultiThread Test
	{
		HZ_PROFILE_SCOPE("Efective Tester");
		static int queryCount = 0;
		static int checkCount = 0;
		static int loadUpCount = 0;
		static float queryTime = 0.0f;
		static float checkTime = 0.0f;
		static float loadUpTime = 0.0f;
		if (queryTime > 4.3f)
		{
			Log::Debug("BCTest>> Query Times: {0}.", queryCount++);
			queryTime = 0.0f;
		}
		queryTime += Time::deltaTime();
		if (checkTime > 13.3f)
		{
			Log::Trace("BCTest>> Check Times: {0}.", checkCount++);
			checkTime = 0.0f;
		}
		checkTime += Time::deltaTime();
		if (loadUpTime > 19.7f)
		{
			Log::Warn("BCTest>> Load Up Times: {0}.", loadUpCount++);
			loadUpTime = 0.0f;
		}
		loadUpTime += Time::deltaTime();
		std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 100));
	}

	{
		HZ_PROFILE_SCOPE("Consensus Tester");
	}

}

void BCTestLayer::OnImGuiRender()
{
	HZ_PROFILE_FUNCTION();
	{
		ImGui::Begin("BCTest Properties");
		{
			ImGui::Text("Test Option:");
			static int curItem = 0;
			ImGui::Combo("Test Mode Select", &curItem, m_ItemName, 4);

			static bool isStateChannel;
			ImGui::Checkbox("Open State Channel", &isStateChannel);
		}
		{
			ImGui::Text("\nBlock Efective Test:");
			static int ths = 0;
			ImGui::SliderInt("Test Thread Numbers", &ths, 1, 24);
		}
		{
			ImGui::Text("\nTrade:");
			static int fake = 0;
			ImGui::SliderInt("Random Fake Block", &fake, 0, 30);
		}
		ImGui::End();
	}
}

void BCTestLayer::OnEvent(Event& e)
{
	hazel::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<KeyPressedEvent>([this](KeyPressedEvent& ev)->bool
		{
			HZ_PROFILE_SCOPE("Deal Suspected Block");
			if (ev.GetKeyCode() == Key::Enter)
			{
				// Trade Test
				{
					switch (rand() % 5)
					{
					case 0: Log::Warn("Hash Reply From {0}: Bytes={1} Internal={2}ms Wrong={3}",
						addA, 256, rand() % 9000 + 4000, "False"); break;
					case 1: Log::Warn("Hash Reply From {0}: Bytes={1} Internal={2}ms Wrong={3}",
						addB, 256, rand() % 9000 + 4000, "False"); break;
					case 2: Log::Warn("Hash Reply From {0}: Bytes={1} Internal={2}ms Wrong={3}",
						addC, 256, rand() % 9000 + 4000, "False"); break;
					case 3: Log::Warn("Hash Reply From {0}: Bytes={1} Internal={2}ms Wrong={3}",
						addD, 256, rand() % 9000 + 4000, "False"); break;
					case 4: Log::Warn("Hash Reply From {0}: Bytes={1} Internal={2}ms Wrong={3}",
						addE, 256, rand() % 9000 + 4000, "False"); break;
					default:
						break;
					}
				}
			}
			if (ev.GetKeyCode() == Key::Backspace)
			{
				switch (rand() % 5)
				{
				case 0: Log::Warn("Find a Block {0} seems like TROJAN", addA); break;
				case 1: Log::Warn("Find a Block {0} seems like TROJAN", addB); break;
				case 2: Log::Warn("Find a Block {0} seems like TROJAN", addC); break;
				case 3: Log::Warn("Find a Block {0} seems like TROJAN", addD); break;
				case 4: Log::Warn("Find a Block {0} seems like TROJAN", addE); break;
				default:
					break;
				}
			}
			return false;
		});
}
