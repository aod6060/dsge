#ifndef SYS_H
#define SYS_H


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>
#include <random>
#include <chrono>
#include <filesystem>


#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#define GLEW_NO_GLU
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <chipmunk/chipmunk.h>

#include "version.h"
#include "app/app.h"
#include "input/input.h"
#include "render/render.h"
#include "sound/sound.h"
#include "physics/physics.h"

#endif