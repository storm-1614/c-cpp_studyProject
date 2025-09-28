// SDL Key Presses and Key States
// SDL 按键实例

#include <SDL3/SDL.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_video.h>
#include <SDL3_image/SDL_image.h>

#include <cstddef>
#include <cstdio>
#include <string>

// 定义窗口大小变量
constexpr int kScreenWidth = 640;
constexpr int kScreenHeight = 480;

class LTexture {
   public:
    LTexture();
    ~LTexture();
    bool loadFromFile(std::string path);
    void destroy();
    void render(float x, float y);

    int getWidth();
    int getHeight();
    bool isLoaded();

   private:
    // WARN: 注意指针
    SDL_Texture* mTexture;

    // Texture dimensions
    int mWidth;
    int mHeight;
};

bool init();
bool loadMedia();
void close();

SDL_Window* gWindow{nullptr};
SDL_Renderer* gRenderer{nullptr};

// The directional images
LTexture gUpTexture, gDownTexture, gLeftTexture, gRightTexture;

/* Class implementations*/

LTexture::LTexture()
    :  //
      mTexture(nullptr),
      mHeight(0),
      mWidth(0)  //
{}

LTexture::~LTexture() {
    // Clean texture
    destroy();
}

bool LTexture::loadFromFile(std::string path) {
    // Cleans up if it already exists
    destroy();

    // load surface
    if (SDL_Surface* loadedSurface = IMG_Load(path.c_str());
        loadedSurface == nullptr) {
        SDL_Log("Unable load image %s! SDL_image error: %s\n", path.c_str(),
                SDL_GetError());
    } else {
        // Create texture from surface
        if (mTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
            mTexture == nullptr) {
            SDL_Log(
                "Unable to create texture from loaded pixels! SDL error: %s\n",
                SDL_GetError());
        } else {
            // 在加载完成后确定 surface 的尺寸
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }
        // 清理不需要的已转化的 surface
        SDL_DestroySurface(loadedSurface);
    }

    // 返回是否创建 texture 成功
    return mTexture != nullptr;
}

void LTexture::destroy() {
    SDL_DestroyTexture(mTexture);
    mTexture = nullptr;
    mHeight = 0;
    mWidth = 0;
}

void LTexture::render(float x, float y) {
    // 创建矩形
    SDL_FRect dstRect{x, y, static_cast<float>(mWidth),
                      static_cast<float>(mHeight)};

    // 渲染 texture
    SDL_RenderTexture(gRenderer, mTexture, NULL, &dstRect);
}

int LTexture::getWidth() { return mWidth; }
int LTexture::getHeight() { return mHeight; }
bool LTexture::isLoaded() { return mTexture != nullptr; }

bool init() {
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) == false) {
        SDL_Log("SDL could not initialize! SDL error %s\n", SDL_GetError());
        success = false;
    } else {
        if (SDL_CreateWindowAndRenderer(
                "SDL3 Tutorial: Key Presses and Key States", kScreenWidth,
                kScreenHeight, 0, &gWindow, &gRenderer) == false) {
            SDL_Log("Window could not be created! SDL error: %s\n",
                    SDL_GetError());
            success = false;
        }
    }
    return success;
}

// 提前加载图片避免潜在错误
bool loadMedia() {
    bool success = true;

    if (gUpTexture.loadFromFile("./03-key-presses-and-key-states/up.png") ==
        false) {
        SDL_Log("Unable to load up image!\n");
        success = false;
    }
    if (gDownTexture.loadFromFile("./03-key-presses-and-key-states/down.png") ==
        false) {
        SDL_Log("Unable to load down image!\n");
        success = false;
    }
    if (gRightTexture.loadFromFile(
            "./03-key-presses-and-key-states/right.png") == false) {
        SDL_Log("Unable to load right image!\n");
        success = false;
    }
    if (gLeftTexture.loadFromFile("./03-key-presses-and-key-states/left.png") ==
        false) {
        SDL_Log("Unable to load left image!\n");
        success = false;
    }
    return success;
}

void close() {
    // Clean up texture;
    gUpTexture.destroy();
    gDownTexture.destroy();
    gRightTexture.destroy();
    gLeftTexture.destroy();

    // Destroy window;
    SDL_DestroyRenderer(gRenderer);
    gRenderer = nullptr;
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;

    // Quit SDL subsystem;
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    int exitcode = 0;

    if (init() == false) {
        SDL_Log("Unable to initialize program!\n");
        exitcode = 1;
    } else {
        if (loadMedia() == false) {
            SDL_Log("Unable to load Media!\n");
            exitcode = 2;
        } else {
            // The quit flag
            bool quit = false;

            // The Event data
            SDL_Event e;
            SDL_zero(e);

            // The current texture
            LTexture* currentTexture = &gUpTexture;

            // Background color defaults to white;
            SDL_Color bgColor{0xFF, 0xFF, 0xFF, 0xFF};

            // Get event data
            while (quit == false) {
                while (SDL_PollEvent(&e)) {
                    if (e.type == SDL_EVENT_QUIT) {
                        quit = true;
                        // On keyboard key press
                    } else if (e.type == SDL_EVENT_KEY_DOWN) {
                        // Set texture
                        if (e.key.key == SDLK_UP) {
                            currentTexture = &gUpTexture;
                        } else if (e.key.key == SDLK_DOWN) {
                            currentTexture = &gDownTexture;
                        } else if (e.key.key == SDLK_LEFT) {
                            currentTexture = &gLeftTexture;
                        } else if (e.key.key == SDLK_RIGHT) {
                            currentTexture = &gRightTexture;
                        }
                    }
                }

                // Reset background color to white
                bgColor.r = 0xFF;
                bgColor.g = 0xFF;
                bgColor.b = 0xFF;

                // Set background color based on key state
                // keyStates 是布尔类型的数组存了各种按键
                const bool* keyStates = SDL_GetKeyboardState(nullptr);
                if (keyStates[SDL_SCANCODE_UP] == true) {
                    // Red
                    bgColor.r = 0xFF;
                    bgColor.g = 0x00;
                    bgColor.b = 0x00;
                } else if (keyStates[SDL_SCANCODE_DOWN] == true) {
                    // Green
                    bgColor.r = 0x00;
                    bgColor.g = 0xFF;
                    bgColor.b = 0x00;
                } else if (keyStates[SDL_SCANCODE_LEFT] == true) {
                    // Yellow
                    bgColor.r = 0xFF;
                    bgColor.g = 0xFF;
                    bgColor.b = 0x00;
                } else if (keyStates[SDLK_RIGHT] == true) {
                    // Blue
                    bgColor.a = 0x00;
                    bgColor.g = 0x00;
                    bgColor.b = 0xFF;
                }
                // Fill the background
                SDL_SetRenderDrawColor(gRenderer, bgColor.r, bgColor.g,
                                       bgColor.b, 0xff);

                // Render image on screen
                SDL_RenderClear(gRenderer);

                // Render image on screen
                // 使得照片在中心
                currentTexture->render(
                    (kScreenWidth - currentTexture->getWidth()) / 2.f,
                    (kScreenHeight - currentTexture->getHeight()) / 2.f);

                // Update screen
                SDL_RenderPresent(gRenderer);
            }
        }
    }

    close();
    return exitcode;
}
