#version 460 core

precision mediump float;

out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D texture1;
//uniform sampler2D texture2;

struct Material
{
    float shininess;
    sampler2D specular;
    sampler2D diffuse;
};
uniform Material material;

struct Light
{
    vec4 position;
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
    float cutOff;
    float outerCutOff;
};
uniform Light light;

uniform vec3 viewPos;
uniform mat4 view;

void main()
{
    vec3 lightPos = light.position.xyz;
    if (light.position.w == 0.) lightPos = -lightPos;
    // attenuation
    float dist = length(lightPos - FragPos);
    float attenuation = 1. / (light.constant + light.linear * dist + light.quadratic * dist * dist);
    // ambient
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoord).xyz;
    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir;
    if (light.position.w == 0.)
    {
        lightDir = normalize(lightPos);
    }
    else if (light.position.w == 1.)
    {
        lightDir = normalize(lightPos - FragPos);
    }
    float diff = max(dot(norm, lightDir), 0.);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoord).xyz;
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular, TexCoord).xyz;
    // cutOff
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0., 1.);
    diffuse *= intensity;
    specular *= intensity;
    // result
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    vec3 result = ambient + diffuse + specular;

    FragColor = texture(texture1, TexCoord) * /*mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.5) * */vec4(result, 1.);
}