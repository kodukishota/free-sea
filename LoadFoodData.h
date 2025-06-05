#pragma once
#include "Node.h"
#include "Food.h"
#include "DxLib.h"

class LoadFoodData : public Node
{
public:
	enum class KindOfFood
	{
		Bread,
		Onigiri,
		Burger,

		Length
	};

	FoodData m_foodData[static_cast<int>(KindOfFood::Length)];

	LoadFoodData()
	{
		int fileHandle = FileRead_open("food_data.csv");

		char dontUseLine[9][256];

		for (int i = 0; i < 1; i++) FileRead_gets(dontUseLine[0], 256, fileHandle);

		for (int i = 0; i <= static_cast<int>(KindOfFood::Length) - 1; i++)
		{
			FileRead_scanf(fileHandle, "%[^,],%[^,],%[^,],%d",
				m_foodData[i].m_foodName, m_foodData[i].m_iconName,
				m_foodData[i].m_flavorText, &m_foodData[i].m_recoveryHungry);//ì«Ç›çûÇ›
		}

		//ÉtÉ@ÉCÉãÇï¬Ç∂ÇÈ
		FileRead_close(fileHandle);
	}
};