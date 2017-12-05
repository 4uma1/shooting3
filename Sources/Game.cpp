#include "Game.hpp"


// TODO: 砲台の位置を画面左に、ターゲットの位置を画面右に移動させる。(A)[HW16A059 北原]
// TODO: 雲の位置を左から右に動かす。見えなくなったら左端に戻す。(B)[HW16A029 大久保]
// TODO: 砲台を青い壁に沿って上下に動かす。(C)[HW16A059 北原]
// TODO: 弾のスピードを速くし、弾が画面右端を通り越したら再度発射可能にする。(D)[HW16A029 大久保]
// TODO: スコアのサイズを大きくする。(E)[HW16A144 長尾]
// TODO: スコアを100点ずつ加算するようにし、5桁の表示に変える。(F)[HW16A040 小川]
// TODO: PlayBGM()関数を使って、BGMを再生する。(G)[HW16A040 小川]
// TODO: PlaySE()関数を使って、弾の発射時とターゲットに当たった時にSEを再生する。(H)[HW16A144 長尾]


Vector2 cloudPos;       //!< 雲の位置
Vector2 cannonPos;      //!< 砲台の位置
Vector2 bulletPos;      //!< 弾の位置
Rect    targetRect;     //!< ターゲットの矩形
Rect outsideRect;       //!< 画面右端の判定位置
int     score;          //!< スコア
int     cannonfrag ;          //!<砲台のためのフラグ

// ゲーム開始時に呼ばれる関数です。
void Start()
{
    cloudPos = Vector2(-320, 100);
    cannonPos = Vector2(-310, -150);
    targetRect = Rect(280, -140, 40, 40);
     outsideRect = Rect(320, -240, 320, 240);
    bulletPos.x = -999;
    score = 0;
    cannonfrag  = 0;
    PlayBGM("bgm_maoudamashii_8bit07.mp3");

}

// 1/60秒ごとに呼ばれる関数です。モデルの更新と画面の描画を行います。
void Update()
{
    // 弾の発射
    if (bulletPos.x <= -999 && Input::GetKeyDown(KeyMask::Space)) {
        bulletPos = cannonPos + Vector2(50, 10);
        PlaySound("se_maoudamashii_explosion03.mp3");
    }

    // 弾の移動
/*<<<<<<< HEAD
    if (bulletPos.x > -999) {
        bulletPos.x += 300 * Time::deltaTime;

        // ターゲットと弾の当たり判定
        Rect bulletRect(bulletPos, Vector2(32, 20));
        if (targetRect.Overlaps(bulletRect)) {
            score += 100;         // スコアの加算
            bulletPos.x = -999; // 弾を発射可能な状態に戻す
            PlaySound("se_maoudamashii_explosion06.mp3");
        }
=======*/
 if (bulletPos.x > -999) {
    bulletPos.x += 200 * Time::deltaTime;

    // ターゲットと弾の当たり判定
    Rect bulletRect(bulletPos, Vector2(32, 20));
    if (targetRect.Overlaps(bulletRect)) {
        score += 100;         // スコアの加算
        bulletPos.x = -999; // 弾を発射可能な状態に戻す
        PlaySound("se_maoudamashii_explosion06.mp3");
//>>>>>>> 16193cb7de0102ec0d0c25a560e00345d177cbb8
    }
    //ターゲットが画面右の外に出たときの処理
    if (outsideRect.Overlaps(bulletRect)) {
        
        bulletPos.x = -999; // 弾を発射可能な状態に戻す
    }
}
    // 背景の描画
    Clear(Color::cyan);
    FillRect(Rect(-320, -240, 640, 100), Color::green);

    // 雲の描画
    DrawImage("cloud1.png", cloudPos);
    if (cloudPos.x > -999) {
        cloudPos.x += 60 * Time::deltaTime;
    }
    if (cloudPos.x >= 320) {
        cloudPos.x = -550;
    }

    // 弾の描画
    if (bulletPos.x > -999) {
        DrawImage("bullet.png", bulletPos);
    }

    // 砲台の描画
    FillRect(Rect(cannonPos.x-10, -140, 20, 100), Color::blue);
    DrawImage("cannon.png", cannonPos);

    //砲台の上下移動
    if (cannonfrag == 0) {
        cannonPos.y += 1;
        if (cannonPos.y > -60) {
            cannonfrag -= 1;
        }
    }
    if (cannonfrag == -1){
        cannonPos.y -= 1;
        if (cannonPos.y < -150) {
            cannonfrag += 1;
            
        }
        
    }
    
    // ターゲットの描画
    FillRect(targetRect, Color::red);

    // スコアの描画
    SetFont("nicoca_v1.ttf", 100.0f);
    DrawText(FormatString("%05d", score), Vector2(-319, 149), Color::black);
    DrawText(FormatString("%05d", score), Vector2(-320, 150), Color::white);
}

