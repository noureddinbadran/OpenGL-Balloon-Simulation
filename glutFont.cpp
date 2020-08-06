#include <windows.h>		// Header File For Windows
#include <GL.h>			// Header File For The OpenGL32 Library
#include <glu.h>			// Header File For The GLu32 Library
#include <glut.h>// Header File For The GLut32 Library
#include <fstream>
#include <math.h>
#include "texture.h"
#include "camera.h"
#include "Model_3DS.h"
#include <sstream>
#include <iostream>
#include <stdarg.h>	
#include "heightMap.h"
#include "Constants.h"
#include "math3d.h"
# include <glut.h>


unsigned int StringLength(void* font, const char* str) {
  int stringSize = 0;
  const char* c;

  for (c=str; *c != '\0'; c++)
    stringSize += glutBitmapWidth(font, *c);
  
  return stringSize;
}



void DisplayString(int x, int y, void* font, const char* str) {
  const char* c;

  // Position the cursor for font drawing
  glRasterPos2i(x, y);

  // Draw the font letter-by-letter
  for (c=str; *c != '\0'; c++)
    glutBitmapCharacter(font, *c);
}