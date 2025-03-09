#pragma once
#include "Singleton.h"

namespace dae
{
	class Time final : public Singleton<Time>
	{
		friend class Singleton<Time>;

	public: 
		float DeltaTime;
	};

}