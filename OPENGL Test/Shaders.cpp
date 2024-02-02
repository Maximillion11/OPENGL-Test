#include "Shaders.h"

namespace Shaders {
	Shader MainShader;
	Shader OtherShader;

	void AssignShaders() {
		MainShader.AssignShader("Shaders/Shader.vs", "Shaders/Shader.fs");
		OtherShader.AssignShader("Shaders/Shader.vs", "Shaders/Shader.fs");
	}
}