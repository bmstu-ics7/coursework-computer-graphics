attribute highp vec4 a_position;
uniform highp mat4 u_projectionLightMatrix;
uniform highp mat4 u_shadowLightMatrix;
uniform highp mat4 u_modelMatrix;
varying highp vec4 v_position;

void main(void)
{
    mat4 mv_matrix = u_shadowLightMatrix * u_modelMatrix;
    v_position = u_projectionLightMatrix * mv_matrix * a_position;
    gl_Position = v_position;
}
