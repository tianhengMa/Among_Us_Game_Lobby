#version 330 core
// This is a sample fragment shader.

// Inputs to the fragment shader are the outputs of the same name from the vertex shader.
// Note that you do not have access to the vertex shader's default output, gl_Position.
//in float sampleExtraOutput;
in vec3 posOutput;
in vec3 normalOutput;

uniform vec3 color;

// Point Light fields
uniform vec3 lightDirection;
uniform vec3 lightAmbient;
uniform vec3 lightDiffuse;
uniform vec3 lightSpecular;

uniform vec3 viewPos;

// switch between rendering models
uniform int isAstronaut;

// Materials
uniform vec3 in_ambient;
uniform vec3 in_diffuse;
uniform vec3 in_specular;
uniform float in_shininess;

// You can output many things. The first vec4 type output determines the color of the fragment
out vec4 fragColor;

void main()
{
    //float dist = abs(distance(lightPos, posOutput) * lightAtten.y);
    //vec3 atten_lightColor = lightColor / dist;
    vec3 viewPos = vec3(0,0,20);
    vec3 normal = normalize(normalOutput);
    vec3 lightDir = normalize(-lightDirection);
    vec3 viewDir = normalize(viewPos - posOutput);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), in_shininess);
    // combine results
    vec3 ambient  = lightAmbient  * in_ambient;
    vec3 diffuse  = lightDiffuse  * diff * in_diffuse;
    vec3 specular = lightSpecular * spec * in_specular;
     
    /*
    vec3 atten_lightColor = lightColor/1.3;
    vec3 viewPos = vec3(0,0,20);

    // ambient
    vec3 ambient = atten_lightColor * in_ambient;
      
    // diffuse
    vec3 norm = normalize(normalOutput);
    vec3 lightDir = normalize(lightPos - posOutput);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = atten_lightColor * (diff * in_diffuse);

    // specular
    vec3 viewDir = normalize(viewPos - posOutput);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), in_shininess);
    vec3 specular = atten_lightColor * (spec * in_specular);
    */
    vec3 result = ambient + diffuse + specular;

    if (isAstronaut == 1){
        // Use the color passed in. An alpha of 1.0f means it is not transparent.
        //fragColor = vec4(color, 1.0);
        
        float intensity = dot(lightDir,normal);
        vec3 newColor;
        if (intensity > 0.95)
            newColor = 1.0f * color;
        else if (intensity > 0.5)
            newColor = 0.7f * color;
        else if (intensity > 0.25)
            newColor = 0.35f * color;
        else
            newColor = 0.1f * color;
        fragColor = vec4(newColor, 1.0);
        
        float edge = max(0, dot(viewDir,normal));
        if (edge < 0.6){
            fragColor = vec4(0,0,0,1.0);
        }
        
        
    } else {
        fragColor = vec4(result, 1.0);
    }
    //fragColor = vec4(result, 1.0);
    //fragColor = vec4(1,0,0,1.0);
}
