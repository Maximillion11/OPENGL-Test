#ifndef RENDERER_H
#define RENDERER_H

namespace Renderer
{
	extern unsigned int VBO, VAO, EBO;
	extern unsigned int texture1, texture2;

	extern void Init();
	
	extern void Deallocate();
}

#endif