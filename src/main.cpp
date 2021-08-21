#include <raylib.h>
#include <iostream>
#include <raymath.h>
#include <vector>
#include <cstdlib>
#include <ctime>

#define WIDTH 640.f
#define HEIGHT 480.f
#define PSPEED 10.f
#define BSPEED 15.f
#define ESPEED 10.f

float rand01() {
  return (float)rand() / (float)RAND_MAX;
}

struct entity {
  Vector2 pos;
  Vector2 vel;
  float radius;
  Color color;
};

void MoveEntity(entity& e) {
  e.pos = Vector2Add(e.pos, e.vel);
}

entity MakePlayer(Vector2 pos) {
  entity player = {};
  player.pos = pos;
  player.vel = (Vector2){0, 0};
  player.radius = 25;
  player.color = RED;
  return player;
}

entity MakeBullet(Vector2 pos, Vector2 vel) {
  entity bullet = {};
  bullet.pos = pos;
  bullet.vel = vel;
  bullet.radius = 10;
  bullet.color = BLACK;
  return bullet;
}

entity MakeEnemy(Vector2 pos){
  entity enemy = {};
  enemy.pos = pos;
  enemy.vel = (Vector2){0, 0};
  enemy.radius = 25;
  enemy.color = BLUE;
  return enemy;
}

void DrawEntity(entity e){
  DrawCircleV(e.pos, e.radius, e.color);
}


int main() {
  srand(time(NULL));
  InitWindow(WIDTH, HEIGHT, "gaym");
  SetTargetFPS(60);
  std::vector<entity> bullets;
  std::vector<entity> enemies;
  int maxenemies = 5;
  entity player = MakePlayer((Vector2){WIDTH / 2.f, HEIGHT / 2.f});
  while (!WindowShouldClose()){
    BeginDrawing();
    ClearBackground(RAYWHITE);


    if (IsKeyDown(KEY_W)) player.vel = (Vector2){0, -PSPEED};
    else if (IsKeyDown(KEY_S)) player.vel = (Vector2){0, PSPEED};
    else if (IsKeyDown(KEY_A)) player.vel = (Vector2){-PSPEED, 0};
    else if (IsKeyDown(KEY_D)) player.vel = (Vector2){PSPEED, 0};
    else player.vel = (Vector2){0, 0};

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
      Vector2 vel = Vector2Scale(Vector2Normalize(Vector2Subtract(GetMousePosition(), player.pos)), BSPEED);
      entity bullet = MakeBullet (player.pos, vel);
      bullets.push_back(bullet);

    }
    
    if(enemies.size() < maxenemies) {
      entity enemy = MakeEnemy((Vector2){rand01() * (WIDTH - 50) + 25, rand01() * (HEIGHT - 50) + 25});
      enemies.push_back(enemy);
    }
    for (int i = enemies.size() - 1; i >= 0; i--){
      DrawEntity(enemies[i]);
    }


    DrawEntity(player);

    MoveEntity(player);
    for (int i = bullets.size() - 1; i >= 0; i--) {
      if (bullets[i].pos.y > HEIGHT || bullets[i].pos.x > WIDTH || bullets[i].pos.y < 0 || bullets[i].pos.x < 0) bullets.erase(bullets.begin() + i);
      MoveEntity(bullets[i]);
      DrawEntity(bullets[i]);
    }


    EndDrawing();
  }
  return 0;
}
