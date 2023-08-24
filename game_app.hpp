#pragma once

#include "game_window.hpp"

#include "lve_device.hpp"
#include "lve_pipeline.hpp"

namespace lve {

const int kWindowHeight = 800;
const int kWindowWidth = 1000;

class GameApp {

private:
    GameWindow window_;
    LveDevice device_{window_};
    LvePipeline pipeline_{
        device_,
        LvePipeline::defaultPipelineConfig(kWindowWidth, kWindowHeight),
        "shaders/simple_shader.vert.spv",
        "shaders/simple_shader.frag.spv",
    };

public:
    GameApp();
    ~GameApp();

    GameApp(const GameApp&) = delete;

    void run();
};

}
