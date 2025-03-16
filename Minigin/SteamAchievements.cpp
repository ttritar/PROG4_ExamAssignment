#include "SteamAchievements.h"

namespace dae
{
	bool dae::UnlockAchievement(const char* achievementID)
    {
        if (SteamUserStats() == nullptr)
        {
            return false;
        }

        bool success = SteamUserStats()->SetAchievement(achievementID);
        SteamUserStats()->StoreStats();

        if (!success)
        {
            std::cout << "Failed to unlock achievement: " << achievementID << "\n";
        }

        return success;
    }
}
