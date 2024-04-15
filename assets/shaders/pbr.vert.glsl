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

const float normalOffset = 0.1;

in vec3 vertexPosition;
in vec2 vertexTexCoord;
in vec3 vertexNormal;
in vec3 vertexTangent;
in vec4 vertexColor;

uniform mat4 mvp;
uniform mat4 matModel;
uniform mat4 matNormal;
uniform vec3 lightPos;
uniform vec4 difColor;

out vec3 fragPosition;
out vec2 fragTexCoord;
out vec4 fragColor;
out vec3 fragNormal;
out mat3 TBN;

void main(void) {
  vec3 vertexBinormal = cross(vertexNormal, vertexTangent);
  mat3 normalMatrix = transpose(inverse(mat3(matModel)));
  fragPosition = vec3(matModel * vec4(vertexPosition, 1.0f));
  fragTexCoord = vertexTexCoord * 2.0;
  fragNormal = normalize(normalMatrix * vertexNormal);
  vec3 fragTangent = normalize(normalMatrix * vertexTangent);
  fragTangent = normalize(fragTangent - (dot(fragTangent, fragNormal) * fragNormal));
  vec3 fragBinormal = normalize(normalMatrix * vertexBinormal);
  fragBinormal = cross(fragNormal, fragTangent);
  TBN = transpose(mat3(fragTangent, fragBinormal, fragNormal));
  gl_Position = mvp * vec4(vertexPosition, 1.0);
}
