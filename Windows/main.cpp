#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <math.h>

// Una implementación de la función gotoxy () para una animación más fluida
// sin desplazarse ni borrar la pantalla.
void gotoxy(SHORT x, SHORT y)
{
  static HANDLE h = NULL;
  if(!h)
    h = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD c = { x, y };
  SetConsoleCursorPosition(h,c);
}

//              k;double sin()
//          ,cos();main(){float A=
//        0,B=0,i,j,z[1760];char b[
//      1760];printf("\x1b[2J");for(;;
//   ){memset(b,32,1760);memset(z,0,7040)
//   ;for(j=0;6.28>j;j+=0.07)for(i=0;6.28
//  >i;i+=0.02){float c=sin(i),d=cos(j),e=
//  sin(A),f=sin(j),g=cos(A),h=d+2,D=1/(c*
//  h*e+f*g+5),l=cos      (i),m=cos(B),n=s\
// in(B),t=c*h*g-f*        e;int x=40+30*D*
// (l*h*m-t*n),y=            12+15*D*(l*h*n
// +t*m),o=x+80*y,          N=8*((f*e-c*d*g
//  )*m-c*d*e-f*g-l        *d*n);if(22>y&&
//  y>0&&x>0&&80>x&&D>z[o]){z[o]=D;;;b[o]=
//  ".,-~:;=!*#$@"[N>0?N:0];}}/*#****!!-*/
//   printf("\x1b[H");for(k=0;1761>k;k++)
//    putchar(k%80?b[k]:10);A+=0.04;B+=
//      0.02;}}/*****####*******!!=;:~
//        ~::==!!!**********!!!==::-
//          .,~~;;;========;;;:~-.
//              ..,--------,*/

int main()
{
     // R1 se toma como 1, ya que solo se multiplica por términos,
     // podemos descuidarlo en este programa.

     // A, B
    float A = 0, B = 0;

    //phi, theta
    float i, j;

    //K1
    int k;

    //z-buffer
    float z[1760];
    char b[1760];
    std::cout << "\x1b[2J";
    while (true)
    {
        memset(b, 32, 1760);
        memset(z, 0, 7040);
        for (j = 0; j < 6.28; j += 0.07)
        {
            for (i = 0; i < 6.28; i += 0.02)
            {
                // Calcularemos la posición y luminancia de cada punto.
                float c = sin(i); // sin(phi)
                float d = cos(j); // cos(theta)
                float e = sin(A); // sin(A)
                float f = sin(j); // sin(theta)
                float g = cos(A); // cos(A)
                float h = d + 2;  // (R2 + R1cos(theta)) //R2 se toma como 2 aquí
                float D = 1 / (c * h * e + f * g + 5); // 1/(z + K2) //K2 se toma como 5
                float l = cos(i); // cos(phi)
                float m = cos(B); // cos(B)
                float n = sin(B); // sin(B)

                float t = c * h * g - f * e;

                // Calculando x (x 'ya que estamos multiplicando por D) (K 1 es 1)
                int x = 40 + 30 * D * (l * h * m - t * n);

                // Calculando y (y 'específicamente porque estamos multiplicando por D)
                int y = 12 + 15 * D * (l * h * n + t * m);

                // Variable para almacenar el carácter ASCII renderizado en el búfer.
                // Estamos usando una matriz 1D.
                int o = x + 80 * y;

                // Luminancia.
                int N = 8 * ((f * e - c * d * g) * m - c * d * e - f * g - l * d * n);
                if (22 > y && y > 0 && x > 0 && 80 > x && D > z[o])
                {
                    // Cadena D en z-buffer
                    z[o] = D;

                    // Elegir un carácter ASCII basado en la luminancia y almacenarlo en el búfer
                    b[o] = ".,-~:;=!*#$@"[N > 0 ? N : 0];
                }
            }
        }
        std::cout << "\x1b[H";
        for (k = 0; k < 1761; k++)
        {
            putchar(k % 80 ? b[k] : 10);
            A += 0.00004;
            B += 0.00002;
        }
        //Sleep(10);
        gotoxy(0,0);
    }


    return 0;
}
