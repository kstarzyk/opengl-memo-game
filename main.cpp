// Krzysztof Starzyk
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <GL/glew.h>
#include <glfw3.h>

GLFWwindow* window;
#include "./common/shader.hpp"
#include "./common/glm/glm.hpp"
#include "./game.hpp"
#include "./card.hpp"

// Game is singleton
Game *Game::g_instance = NULL;

/*
 * The callback is outside of a class because of glfw C-way of passing key_callback function
 * Callback mustn't be member method, at least it may be static member function
 * So to avoid overkilling small game with safely type-checking-generic classes I'm just using
 * outside (in terms of being in some kind of structure) function to interact with game object.
 */
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  auto game = Game::getInstance();
  if (action == GLFW_PRESS) {
    if (game->cardsShown) {
      game -> action();
    }
    switch (key) {
      case GLFW_KEY_UP:
        game -> moveUp();
        break;
      case GLFW_KEY_DOWN:
        game -> moveDown();
        break;
      case GLFW_KEY_LEFT:
        game -> moveLeft();
        break;
      case GLFW_KEY_RIGHT:
        game -> moveRight();
        break;
      case GLFW_KEY_SPACE:
        game -> action();
      break;
     }
  }
  game->needUpdate = true;
}


void display_help() {
  printf("MEMO game\nPodstawy Grafiki Komputerowej 2016\nauthor: kstarzyk 264734\n\n");
  printf("\tBuild:   $ make linux OR $ make mac (default: make mac)\n");
  printf("\tUsage:   $ ./memo M N K W (default values: 6 4 3 3)\n");
  printf("\tExample: $ ./memo 8 4 3 (M=8, N=4, K=3, W=3(default))\n\n");
}

int main( int argc, char *argv[] )
{
  /* UTILS */
  if (argc == 2 && strncmp(argv[1],"help", 4) == 0) {
    display_help();
    return -1;
  }

  int _M = 6, _N = 4, _K = 3, _W = 3;
  if (argc > 1)
    _M = atoi(argv[1]);
  if (argc > 2)
    _N = atoi(argv[2]);
  if (argc > 3)
    _K = atoi(argv[3]);
  if (argc > 4)
    _W = atoi(argv[4]);

  printf("\tM = %d\n\tN = %d\n\tK = %d\n\tW = %d\n", _M, _N, _K, _W);

  /* INITIALIZE GLFW */
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	window = glfwCreateWindow( 1024, 768, "memo", NULL, NULL);
	if( window == NULL )
  {
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = true;
	if (glewInit() != GLEW_OK)
  {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	GLuint programID = LoadShaders( "vertex.glsl", "fragment.glsl" );

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
  glfwSetKeyCallback(window,key_callback);
	glClearColor(0.68f, 0.55f, 0.86f, 0.0f);

  GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

  GLuint vertexbuffer;

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(card_vertex), card_vertex, GL_STATIC_DRAW);

  glUseProgram(programID);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
  glEnableVertexAttribArray(0);

  /* SETUP GAME */
  auto game = Game::getInstance();
  if (!game->setupGame(programID, _M, _N, _K, _W))
  {
    fprintf(stderr, "Failed to initialize game!\n");
    return -1;
  }


  /* MAIN LOOP */

	do {
    if (game->needUpdate) {
      glClear( GL_COLOR_BUFFER_BIT );

      game->draw();

      glfwSwapBuffers(window);
      //game->needUpdate = false;
  }

  glfwPollEvents();

	}
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 &&
      game->isRunning);

  /* CLEAN */
  glDisableVertexAttribArray(0);
	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteProgram(programID);
	glDeleteBuffers(1, &vertexbuffer);

	glfwTerminate();
	return 0;
}

