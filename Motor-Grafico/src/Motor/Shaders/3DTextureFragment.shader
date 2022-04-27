#version 330 core
out vec4 FragColor;

in vec3 ourNormal;
in vec3 ourColor;
in vec2 TexCoord;
in vec3 fragWorldPos;

uniform vec3 cameraPos;

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;

uniform vec3 color = vec3(1.0f, 1.0f, 1.0f);
uniform float a = 1.0f;

struct Material {
    vec3 ambient;
    sampler2D diffuseTexture;
    vec3 diffuse;
    sampler2D specularTexture;
    vec3 specular;
    float shininess;
};

uniform Material material;

void main()
{
    vec4 diffuseTex = texture(material.diffuseTexture, TexCoord);
    vec3 diffuseColor = vec3(diffuseTex.x, diffuseTex.y, diffuseTex.z);
    vec4 specularTex = texture(material.specularTexture, TexCoord);
    vec3 specularColor = vec3(specularTex.x, specularTex.y, specularTex.z);

    //Ambient
    vec3 ambient = light.ambient * material.ambient;

    //Diffuse
    vec3 norm = normalize(ourNormal);
    vec3 lightDir = normalize(light.position - fragWorldPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = (diff * material.diffuse * diffuseColor) * light.diffuse;

    //Specular
    vec3 viewDir = normalize(cameraPos - fragWorldPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess * 128);
    vec3 specular = (spec * material.specular * specularColor) * light.specular;

    //light
    vec3 light = (ambient + diffuse + specular) * ourColor * color;

    FragColor = vec4(light, a);
}