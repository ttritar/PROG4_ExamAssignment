#pragma once
#include <cstdint>

namespace dae
{
	unsigned int make_sdbm_hash(const char* str);

	using EventId = unsigned int;
	struct Event 
	{
		const EventId id;
		void* arg;
		explicit Event(EventId _id, void* ptr = nullptr) : id{ _id }, arg{ ptr } {}
	};

	class GameObject;
	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void Notify(const Event& event, GameObject* object) = 0;
	};
}

