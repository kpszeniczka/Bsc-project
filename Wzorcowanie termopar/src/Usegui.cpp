#include "Usegui.h"

struct ScrollingBuffer {
    int MaxSize;
    int Offset;
    ImVector<ImVec2> Data;
    ScrollingBuffer(int max_size = 100000) {
        MaxSize = max_size;
        Offset = 0;
        Data.reserve(MaxSize);
    }
    void AddPoint(float x, float y) {
        if (Data.size() < MaxSize)
            Data.push_back(ImVec2(x, y));
        else {
            Data[Offset] = ImVec2(x, y);
            Offset = (Offset + 1) % MaxSize;
        }
    }
    void Erase() {
        if (Data.size() > 0) {
            Data.shrink(0);
            Offset = 0;
        }
    }
};

void UseGui::Init(GLFWwindow* window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImPlot::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
}

void UseGui::NewFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void UseGui::MainGui(GLFWwindow* window) {
    static bool use_work_area = true;
    static bool is_open = true;
    static bool used_sensors[10] = {false};
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_MenuBar;
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(use_work_area ? viewport->WorkPos : viewport->Pos);
    ImGui::SetNextWindowSize(use_work_area ? viewport->WorkSize : viewport->Size);

    static ScrollingBuffer sdata1, sdata2;

    ImVec2 mouse = ImGui::GetMousePos();
    static float max_value = 0;

    if (max_value < mouse.x) {
        max_value = 1.1 * mouse.x;
    }

    static float measurement_time = 0;
    measurement_time += ImGui::GetIO().DeltaTime;
    sdata1.AddPoint(measurement_time, mouse.x);
    sdata2.AddPoint(measurement_time, mouse.y);

    static float history = 100.0f;
    static ImPlotAxisFlags flags = 0;

    static float x_start = 0;
    static float x_end;

    x_end = x_start + history;

    ImGuiIO& io = ImGui::GetIO();

    if (io.MouseWheel != 0) {
        history -= io.MouseWheel * 5.0f;
        if (history < 10.0f) history = 10.0f;
    }

    if(is_open){
        if (ImGui::Begin("Wzorcowanie Termopar", &is_open, window_flags)) {
            if (ImGui::BeginMenuBar()) {
                if (ImGui::BeginMenu("Plik")) {
                    if(ImGui::MenuItem("Close")) {
                        is_open = false;
                    }
                    ImGui::EndMenu();
                }
                ImGui::EndMenuBar();
            }
            ImGui::Text("history: %.2f, %.2f", history, x_start);
            if (ImGui::Button("piec")) {
                is_open = false;
            }
            ImGui::SliderFloat("x_start", &x_start, 0.0f, measurement_time - 10);
            ImGui::Separator();
            ImGui::Columns(2, "plot", 0);
            ImGui::SetColumnWidth(0, 150);

            if (ImGui::BeginTable("switch", 2)) {
                for (int row = 0; row < 10; row++) {
                    ImGui::TableNextRow();  // Przejœcie do nowego wiersza

                    // Pierwsza kolumna - checkbox
                    ImGui::TableNextColumn();
                    std::string label = (row > 4) ? "B" + std::to_string(row - 5) : "A" + std::to_string(row);
                    ImGui::Checkbox(label.c_str(), &used_sensors[row]);

                    // Druga kolumna - tekst
                    ImGui::TableNextColumn();
                    ImGui::Text("Sensor %d", row);  // Wyœwietlenie tekstu w drugiej kolumnie
                    ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, ImGui::GetColorU32(ImGuiCol_Button));
                }
                ImGui::EndTable();
            }
            ImGui::NextColumn();
            if (ImPlot::BeginPlot("MainPlot", ImVec2(-1, -1))) {
                ImPlot::SetupAxes("Czas", "Temperatura", flags, flags);
                ImPlot::SetupAxisLimits(ImAxis_X1, x_start, measurement_time < x_end ? measurement_time : x_end, ImGuiCond_Always);
                ImPlot::SetupAxisLimits(ImAxis_Y1, 0, max_value, ImGuiCond_Always);
                ImPlot::PlotLine("Mouse X", &sdata1.Data[0].x, &sdata1.Data[0].y, sdata1.Data.size(), 0, sdata1.Offset, 2 * sizeof(float));
                ImPlot::PlotLine("Mouse Y", &sdata2.Data[0].x, &sdata2.Data[0].y, sdata2.Data.size(), 0, sdata2.Offset, 2 * sizeof(float));
                ImPlot::EndPlot();
            }
            ImGui::End();
        }
    }
    else {
        glfwSetWindowShouldClose(window, 1);
    }
}

void UseGui::Render() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UseGui::Shutdown() {
    ImPlot::DestroyContext();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}