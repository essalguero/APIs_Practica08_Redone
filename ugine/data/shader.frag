varying vec3 N;
varying vec4 vertexObserver;

varying vec2 fTexture;
uniform bool isTexturized;
uniform sampler2D texSampler;
uniform vec4 color;

const int MAX_LIGHTS = 8;

uniform int numberLights;
uniform int shininess;
uniform vec3 ambientLight;

uniform bool isCubemap;

uniform bool hasNormalTexture;
varying mat3 tbn;
uniform bool hasRefractionTexture;
uniform bool hasReflectionTexture;

uniform samplerCube texSamplerCube;

uniform sampler2D normalTexture;
uniform samplerCube  normalTextureCube;

uniform sampler2D refractionTexture;
uniform samplerCube  refractionTextureCube;

uniform sampler2D reflectionTexture;
uniform samplerCube  reflectionTextureCube;

varying vec3 uvw;
varying vec3 uvwRefraction;
varying vec3 uvwReflection;

vec3 normalizedN;

uniform bool hasTexture;

struct LightInfo                                                           
{  
	vec4 lightColor;
	float linearAttenuation;

	vec4 lightVector;
};
uniform LightInfo lights[MAX_LIGHTS];

struct LightComponents
{
	vec4 diffuseComponent;
	vec4 specularComponent;
};


LightComponents calculateLight(int i)
{

	LightComponents currentLight;

	vec4 diffuseComponent = vec4(ambientLight, 1.0);
	vec4 specularComponent = vec4(0.0, 0.0, 0.0, 1.0);
	float NdotL;

	vec3 normalizedN = normalize(N);

	vec3 L = lights[i].lightVector.xyz;

	float attenuationFactor = 1.0;

	if (lights[i].lightVector.w == 1.0)
	{
		L = L - vertexObserver.xyz;
		attenuationFactor = 1.0 / (1.0 + (lights[i].linearAttenuation * length(L)));
	}

	L = normalize(L);
	NdotL = max(dot(normalizedN, L), 0.0);

	diffuseComponent += NdotL * lights[i].lightColor * attenuationFactor;

	if ((shininess > 0) && (NdotL > 0.0))
	{
		vec4 vertexObserverNorm = normalize(vertexObserver);
		vec3 H = L - vertexObserverNorm.xyz;
		H = normalize(H);
		
		float NdotH = max(dot(normalizedN, H), 0.0);

		specularComponent += pow(NdotH, float(shininess)) * attenuationFactor;
	}

	currentLight.diffuseComponent = diffuseComponent;
	currentLight.specularComponent = specularComponent;

	return currentLight;
}


void main()
{
	vec4 diffuseComponent = vec4(1, 1, 1, 1);
	vec4 specularComponent = vec4(0, 0, 0, 0);
	LightComponents currentLight; 

	/*if (numberLights > 0)
	{
		diffuseComponent = vec4(0, 0, 0, 1);

		for (int i = 0; i < numberLights; ++i)
		{
			currentLight = calculateLight(i);
			
			specularComponent += currentLight.specularComponent;
			diffuseComponent += currentLight.diffuseComponent;
			
		}
	}*/

	vec4 finalColor = diffuseComponent * color;

	if (isTexturized)
	{
		 finalColor *= texture2D(texSampler, fTexture);
	}
	
	gl_FragColor = finalColor + specularComponent;

}