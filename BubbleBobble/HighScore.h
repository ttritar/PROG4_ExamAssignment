#pragma once
#include <fstream>
#include <string>

struct HighScore
{
	std::string playerName;
	int score{ 0 };

	void WriteToFile()
	{
		std::ofstream file("../HighScore.txt", std::ios::app); 
		if (file.is_open())
		{
			file << playerName << ' ' << score << '\n';
			file.close();
		}
	}

	static std::vector<HighScore> ReadFromFile()
	{
		std::ifstream file("../HighScore.txt");
		std::vector<HighScore> scores;

		if (file.is_open())
		{
			std::string name;
			int score;
			while (file >> name >> score)
			{
				scores.push_back({ name, score });
			}
			file.close();
		}

		return scores;
	}
};
