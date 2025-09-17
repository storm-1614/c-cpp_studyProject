// SDL3 加载图片实例
// Textures and Extension Libraries
//
// 编译参数:
// g++ main.cpp -o ./main -lSDL3 -lSDL3_image

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>

#include <string>

/* Constants*/
// Screen dimension constants
constexpr int kScreenWidth{640};
constexpr int kScreenHeight{480};

/* Class Prototypes */
class LTexrure {
   public:
    // Initializes texture variables
    LTexrure();

    // Cleans up texture variables
    ~LTexrure();

    // Loads texture for disk
    // will load the image
    bool loadFromFile(std::string path);

    // Cleans up texture
    void destroy();

    // Draws texture
    // Draw the image at the specified position
    void render(float x, float y);

    // Gets texture attributes
    // Get the image attributes
    int getWidth();
    int getHeight();
    bool isLoaded();

   private:
    // Contains texture data
    // starts with m because it's a member variables much like how global
    // variables start with a g;
    SDL_Texture* mTexture;

    // texture dimensions
    int mWidth;
    int mHeight;
};

/* Global Variables*/
// The window w'll be rendering to
SDL_Window* gWindow{nullptr};

// The renderer used to draw to the window
SDL_Renderer* gRenderer{nullptr};

// The PNG image we will render
LTexrure gPngTesture;

/* Class Implementations */
// LTexture Implementations

LTexrure::LTexrure()
    :  // Initialize texture variables
      mTexture{nullptr},
      mWidth{0},
      mHeight{0} {}   //这个大括号是函数内容，为空，不是多余的……

LTexrure::~LTexrure() {
    // Clean up texture
    destroy();
}

bool LTexrure::loadFromFile(std::string path) {
    // Clean up testure if it already exists
    // 以防万一他已经加载了数据
    destroy();
    // Load surface
    // 加载图片 surface 保存的图片信息
    if (SDL_Surface* loadedSurface = IMG_Load(path.c_str());
        loadedSurface == nullptr) {
        SDL_Log("Unable to load image %s! SDL_image error: %s\n", path.c_str(),
                SDL_GetError());
    } else {
        // Create texture from surface
        // 使用分号是合法的 if 语句可以在里面放一个完整的表达式语句
        // 使用 SDL_CreateTextureFromSurface 创建 texture。
        // SDL_CreateTextureFromSurface 需要传入渲染器和用于创建纹理的 surface
        if (mTexture = SDL_CreateTextureFromSurface(gRenderer,
                                                    loadedSurface);  // 执行赋值
            mTexture == nullptr) {                                   // 检查结果
            SDL_Log(
                "Unable to create texture from loaded pixels! SDL_image error: "
                "%s\n",
                SDL_GetError());
        } else {
            // Get image dimenstions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        // Clean up loaded surface
        SDL_DestroySurface(loadedSurface);
    }

    // Return success if texture loaded
    return mTexture != nullptr;
}

void LTexrure::destroy() {
    // Clean up texture
    SDL_DestroyTexture(mTexture);
    // 重新初始化成员变量
    mTexture = nullptr;
    mWidth = 0;
    mHeight = 0;
}

// 绘制我们的 texture
void LTexrure::render(float x, float y) {
    // Set texture position  
    //
    //  static_cast<>() 静态转换函数，比如这个把 mWidth 从 int 转换成 float
    SDL_FRect dstRect{x, y, static_cast<float>(mWidth),
                      static_cast<float>(mHeight)};
    // Render texture
    SDL_RenderTexture(gRenderer, mTexture, nullptr, &dstRect);
}

// 简单的读取函数，提供了 texture 的坐标无论 texture 有没有加载

int LTexrure::getWidth() { return mWidth; }

int LTexrure::getHeight() { return mHeight; }

bool LTexrure::isLoaded() { return mTexture != nullptr; }

/* Function Implementations*/
bool init() {
    // Initialization flag
    bool success{true};
    if (SDL_Init(SDL_INIT_VIDEO) == false) {
        SDL_Log("SDL could not initialize! SDL error: %s\n", SDL_GetError());
        success = false;
    } else {
        // Create a window with default renderer
        if (SDL_CreateWindowAndRenderer(
                "SDL3 Tutorial: Textures and Extension Libraries", kScreenWidth,
                kScreenHeight, 0, &gWindow, &gRenderer) == false) {
            SDL_Log("Window could not be created! SDL error: %s\n",
                    SDL_GetError());
            success = false;
        }
    }
    return success;
}

bool loadMedia() {
    // File loading flag
    bool success{true};

    // Load image
    if (gPngTesture.loadFromFile("./1.png") == false) {
        SDL_Log("Unable to load png image!\n");
        success = false;
    }

    return true;
}

void close() {
    // Clean up texture
    gPngTesture.destroy();

    // Destroy window
    SDL_DestroyRenderer(gRenderer);
    gRenderer = nullptr;
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;

    // Quit SDL subsystems
    SDL_Quit();
}

int main(int argc, char* args[]) {
    // Final exit code
    int exitCode{0};

    // Initialize
    if (init() == false) {
        SDL_Log("unable to initialize program!\n");
        exitCode = 1;
    } else {
        // Load media
        if (loadMedia() == false) {
            SDL_Log("Unable to load media!\n");
            exitCode = 2;
        } else {
            // The quit flag
            bool quit{false};
            // The event data
            
            // SDL_Event 是一个联合体
        
            SDL_Event e;
            SDL_zero(e);

            // The main loop
            while (quit == false) {
                // Get event data
                while (SDL_PollEvent(&e) == true) {
                    // If event is quit type
                    if (e.type == SDL_EVENT_QUIT) {
                        // End the main loop
                        quit = true;
                    }
                }

                // Fill the background white
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(gRenderer);

                // Render image on screen
                gPngTesture.render(0.f, 0.f);
                //使用 0.f 是因为 0.0 编译器会识别为 double， 而 0.f 则是 float 类型的 0

                // Update screen
                SDL_RenderPresent(gRenderer);
            }
        }
    }

    // Clean up
    close();

    return exitCode;
}
