#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <math.h>
#include <stdio.h>

float WIDTH = 700;
float HEIGHT = 700;

typedef struct {
  double x;
  double y;
  double z;
} Vertex;

Vertex project(Vertex vert) {
  if (vert.z == 0) {
    return (Vertex){0, 0, 0};
  }
  vert.x /= vert.z;
  vert.y /= vert.z;
  return vert;
}

Vertex screen(Vertex vert) {
  vert.x = (vert.x + 1) * (WIDTH / 2);
  vert.y = (1 - vert.y) * (HEIGHT / 2);
  return vert;
}

Vertex translate_z(Vertex vert, double dz) {
  vert.z += dz;
  return vert;
}

Vertex rotate_xz(Vertex vert, double theta) {
  double s = sin(theta);
  double c = cos(theta);
  double x = vert.x * c - vert.z * s;
  double z = vert.x * s + vert.z * c;
  return (Vertex){x, vert.y, z};
}

Vertex rotate_xy(Vertex vert, double theta) {
  double s = sin(theta);
  double c = cos(theta);
  double x = vert.x * c - vert.y * s;
  double y = vert.x * s + vert.y * c;
  return (Vertex){x, y, vert.z};
}

Vertex rotate_yz(Vertex vert, double theta) {
  double s = sin(theta);
  double c = cos(theta);
  double y = vert.y * c - vert.z * s;
  double z = vert.y * s + vert.z * c;
  return (Vertex){vert.x, y, z};
}

void point(Vertex vert, SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderDrawPointF(renderer, vert.x, vert.y);
}

int main(void) {
  printf("Starting...\n");

  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("SDL_Init failed: %s\n", SDL_GetError());
    return 1;
  }
  printf("SDL initialized\n");

  const char *driver = SDL_GetCurrentVideoDriver();
  printf("Video driver: %s\n", driver ? driver : "none");

  SDL_Window *window = NULL;
  SDL_Renderer *renderer = NULL;
  SDL_CreateWindowAndRenderer(700, 700, 0, &window, &renderer);

  if (!window) {
    printf("Window failed: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  printf("Window created\n");
  int running = 1;
  SDL_Event event;
  double points[8][3] = {{0.25, 0.25, 0.25},    {-0.25, 0.25, 0.25},
                         {-0.25, -0.25, 0.25},  {0.25, -0.25, 0.25},
                         {0.25, 0.25, -0.25},   {-0.25, 0.25, -0.25},
                         {-0.25, -0.25, -0.25}, {0.25, -0.25, -0.25}};
  int len = 8;
  float dz = 1;
  float angle = M_PI * 2;
  while (running) {
    // dz += 1.0 / 16;
    angle += 1.0 / 16;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = 0;
      }
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    for (int i = 0; i < len; i++) {
      point(screen(project(translate_z(
                rotate_xz((Vertex){points[i][0], points[i][1], points[i][2]},
                          angle),
                dz))),
            renderer);
    }
    SDL_RenderPresent(renderer);
    SDL_Delay(16);
  }

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
