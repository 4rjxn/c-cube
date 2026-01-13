#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <math.h>
#include <stdio.h>

float WIDTH = 700;
float HEIGHT = 700;

float points[][3] = {
    // TOP
    {0.0f, 0.4f, 0.0f},

    // RING 1
    {0.14f, 0.35f, 0.00f},
    {0.12f, 0.35f, 0.07f},
    {0.07f, 0.35f, 0.12f},
    {0.00f, 0.35f, 0.14f},
    {-0.07f, 0.35f, 0.12f},
    {-0.12f, 0.35f, 0.07f},
    {-0.14f, 0.35f, 0.00f},
    {-0.12f, 0.35f, -0.07f},
    {-0.07f, 0.35f, -0.12f},
    {0.00f, 0.35f, -0.14f},
    {0.07f, 0.35f, -0.12f},
    {0.12f, 0.35f, -0.07f},

    // RING 2
    {0.28f, 0.25f, 0.00f},
    {0.24f, 0.25f, 0.14f},
    {0.14f, 0.25f, 0.24f},
    {0.00f, 0.25f, 0.28f},
    {-0.14f, 0.25f, 0.24f},
    {-0.24f, 0.25f, 0.14f},
    {-0.28f, 0.25f, 0.00f},
    {-0.24f, 0.25f, -0.14f},
    {-0.14f, 0.25f, -0.24f},
    {0.00f, 0.25f, -0.28f},
    {0.14f, 0.25f, -0.24f},
    {0.24f, 0.25f, -0.14f},

    // RING 3
    {0.35f, 0.00f, 0.00f},
    {0.30f, 0.00f, 0.18f},
    {0.18f, 0.00f, 0.30f},
    {0.00f, 0.00f, 0.35f},
    {-0.18f, 0.00f, 0.30f},
    {-0.30f, 0.00f, 0.18f},
    {-0.35f, 0.00f, 0.00f},
    {-0.30f, 0.00f, -0.18f},
    {-0.18f, 0.00f, -0.30f},
    {0.00f, 0.00f, -0.35f},
    {0.18f, 0.00f, -0.30f},
    {0.30f, 0.00f, -0.18f},

    // RING 4
    {0.28f, -0.25f, 0.00f},
    {0.24f, -0.25f, 0.14f},
    {0.14f, -0.25f, 0.24f},
    {0.00f, -0.25f, 0.28f},
    {-0.14f, -0.25f, 0.24f},
    {-0.24f, -0.25f, 0.14f},
    {-0.28f, -0.25f, 0.00f},
    {-0.24f, -0.25f, -0.14f},
    {-0.14f, -0.25f, -0.24f},
    {0.00f, -0.25f, -0.28f},
    {0.14f, -0.25f, -0.24f},
    {0.24f, -0.25f, -0.14f},

    // RING 5
    {0.14f, -0.35f, 0.00f},
    {0.12f, -0.35f, 0.07f},
    {0.07f, -0.35f, 0.12f},
    {0.00f, -0.35f, 0.14f},
    {-0.07f, -0.35f, 0.12f},
    {-0.12f, -0.35f, 0.07f},
    {-0.14f, -0.35f, 0.00f},
    {-0.12f, -0.35f, -0.07f},
    {-0.07f, -0.35f, -0.12f},
    {0.00f, -0.35f, -0.14f},
    {0.07f, -0.35f, -0.12f},
    {0.12f, -0.35f, -0.07f},

    // BOTTOM
    {0.0f, -0.4f, 0.0f}};
int faces[][3] = {
    // ===== TOP CAP =====
    {0, 1, 2},
    {0, 2, 3},
    {0, 3, 4},
    {0, 4, 5},
    {0, 5, 6},
    {0, 6, 7},
    {0, 7, 8},
    {0, 8, 9},
    {0, 9, 10},
    {0, 10, 11},
    {0, 11, 12},
    {0, 12, 1},

    // ===== RING 1 -> RING 2 =====
    {1, 13, 2},
    {2, 13, 14},
    {2, 14, 3},
    {3, 14, 15},
    {3, 15, 4},
    {4, 15, 16},
    {4, 16, 5},
    {5, 16, 17},
    {5, 17, 6},
    {6, 17, 18},
    {6, 18, 7},
    {7, 18, 19},
    {7, 19, 8},
    {8, 19, 20},
    {8, 20, 9},
    {9, 20, 21},
    {9, 21, 10},
    {10, 21, 22},
    {10, 22, 11},
    {11, 22, 23},
    {11, 23, 12},
    {12, 23, 24},
    {12, 24, 1},
    {1, 24, 13},

    // ===== RING 2 -> RING 3 =====
    {13, 25, 14},
    {14, 25, 26},
    {14, 26, 15},
    {15, 26, 27},
    {15, 27, 16},
    {16, 27, 28},
    {16, 28, 17},
    {17, 28, 29},
    {17, 29, 18},
    {18, 29, 30},
    {18, 30, 19},
    {19, 30, 31},
    {19, 31, 20},
    {20, 31, 32},
    {20, 32, 21},
    {21, 32, 33},
    {21, 33, 22},
    {22, 33, 34},
    {22, 34, 23},
    {23, 34, 35},
    {23, 35, 24},
    {24, 35, 36},
    {24, 36, 13},
    {13, 36, 25},

    // ===== RING 3 -> RING 4 =====
    {25, 37, 26},
    {26, 37, 38},
    {26, 38, 27},
    {27, 38, 39},
    {27, 39, 28},
    {28, 39, 40},
    {28, 40, 29},
    {29, 40, 41},
    {29, 41, 30},
    {30, 41, 42},
    {30, 42, 31},
    {31, 42, 43},
    {31, 43, 32},
    {32, 43, 44},
    {32, 44, 33},
    {33, 44, 45},
    {33, 45, 34},
    {34, 45, 46},
    {34, 46, 35},
    {35, 46, 47},
    {35, 47, 36},
    {36, 47, 48},
    {36, 48, 25},
    {25, 48, 37},

    // ===== RING 4 -> RING 5 =====
    {37, 49, 38},
    {38, 49, 50},
    {38, 50, 39},
    {39, 50, 51},
    {39, 51, 40},
    {40, 51, 52},
    {40, 52, 41},
    {41, 52, 53},
    {41, 53, 42},
    {42, 53, 54},
    {42, 54, 43},
    {43, 54, 55},
    {43, 55, 44},
    {44, 55, 56},
    {44, 56, 45},
    {45, 56, 57},
    {45, 57, 46},
    {46, 57, 58},
    {46, 58, 47},
    {47, 58, 59},
    {47, 59, 48},
    {48, 59, 60},
    {48, 60, 37},
    {37, 60, 49},

    // ===== BOTTOM CAP =====
    {61, 50, 49},
    {61, 51, 50},
    {61, 52, 51},
    {61, 53, 52},
    {61, 54, 53},
    {61, 55, 54},
    {61, 56, 55},
    {61, 57, 56},
    {61, 58, 57},
    {61, 59, 58},
    {61, 60, 59},
    {61, 49, 60},
};

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
  // double points[8][3] = {{0.25, 0.25, 0.25},    {-0.25, 0.25, 0.25},
  //                        {-0.25, -0.25, 0.25},  {0.25, -0.25, 0.25},
  //                        {0.25, 0.25, -0.25},   {-0.25, 0.25, -0.25},
  //                        {-0.25, -0.25, -0.25}, {0.25, -0.25, -0.25}};
  //   int faces[6][4] = {
  //      {0, 1, 2, 3}, {4, 5, 6, 7}, {0, 1, 5, 4},
  //       {2, 3, 7, 6}, {3, 0, 4, 7}, {2, 1, 5, 6},
  // };
  int len = 120;
  int flen = 3;
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
