#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
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

void line(Vertex start, Vertex end, SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderDrawLineF(renderer, start.x, start.y, end.x, end.y);
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
  int faces[6][4] = {
      {0, 1, 2, 3}, {4, 5, 6, 7}, {0, 1, 5, 4},
      {2, 3, 7, 6}, {3, 0, 4, 7}, {2, 1, 5, 6},
  };
  int len = 6;
  int flen = 4;
  float dz = 1;
  float angle = M_PI * 2;
  Vertex a, b;
  while (running) {
    // dz += 1.0 / 16;
    // angle += 1.0 / 16;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = 0;
      }
      if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_UP) {
          dz += 0.1;
        }
        if (event.key.keysym.sym == SDLK_DOWN) {
          dz -= 0.1;
        }
        if (event.key.keysym.sym == SDLK_LEFT) {
          angle -= 0.1;
        }
        if (event.key.keysym.sym == SDLK_RIGHT) {
          angle += 0.1;
        }
      }
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    for (int i = 0; i < len; i++) {
      for (int j = 0; j < flen; j++) {
        a = screen(project(translate_z(
            rotate_xz((Vertex){points[faces[i][j]][0], points[faces[i][j]][1],
                               points[faces[i][j]][2]},
                      angle),
            dz)));
        b = screen(project(
            translate_z(rotate_xz((Vertex){points[faces[i][(j + 1) % flen]][0],
                                           points[faces[i][(j + 1) % flen]][1],
                                           points[faces[i][(j + 1) % flen]][2]},
                                  angle),
                        dz)));
        line(a, b, renderer);
      }
    }
    SDL_RenderPresent(renderer);
    SDL_Delay(16);
  }

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
