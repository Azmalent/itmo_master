struct VERT_IN
{
	float4 pos : POSITION0;
	float4 col : COLOR0;
};

struct FRAG_IN
{
	float4 pos : SV_POSITION;
	float4 col : COLOR;
};

FRAG_IN main(VERT_IN input)
{
	FRAG_IN output = (FRAG_IN)0;

	output.pos = input.pos;
	output.col = input.col;

	return output;
}