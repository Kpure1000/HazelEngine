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
	const char* m_ItemName = "Efective Test\0Trade Success Rate\0Consensus Rate\0Hack Test";
	const string addA = "d3c1ef4b4a6f6fe6466fe6c322daf4ce";
	const string addB = "3b4eacb34c4ba5f6fe64b4a69c3ff234";
	const string addC = "46b4b2daacba5fb34a91652ef032d3cc";
	const string addD = "2fc4e094b06fe692da3c34178d3b34ba";
	const string addE = "a34dac3aba5fbacba50cdf3da3f4b906";
};

