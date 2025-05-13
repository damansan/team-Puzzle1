#include "Player.h"
#include "System/Input.h"
#include "BoxManager.h"
#include "Collision.h"
#include "FalseBox.h"
#include "Camera.h"

//コンストラクタ
Player::Player()
{
	//model = new Model("Data/Model/Player/Player.mdl");
	model = new Model("Data/Model/Ufo/ufo.mdl");
	//スケーリング
	scale.x = scale.y = scale.z = 0.5f;
	position.z = -5;
	position.y = 0.01f;
}

//デストラクタ
Player::~Player()
{
	delete model;
}

//更新処理
void Player::Update(float elapsedTime)
{

	//移動入力処理
	InputMove(elapsedTime);

	//プレイヤーとボックスの衝突判定
	CollisionPlayerVsBoxs();

	//オブジェクト行列更新
	UpdateTransform();

	//モデル行列更新
	model->UpdateTransform();

}

//描画処理
void Player::Render(const RenderContext& rc, ModelRenderer* renderer)
{
	renderer->Render(rc, transform, model, ShaderId::Lambert);
}

//移動処理
void Player::Move(float elapsedTime, float vx, float vz, float speed)
{
	speed *= elapsedTime;
	position.x += vx * speed;
	position.z += vz * speed;
}
//移動入力処理
void Player::InputMove(float elapsedTime)
{
	//進行ベクトル取得
	DirectX::XMFLOAT3 moveVec = GetMoveVec();
	//移動処理
	Move(elapsedTime, moveVec.x, moveVec.z, moveSpeed);
	//旋回処理
	Turn(elapsedTime, moveVec.x, moveVec.z, turnSpeed);
}
//旋回処理
void Player::Turn(float elapsedTime, float vx, float vz, float speed)
{
	speed *= elapsedTime;

	//進行ベクトルがゼロベクトルの場合は処理する必要なし
	float length = sqrtf(vx * vx + vz * vz);
	if (length < 0.001f) return;

	//進行ベクトルを単位ベクトル化
	vx /= length;
	vz /= length;

	//自身の回転から前方向を求める
	float frontX = sinf(angle.y);
	float frontZ = cosf(angle.y);

	//回転角を求めるため、２つのベクトルの内積を計算する
	float dot = (frontX * vx) + (frontZ * vz);

	//内積値は-1.0～1.0で表現されており、２つの単位ベクトルの角度が
	// 小さいほど1.0に近づくという性質を利用して回転速度を調整する
	float rot = 1.0 - dot;
	if (rot > speed) rot = speed;

	//左右判定を行うために２つの単位ベクトルの外積を計算する
	float cross = (frontZ * vx) - (frontX * vz);

	//2Dの外積値が正の場合か負の場合によって左右判定が行える
	//左右判定を行うことによって左右回転を選択する
	if (cross < 0.0f)
	{
		angle.y -= rot;
	}
	else
	{
		angle.y += rot;
	}

}

//スティック入力値から移動ベクトルを取得
DirectX::XMFLOAT3 Player::GetMoveVec()const
{
	//GamePad& gamePad = Input::Instance().GetGamePad();
	//const GamePadButton ButtonW = GamePad::BTN_1;
	//const GamePadButton ButtonA = GamePad::BTN_2;
	//const GamePadButton ButtonS = GamePad::BTN_3;
	//const GamePadButton ButtonD = GamePad::BTN_4;

	//入力情報を取得
	//float ax =0.0f;
	//float ay =0.0f;

	//if (gamePad.GetButtonDown() & ButtonW)ay += 10.0f;
	//if (gamePad.GetButtonDown() & ButtonS)ay -= 10.0f;
	//if (gamePad.GetButtonDown() & ButtonD)ax += 10.0f;
	//if (gamePad.GetButtonDown() & ButtonA)ax -= 10.0f;


	GamePad& gamePad = Input::Instance().GetGamePad();
	float ax = gamePad.GetAxisLX();
	float ay = gamePad.GetAxisLY();


	//カメラ方向とスティック入力値によって進行方向を計算する
	Camera& camera = Camera::Instance();
	const DirectX::XMFLOAT3& cameraRight = camera.GetRight();
	const DirectX::XMFLOAT3& cameraFront = camera.GetFront();

	//移動ベクトルはXZ平面に水平なベクトルになるようにする

	//カメラ右方向ベクトルをXZ単位ベクトルに変換
	float cameraRightX = cameraRight.x;
	float cameraRightZ = cameraRight.z;
	float cameraRightLenght = sqrtf(cameraRightX * cameraRightX + cameraRightZ * cameraRightZ);
	if (cameraRightLenght > 0.0f)
	{
		//単位ベクトル化
		cameraRightX /= cameraRightLenght;
		cameraRightZ /= cameraRightLenght;
	}
	//カメラ前方向ベクトルをZX単位ベクトルに変換
	float cameraFrontX = cameraFront.x;
	float cameraFrontZ = cameraFront.z;
	float cameraFrontLenght = sqrtf(cameraFrontX * cameraFrontX + cameraFrontZ * cameraFrontZ);
	if (cameraFrontLenght > 0.0f)
	{
		//単位ベクトル化
		cameraFrontX /= cameraFrontLenght;
		cameraFrontZ /= cameraFrontLenght;
	}

	//スティックの水平入力値をカメラ右方向に反映し、
	//スティックの水平入力値をカメラ前方向に反映し、
	//進行ベクトルを計算
	DirectX::XMFLOAT3 vec;
	vec.x = (cameraRightX * ax) + (cameraFrontX * ay);
	vec.z = (cameraRightZ * ax) + (cameraFrontZ * ay);
	// Y軸方向には移動しない
	vec.y = 0.0f;
	return vec;
}

//プレイヤーとボックスの当たり判定
void Player::CollisionPlayerVsBoxs()
{
	BoxManager& boxManager = BoxManager::Instance();

	// 総当たりでボックスとの衝突処理
	int boxCount = boxManager.GetBoxCount();
	for (int i = 0; i < boxCount; ++i)
	{
		Box* box = boxManager.GetBox(i);

		// FalseBox 以外とだけ衝突処理を行う
		if (dynamic_cast<FalseBox*>(box) == nullptr)
		{
			DirectX::XMFLOAT3 outPosition;

			// 衝突処理（四角 vs 四角）
			if (Collision::IntersectAndPushBoxVSBox(
				this->position,
				this->halfSize,  // プレイヤーの半サイズ
				box->GetPosition(),
				box->GethalfSize(),  // ボックスの半サイズ
				outPosition))
			{
				// 押し出し後の位置設定
				box->SetPosition(outPosition);
			}
		}
	}
}
//デバッグ用GUI描画
#ifdef _DEBUG
void Player::DrawGUI()
{
	ImVec2 pos = ImGui::GetMainViewport()->GetWorkPos();
	ImGui::SetNextWindowPos(ImVec2(pos.x + 10, pos.y + 10), ImGuiCond_Once);
	ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_FirstUseEver);

	if(ImGui::Begin("Player",nullptr,ImGuiWindowFlags_None))
	{
		//トランスフォーム
		if (ImGui::CollapsingHeader("Player Position", ImGuiTreeNodeFlags_DefaultOpen))
		{
			//位置
			ImGui::InputFloat3("Position", &position.x);
			//回転
			DirectX::XMFLOAT3 a;
			a.x =DirectX::XMConvertToDegrees(angle.x);
			a.y =DirectX::XMConvertToDegrees(angle.y);
			a.z =DirectX::XMConvertToDegrees(angle.z);
			ImGui::InputFloat3("Angle", &a.x);
			angle.x =DirectX::XMConvertToRadians(a.x);
			angle.y =DirectX::XMConvertToRadians(a.y);
			angle.z =DirectX::XMConvertToRadians(a.z);
			 //スケール
			ImGui::InputFloat3("Scale", &scale.x);

		}
		//ジャッジ
		//if (ImGui::CollapsingHeader("TrueBoX & GoalTile Position & GoalFlag", ImGuiTreeNodeFlags_DefaultOpen))
		//{
		//	judge.DrawGUI();
		//}

	}
	ImGui::End();
}
#endif // DEBUG
