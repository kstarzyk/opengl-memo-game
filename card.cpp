#include "card.hpp"

Card::Card(int _color, int _shape)  {
  isHighlighted = false;
  isPernament = false;
  isShown = false;
  background = BACKGROUNDS[_color];
  shape = Pattern(_shape);
  _hash = 100 * _color + _shape;

}

void Card::draw(GLuint translate, GLuint backgroundColor) {
  glUniform2f(translate, posX, posY);
  if (isShown || isPernament)
    glUniform3fv(backgroundColor, 1, &background[0]);
  else
    glUniform3fv(backgroundColor, 1, &card_cover_color[0]);

  glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

  if (isHighlighted)
    glDrawArrays(GL_LINE_LOOP, 4, 4);

  if (isShown || isPernament)
    drawShape(backgroundColor);

}

void Card::drawShape(GLuint backgroundColor) {
  // set to black
  glUniform3f(backgroundColor, 0,0,0);
  switch (shape) {
    case Pattern::Line:
      glDrawArrays(GL_LINES, 8, 2);
      break;
    case Pattern::Cross:
      glDrawArrays(GL_LINES, 8, 4);
      break;
    case Pattern::Triangle:
      glDrawArrays(GL_TRIANGLES, 12, 3);
      break;
    case Pattern::X:
      glDrawArrays(GL_LINES, 15, 4);
      break;
    case Pattern::COUNT_ON_END: // for muting g++ warning -wSwitch
      break;
  }
}

void Card::select() {
  isHighlighted = true;
}

void Card::unselect() {
  isHighlighted = false;
}

void Card::show() {
  isShown = true;
}

void Card::showPernament() {
  isShown = true;
  isPernament = true;
}

void Card::cover() {
  isShown = false;
}

void Card::setPosition(float _posX, float _posY) {
  posX = _posX;
  posY = _posY;
}

bool operator ==(const Card& A, const Card& B) {
  return A._hash == B._hash;
}

