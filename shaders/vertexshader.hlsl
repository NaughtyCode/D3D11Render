struct VS_INPUT
{
	float4 vPosition : POSITION;
};

float4 VSMain( VS_INPUT Input ): SV_POSITION
{
	return Input.vPosition;
}
