#ifndef _GAME_H_
#define _GAME_H_
#include <GL/glew.h>
#include <glfw3.h>
#include <vector>
#include "card.hpp"
#include "./common/glm/glm.hpp"


class Game {
  private:
    static Game* g_instance;
    std::vector<Card*> cards;
    GLint translate;
    GLint cardBackgroundColor;
    Game();
    void over();
  public:
    ~Game();
    // current selection
    int selected;
    int candidate_1;
    int candidate_2;

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    // space triggered
    void action();

    static Game* getInstance() {
      if (g_instance == NULL) {
        g_instance = new Game;
      }
      return g_instance;
    }

    int M, N, K, W; // kolumny, rzędy, kolory, ksztalty
    int totalCards;
    int round;
    int hits;


    bool setupGame(GLuint programId, int M, int N, int K, int W);
    void draw();
    void status();

    bool success;
    bool nextRound;
    bool needUpdate;
    bool cardsShown;
    bool isFinished;
    bool isRunning;

};

#endif
