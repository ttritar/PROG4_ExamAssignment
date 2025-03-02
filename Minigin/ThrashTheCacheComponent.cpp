#include "ThrashTheCacheComponent.h"

dae::ThrashTheCacheComponent::ThrashTheCacheComponent(std::shared_ptr<dae::GameObject> owner)

	:BaseComponent(*owner)
{

    MeasureTimeGameObject3D(67108864,5);
}


void dae::ThrashTheCacheComponent::MeasureTimeInt(const int arrSize, const int sampleSize)
{
    int* m_array = new int[arrSize]();

    for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
    {
        long long totalTime = 0;

        for (int sample = 0; sample < sampleSize; ++sample)
        {
            // chrono - start
            const auto start = std::chrono::high_resolution_clock::now();

            for (int i = 0; i < arrSize; i += stepsize)
            {
                m_array[i] *= 2;
            }

            // chrono - end
            auto end = std::chrono::high_resolution_clock::now();
            totalTime += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        }

        // Compute average time
        auto averageTime = totalTime / sampleSize;
        std::cout << stepsize << " ; " << averageTime << std::endl;
    }


    delete[] m_array;

}

void dae::ThrashTheCacheComponent::MeasureTimeGameObject3D(const int arrSize, const int sampleSize)
{
    GameObject3DAlt* m_array = new GameObject3DAlt[arrSize]();

    for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
    {
        long long totalTime = 0;

        for (int sample = 0; sample < sampleSize; ++sample)
        {
            // chrono - start
            const auto start = std::chrono::high_resolution_clock::now();

            for (int i = 0; i < arrSize; i += stepsize)
            {
                m_array[i].ID *= 2;
            }

            // chrono - end
            auto end = std::chrono::high_resolution_clock::now();
            totalTime += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        }

        // Compute average time
        auto averageTime = totalTime / sampleSize;
        std::cout << stepsize << " ; " << averageTime << std::endl;

    }


    delete[] m_array;
}
