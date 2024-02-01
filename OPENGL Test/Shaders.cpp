#include "Shaders.h"

namespace Shaders {
	Shader MainShader;
	Shader OtherShader;

	void AssignShaders() {
		MainShader.AssignShader("Shader.vs", "Shader.fs");
		OtherShader.AssignShader("Shader.vs", "Shader.fs");
	}
}