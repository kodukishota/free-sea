#pragma once
#include "Node.h"
#include "Sprite.h"

class LoadPlayer;

class Menu : public Node
{
private:
	static constexpr int MaxPal = 150;	// 輝度の最大値
	// 画面のフィルター用
	static const char* FilterTexture;

	Sprite m_brackImg;
	Sprite m_background;

	Transform m_transform;

	LoadPlayer* m_player;

protected:
	virtual void Load() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Draw() override;

public:
	Menu(LoadPlayer* player);
};