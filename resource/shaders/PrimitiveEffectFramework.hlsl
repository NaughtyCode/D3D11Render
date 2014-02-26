
struct VS_INPUT
{
	float4 pos : POSITION;
};

float4 VSMain( VS_INPUT Input ): SV_POSITION
{
	return Input.pos;
}

float4 PSMain( float4 Pos : SV_POSITION ) : SV_Target
{
	return float4(0.2,1.0,0,1.0);
}

technique11 BasicEffect
{
  pass pass1
  {
    SetVertexShader( CompileShader( vs_5_0,VSMain() ) );
    SetGeometryShader(NULL);
    SetPixelShader( CompileShader(ps_5_0,PSMain() ) );
  }
}

