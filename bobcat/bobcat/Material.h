#pragma once
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include "Shader.h"
#include "Texture.h"
#include "LogManager.h"

namespace bobcat {

	class Material {
	private:
		Shader* m_shader;
	public:
		Material(){};
		~Material(){};

		Shader* getShader(){
			return m_shader;
		}
		void setShader(Shader* _shader){
			m_shader = _shader;
			if (_shader == nullptr){
				LogManager* logManager = LogManager::getInstance();
				logManager->log(LogLevel::LOG_ERROR, "ERROR: Shader provided for material is NULL!");
			}
			//Getting relevant uniforms from shader
			colorLoc = m_shader->getShaderUniform("uniColor");
			texSamplerLoc = m_shader->getShaderUniform("tex");
		}

		__declspec(property(get = getShader, put = setShader)) Shader* shader;
		glm::vec4 color;
		Texture* texture;

		GLuint colorLoc, texSamplerLoc;

		inline void Bind(){
			if (shader == nullptr) return; //do not bind if shader isn't present
			/*Send uniforms to the shader*/
			//Color
			glUniform4fv(colorLoc, 1, glm::value_ptr(color));
			//Texture
			if (texture != nullptr){
				texture->Bind(texSamplerLoc);
			}
		}

		inline void Unbind(){
			//Unbind Texture when done
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	};

}