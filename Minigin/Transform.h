#pragma once
#include <glm.hpp>

namespace dae
{
	class Transform final
	{
	public:
		
		void SetPosition(float x, float y, float z);

		//const float GetRotation() const { return m_rotation; }
		//void SetRotation(const float rotation);
	private:
		//const glm::vec3& GetPosition() const { return m_position; }
		glm::vec3 m_position;
		//float m_rotation;
	};
}
