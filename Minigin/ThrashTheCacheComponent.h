#pragma once
#include "GameObject.h"

#include <iostream>
#include <chrono>


namespace dae
{

	struct WorldTransform
	{
		float matrix[16] = {
			1,0,0,0,
			0,1,0,0,
			0,0,1,0,
			0,0,0,1 };
	};

	class GameObject3D
	{
	public:
		WorldTransform transform;
		int ID;
	};

	class GameObject3DAlt
	{
	public:
		WorldTransform* transform;
		int ID;
	};


	class ThrashTheCacheComponent final : public BaseComponent
	{
	public:
		void Render()const override;
		void ImGuiWindow()const;
		void ImGuiCreateGraph(const std::vector<glm::vec2>&resultsVec)const;

		void TrashTheCacheInt()const;
		void TrashTheCacheGameObject3D()const;
		void TrashTheCacheGameObject3DAlt()const;


		ThrashTheCacheComponent(std::shared_ptr<dae::GameObject> owner);

		virtual ~ThrashTheCacheComponent() = default;
		ThrashTheCacheComponent(const ThrashTheCacheComponent& other) = delete;
		ThrashTheCacheComponent(ThrashTheCacheComponent&& other) = delete;
		ThrashTheCacheComponent& operator=(const ThrashTheCacheComponent& other) = delete;
		ThrashTheCacheComponent& operator=(ThrashTheCacheComponent&& other) = delete;


	private:
		mutable int m_sampleSize = 10;
		mutable std::vector<glm::vec2> m_resultsInt;
		mutable std::vector<glm::vec2> m_resultsGameObject3D;
		mutable std::vector<glm::vec2> m_resultsGameObject3DAlt;
		mutable bool m_isAlt = 0;
	};

}