#pragma once
#include "BaseComponent.h"
#include <memory>

namespace dae
{
	class ScoreComponent : public BaseComponent
	{
	public:
		ScoreComponent(std::shared_ptr<dae::GameObject> owner)
			:BaseComponent(*owner)
		{
		};

		virtual ~ScoreComponent() = default;
		ScoreComponent(const ScoreComponent& other) = delete;
		ScoreComponent(ScoreComponent&& other) = delete;
		ScoreComponent& operator=(const ScoreComponent& other) = delete;
		ScoreComponent& operator=(ScoreComponent&& other) = delete;



		int GetCurrentScore() { return m_currentScore; }

		void GainScore(int amount);

	private:
		int m_currentScore{};
	};

}
