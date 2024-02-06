#include "Shaders.h"

namespace Shaders {
	// Scene 0 = LearnOpenGLGettingStarted
	Shader OpenGLGettingStartedShader;

	// Scene 1 = LearnOpenGLLighting
	Shader OpenGLLightingCubeShader;
	Shader OpenGLLightingLightShader;

	void AssignShaders(unsigned int activeScene) {
		// Scene 0 = LearnOpenGLGettingStarted
		if (activeScene == 0) 
		{
			OpenGLGettingStartedShader.AssignShader("Shaders/OpenGLGettingStartedShader.vs", "Shaders/OpenGLGettingStartedShader.fs");
		}
		// Scene 1 = LearnOpenGLLighting
		else if (activeScene == 1)
		{
			OpenGLLightingCubeShader.AssignShader("Shaders/OpenGLLightingCubeShader.vs", "Shaders/OpenGLLightingCubeShader.fs");
			OpenGLLightingLightShader.AssignShader("Shaders/OpenGLLightingLightSourceShader.vs", "Shaders/OpenGLLightingLightSourceShader.fs");
		}
	}
}