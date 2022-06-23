struct FRAG_IN
{
	float4 pos : SV_POSITION;
	float4 worldPos : TEXCOORD0;
	float4 normal : NORMAL;
	float4 color : COLOR;
};

struct MaterialData //8 * 4 = 32
{
	float4 diffuseColor;
	float diffuse;
	float ambient;
	float specular;
	float shininess;
};

struct PointLightData //16 * 4 = 64
{
	float4 diffuseColor;
	float4 specularColor;
	float4 position;
	float specularPower;
	float innerRadius;
	float outerRadius;

	float _padding[1];
};

cbuffer ConstBuffer : register(b0)
{
	MaterialData material;		//32
	PointLightData pointLight;	//96
	float4 ambientLight;		//112
	float4 cameraPosition;		//128
}

float4 main(FRAG_IN input) : SV_Target
{
	//ambient light
	float3 phong = ambientLight.xyz;

	// Point light
	float3 N = normalize(input.normal.xyz);
	float3 V = normalize(cameraPosition.xyz - input.worldPos.xyz);

	float3 L = normalize(pointLight.position.xyz - input.worldPos.xyz);
	float3 R = reflect(-L, N);

	float NdotL = dot(N, L);
	if (NdotL > 0) {
		/*Diffuse color*/
		float dist = distance(input.worldPos.xyz, pointLight.position.xyz);
		float sstep = smoothstep(pointLight.innerRadius, pointLight.outerRadius, dist);

		float3 diffuseColor = lerp(pointLight.diffuseColor.xyz, float3(0.0f, 0.0f, 0.0f), sstep);
		phong += (diffuseColor * NdotL);

		/*Specular color*/
		float RdotV = dot(R, V);
		phong += pointLight.specularColor.xyz * pow(max(0.0f, RdotV), pointLight.specularPower);
	}

	float4 finalPhong = float4(phong, 0.0f);
	return input.color * saturate(finalPhong);
}