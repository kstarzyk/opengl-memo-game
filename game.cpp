#include "game.hpp"
#include <algorithm>
#include <random>

Game::Game() {
  round = 1;
  hits = 0;
  candidate_1 = -1;
  candidate_2 = -1;
  needUpdate = true;
  cardsShown = false;
}

Game::~Game() {
  for (std::vector<Card*>::iterator it = cards.begin(); it != cards.end(); ++it)
    delete (*it);
  cards.clear();
}

bool Game::setupGame(GLuint programID, int _M, int _N, int _K, int _W) {
  M = _M;
  N = _N;
  K = _K;
  W = _W;
  printf("Start game: %dX%d (%d cards in total), colors: %d shapes: %d\n", M,N,M*N,K,W);

  // need only once
  glUniform2f(glGetUniformLocation(programID, "scale"), 1.0/float(M), 1.0/float(N));

  translate = glGetUniformLocation(programID, "translate");
  cardBackgroundColor = glGetUniformLocation(programID, "cardBackgroundColor");

  if (M*N % 2) {
    printf("Error! M*N equals %d, but M*N mustn't be odd!\n", M*N);
    return false;
  } else if (K > 7 || K < 1)  {
    printf("Error! K equals %d whereas 0 < K < 7!\n", K);
    return false;

  } else if (W > (int)Pattern::COUNT_ON_END || W < 1) {
    printf("Error! W is given as %d but there are %d shapes defined!\n", W, (int)Pattern::COUNT_ON_END);
    return false;
  } else if(M*N < 2*K*W) {
    printf("Error! If you want to play with %d color and %d shapes you need to have M*N >= %d  (NOW: %d)!\n", K, W, 2*K*W, M*N);
    return false;

  }

  for (int i=0; i<K; i++) {
    for (int j=0; j<W; j++) {
      cards.push_back(new Card(int(i), j));
      cards.push_back(new Card(int(i), j));
    }
  }
  int count = ( K*W+M*N-K*W ) / 2;
  totalCards = count;
  std::random_device rd;
  std::mt19937 g(rd());
  int diff = count - K*W;
  while (diff > 0) {
    int i = g() % K;
    int j = g() % W;
    cards.push_back(new Card(i, j));
    cards.push_back(new Card(i, j));
    diff--;
  }

  std::shuffle(cards.begin(), cards.end(), g);
  for (unsigned int it=0; it<cards.size(); it++) {
    int i = it % M;
    int j = it / M;
    cards[it]->setPosition(-1.0 + 1.0 / float(M) + 2.0*float(i)/float(M), -1.0 + 1.0 / float(N) + 2.0*float(j)/float(N));
}
  selected = M*N/2;
  cards[selected]->select();
  isRunning = true;
  nextRound = false;
  return true;
}

void Game::status() {
  // if (!nextRound)
  //  return;
  printf("Round %d ended with: ", round);
  if (success) printf(" SUCCESS :)\n");
  else printf(" FAILURE :(\n");

  if (2*hits == M*N) {
    isRunning = false;
    over();
  }

}

void Game::over() {
  printf("You won in %d rounds!\n", round);
  double hitRate = float(hits) / float(round);
  printf("With %0.2f hit rate you are given the title of:\n\t", hitRate);
  if (hitRate < 0.3)
    printf("Novice\n");
  else if (hitRate >= 0.3 && hitRate <= 0.6)
    printf("Adept\n");
  else
    printf("Master\n");

}


void Game::draw() {
  for (auto card : cards) {
    card->draw(translate, cardBackgroundColor);
  }
  needUpdate = false;
}

void Game::moveUp() {
  if (selected + M < M*N) {
    cards[selected]->unselect();
    selected += M;
    cards[selected]->select();
  }
}

void Game::moveDown() {
  if (selected - M >= 0) {
    cards[selected]->unselect();
    selected -= M;
    cards[selected]->select();
  }
}

void Game::moveLeft() {
  if (selected % M != 0) {
    cards[selected]->unselect();
    selected--;
    cards[selected]->select();
  }
}

void Game::moveRight() {
  if ((selected+1) % M != 0) {
    cards[selected]->unselect();
    selected++;
    cards[selected]->select();
  }
}

void Game::action() {
  if (selected == candidate_1 || cards[selected]->isPernament)
    return;
  if (cardsShown) {
    if (!success) {
      cards[candidate_1]->cover();
      cards[candidate_2]->cover();
    }
    candidate_1 = -1;
    candidate_2 = -1;

    round++;
    nextRound = true;
    cardsShown = false;

    return;
  }

  if (candidate_1 == -1) {
    candidate_1 = selected;
    cards[candidate_1]->show();
    candidate_1 = selected;
  } else if (candidate_2 == -1) {
    candidate_2 = selected;
    cards[candidate_2]->show();
    candidate_2 = selected;
    if (*cards[candidate_1] == *cards[candidate_2]) {
      success = true;
      cards[candidate_1]->showPernament();
      cards[candidate_2]->showPernament();
      hits++;
    } else {
      success = false;
    }
    status();
    cardsShown = true;

  }

}
