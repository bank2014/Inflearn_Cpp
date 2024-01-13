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


// TODO: �̰� ��� ó������ ����غ���
//void MoveTo(float destX, float destY, float destZ, float speed) {
//    m_dest.x = destX;
//    m_dest.y = destY;
//    m_dest.z = destZ;
//    m_speed = speed;
//    m_isMoving = true;
//}
//XMFLOAT3 m_dest;   // ������
//float m_speed;     // �ӵ�
//bool m_isMoving;   // �����̰� �ִ��� ����

    //if (m_isMoving) {
    //    // ���� ��ġ�� ������ ������ �Ÿ��� ���
    //    float dx = m_dest.x - m_Position.x;
    //    float dy = m_dest.y - m_Position.y;
    //    float dz = m_dest.z - m_Position.z;
    //    float distance = std::sqrt(dx * dx + dy * dy + dz * dz);
    //
    //    // ���� �̵��� �ӵ��� ���
    //    float actualSpeed = m_speed * deltaTime;
    //
    //    // �������� �����ߴ��� Ȯ��
    //    if (distance < actualSpeed) {
    //        m_Position = m_dest;
    //        m_isMoving = false;
    //    }
    //    else {
    //        // ���� ���͸� ���
    //        float ux = dx / distance;
    //        float uy = dy / distance;
    //        float uz = dz / distance;
    //
    //        // �� �����Ӹ��� �ӵ��� ���� �̵�
    //        m_Position.x += ux * actualSpeed;
    //        m_Position.y += uy * actualSpeed;
    //        m_Position.z += uz * actualSpeed;
    //    }
    //
    //    // AABB ��ġ ����
    //    AABB.SetCenter(m_Position.x, m_Position.y ); // ����: TVector2�� x, y ��ǥ�� ����
    //}
    //// �̵������ϱ� ���� ����� ����
    //UpdateWorldMatrix();