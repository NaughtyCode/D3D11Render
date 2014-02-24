struct VS_INPUT
{
	float4 vPosition : POSITION;
};

struct VS_OUTPUT
{
	float4 vNormal : SV_POSITION;
};

float4 VSMain( VS_INPUT Input ): SV_POSITION
{
	return Input.vPosition;
}
