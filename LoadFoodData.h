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
		ChillCrab,
		MeatPie,
		ChillSausage,
		FriedChicken,

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
			FileRead_scanf(fileHandle, "%[^,],%[^,],%[^,],%d,%d",
				m_foodData[i].m_foodName, m_foodData[i].m_iconName,m_foodData[i].m_flavorText,
				&m_foodData[i].m_recoveryHungry, &m_foodData[i].m_warmthValue);//読み込み
		}

		//ファイルを閉じる
		FileRead_close(fileHandle);
	}
};