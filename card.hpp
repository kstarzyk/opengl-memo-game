#ifndef _CARD_H_
#define _CARD_H_

#include <stdio.h>
#include <GL/glew.h>
#include "./common/glm/glm.hpp"

//  constants for easy manipulating with sizes
static const GLfloat v = 0.4f;
static const GLfloat vs = 0.5f;
static const GLfloat ss = 0.2f;
//  one and the only one VBO
static const GLfloat card_vertex[] = {
  -v,  -v,      // card vertex begin
   v,  -v,
   v,   v,
  -v,   v,      // card veretex end and card vertex frame start
 -vs, -vs,
  vs, -vs,
  vs,  vs,
 -vs,  vs,      // card vertex frame end
   0,  -ss,     // line begin cross begin
   0,   ss,     // line end
 -ss,  ss*.2f,
  ss,  ss*.2f,  // cross end
  ss, -ss,      // triangle begin
  0,   ss,
 -ss, -ss,      // triangle end
  ss,  ss,      // x begin
 -ss, -ss,
 -ss,  ss,
  ss, -ss,      // x end

};

// COUNT_ON_END probide info about number of available shapes
enum class Pattern {Line=0, Cross, Triangle, X, COUNT_ON_END};
enum class Color {Red=0, Green, Blue, Yellow, Magenta, Cyan};
static const glm::vec3 BACKGROUNDS[] = {
  glm::vec3(1,0,0), // red
  glm::vec3(0,1,0), // green
  glm::vec3(0,0,1), // blue
  glm::vec3(1,1,0), // yellow
  glm::vec3(1,0,1), // magenta
  glm::vec3(0,1,1), //cyan
};
static const glm::vec3 card_cover_color = glm::vec3(0.5,0.5,0.5);

class Card {
  public:
    Card(int _color, int _shape);
    glm::vec3 background;
    bool isHighlighted, isShown, isPernament;
    float posX, posY;

    void select();
    void unselect();
    void show();
    void cover();
    void showPernament();

    void draw(GLuint translate, GLuint backgroundColor);
    friend bool operator ==(const Card&, const Card&);
    void setPosition(float, float);
  private:
    int _hash; // different for every
    void drawShape(GLuint backgroundColor);
    Pattern shape;
};
#endif
