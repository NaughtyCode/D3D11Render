


float4 PSMain( float4 Pos : SV_POSITION ) : SV_Target
{
	return float4(Pos.z,Pos.x/20,Pos.y/100,1.0);
}
