#pragma once
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include "Shader.h"
#include "Texture.h"

namespace bobcat {

	class Material {
	public:
		Material(){};
		~Material(){};

		Shader* shader;
		glm::vec4 color;
		Texture* texture;

		inline void Bind(){
			if (shader == nullptr) return; //do not bind if shader isn't present
			/*Send uniforms to the shader*/
			//Color
			glUniform4fv(shader->colorLoc, 1, glm::value_ptr(color));
			//Texture
			if (texture != nullptr){
				texture->Bind(shader->texSamplerLoc);
			}
		}

		inline void Unbind(){
			//Unbind Texture when done
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	};

}