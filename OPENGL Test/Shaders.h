#ifndef SHADERS_H
#define SHADERS_H

#include "Shader.h"

namespace Shaders {
	// Scene 0 = LearnOpenGLGettingStarted
	extern Shader OpenGLGettingStartedShader;

	// Scene 1 = LearnOpenGLLighting
	extern Shader OpenGLLightingCubeShader;
	extern Shader OpenGLLightingLightShader;

	extern void AssignShaders(unsigned int activeScene = 0);
}

#endif