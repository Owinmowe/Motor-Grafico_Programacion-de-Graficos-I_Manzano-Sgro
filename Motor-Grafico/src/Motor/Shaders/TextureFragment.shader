#version 330 core
out vec4 FragColor;

in vec3 ourNormal;
in vec3 ourColor;
in vec2 TexCoord;
in vec3 fragWorldPos;

uniform vec3 lightColor;
uniform vec3 lightDirection;
uniform vec3 lightPosition;

uniform vec3 color = vec3(1.0f, 1.0f, 1.0f);
uniform float a = 1.0f;
uniform sampler2D ourTexture;

void main()
{
    vec4 texColor = texture(ourTexture, TexCoord);
    if(texColor.a < 0.1f)
    {
        discard;
    }

    vec3 norm = normalize(ourNormal);
    vec3 lightDir = normalize(lightPosition - fragWorldPos);

    float diff = max(dot(norm, lightDirection), 0.0);
    vec3 diffuse = diff * lightColor;


    FragColor = texColor * vec4(ourColor.x * color.x * diffuse.x, ourColor.y * color.y * diffuse.y, ourColor.z * color.z * diffuse.z, a);
}