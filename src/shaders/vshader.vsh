attribute highp vec4 a_position;
attribute highp vec2 a_texcoord;
uniform highp mat4 u_projectionMatrix;
uniform highp mat4 u_viewMatrix;
uniform highp mat4 u_modelMatrix;

uniform highp vec4 u_lightDirection;

uniform highp mat4 u_projectionLightMatrix;
uniform highp mat4 u_shadowLightMatrix;
uniform highp mat4 u_lightMatrix;

varying highp vec4 v_lightDirection;
varying highp vec4 v_positionLightMatrix;

void main(void)
{
    mat4 mv_matrix = u_viewMatrix * u_modelMatrix;
    gl_Position = u_projectionMatrix * mv_matrix * a_position;

    v_positionLightMatrix = u_projectionLightMatrix * u_shadowLightMatrix * u_modelMatrix * a_position;
    v_lightDirection = u_viewMatrix * u_lightMatrix * u_lightDirection;
}
