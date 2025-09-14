//SDL 实例
//绘制一个彩虹三角形
#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_timer.h>

#include <array>
#include <cstdint>
#include <vector>

std::array<SDL_Vertex, 3> origin_vertices = {
    SDL_Vertex{{150, 100}, {1.0f, 0.0f, 0.0f, 1.0f}},
    SDL_Vertex{{000, 300}, {0.0f, 1.0f, 0.0f, 1.0f}},
    SDL_Vertex{{300, 300}, {0.0f, 0.0f, 1.0f, 1.0f}}};

int main(int argc, char* argv[]) {
    // 设置日志输出级别
    SDL_SetLogPriorities(SDL_LOG_PRIORITY_VERBOSE);

    // 初始化 SDL 库
    // 指定初始化的子系统为视频系统
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return -1;
    }

    // 创建窗口和渲染器
    // 创建一个 800x600 大小的窗口，然后移动到屏幕居中的位置
    SDL_Window* window =
        SDL_CreateWindow("Hello, SDL3", 800, 600, SDL_WINDOW_RESIZABLE);
    if (!window) {
        SDL_Log("Could not create a window: %s", SDL_GetError());
        return -1;
    }
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED,
                          SDL_WINDOWPOS_CENTERED);

    // 创建和窗口关联的渲染器
    SDL_Renderer* renderer = SDL_CreateRenderer(window, "opengl");
    // 所有图形图像都是通过渲染器绘制到窗口
    // 这里背景色使用 RGBA 绘制
    SDL_SetRenderDrawColor(renderer, 16, 0, 16, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    // 事件循环
    SDL_Event event{};
    bool keep_going = true;

    uint64_t last_tickets = SDL_GetTicks();
    float position = 0.0f;
    float direction = 1.0f;

    while (keep_going) {
        SDL_Log("Event: %d", event.type);
        //        SDL_WaitEvent(&event);
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                // 表示点击了关闭窗口按钮收到该事件欧跳出循环
                case SDL_EVENT_QUIT: {
                    keep_going = false;
                    break;
                }
                // 键盘按下事件，这里实现了按 esc 键退出
                case SDL_EVENT_KEY_DOWN: {
                    keep_going = keep_going && (event.key.key != SDLK_ESCAPE);
                    break;
                }
            }
        }

        uint64_t current_ticks = SDL_GetTicks();
        float delta_time = (current_ticks - last_tickets) / 1000.0f;
        last_tickets = current_ticks;
        position += 200.0f * delta_time * direction;

        int width = 0;
        SDL_GetRenderOutputSize(renderer, &width, nullptr);
        float max_position =
            static_cast<float>(width) -
            (origin_vertices[2].position.x - origin_vertices[1].position.x);

        if (position > max_position) {
            direction = -1.0f;
        } else if (position < 0.0f) {
            position = 0.0f;
            direction = 1.0f;
        }

        std::vector<SDL_Vertex> vertices;
        for (const auto& vertex : origin_vertices) {
            vertices.push_back(vertex);
            vertices.back().position.x += position;
        }
        // 表示需要对窗口进行重绘
        SDL_SetRenderDrawColor(renderer, 16, 0, 16, 255);
        SDL_RenderClear(renderer);
        SDL_RenderGeometry(renderer, nullptr, vertices.data(), vertices.size(),
                           nullptr, 0);
        SDL_RenderPresent(renderer);
    }
    return 0;
}
