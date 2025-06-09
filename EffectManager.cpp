#include "DxLib.h"
#include "EffectManager.h"

// 初期化
void EffectManager::Initialize()
{
    // 引数には画面に表示する最大パーティクル数を設定する。
    if (Effekseer_Init(EffectParticleLimit) == -1)
    {
        DxLib_End();
    }

    // フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ。
    // Effekseerを使用する場合は必ず設定する。
    SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

    // DXライブラリのデバイスロストした時のコールバックを設定する。
    // ウインドウとフルスクリーンの切り替えが発生する場合は必ず実行する。
    Effekseer_SetGraphicsDeviceLostCallbackFunctions();

    // Zバッファを有効にする。
    // Effekseerを使用する場合、2DゲームでもZバッファを使用する。
    SetUseZBuffer3D(TRUE);

    // Zバッファへの書き込みを有効にする。
    // Effekseerを使用する場合、2DゲームでもZバッファを使用する。
    SetWriteZBuffer3D(TRUE);
}

//読み込み
int EffectManager::Load(const char* effectFilePath, float size)
{
    // エフェクトのリソースを読み込む
    return LoadEffekseerEffect(effectFilePath, size);
}

//更新
void EffectManager::Update()
{
    //Effekseerにより再生中のエフェクトを更新する。
    UpdateEffekseer3D();
}

//描画
void EffectManager::Draw()
{
    //Effekseerにより再生中のエフェクトを描画する。
    DrawEffekseer3D();
}