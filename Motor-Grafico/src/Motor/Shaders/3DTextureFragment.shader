#version 330 core
out vec4 FragColor;

in vec3 ourNormal;
in vec3 ourColor;
in vec2 TexCoord;
in vec3 fragWorldPos;

uniform vec3 cameraPos;

struct DirectionalLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform DirectionalLight directionalLight;

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

    //Ambient
    vec3 ambient = directionalLight.ambient * material.ambient;

    //Diffuse
    vec3 norm = normalize(ourNormal);
    vec3 lightDir = normalize(-directionalLight.direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * material.diffuse * directionalLight.diffuse * texture(material.diffuseTexture, TexCoord).rgb;

    //Specular
    vec3 viewDir = normalize(cameraPos - fragWorldPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess * 128);
    vec3 specular = spec * material.specular * directionalLight.specular * texture(material.specularTexture, TexCoord).rgb;

    //light
    vec3 result = ambient + diffuse + specular;

    FragColor = vec4(result * color, a);
}