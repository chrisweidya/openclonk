/*
 * OpenClonk, http://www.openclonk.org
 *
 * Copyright (c) 2015, The OpenClonk Team and contributors
 *
 * Distributed under the terms of the ISC license; see accompanying file
 * "COPYING" for details.
 *
 * "Clonk" is a registered trademark of Matthes Bender, used with permission.
 * See accompanying file "TRADEMARK" for details.
 *
 * To redistribute this file separately, substitute the full license texts
 * for the above references.
 */

// Default Vertex Shader for mesh-based objects.

// Input uniforms:
//   bones: array of 4x3 bone transformation matrices.


// Input vertex attributes:
//   oc_BoneWeights0 and oc_BoneWeight1: vectors of bone influence weights.
//     The sum of weights must be 1. Each component of these vectors will be
//     matched up with its corresponding component of the oc_BoneIndices0 or
//     oc_BoneIndices1 vectors to specify a vertex bone assignment.
//  oc_BoneIndices0 and oc_BoneIndices1: vectors of bone influence indices.
//    The integer part of every component of these vectors selects one of the
//    bones from the bone matrix array to influence the current vertex.

// If the vertex is not influenced by any bones, it must use a dummy entry
// inside the bone matrix array that contains the identity matrix, with a bone
// weight of 1.0.

varying vec3 normalDir;
uniform mat4x3 bones[80];

// For more performance, this should be set by the engine, and this shader
// should be compiled three times: with BONE_COUNT set to 0, 4, and 8,
// respectively. (Or we could split it even further.)
#define BONE_COUNT 8

attribute vec4 oc_BoneIndices0;
attribute vec4 oc_BoneWeights0;

#if BONE_COUNT > 4
attribute vec4 oc_BoneIndices1;
attribute vec4 oc_BoneWeights1;
#endif

vec4 merge_bone(vec4 vertex, vec4 original, mat4x3 bone, float weight)
{
	return (mat4(bone) * original) * weight + vertex;
}

slice(position)
{
#if BONE_COUNT == 0
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
#else
	vec4 vertex = vec4(0, 0, 0, 0);
	vertex = merge_bone(vertex, gl_Vertex, bones[int(oc_BoneIndices0.x)], oc_BoneWeights0.x);
	vertex = merge_bone(vertex, gl_Vertex, bones[int(oc_BoneIndices0.y)], oc_BoneWeights0.y);
	vertex = merge_bone(vertex, gl_Vertex, bones[int(oc_BoneIndices0.z)], oc_BoneWeights0.z);
	vertex = merge_bone(vertex, gl_Vertex, bones[int(oc_BoneIndices0.w)], oc_BoneWeights0.w);
#if BONE_COUNT > 4
	vertex = merge_bone(vertex, gl_Vertex, bones[int(oc_BoneIndices1.x)], oc_BoneWeights1.x);
	vertex = merge_bone(vertex, gl_Vertex, bones[int(oc_BoneIndices1.y)], oc_BoneWeights1.y);
	vertex = merge_bone(vertex, gl_Vertex, bones[int(oc_BoneIndices1.z)], oc_BoneWeights1.z);
	vertex = merge_bone(vertex, gl_Vertex, bones[int(oc_BoneIndices1.w)], oc_BoneWeights1.w);
#endif
	gl_Position = gl_ModelViewProjectionMatrix * vertex;
#endif
}

slice(texcoord)
{
	texcoord = gl_MultiTexCoord0.st;
}

slice(normal)
{
#if BONE_COUNT == 0
	normalDir = normalize(gl_NormalMatrix * gl_Normal);
#else
	vec4 base_normal = vec4(gl_Normal, 0.0);
	vec4 normal = vec4(0, 0, 0, 0);
	normal = merge_bone(normal, base_normal, bones[int(oc_BoneIndices0.x)], oc_BoneWeights0.x);
	normal = merge_bone(normal, base_normal, bones[int(oc_BoneIndices0.y)], oc_BoneWeights0.y);
	normal = merge_bone(normal, base_normal, bones[int(oc_BoneIndices0.z)], oc_BoneWeights0.z);
	normal = merge_bone(normal, base_normal, bones[int(oc_BoneIndices0.w)], oc_BoneWeights0.w);
#if BONE_COUNT > 4
	normal = merge_bone(normal, base_normal, bones[int(oc_BoneIndices1.x)], oc_BoneWeights1.x);
	normal = merge_bone(normal, base_normal, bones[int(oc_BoneIndices1.y)], oc_BoneWeights1.y);
	normal = merge_bone(normal, base_normal, bones[int(oc_BoneIndices1.z)], oc_BoneWeights1.z);
	normal = merge_bone(normal, base_normal, bones[int(oc_BoneIndices1.w)], oc_BoneWeights1.w);
#endif
	normalDir = normalize(gl_NormalMatrix * normal.xyz);
#endif
}
