#ifndef RENDERER_H
#define RENDERER_H

namespace Renderer
{
	// Scene 0 = LearnOpenGLGettingStarted
	extern unsigned int VBOgettingstarted, VAOgettingstarted;
	extern unsigned int texture1gettingstarted, texture2gettingstarted;

	// Scene 1 = LearnOpenGLLighting
	extern unsigned int VBOlighting, cubeVAOlighting;
	extern unsigned int lightVAOlighting;
	extern unsigned int texture1lighting, texture2lighting;

	extern void Init(unsigned int sceneID = 0);
	
	extern void Deallocate(unsigned int sceneID = 0);

	extern unsigned int CreateTexture(const char* fileLocation);
}

#endif