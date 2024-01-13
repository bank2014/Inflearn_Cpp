#include "Global.h"
#include "Core.h"
#include "Girl.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {

    EngineCore game;
    game.MakeWindow(L"Game", hInstance, 1280, 720);
    game.Init();
    game.Run();
    return 0;
};


// TODO: 이거 어떻게 처리할지 고민해보기
//void MoveTo(float destX, float destY, float destZ, float speed) {
//    m_dest.x = destX;
//    m_dest.y = destY;
//    m_dest.z = destZ;
//    m_speed = speed;
//    m_isMoving = true;
//}
//XMFLOAT3 m_dest;   // 목적지
//float m_speed;     // 속도
//bool m_isMoving;   // 움직이고 있는지 여부

    //if (m_isMoving) {
    //    // 현재 위치와 목적지 사이의 거리를 계산
    //    float dx = m_dest.x - m_Position.x;
    //    float dy = m_dest.y - m_Position.y;
    //    float dz = m_dest.z - m_Position.z;
    //    float distance = std::sqrt(dx * dx + dy * dy + dz * dz);
    //
    //    // 실제 이동할 속도를 계산
    //    float actualSpeed = m_speed * deltaTime;
    //
    //    // 목적지에 도착했는지 확인
    //    if (distance < actualSpeed) {
    //        m_Position = m_dest;
    //        m_isMoving = false;
    //    }
    //    else {
    //        // 단위 벡터를 계산
    //        float ux = dx / distance;
    //        float uy = dy / distance;
    //        float uz = dz / distance;
    //
    //        // 매 프레임마다 속도에 따라 이동
    //        m_Position.x += ux * actualSpeed;
    //        m_Position.y += uy * actualSpeed;
    //        m_Position.z += uz * actualSpeed;
    //    }
    //
    //    // AABB 위치 갱신
    //    AABB.SetCenter(m_Position.x, m_Position.y ); // 가정: TVector2는 x, y 좌표를 저장
    //}
    //// 이동했으니까 월드 행렬을 갱신
    //UpdateWorldMatrix();