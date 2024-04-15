/*
 * GNU Sparky --- A 5v5 character-based libre tactical shooter
 * Copyright (C) 2024 Wasym A. Alonso
 *
 * This file is part of Sparky.
 *
 * Sparky is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Sparky is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Sparky.  If not, see <http://www.gnu.org/licenses/>.
 */


#version 330

#define PI                3.14159265358979323846
#define MAX_LIGHTS        4
#define LIGHT_POINT       1
#define LIGHT_DIRECTIONAL 0

struct Light {
  int enabled;
  int type;
  vec3 position;
  vec3 target;
  vec4 color;
  float intensity;
};

in vec3 fragPosition;
in vec2 fragTexCoord;
in vec4 fragColor;
in vec3 fragNormal;
in vec4 shadowPos;
in mat3 TBN;

uniform int numOfLights;
uniform sampler2D albedoMap;
uniform sampler2D mraMap;
uniform sampler2D normalMap;
uniform sampler2D emissiveMap;
uniform vec2 tiling;
uniform vec2 offset;
uniform int useTexAlbedo;
uniform int useTexNormal;
uniform int useTexMRA;
uniform int useTexEmissive;
uniform vec4  albedoColor;
uniform vec4  emissiveColor;
uniform float normalValue;
uniform float metallicValue;
uniform float roughnessValue;
uniform float aoValue;
uniform float emissivePower;
uniform Light lights[MAX_LIGHTS];
uniform vec3 viewPos;
uniform vec3 ambientColor;
uniform float ambient;

out vec4 finalColor;

vec3 SchlickFresnel(float hDotV, vec3 refl) {
  return refl + ((1.0 - refl) * pow(1.0 - hDotV, 5.0));
}

float GgxDistribution(float nDotH, float roughness) {
  float a = roughness * roughness * roughness * roughness;
  float d = nDotH * nDotH * (a - 1.0) + 1.0;
  d = PI * d * d;
  return a / max(d, 0.0000001);
}

float GeomSmith(float nDotV,float nDotL,float roughness) {
  float r = roughness + 1.0;
  float k = (r * r) / 8.0;
  float ik = 1.0 - k;
  float ggx1 = nDotV / ((nDotV * ik) + k);
  float ggx2 = nDotL / ((nDotL * ik) + k);
  return ggx1 * ggx2;
}

vec3 ComputePBR(void) {
  vec3 albedo = texture(albedoMap, vec2((fragTexCoord.x * tiling.x) + offset.x, (fragTexCoord.y * tiling.y) + offset.y)).rgb;
  albedo = vec3(albedoColor.x * albedo.x, albedoColor.y * albedo.y, albedoColor.z * albedo.z);
  float metallic = clamp(metallicValue, 0.0, 1.0);
  float roughness = clamp(roughnessValue, 0.0, 1.0);
  float ao = clamp(aoValue, 0.0, 1.0);  
  if (useTexMRA == 1) {
    vec4 mra = texture(mraMap, vec2((fragTexCoord.x * tiling.x) + offset.x, (fragTexCoord.y * tiling.y) + offset.y)) * useTexMRA;
    metallic = clamp(mra.r + metallicValue, 0.04, 1.0);
    roughness = clamp(mra.g + roughnessValue, 0.04, 1.0);
    ao = (mra.b + aoValue) * 0.5;
  }
  vec3 N = normalize(fragNormal);
  if (useTexNormal == 1) {
    N = texture(normalMap, vec2((fragTexCoord.x * tiling.x) + offset.y, (fragTexCoord.y * tiling.y) + offset.y)).rgb;
    N = normalize((N * 2.0) - 1.0);
    N = normalize(N * TBN);
  }
  vec3 V = normalize(viewPos - fragPosition);
  vec3 emissive = vec3(0);
  emissive = (texture(emissiveMap, vec2((fragTexCoord.x * tiling.x) + offset.x, (fragTexCoord.y * tiling.y) + offset.y)).rgb).g * emissiveColor.rgb * emissivePower * useTexEmissive;
  vec3 baseRefl = mix(vec3(0.04), albedo.rgb, metallic);
  vec3 lightAccum = vec3(0.0);
  for (int i = 0; i < numOfLights; ++i) {
    vec3 L = normalize(lights[i].position - fragPosition);
    vec3 H = normalize(V + L);
    float dist = length(lights[i].position - fragPosition);
    float attenuation = 1.0 / (dist * dist * 0.23);
    vec3 radiance = lights[i].color.rgb * lights[i].intensity * attenuation;
    float nDotV = max(dot(N, V), 0.0000001);
    float nDotL = max(dot(N, L), 0.0000001);
    float hDotV = max(dot(H, V), 0.0);
    float nDotH = max(dot(N, H), 0.0);
    float D = GgxDistribution(nDotH, roughness);
    float G = GeomSmith(nDotV, nDotL, roughness);
    vec3 F = SchlickFresnel(hDotV, baseRefl);
    vec3 spec = (D * G * F) / (4.0 * nDotV * nDotL);
    vec3 kD = vec3(1.0) - F;
    kD *= 1.0 - metallic;
    lightAccum += (((kD * (albedo.rgb / PI)) + spec) * radiance * nDotL) * lights[i].enabled;
  }
  vec3 ambientFinal = (ambientColor + albedo) * ambient * 0.5;
  return ambientFinal + (lightAccum * ao) + emissive;
}

void main(void) {
  vec3 color = ComputePBR();
  color = pow(color, color + vec3(1.0));
  color = pow(color, vec3(1.0 / 2.2));
  finalColor = vec4(color, 1.0);
}
