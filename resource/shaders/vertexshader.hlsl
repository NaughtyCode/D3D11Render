


struct VS_INPUT
{
	float4 pos : POSITION;
};

float4 VSMain( VS_INPUT Input ): SV_POSITION
{
	return Input.pos;
}
