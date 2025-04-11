#include <Novice.h>
#include <cmath>

// タイトル
const char kWindowTitle[] = "LE2B_19_ハタナカ_タロウ";

// 列の幅
static const int kColumnWidth = 60;

// 行の高さ
static const int kRowHeight = 20;

/// <summary>
/// 3次元ベクトル
/// </summary>
typedef struct Vector3 {
	float x;
	float y;
	float z;
}Vector3;

/// <summary>
/// ベクトルの値をを表示
/// </summary>
/// <param name="x">ベクトルの値を表示するx座標</param>
/// <param name="y">ベクトルの値を表示するy座標<</param>
/// <param name="vector">表示するベクトル</param>
/// <param name="label">ベクトルのラベル</param>
void VectorScreenPrintf(int x, int y, const Vector3 &vector, const char *label) {
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
}

/// <summary>
/// 加算
/// </summary>
/// <param name="v1">加算するベクトル1</param>
/// <param name="v2">加算するベクトル2</param>
/// <returns>加算後のベクトル</returns>
Vector3 Add(const Vector3 &v1, const Vector3 &v2) {
	Vector3 result;
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return result;
}

/// <summary>
/// 減算
/// </summary>
/// <param name="v1">減算するベクトル1</param>
/// <param name="v2">減算するベクトル2</param>
/// <returns>減算後のベクトル</returns>
Vector3 Subtract(const Vector3 &v1, const Vector3 &v2) {
	Vector3 result;
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return result;
}

/// <summary>
/// スカラー倍
/// </summary>
/// <param name="scalar">スカラー倍するスカラー</param>
/// <param name="v">スカラー倍するベクトル</param>
/// <returns>スカラー倍後のベクトル</returns>
Vector3 Multiply(float scalar, const Vector3 &v) {
	Vector3 result;
	result.x = v.x * scalar;
	result.y = v.y * scalar;
	result.z = v.z * scalar;
	return result;
}

/// <summary>
/// 内積
/// </summary>
/// <param name="v1">内積を計算するベクトル1</param>
/// <param name="v2">内積を計算するベクトル2</param>
/// <returns>計算後の内積</returns>
float Dot(const Vector3 &v1, const Vector3 &v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

/// <summary>
/// 長さ(ノルム)
/// </summary>
/// <param name="v">長さを計算するベクトル</param>
/// <returns>計算後の長さ(ノルム)</returns>
float Length(const Vector3 &v) {
	return std::sqrtf(Dot(v, v));
}

/// <summary>
/// 正規化
/// </summary>
/// <param name="v">正規化するベクトル</param>
/// <returns>正規化後のベクトル</returns>
Vector3 Normalize(const Vector3 &v) {
	Vector3 result;
	float length = 1.0f / Length(v);
	result.x = v.x * length;
	result.y = v.y * length;
	result.z = v.z * length;
	return result;
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	// ベクトルを宣言
	Vector3 v1{ 1.0f,3.0f,-5.0f };
	Vector3 v2{ 4.0f,-1.0f,2.0f };
	float k = { 4.0f };

	// ベクトルを計算
	Vector3 resultAdd = Add(v1, v2);
	Vector3 resultSubtract = Subtract(v1, v2);
	Vector3 resultMultiply = Multiply(k, v1);
	float resultDot = Dot(v1, v2);
	float resultLength = Length(v1);
	Vector3 resultNormalize = Normalize(v2);

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		// ベクトルの表示
		VectorScreenPrintf(0, 0, resultAdd, " : Add");
		VectorScreenPrintf(0, kRowHeight, resultSubtract, " : Subtract");
		VectorScreenPrintf(0, kRowHeight * 2, resultMultiply, " : Multiply");
		Novice::ScreenPrintf(0, kRowHeight * 3, "%.02f : Dot", resultDot);
		Novice::ScreenPrintf(0, kRowHeight * 4, "%.02f : Length", resultLength);
		VectorScreenPrintf(0, kRowHeight * 5, resultNormalize, " : Normalize");

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
