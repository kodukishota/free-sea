#pragma once
#include"Actor3D.h"
#include"Vector3.h"
#include"DxLib.h"
#include<vector>

class Camera;
class Animation3D;
class CollisionStage;

class LoadPlayer : public Actor3D
{
public:
	// アニメーション
	enum class Anim
	{
		Idle,
		Walk,
		Run,
		Death,

		Length,
	};

private:
	std::vector<Animation3D*> m_attachAnimList;

	static constexpr int AnimNum = static_cast<int>(Anim::Length);	// アニメーションの数

	static constexpr float WalkSpeed = 4.0f;	// 歩く速度
	static constexpr float RunSpeed = 12.0f;	// 走る速度
	static constexpr float RotateSpeed = 10.0f;	// 回転速度
	static constexpr float DurationTime = 1.0f;
	static constexpr float JumpPower = 4.0f;	// 初速度
	static constexpr float Gravity = 9.8f;		// 重力加速度
	static constexpr Vector3 SpawnPos = Vector3(850, 100, 850);	// ステージにスポーンする場所
	static constexpr Vector3 ColOffset = Vector3(0, 90, 0);	// コライダーのオフセット
	static constexpr Vector3 ColSize = Vector3(50, 180, 50);	// コライダーのサイズ
	static constexpr int MaxHp = 100;	// 体力の最大値

	static constexpr float MaxBodyTemperature = 100;	//プレイヤーの最大体温

	static constexpr float DownHungerLevelValue = 5;	//おなかが減る量の初期値
	static constexpr float DownHungerLevelTime = 5;		//おなかが減る時間の初期値
	static constexpr int FullStomach = 100;		//プレイヤーの満腹時

	static constexpr int IncreasedSleepiness = 2;		//眠気の増加量
	static constexpr int IncreasedSleepinessTime = 5;	//眠気の増加量する時間
	static constexpr int FirstSleepiness = 100;		//眠気がないとき


	// スタミナ関連
	static constexpr float MaxStamina = 100;	// 走るのに必要なスタミナの最大値
	static constexpr float StaminaRecoveryAmount = 10;	// スタミナの回復量
	static constexpr float StaminaDecreaseAmount = 20;	// スタミナの消費量
	static constexpr float TimeToRecoverStamina = 1;	// スタミナが回復し始めるまでの時間

	static constexpr float FirstDownTemperature = 5;	//下がる体温の初期値
	static constexpr float FirstDownTemperatureTime = 5;//体温が下がる時間の初期値

	Vector3 AxisY = Vector3(0.0f, 1.0f, 0.0f);	// 回転軸(Y軸で上方向)

	static const char* AnimList[AnimNum];

	int m_model;	// プレイヤーのモデル(mv1)

	int m_animIndex;	// 再生中のアニメーション

	float m_runSpeed;
	bool m_isJump;
	bool m_isJumping;
	bool m_isFall;	// 現在落下しているか
	bool m_isFloating;
	float m_fallStartY;	// 落下し始めの高さ

	float m_hungerLevel;	//空腹度
	float m_sleepiness;		//眠気

	float m_hungerTime;		//おなかが減るクールダウン
	float m_sleepinessTime;	//眠気が増えるクールダウン

	bool m_isCold;		//体温が冷え切っているか
	bool m_isHungry;	//おなかがすいているか
	bool m_isTired;	//疲労しているか

	float m_dethCountDown;	//冷え切った時の死亡するまでのクールダウン

	int m_seDamage;	// 攻撃を受けたときのSE

	bool m_isDeath;	// 死亡フラグ
	bool m_finish;	// 死亡アニメーションが終わったか

	bool m_cutTree;		//木を伐り始めたか
	bool m_fellDown;	//木を伐り終えたか

	bool m_isMenu;		//メニューを開いているか

	bool m_isSleep;		//寝たか

	Camera* m_camNode;
	CollisionStage* m_collisionStage;

	Vector3 m_playerPastPos;
	Vector3 m_playerRotate;
	Vector3 m_moveDirection;

	// アニメーション切り替え用
	Anim m_nowAnim;
	Anim m_nextAnim;

	bool m_moving;	// 移動アニメーションが再生中か
	float m_elapsedTime;	// 経過時間保持
	float m_fallTime;		// 自由落下を加速させる用

	// プレイヤーの体力に関する変数
	int m_hp;	// プレイヤーの体力

	float m_bodyTemperature;	//プレイヤーの体温

	float m_stamina;	// プレイヤーの現在のスタミナ	
	bool m_isDash;		// 走っているか
	float m_duration;	// 時間経過をカウントする用
	float m_staminaRecovery;	// スタミナの回復量
	float m_staminaDecrease;	// スタミナの消費量

	bool m_isWarmthFlag;	//暖炉の近くにいて温まれるか

	float m_downTemperature;		//下がる体温
	float m_downTemperatureCoolDown;	//体温が下がる時間
	float m_warmthTemperatureCoolDown;	//体温が上がる時間

	bool m_nowTrede;	//トレード中かどうか

	// プレイヤーのジャンプ処理
	void Jumping();		// 自分でジャンプする処理

	// ---- SE ----
	int m_seWalk;
	int m_seRun;

protected:
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Load() override;
	virtual void Release() override;
	virtual void OnCollision(const Actor3D* other) override;

public:
	LoadPlayer(
		CollisionStage* collisionStage,
		const Vector3& pos
	);

	// アニメーションを切り替える(Lerp)
	void ChangeAnimLerp();

	// アニメーションを切り替える(即座)
	void ChangeAnimQuick(const Anim nextAnim);

	// アニメーションを再生する
	void PlayAnim();

	// プレイヤーの通常移動
	void NormalMove();

	// 移動先を決める
	void CheckMove();

	// 落下した高さを計算する
	void CountFallHeight();

	// プレイヤーが冷え切った時
	void ColdPlayer();

	void DownBodyTemperature();

	void WarmthBodyTemperature();

	void PlayerSleepiness();

	bool IsJump()
	{
		return m_isJump;
	}
	
	// 現在のHpの割合を返す
	float GetHpRatio()
	{
		return static_cast<float>(m_hp) / static_cast<float>(MaxHp);
	}

	// 死亡フラグを取得
	bool GetIsDeath()
	{
		return m_isDeath;
	}

	// スタミナ管理
	void StaminaManagement();

	// 現在のスタミナを取得
	float GetStamina()
	{
		return m_stamina;
	}

	// スタミナの最大値を取得
	float GetMaxStamina()
	{
		return MaxStamina;
	}

	// 体力が0になったか
	bool GetIsFinsh()
	{
		return m_finish;
	}

	bool GetCutTree()
	{
		return m_cutTree;
	}

	void FellDownTree()
	{
		m_cutTree = false;
	}

	float GetBodyTempature()
	{
		return m_bodyTemperature;
	}

	float GetMaxBodyTempature()
	{
		return MaxBodyTemperature;
	}

	bool GetNowTrede()
	{
		return m_nowTrede;
	}

	void ResetNowTrede()
	{
		m_nowTrede = false;
	}

	void SwitchIsMenu()
	{
		m_isMenu = !m_isMenu;
	}

	bool GetIsMenu()
	{
		return m_isMenu;
	}

	void DownHungerLevel();

	float GetHungerLevel()
	{
		return m_hungerLevel;
	}

	int GetMaxHungerLevel()
	{
		return FullStomach;
	}

	void EatingFood(int recoveryHungry)
	{
		m_hungerLevel += recoveryHungry;
	}

	bool GetIsSleep()
	{
		return m_isSleep;
	} 

	float GetSleepiness()
	{
		return m_sleepiness;
	}

	float GetMaxSleepiness()
	{
		return FirstSleepiness;
	}

	void ResetIsSleep()
	{
		m_isSleep = false;
	}

	void DontWarmth()
	{
		m_isWarmthFlag = false;
	}

	bool GetIsTired()
	{
		return m_isTired;
	}

	bool CanInteractObject(Vector3 objectPos,float interactRange,Vector3 offSet = Vector3(0,0,0));
};