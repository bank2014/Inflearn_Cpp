struct VS_IN
{
    float4 position : POSITION;
    float2 tex : TEXCOORD0;
};

struct VS_OUT
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
};

cbuffer cb0 
{
    matrix orthoMatrix;
}

VS_OUT VS(VS_IN input)
{
    VS_OUT output;
    
    output.position = mul(input.position, orthoMatrix);
    output.tex = input.tex;
    
    return output;
}



Texture2D shaderTexture;
SamplerState sampleType;

struct PS_IN
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
};

float4 PS(PS_IN input) : SV_Target
{
    float4 textureColor;
    
    textureColor = shaderTexture.Sample(sampleType, input.tex);
    
    return textureColor;
}