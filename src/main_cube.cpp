/* 
 * main.cpp
 * Główny program oraz okno aplikacji GLFW.
 * Wymiary okna podawane jako argumenty programu.
 * Program wymaga kompilatora wspierającego standart C++11.
 *
 * g++ -std=c++11 -O2 Controls/GLFWControls.cpp Controls/ProgramArguments.cpp DataLoaders/ShaderProgram.cpp main_cube.cpp -o CUBE -lglfw -lGL -lGLEW
 *   dla komputerów UJ:
 * export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:./Libraries"
 * g++ -std=c++11 -O2 Controls/GLFWControls.cpp Controls/ProgramArguments.cpp DataLoaders/ShaderProgram.cpp main_cube.cpp -o CUBE -L./Libraries/ -lglfw3 -lX11 -lXrandr -lXinerama -lXi -lXcursor -lGL -lGLEW
 *
 * (C) Jan Bielański 2016
 */

#include <iostream>
#include <string>
#include <random>

#include "ProgramArguments.hpp"
#include "OpenGL.hpp"
#include "GLFWControls.hpp"
#include "ShaderProgram.hpp"

/* ZARZĄDZANIE OBIEKTAMI - STRUKTURY DANYCH */
typedef struct COORD // Współrzędne punktów
{
   float x, y, z;
} COORD;
typedef struct COLOR // Wartości koloru
{
   float r, g, b, a; //Z przedziału [0 - 1]
} COLOR;

// Stuktura obiektu
typedef struct OBJECT {
   COORD *Vert; //Tablica wierzchołków
   COLOR *Color; //Tablica kolorów

   GLuint *IndexVert; //Tablica indeksów wierzchołków

   GLuint sizeVert, sizeIndexVert; //Rozmiar tablicy wierzchołków i indeksów wierzchołków

   OBJECT() { //Konstruktor domyślny
      Vert = nullptr;
      IndexVert = nullptr;
      sizeVert = 0;
      sizeIndexVert = 0;
      Color = nullptr;

   };

   ~OBJECT() { //Destruktor
      if (!Vert) { delete[] Vert; }
      if (!IndexVert) { delete[] IndexVert; }
      if (!Color) { delete[] Color; }
      Vert = nullptr;
      IndexVert = nullptr;
      sizeVert = 0;
      sizeIndexVert = 0;
      Color = nullptr;
   };

} OBJECT;
/* ---------------------------------------- */

// Tworzenie sześcianu
void CreateCUBE(OBJECT *Object) {

  // Ustalanie współrzędnych
  Object->Vert = new COORD[8]; Object->sizeVert=8;

  //     (5)-------(4)
  //     /|        /|
  //    / |       / |
  //  (1)-------(0) |
  //   |  |      |  |
  //   |  |      |  |
  //   | (6)-----|-(7)
  //   | /       | /
  //   |/        |/
  //  (2)-------(3)
  //

  Object->Vert[0].x =  0.5f; Object->Vert[0].y =  0.5f; Object->Vert[0].z = 0.5f;
  Object->Vert[1].x = -0.5f; Object->Vert[1].y =  0.5f; Object->Vert[1].z = 0.5f;
  Object->Vert[2].x = -0.5f; Object->Vert[2].y = -0.5f; Object->Vert[2].z = 0.5f;
  Object->Vert[3].x =  0.5f; Object->Vert[3].y = -0.5f; Object->Vert[3].z = 0.5f;

  Object->Vert[4].x =  0.5f; Object->Vert[4].y =  0.5f; Object->Vert[4].z = -0.5f;
  Object->Vert[5].x = -0.5f; Object->Vert[5].y =  0.5f; Object->Vert[5].z = -0.5f;
  Object->Vert[6].x = -0.5f; Object->Vert[6].y = -0.5f; Object->Vert[6].z = -0.5f;
  Object->Vert[7].x =  0.5f; Object->Vert[7].y = -0.5f; Object->Vert[7].z = -0.5f;


  // Tablica indeksów
  Object->IndexVert = new GLuint[36]; Object->sizeIndexVert=36;  // ściana: 2 trójkąty -> liczba ścian: 6 -> liczba trójkątów: 12 -> wierzchołki trójkąta 3 --> ŁĄCZNIE 36 wartości!!!

  // Zasady nawijania
  //      (2)                                 (2)
  //     /   ^     Ściana PRZODEM do         ^   \        Ściana TYŁEM do
  //    /     \       obserwatora           /     \         obserwatora
  //   v       \                           /       v
  // (0) ----> (1)                       (0) <---- (1)
  //

  //ZADANIE 1:
  // a) Narysować sześcian, poprzez odpowiednie wypełnienie tablicy indeksów wierzchołków.
  // b) Proszę poeksperymentować z wartościami kolorów


  Object->IndexVert[0] = 0; Object->IndexVert[1] =4; Object->IndexVert[2] = 5; //T
  Object->IndexVert[3] = 5; Object->IndexVert[4] = 1; Object->IndexVert[5] = 0; //T

  Object->IndexVert[6] = 0; Object->IndexVert[7] = 1; Object->IndexVert[8] = 3; //F
  Object->IndexVert[9] = 3; Object->IndexVert[10] = 1; Object->IndexVert[11] = 2; //F
  Object->IndexVert[12] = 4; Object->IndexVert[13] = 6; Object->IndexVert[14] = 5; //B
  Object->IndexVert[15] = 4; Object->IndexVert[16] = 7; Object->IndexVert[17] = 6; //B
  Object->IndexVert[18] = 7; Object->IndexVert[19] = 3; Object->IndexVert[20] = 6; //Bot
  Object->IndexVert[21] = 3; Object->IndexVert[22] = 2; Object->IndexVert[23] = 6; //Bot
  Object->IndexVert[24] = 7; Object->IndexVert[25] = 4; Object->IndexVert[26] = 0; //R
  Object->IndexVert[27] = 3; Object->IndexVert[28] = 7; Object->IndexVert[29] = 0; //R
  Object->IndexVert[30] = 2; Object->IndexVert[31] = 1; Object->IndexVert[32] = 6; //L
  Object->IndexVert[33] = 6; Object->IndexVert[34] = 1; Object->IndexVert[35] = 5; //Trójkąt 12

  // Tablica kolorów
  Object->Color = new COLOR[8];

  for(int i=0; i<8; i++) {
    Object->Color[i].r = i/8.0f;
    Object->Color[i].g = 1.0;
    Object->Color[i].b = (float) 1.0 - i/8.0f;
    Object->Color[i].a = 1.0;
  }
   Object->Color[0].r = 1;
   Object->Color[0].g = 0;
   Object->Color[0].b = 0;
   Object->Color[0].a = 1.0;
}

// GŁÓWNY PROGRAM
int main(int argc, char *argv[]) {
   // Zmienne przechowujące parametry okna (można to zrobić ładniej w klasie)
   int win_width;
   int win_height;
   std::string win_name;

   //Pobranie argumentów
   getArguments(argc, argv, &win_width, &win_height, &win_name);

   //Okno programu GLFW
   GLFWwindow *window = nullptr;

   //Inicjowanie biblioteki GLFW
   if (!glfwInit()) { //Obsługa błedów
      exit(EXIT_FAILURE);
   }

   //Tworzenie okna aplikacji GLFW w trybie okno (windowed mode) i kontekstu OpenGL
   window = glfwCreateWindow(win_width, win_height, win_name.c_str(), NULL, NULL);
   if (!window) { //Obsługa błedów
      glfwTerminate(); //Usunięcie okna
      exit(EXIT_FAILURE);
   }

   //Ustawienie kontekstu dla utworzonego okna
   glfwMakeContextCurrent(window);

   // +++ Modyfikacja czasu działania animacji (okres oczekiwania przed opróżnieniem bufora) +++
   glfwSwapInterval(5); //Obsługa czasu

   //Uruchomienie wsparcia GLEW
   glewExperimental = GL_TRUE;
   glewInit();

   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LESS);
   //glEnable(GL_CULL_FACE);



   //Informacje na temat wspieranej wersji OpenGL
   const GLubyte *renderer = glGetString(GL_RENDERER); //System renderujący (karta graficzna)
   const GLubyte *version = glGetString(GL_VERSION); //Wersja OpenGL
   printf("Renderer: %s\n", renderer);
   printf("OpenGL version supported %s\n", version);

   //Dołaczenie funkcji obsługi błędów
   glfwSetErrorCallback(error_callback);

   //Dołaczenie funkcji do obsługi zdarzen z klawiatury
   glfwSetKeyCallback(window, key_callback);

   //Dołączenie dunkcji do obsłufi zdarzeń myszy
   glfwSetCursorPosCallback(window, mouse_position_callback);
   glfwSetMouseButtonCallback(window, mouse_button_callback);
   glfwSetScrollCallback(window, mouse_scroll_callback);

   // TWORZENIE PROGRAMU SHADERA
   ShaderProgram program;

   //Utworzenie i kompilacja shadera wierzchołków [NIEZBĘDNE DO PRACY OPENGL]
   program.AddShaderFromFile(GL_VERTEX_SHADER, "vertex_shader.vs");

   //Utworzenie i kompilacja shadera fragmentów [NIEZBĘDNE DO PRACY OPENGL]
   program.AddShaderFromFile(GL_FRAGMENT_SHADER, "fragment_shader.fs");

   //Linkowanie programu
   program.Link(); // Linkowanie programu

   // Przygotowanie struktury danych na SZEŚCIAN i utworzenie sześcianu
   OBJECT Cube;
   CreateCUBE(&Cube);
   GLuint DATA_BUFFER[3];
   GLuint VAO;

   // GENEROWANIE BUFFORÓW
   glGenVertexArrays(1, &VAO);
   glGenBuffers(3, DATA_BUFFER); //Utworzenie czterech buforów

   glBindVertexArray(VAO); //Aktywowanie tablicy wierzchołków

   // TWORZENIE BUFORA Z WSPÓŁRZĘDNYMI WIERZCHOŁKÓW
   glBindBuffer(GL_ARRAY_BUFFER, DATA_BUFFER[0]); //Powiązanie bufora z typem bufora
   glBufferData(GL_ARRAY_BUFFER, sizeof(COORD) * Cube.sizeVert, Cube.Vert, GL_STATIC_DRAW);
   glVertexAttribPointer(glGetAttribLocation(program.Get(), "inPosition"), 3, GL_FLOAT, GL_FALSE, 0, 0);

   // TWORZENIE BUFORA Z TABLICĄ INDEKSÓW WIERZCHOŁKÓW
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, DATA_BUFFER[1]);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * Cube.sizeIndexVert, Cube.IndexVert, GL_STATIC_DRAW);

   // TWORZENIE BUFORA Z WARTOŚCIAMI KOLORÓW
   glBindBuffer(GL_ARRAY_BUFFER, DATA_BUFFER[2]); //Powiązanie bufora z typem bufora
   glBufferData(GL_ARRAY_BUFFER, sizeof(COLOR) * Cube.sizeVert, Cube.Color, GL_STATIC_DRAW);
   glVertexAttribPointer(glGetAttribLocation(program.Get(), "inColor"), 4, GL_FLOAT, GL_FALSE, 0, 0);


   //Pobranie informacji na temat sceny i danych
   GLuint mvp_location;
   mvp_location = glGetUniformLocation(program.Get(), "MVP"); //Model-View Projection matrix

   glEnableVertexAttribArray(glGetAttribLocation(program.Get(), "inPosition"));
   glEnableVertexAttribArray(glGetAttribLocation(program.Get(), "inColor"));

   glBindVertexArray(0); //Wyłączanie tablicy wierzchołków

   glm::vec3 cubePositions[] = {
         glm::vec3( 0.0f,  0.0f,  0.0f),
         glm::vec3( 2.0f,  5.0f, -15.0f),
         glm::vec3(-1.5f, -2.2f, -2.5f),
         glm::vec3(-3.8f, -2.0f, -12.3f),
         glm::vec3( 2.4f, -0.4f, -3.5f),
         glm::vec3(-1.7f,  3.0f, -7.5f),
         glm::vec3( 1.3f, -2.0f, -2.5f),
         glm::vec3( 1.5f,  2.0f, -2.5f),
         glm::vec3( 1.5f,  0.2f, -1.5f),
         glm::vec3(-1.3f,  1.0f, -1.5f)
   };

   float rotation = 0;
   float lastFrame = 0;
   float delta = 0;
   //GŁÓWNA PĘTLA APLIKACJI (pętla wykonywana do czasu zamknięcia programu przez użytkownika)
   while (!glfwWindowShouldClose(window)) {
      //PROCEDURY RENEROWANIA [tu umieszczamy wszystkie procedury związane z wyświetlaniem w naszym programie]

      delta = (float) glfwGetTime() - lastFrame;
      lastFrame += delta;

      float fov = 45.0f; //Kąt widzenia
      float ratio; // Stosunek wymiaru okna szerokość/wysokość
      glm::mat4 m, v, p, mvp; // Macierze: model, projekcja, iloczyn macierzy modelu/widoku/projekcji

      glfwGetWindowSize(window, &win_width, &win_height); // Pobranie wymiarów okna

      ratio = win_width / (float) win_height; // Stosunek wymiaru okna szerokość/wysokość

      glViewport(0, 0, win_width, win_height);  // Dostosowanie rederowanego obrazu do wymiarów okna

      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Wyczyszczenie okna kolorem (czarnym)

      for (int i = 0; i < 10; i++) {
         m = glm::mat4(1.0);
         v = glm::mat4(1.0);

         /* --- OBRÓT --- */
         rotation += delta;
         rotation = rotation > 360 ? rotation - 360 : rotation;

         m = glm::translate(m, cubePositions[i]);
         m = glm::rotate(m, glm::radians(rotation), glm::vec3(1.0f, 0.0f, 0.0f));
         m = glm::scale(m, glm::vec3(1.0f, 1.0f, 1.0f));

         /* --- WIDOK --- */
         GLfloat radius = 10.f;
         GLfloat camX = sin(glfwGetTime()) * radius;
         GLfloat camZ = cos(glfwGetTime()) * radius;

         v = glm::lookAt(glm::vec3(camX, 0.f, camZ), glm::vec3(.0f, .0f, .0f), glm::vec3(.0f, 1.f, .0f));

         p = glm::perspective(glm::radians(45.f), ratio, 0.1f, 100.f);
         //p = glm::ortho(-ratio * 1.f, ratio * 1.f, -1.f, 1.f, 0.1f, 100.f);

         mvp = p * v * m; // Macierz modelu-widoku-projekcji

         glBindVertexArray(VAO);//Aktywowanie tablicy wierzchołków

         program.Use(); // Wykonanie programu OpenGL

         glUniformMatrix4fv(mvp_location, 1, GL_FALSE,
                            glm::value_ptr(
                                  mvp)); // Przekazanie danych macierzy modelu-widoku-projekcji do programu OpenGL

         /* RYSOWANIE NA PODSTAWIE TABLICY DANYCH */
         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, DATA_BUFFER[1]);


         //ZADANIE 2:
         //  a) Proszę narysować wierzchołki sześcianu (proszę poeksperymentować z rozmiarem punktu)
         //  b) Proszę narysować krawędzie sześcianu

         glLineWidth(10.0f);

         glDrawElements(GL_TRIANGLES, Cube.sizeIndexVert, GL_UNSIGNED_INT, NULL);
      }
      glBindVertexArray(0);//Wyłączanie tablicy wierzchołków

      //Wysłanie danych na ekran (opróżnienie buforów)
      glfwSwapBuffers(window);

      //Obsługa zdarzeń
      glfwPollEvents();
   }

   glfwTerminate(); //Usunięcie okna

   exit(EXIT_SUCCESS);
}



