#include "ThrashTheCacheComponent.h"

#include "imgui.h"
#include "implot.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_opengl3.h"  // Change if using Vulkan/DirectX


dae::ThrashTheCacheComponent::ThrashTheCacheComponent(std::shared_ptr<dae::GameObject> owner)

    :BaseComponent(*owner)
{
   //TrashTheCacheInt();
   //TrashTheCacheGameObject3D();
   //TrashTheCacheGameObject3DAlt();
}



void dae::ThrashTheCacheComponent::Render() const
{

    ImGuiWindow();
}

void dae::ThrashTheCacheComponent::ImGuiWindow() const
{
    if (ImGui::Begin("Exercise 2"))
    {
        ImGui::PushItemWidth(100);
        ImGui::InputInt("# samples", &m_sampleSize);
        ImGui::PopItemWidth();


        // BUTTONS
        if (ImGui::Button("Thrash the cache"))
        {
            TrashTheCacheInt();
        }


        ImGuiCreateGraph(m_resultsInt);

        ImGui::End();
    }

    // Create a window 
    if(ImGui::Begin("Exercise 3"))
    {

        ImGui::PushItemWidth(100);
        ImGui::InputInt("# samples", &m_sampleSize);
        ImGui::PopItemWidth();

        // BUTTONS
        if (ImGui::Button("Thrash the cache with GameObject3d"))
        {
            TrashTheCacheGameObject3D();
            m_isAlt = 0;
        }
        if (ImGui::Button("Thrash the cache with GameObject3dAlt"))
        {
            TrashTheCacheGameObject3DAlt();
            m_isAlt = 1;
        }
       
        if(m_isAlt)
            ImGuiCreateGraph(m_resultsGameObject3DAlt);
        else
            ImGuiCreateGraph(m_resultsGameObject3D);


        ImGui::End();
    }
}
void dae::ThrashTheCacheComponent::ImGuiCreateGraph(const std::vector<glm::vec2>& resultsVec) const
{
    if (resultsVec.empty())
    {
        return;
    }

    ImPlot::PushStyleColor(ImPlotCol_PlotBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f)); // Fully transparent background
    ImPlot::PushStyleColor(ImPlotCol_AxisGrid, ImVec4(0.3f, 0.3f, 0.5f, 0.8f)); // Light blue grid lines
    ImPlot::PushStyleColor(ImPlotCol_AxisBg, ImVec4(0.05f, 0.05f, 0.1f, 1.0f)); // Dark axis background

    if (ImPlot::BeginPlot("##Trash the cache", ImVec2(-1, 0), ImPlotFlags_NoLegend | ImPlotFlags_NoMenus | ImPlotFlags_NoBoxSelect |
        ImPlotFlags_NoMouseText | ImPlotFlags_NoFrame))
    {

        int numPoints = static_cast<int>(resultsVec.size());
      
        std::vector<float> x_data(numPoints);
        std::vector<float> y_data(numPoints);

        for (int i = 0; i < numPoints; ++i)
        {
            x_data[i] = static_cast<float>(resultsVec[i].x);
            y_data[i] = static_cast<float>(resultsVec[i].y);
        }

        ImPlot::SetNextLineStyle(ImVec4(0.0f, 1.0f, 0.0f, 1.0f));
        ImPlot::PlotLine("##Trash the cache", x_data.data(), y_data.data(), numPoints);

        if (ImPlot::IsPlotHovered()) 
        {
            auto mousePos = ImPlot::GetPlotMousePos();

            // Find the closest data point
            int closest_index = 0;
            float min_dist = FLT_MAX;
            for (int i = 0; i < numPoints; ++i)
            {
                double dx =x_data[i] - mousePos.x;
                double dy =y_data[i] - mousePos.y;
                double dist = dx * dx + dy * dy;
                if (dist < min_dist) 
                {
                    min_dist = static_cast<float>(dist);
                    closest_index = i;
                }
            }

            // Highlight the closest point
            ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle, 5.0f, ImVec4(1, 0, 0, 1), 2.0f, ImVec4(1, 1, 1, 1));
            ImPlot::PlotScatter("##Highlighted", &x_data[closest_index], &y_data[closest_index], 1);

            // Show tooltip
            ImGui::BeginTooltip();
            ImGui::Text("x=%.2f, y=%.2f", x_data[closest_index], y_data[closest_index]);
            ImGui::EndTooltip();
        }

        ImPlot::PopStyleColor(3);
        ImPlot::EndPlot();
    }
}



void dae::ThrashTheCacheComponent::TrashTheCacheInt()  const
{
    m_resultsInt.clear();

    const int arrSize = 33554432;
    int* m_array = new int[arrSize]();

    for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
    {
        long long totalTime = 0;

        for (int sample = 0; sample < m_sampleSize; ++sample)
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
        auto averageTime = totalTime / m_sampleSize;
        std::cout << stepsize << " ; " << averageTime << std::endl;

        glm::vec2 res = { stepsize,static_cast<int>(averageTime) };
        m_resultsInt.emplace_back(res);
    }


    delete[] m_array;

}

void dae::ThrashTheCacheComponent::TrashTheCacheGameObject3D() const
{
    m_resultsGameObject3D.clear();

    const int arrSize = 33554432;
    GameObject3D* m_array = new GameObject3D[arrSize]();

    for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
    {
        long long totalTime = 0;

        for (int sample = 0; sample < m_sampleSize; ++sample)
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
        auto averageTime = totalTime / m_sampleSize;
        std::cout << stepsize << " ; " << averageTime << std::endl;

        glm::vec2 res = { stepsize,static_cast<int>(averageTime) };
        m_resultsGameObject3D.emplace_back(res);
    }


    delete[] m_array;
}

void dae::ThrashTheCacheComponent::TrashTheCacheGameObject3DAlt() const
{
    m_resultsGameObject3DAlt.clear();

    const int arrSize = 33554432;
    GameObject3DAlt* m_array = new GameObject3DAlt[arrSize]();

    for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
    {
        long long totalTime = 0;

        for (int sample = 0; sample < m_sampleSize; ++sample)
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
        auto averageTime = totalTime / m_sampleSize;
        std::cout << stepsize << " ; " << averageTime << std::endl;

        glm::vec2 res = { stepsize,static_cast<int>(averageTime) };
        m_resultsGameObject3DAlt.emplace_back(res);

    }


    delete[] m_array;
}

