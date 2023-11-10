#include "pch.h"
#include "AActor.h"

//
//void ASpriteUV::InitThis(SpriteDesc& desc)
//{
//    Sprite = std::move(desc);
//
//    SetDevice(g_pDevice, g_pContext);
//    SetPos(Sprite.Position);
//    SetScale(Sprite.scale);
//
//    // 알파텍스처가 있다면 로드
//    if (!Sprite.AlphaTextureFileName.empty())
//    {
//        Sprite.AlphaTexture = TEXTURE_MANAGER.LoadTextureFile(Sprite.AlphaTextureFileName);
//    }
//
//    //SetUVFrameFromSprite
//    UVFrame uvFrame;
//    TVector2 UV;
//
//    float offsetX = 1.0f / Sprite.ColumnCount;
//    float offsetY = 1.0f / Sprite.RowCount;
//    for (int row = 0; row < Sprite.RowCount; row++)
//    {
//        UV.y = offsetY * row;
//        for (int column = 0; column < Sprite.ColumnCount; column++)
//        {
//            UV.x = offsetX * column;
//            uvFrame.m_Min = UV;
//            uvFrame.m_Max.x = UV.x + offsetX;
//            uvFrame.m_Max.y = UV.y + offsetY;
//            UVFrameList.push_back(uvFrame);
//        }
//    }
//    Sprite.OffsetTime = Sprite.TotalAnimTimeInSecond / UVFrameList.size();
//
//    SetupGraphicsPipeline();
//    Init();
//}
//bool ASpriteUV::Init()
//{
//    AActor::Init();
//    return true;
//}
//bool ASpriteUV::TickComponent()
//{
//    AActor::TickComponent();
//    Sprite.ElapsedTime += g_DeltaTime;
//    if (Sprite.ElapsedTime >= Sprite.OffsetTime)
//    {
//        Sprite.CurrentAnimFrameIndex++;
//        if (Sprite.CurrentAnimFrameIndex >= UVFrameList.size())
//        {
//            Sprite.CurrentAnimFrameIndex = 0;
//        }
//        Sprite.ElapsedTime -= Sprite.OffsetTime;
//    }
//    return true;
//}
//bool ASpriteUV::Render()
//{
//    UVFrame UV = UVFrameList[Sprite.CurrentAnimFrameIndex];
//    m_Vertices[0].UV = UV.m_Min;
//    m_Vertices[1].UV.x = UV.m_Max.x;
//    m_Vertices[1].UV.y = UV.m_Min.y;
//
//    m_Vertices[2].UV.x = UV.m_Min.x;
//    m_Vertices[2].UV.y = UV.m_Max.y;
//    m_Vertices[3].UV = m_Vertices[2].UV;
//
//    m_Vertices[4].UV = m_Vertices[1].UV;
//    m_Vertices[5].UV = UV.m_Max;
//
//    m_ImmediateContext->UpdateSubresource(m_pVertexBuffer, 0, nullptr, &m_Vertices.at(0), 0, 0);
//
//    PreRender();
//    if (Sprite.AlphaTexture)
//    {
//        Sprite.AlphaTexture->BindToPipeline(m_ImmediateContext, 1);
//    }
//    PostRender();
//    return true;
//}
//bool ASpriteUV::Release()
//{
//    AActor::Release();
//    return true;
//}
//ASpriteUV::~ASpriteUV()
//{
//    Release();
//}
