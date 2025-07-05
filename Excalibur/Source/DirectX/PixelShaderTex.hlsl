
struct vs_out 
{
    float4 position_clip : SV_POSITION; 
    float4 color : COLOR0;
    float2 tex_coord : TEXCOORD0;
    float alpha : COLOR1;
};

Texture2D ObjTexture;
SamplerState ObjSamplerState;

float4 main(vs_out input) : SV_TARGET 
{
    float4 color = ObjTexture.Sample(ObjSamplerState, input.tex_coord);
    color.w *= input.alpha;
    return color;
}