struct FRAG_IN
{
	float4 pos : SV_POSITION;
	float4 worldPos : TEXCOORD0;
	float4 normal : NORMAL;
	float4 color : COLOR;
};

struct MaterialData //32
{
	float3 diffuseColor;
	float diffuse;
	float ambient;
	float specular;
	float shininess;
	float _padding[1];
};

struct PointLightData //48
{
	float3 diffuseColor;
	float3 specularColor;
	float3 position;
	float specularPower;
	float innerRadius;
	float outerRadius;
};

cbuffer ConstBuffer : register(b0)
{
	MaterialData material;		//32
	PointLightData pointLight;	//80
	float3 ambientLight;		//92
	float3 cameraPosition;		//104

	float _padding[2];			//112
}

float4 main(FRAG_IN input) : SV_Target
{
	//ambient light
	float3 phong = ambientLight;

	// Point light
	float3 N = normalize(input.normal);
	float3 V = normalize(cameraPosition - input.worldPos);

	float3 L = normalize(pointLight.position - input.worldPos);
	float3 R = reflect(-L, N);

	float NdotL = dot(N, L);
	if (NdotL > 0) {
		/*Diffuse color*/
		float dist = distance(input.worldPos, pointLight.position);
		float sstep = smoothstep(pointLight.innerRadius, pointLight.outerRadius, dist);

		float3 diffuseColor = lerp(pointLight.diffuseColor, float3(0.0f, 0.0f, 0.0f), sstep);
		phong += (diffuseColor * NdotL);

		/*Specular color*/
		float RdotV = dot(R, V);
		phong += pointLight.specularColor * pow(max(0.0f, RdotV), pointLight.specularPower);
	}

	float4 finalPhong = float4(phong, 0.0f);
	return input.color * saturate(finalPhong);
}