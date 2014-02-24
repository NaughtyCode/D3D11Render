


float4 PSMain( float4 Pos : SV_POSITION ) : SV_Target
{
	return float4(Pos.z,sin(Pos.x),cos(Pos.y),1.0);
}
