uniform vec4 u_color;
uniform sampler2D u_shadowMap;

varying highp vec4 v_lightDirection;
varying highp vec4 v_positionLightMatrix;

float SampleShadowMap(sampler2D map, vec2 coords, float compare)
{
    vec4 v = texture2D(map, coords);
    float value = v.x * 255.0 + (v.y * 255.0 + (v.z * 255.0 + v.w) / 255.0) / 255.0;
    return step(compare, value);
}

float SampleShadowMapLinear(sampler2D map, vec2 coords, float compare, vec2 texelSize)
{
    vec2 pixelPos = coords / texelSize + 0.5;
    vec2 fractPart = fract(pixelPos);
    vec2 startTexel = (pixelPos - fractPart) * texelSize;

    float blTexel = SampleShadowMap(map, startTexel, compare);
    float brTexel = SampleShadowMap(map, startTexel + vec2(texelSize.x, 0.0), compare);
    float tlTexel = SampleShadowMap(map, startTexel + vec2(0.0, texelSize.y), compare);
    float trTexel = SampleShadowMap(map, startTexel + texelSize, compare);

    float mixA = mix(blTexel, tlTexel, fractPart.y);
    float mixB = mix(brTexel, trTexel, fractPart.y);

    return mix(mixA, mixB, fractPart.x);
}

float SampleShadowMapPCF(sampler2D map, vec2 coords, float compare, vec2 texelSize)
{
    float result = 0.0;
    for (float y = -1.0; y <= 1.0; y += 1.0) {
        for (float x = -1.0; x <= 1.0; x += 1.0) {
            vec2 offset = vec2(x, y) * texelSize;
            result += SampleShadowMapLinear(map, coords + offset, compare, texelSize);
        }
    }

    return result / 9.0;
}

float CalcShadowAmount(sampler2D map, vec4 initialShadowCoords)
{
    vec3 tmp = initialShadowCoords.xyz / initialShadowCoords.w;
    tmp = tmp * vec3(0.5) + vec3(0.5);
    return SampleShadowMapPCF(u_shadowMap, tmp.xy, tmp.z * 255.0 - 0.7, vec2(1.0 / 1024.0));
}

void main(void)
{
    float shadowCoef = CalcShadowAmount(u_shadowMap, v_positionLightMatrix);
    shadowCoef = 0.6 * shadowCoef + 0.4;

    gl_FragColor = u_color * shadowCoef;
}
