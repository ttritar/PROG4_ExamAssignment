#pragma once
#include "BaseComponent.h"
#include <memory>

namespace cat
{
	class ScoreComponent : public dae::BaseComponent
	{
	public:
		ScoreComponent(dae::GameObject& owner);

		virtual ~ScoreComponent() = default;
		ScoreComponent(const ScoreComponent& other) = delete;
		ScoreComponent(ScoreComponent&& other) = delete;
		ScoreComponent& operator=(const ScoreComponent& other) = delete;
		ScoreComponent& operator=(ScoreComponent&& other) = delete;


		static int GetCurrentScore() { return m_currentScore; }

		void GainScore(int amount);

	private:
		static inline int m_currentScore;
	};

}
