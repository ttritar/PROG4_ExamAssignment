#pragma once
#include "GameObject.h"

#include <iostream>
#include <chrono>


namespace dae
{

	struct TransformAlt
	{
		float matrix[16] = {
			1,0,0,0,
			0,1,0,0,
			0,0,1,0,
			0,0,0,1 };
	};

	class GameObject3DAlt
	{
	public:
		TransformAlt transform;
		int ID;
	};


	class ThrashTheCacheComponent final : public BaseComponent
	{
	public:
		//void Update(float deltaTime) override;

		ThrashTheCacheComponent(std::shared_ptr<dae::GameObject> owner);

		void MeasureTimeInt(const int arrSize, const int sampleSize);	//Default = int
		void MeasureTimeGameObject3D(const int arrSize, const int sampleSize);

		virtual ~ThrashTheCacheComponent() = default;
		ThrashTheCacheComponent(const ThrashTheCacheComponent& other) = delete;
		ThrashTheCacheComponent(ThrashTheCacheComponent&& other) = delete;
		ThrashTheCacheComponent& operator=(const ThrashTheCacheComponent& other) = delete;
		ThrashTheCacheComponent& operator=(ThrashTheCacheComponent&& other) = delete;


	private:
		
	};

}