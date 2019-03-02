#version 330 core
out vec4 myColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform vec3 viewPos;

struct Material{
        sampler2D diffuse;
        sampler2D specular;
        float shininess;
};
struct DirectionLight{
        vec3 direction;
        vec3 ambient;
        vec3 diffuse;
        vec3 specular;
};

struct PointLight{
        float constant;
        float linear;
        float quadratic;

        vec3 position;
        vec3 ambient;
        vec3 diffuse;
        vec3 specular;
};
struct FlashLight{
        vec3 position;
        vec3 direction;
        
        float cutoff;
        float outerCutoff;

        vec3 ambient;
        vec3 diffuse;
        vec3 specular;

         float constant;
        float linear;
        float quadratic;
};
# define NR_OF_POINTSLIGHT 4
uniform DirectionLight directionLight;
uniform PointLight pointLight[NR_OF_POINTSLIGHT];
uniform FlashLight flashLight;
uniform Material material;

vec3 calculateDirLight(DirectionLight dirLight,vec3 normal,vec3 viewDir);
vec3 calculatePointLight(PointLight pointLight,vec3 normal,vec3 viewDir,vec3 FragPos);
vec3 calculateFlashLight(FlashLight flashLight,vec3 normal,vec3 viewDir,vec3 FragPos);
void main()
{
        vec3 norm=normalize(Normal);
        vec3 viewDir=normalize(FragPos-viewPos);
        vec3 lightSum=vec3(0,0,0);
        //direction light
        lightSum+=calculateDirLight(directionLight,norm,viewDir);
        for(int i=0;i<NR_OF_POINTSLIGHT;i++)
                lightSum+=calculatePointLight(pointLight[i],norm,viewDir,FragPos);
        lightSum+=calculateFlashLight(flashLight,norm,viewDir,FragPos);
        myColor=vec4(lightSum,1.0f);
        
}
vec3 calculateDirLight(DirectionLight dirLight,vec3 normal,vec3 viewDir)
{       
        vec3 lightDir=normalize(dirLight.direction);
        float diff=max(dot(normal,-lightDir),0.0);
        vec3 ambient=dirLight.ambient*vec3(texture(material.diffuse,TexCoords));
        vec3 diffuse=dirLight.diffuse*diff*vec3(texture(material.diffuse,TexCoords));
        vec3 reflectDir=reflect(lightDir,normal);
        float spec=pow(max(dot(reflectDir,-viewDir),0.0),material.shininess);
        vec3 specular=spec*dirLight.specular*vec3(texture(material.specular,TexCoords));
        return ambient+diffuse+specular;
}
vec3 calculatePointLight(PointLight pointLight,vec3 normal,vec3 viewDir,vec3 FragPos)
{       
        vec3 lightDir=normalize(pointLight.position-FragPos);
        float diff=max(dot(normal,-lightDir),0.0);
        vec3 ambient=pointLight.ambient*vec3(texture(material.diffuse,TexCoords));
        vec3 diffuse=pointLight.diffuse*diff*vec3(texture(material.diffuse,TexCoords));
        vec3 reflectDir=reflect(lightDir,normal);
        float spec=pow(max(dot(reflectDir,-viewDir),0.0),material.shininess);
        vec3 specular=spec*pointLight.specular*vec3(texture(material.specular,TexCoords));
        float distance=length(pointLight.position-FragPos);
        float attenuation=1.0/(pointLight.constant+pointLight.linear*distance+pointLight.quadratic*distance*distance);
        
        ambient  *= attenuation;
        diffuse  *= attenuation;
        specular *= attenuation;
        return ambient+diffuse+specular;
}
vec3 calculateFlashLight(FlashLight flashLight,vec3 normal,vec3 viewDir,vec3 FragPos)
{
        vec3 lightDir=normalize(FragPos-flashLight.position);
        float theta=dot(lightDir,flashLight.direction);
        float delta=(theta-flashLight.outerCutoff)/(flashLight.cutoff-flashLight.outerCutoff);
        float intensity=clamp(delta,0.0,1.0);

        float diff=max(dot(normal,-lightDir),0.0);
        vec3 ambient=flashLight.ambient*vec3(texture(material.diffuse,TexCoords));
        vec3 diffuse=flashLight.diffuse*diff*vec3(texture(material.diffuse,TexCoords));
         vec3 reflectDir=reflect(-lightDir,normal);
        float spec=pow(max(dot(reflectDir,-viewDir),0.0),material.shininess);
         vec3 specular=spec*flashLight.specular*vec3(texture(material.specular,TexCoords));

         float distance=length(flashLight.position-FragPos);
         float attenuation=1.0/(flashLight.constant+flashLight.linear*distance+flashLight.quadratic*distance*distance);
        
        ambient  *= attenuation;
        diffuse  *= attenuation;
        specular *= attenuation;
        return (ambient+diffuse+specular)*intensity;


}