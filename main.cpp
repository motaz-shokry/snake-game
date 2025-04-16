#include <deque>
#include <iostream>
#include <raylib.h>
#include <raymath.h>

Color green = {152, 151, 26, 255};
Color darkGreen = {43, 51, 24, 255};

float cellSize = 30;
float cellCount = 25;
float lastUpdateTime = 0;
float offset = 55;

bool eventTriggered(float interval);
bool elementInDeque(Vector2 element, std::deque<Vector2> deque);

class Snake {

  public:
    std::deque<Vector2> body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
    Vector2 direction = {1, 0};
    bool addSecment = false;

    void Draw() {
        for (unsigned short i = 0; i < body.size(); i++) {
            float x = body.at(i).x;
            float y = body.at(i).y;
            Rectangle segment = {offset + x * cellSize, offset + y * cellSize,
                                 cellSize, cellSize};
            DrawRectangleRounded(segment, 0.5, 6, darkGreen);
        }
    }

    void Update() {

        body.push_front(Vector2Add(body.front(), direction));

        if (addSecment) {
            addSecment = false;
        } else {
            body.pop_back();
        }
    }

    void Reset() {

        body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
        direction = {1, 0};
    }
};

class Food {

  public:
    Vector2 position;
    Texture2D texture;

    Food(std::deque<Vector2> snakeBody) {
        Image image = LoadImage("assets/food.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);

        position = GenerateRandomPos(snakeBody);
    }

    ~Food() { UnloadTexture(texture); }

    void Draw() {
        DrawTexture(texture, offset + position.x * cellSize,
                    offset + position.y * cellSize, WHITE);
    }

    Vector2 GenerateRandomCell() {

        float x = GetRandomValue(0, 24);
        float y = GetRandomValue(0, 24);
        return {x, y};
    }

    Vector2 GenerateRandomPos(std::deque<Vector2> snakeBody) {

        Vector2 position = GenerateRandomCell();
        while (elementInDeque(position, snakeBody)) {
            position = GenerateRandomCell();
        }

        return position;
    }
};

class Game {

  public:
    Snake snake;
    Food food = Food(snake.body);
    bool running = false;
    short score = 0;
    Sound eatSound;
    Sound wallSound;

    Game() {
        InitAudioDevice();
        eatSound = LoadSound("assets/eat.mp3");
        wallSound = LoadSound("assets/wall.mp3");
    }

    ~Game() {
        UnloadSound(eatSound);
        UnloadSound(wallSound);
        CloseAudioDevice();
    }

    void Draw() {

        snake.Draw();
        food.Draw();
    }

    void Update() {

        if (running) {
            snake.Update();
            CheckCollisionWithFood();
            CheckCollisionWithEdges();
            CheckCollisionWithAnySecment();
        }
    }

    void CheckCollisionWithFood() {

        if (Vector2Equals(snake.body.front(), food.position)) {

            food.position = food.GenerateRandomPos(snake.body);
            snake.addSecment = true;
            score++;
            PlaySound(eatSound);
        }
    }

    void CheckCollisionWithEdges() {
        if (snake.body.front().x == cellCount || snake.body.front().x == -1) {
            GameOver();
        }
        if (snake.body.front().y == cellCount || snake.body.front().y == -1) {
            GameOver();
        }
    }

    void CheckCollisionWithAnySecment() {

        std::deque<Vector2> headlessBody = snake.body;
        headlessBody.pop_front();

        if (elementInDeque(snake.body.front(), headlessBody)) {
            Game::GameOver();
        }
    }

    void GameOver() {
        snake.Reset();
        food.position = food.GenerateRandomPos(snake.body);
        running = false;
        score = 0;
        PlaySound(wallSound);
    }
};

int main(void) {

    InitWindow(2 * offset + cellSize * cellCount,
               2 * offset + cellSize * cellCount, "Snake Game");
    SetTargetFPS(60);

    Game game;

    while (!WindowShouldClose()) {
        BeginDrawing();

        if (eventTriggered(0.2)) {
            game.Update();
        }

        // Key press movment
        if (IsKeyPressed(KEY_UP) && game.snake.direction.y != 1) {
            game.snake.direction = {0, -1};
            game.running = true;
        }
        if (IsKeyPressed(KEY_DOWN) && game.snake.direction.y != -1) {
            game.snake.direction = {0, 1};
            game.running = true;
        }
        if (IsKeyPressed(KEY_LEFT) && game.snake.direction.x != 1) {
            game.snake.direction = {-1, 0};
            game.running = true;
        }
        if (IsKeyPressed(KEY_RIGHT) && game.snake.direction.x != -1) {
            game.snake.direction = {1, 0};
            game.running = true;
        }

        // drawing
        ClearBackground(green);
        DrawRectangleLinesEx({offset - 5, offset - 5, cellSize * cellCount + 10,
                              cellSize * cellCount + 10},
                             3, darkGreen);
        DrawText("Retro Snake Game", 300, 15, 30, darkGreen);
        DrawText(TextFormat("%i", game.score),
                 offset + cellSize * (cellCount / 2),
                 offset + cellSize * cellCount + 10, 40, darkGreen);
        game.Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

bool eventTriggered(float interval) {

    float currentTime = GetTime();

    if (currentTime - lastUpdateTime >= interval) {
        lastUpdateTime = currentTime;
        return true;
    }

    return false;
}

bool elementInDeque(Vector2 element, std::deque<Vector2> deque) {

    for (unsigned short i = 0; i < deque.size(); i++) {

        if (Vector2Equals(element, deque.at(i))) {

            return true;
        }
    }

    return false;
}
