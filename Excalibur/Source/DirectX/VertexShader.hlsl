struct vs_in 
{
    float2 position_local : POSITION;
    float4 color : COLOR;
    float2 tex_coord : TEX;
};

struct vs_out 
{
    float4 position_clip : SV_POSITION; 
    float4 color : COLOR0;
    float2 tex_coord : TEXCOORD0;
    float alpha : COLOR1;
};

cbuffer cbPerObject
{
    float4x4 worldViewProjection;
    float2 scale;
    float2 texOffset;
    float4x4 rotation;
    float2 worldPosition;
    float alpha;
    float padding;
};

vs_out main(vs_in input) 
{
    vs_out output = (vs_out)0;

    float4 v = float4(input.position_local.x * scale.x, input.position_local.y * scale.y, 0.0, 1.0);
    v = mul(v, rotation);
    v = v + float4(worldPosition.x, worldPosition.y, 0.0, 0.0);
    output.position_clip = mul(v, worldViewProjection);

    output.color = input.color;
    output.tex_coord = input.tex_coord + texOffset;
    output.alpha = alpha;

    return output;
}

