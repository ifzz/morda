#pragma once

#include "../../../src/morda/render/VertexArray.hpp"

#include <GL/glew.h>


class OpenGL2VertexArray : public morda::VertexArray{
	GLuint arr;
public:
	OpenGL2VertexArray(std::vector<std::shared_ptr<morda::VertexBuffer>>&& buffers);
	
	OpenGL2VertexArray(const OpenGL2VertexArray&) = delete;
	OpenGL2VertexArray& operator=(const OpenGL2VertexArray&) = delete;
	
	~OpenGL2VertexArray()noexcept;
	
private:

};

