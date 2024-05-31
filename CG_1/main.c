#include <stdio.h> #include <math.h> #include <windows.h> #include <conio.h> #include <string.h>
     #define roundf(x) floor((x) + 0.5f) //округление
     //объявление начальных массивов с координатами отрезков
     float AB[2][3] = {{200, 300, 1}, //x0, y0, 1
                       {450, 300, 1}}; //x1, y1, 1
     float CD[2][3] = {{400, 400, 1}, //x2, y2, 1
                       {270, 150, 1}}; //x3, x4, 1
//интерфейсы используемых функций
void move(float new[2][3], float ABBC[2][3]);
void rotate(float new[2][3], float ABBC[2][3], float centerX,
float centerY);
     void scale(float new[2][3], float ABBC[2][3], float centerX,
float centerY);
     float CenterX(float new_AB[2][3], float new_CD[2][3]);
     float CenterY(float new_AB[2][3], float new_CD[2][3]);
     //объявление глобальных переменных
     float dx = 0;    //смещение по оси x
     float dy = 0;    //смещение по оси y
     float ang = 0; //угловой поворот в радианах
     float S = 1;  //масштабирование
     //изначальные координаты точки центра
     float centerX;
     float centerY;
     //основная  функция  обработки  клавиш  и  вызова  остальных функций
      LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam,
LPARAM lParam) {
float new_AB[2][3] = {{200, 300, 1}, //текущие координаты первого отрезка
{450, 300, 1}};
float new_CD[2][3] = {{400, 400, 1}, //текущие координаты
второго отрезка
                               {270, 150, 1}};
         centerX = CenterX(new_AB, new_CD);
         centerY = CenterY(new_AB, new_CD);
         //обработка клавиш
         switch (msg) {
         case WM_PAINT:
         case WM_KEYDOWN: {
             switch (wParam) {
             case 'W':
             case 'w': {
                 dy -= 5;
                 move(new_AB, AB);
                 move(new_CD, CD);
                 centerX = CenterX(new_AB, new_CD); //расчитываем координаты нового центра
                 centerY = CenterY(new_AB, new_CD);
                 rotate(new_AB, new_AB, centerX, centerY);
                 rotate(new_CD, new_CD, centerX, centerY);
                 scale(new_AB, new_AB, centerX, centerY);
                 scale(new_CD, new_CD, centerX, centerY);
                 win_paint(hwnd, new_AB, new_CD);
                 InvalidateRect(hwnd, NULL, TRUE);
break; }
             case 'S':
             case 's': {
                dy += 5;
    move(new_AB, AB);
    move(new_CD, CD);
    centerX = CenterX(new_AB, new_CD);
    centerY = CenterY(new_AB, new_CD);
    rotate(new_AB, new_AB, centerX, centerY);
    rotate(new_CD, new_CD, centerX, centerY);
    scale(new_AB, new_AB, centerX, centerY);
    scale(new_CD, new_CD, centerX, centerY);
    win_paint(hwnd, new_AB, new_CD);
    InvalidateRect(hwnd, NULL, TRUE);
    break;
}
case 'A':
case 'a': {
    dx -= 5;
    move(new_AB, AB);
    move(new_CD, CD);
    centerX = CenterX(new_AB, new_CD);
    centerY = CenterY(new_AB, new_CD);
    rotate(new_AB, new_AB, centerX, centerY);
    rotate(new_CD, new_CD, centerX, centerY);
    scale(new_AB, new_AB, centerX, centerY);
    scale(new_CD, new_CD, centerX, centerY);
    win_paint(hwnd, new_AB, new_CD);
    InvalidateRect(hwnd, NULL, TRUE);
    break;
}
case 'D':
case 'd': {
    dx += 5;
    move(new_AB, AB);
    move(new_CD, CD);
    centerX = CenterX(new_AB, new_CD);
    centerY = CenterY(new_AB, new_CD);
    rotate(new_AB, new_AB, centerX, centerY);
    rotate(new_CD, new_CD, centerX, centerY);
    scale(new_AB, new_AB, centerX, centerY);
    scale(new_CD, new_CD, centerX, centerY);
    win_paint(hwnd, new_AB, new_CD);
    InvalidateRect(hwnd, NULL, TRUE);
break; }
case 'Q':
case 'q': {
    ang -= 0.05;
    move(new_AB, AB);
    move(new_CD, CD);
    centerX = CenterX(new_AB, new_CD);
    centerY = CenterY(new_AB, new_CD);
    rotate(new_AB, new_AB, centerX, centerY);
    rotate(new_CD, new_CD, centerX, centerY);
    scale(new_AB, new_AB, centerX, centerY);
    scale(new_CD, new_CD, centerX, centerY);
    win_paint(hwnd, new_AB, new_CD);
    InvalidateRect(hwnd, NULL, TRUE);
break; }
case 'E':
case 'e': {
    ang += 0.05;
    move(new_AB, AB);
    move(new_CD, CD);
    centerX = CenterX(new_AB, new_CD);
    centerY = CenterY(new_AB, new_CD);
    rotate(new_AB, new_AB, centerX, centerY);
    rotate(new_CD, new_CD, centerX, centerY);
    scale(new_AB, new_AB, centerX, centerY);
    scale(new_CD, new_CD, centerX, centerY);
    win_paint(hwnd, new_AB, new_CD);
    InvalidateRect(hwnd, NULL, TRUE);
break;
 }
    case 'V':
    case 'v': {
S -= 0.01;
        move(new_AB, AB);
        move(new_CD, CD);
        centerX = CenterX(new_AB, new_CD);
        centerY = CenterY(new_AB, new_CD);
        rotate(new_AB, new_AB, centerX, centerY);
        rotate(new_CD, new_CD, centerX, centerY);
        scale(new_AB, new_AB, centerX, centerY);
        scale(new_CD, new_CD, centerX, centerY);
        win_paint(hwnd, new_AB, new_CD);
        InvalidateRect(hwnd, NULL, TRUE);
        break;
    }
    case 'B':
    case 'b': {
        S += 0.01;
        move(new_AB, AB);
        move(new_CD, CD);
        centerX = CenterX(new_AB, new_CD);
        centerY = CenterY(new_AB, new_CD);
        rotate(new_AB, new_AB, centerX, centerY);
        rotate(new_CD, new_CD, centerX, centerY);
        scale(new_AB, new_AB, centerX, centerY);
        scale(new_CD, new_CD, centerX, centerY);
        win_paint(hwnd, new_AB, new_CD);
        InvalidateRect(hwnd, NULL, TRUE);
        break;
}
} break; 
}
case WM_CLOSE:
DestroyWindow(hwnd);
             break;
         default:
             return DefWindowProc(hwnd, msg, wParam, lParam);
         }
return 0; }
     //основная функция main
     int main(){
         //Определение  структуры  оконного  класса  и  установка
начальных значений
         WNDCLASS wc = { 0 };
             wc.lpfnWndProc = WndProc;
             wc.hInstance = GetModuleHandle(NULL);
             wc.lpszClassName = L"myWindowClass";
             RegisterClass(&wc);
             //Создание окна и определение его свойств
             HWND hwnd = CreateWindow(
                 L"myWindowClass",
                 L"Lab_1",
                 WS_OVERLAPPEDWINDOW,
                 CW_USEDEFAULT,
                 CW_USEDEFAULT,
                 CW_USEDEFAULT,
                 CW_USEDEFAULT,
                 NULL,
                 NULL,
                 GetModuleHandle(NULL),
                 NULL
);
ShowWindow(hwnd, SW_SHOWDEFAULT);
//Создаем цикл сообщений для обработки сообщений окна MSG msg = { 0 };
while (GetMessage(&msg, NULL, 0, 0))
{
    TranslateMessage(&msg);
    DispatchMessage(&msg);
}
return 0;
     }
      //функция смещения по x и y
     void move(float new[2][3], float ABBC[2][3]){
         int cnt = 0; //счетчик
         float out[2][3] = { {0, 0, 0},
{0, 0, 0} }; //выходной массив с
новыми значениями
         float MATRIX_1[3][3] = { {1, 0, 0},
{0, 1, 0},
{dx, dy, 1} };//матрица смещения
         for (int i = 0; i < 2; i++)
                for (int j = 0; j < 3; j++)
                {
                    out[i][j] = 0;
                    for (int k = 0; k < 3; k++) {
                        out[i][j] += ABBC[i][k] * MATRIX_1[k][j];
                        cnt++;
                        if (cnt == 3) {
                            new[i][j] = out[i][j];
cnt = 0; }
} }
     }
     //функция углового поворота
     void rotate(float new[2][3], float ABBC[2][3], float centerX, float centerY)
     {
         int cnt = 0; //счетчик
         float out[2][3] = { {0, 0, 0},
{0, 0, 0} }; //выходной массив с
новыми значениями
         float matrix_translate[3][3] = { {1, 0, 0},
{0, 1, 0},
                                          {-centerX, -centerY, 1}
}; //матрица для переноса точек к началу координат
         float MATRIX_2[3][3] = { {cos(ang), sin(ang), 0},
                                  {-sin(ang), cos(ang), 0},
                                  {0, 0, 1} }; //матрица углового
поворота
         float matrix_translate_back[3][3] = { {1, 0, 0},
{0, 1, 0},
                                               {centerX, centerY,
1} }; //матрица для переноса точек обратно после вращения
float tmp[2][3] = { {0, 0, 0},
{0, 0, 0} }; //массив для
промежуточных вычислений
         //перенос
         for (int i = 0; i < 2; i++)
             for (int j = 0; j < 3; j++)
             {
                 out[i][j] = 0;
                 for (int k = 0; k < 3; k++) {
out[i][j] += matrix_translate[k][j];
} }
         //поворот
         for (int i = 0; i < 2; i++)
             for (int j = 0; j < 3; j++)
             {
                tmp[i][j] = 0;
        for (int k = 0; k < 3; k++) {
            tmp[i][j] += out[i][k] * MATRIX_2[k][j];
        }
    }
//обратный перенос
for (int i = 0; i < 2; i++)
    for (int j = 0; j < 3; j++)
    {
        new[i][j] = 0;
        for (int k = 0; k < 3; k++) {
                     new[i][j]
matrix_translate_back[k][j];
} }
     //фукнкция масштабирования
+= tmp[i][k] *
}
     void scale(float new[2][3], float ABBC[2][3], float centerX,
float centerY)
{
int cnt = 0;
};
float out[2][3] = { {0, 0, 0},
                    {0, 0, 0} };
float matrix_translate[3][3] = { {1, 0, 0},
                                 {0, 1, 0},
                                 {-centerX, -centerY, 1}};
float MATRIX_3[3][3] = { {S, 0, 0},
                         {0, S, 0},
                         {0, 0, 1} };
float matrix_translate_back[3][3] = { {1, 0, 0},
                                      {0, 1, 0},
                                      {centerX, centerY, 1} };
float tmp[2][3] = { {0, 0, 0}, {0, 0, 0} };

 //Перенос
         for(int i = 0; i < 2; i++){
             for (int j = 0; j < 3; j++) {
                 out[i][j] = 0;
                 for (int k = 0; k < 3; k++) {
out[i][j] += matrix_translate[k][j];
} }
         //Масштабирование
         for (int i = 0; i < 2; i++)
             for (int j = 0; j < 3; j++)
             {
                 tmp[i][j] = 0;
                 for (int k = 0; k < 3; k++) {
ABBC[i][k] *
                     tmp[i][j] += out[i][k] * MATRIX_3[k][j];
                 }
}
         //Перенос обратно
         for (int i = 0; i < 2; i++)
             for (int j = 0; j < 3; j++)
             {
                 new[i][j] = 0;
                 for (int k = 0; k < 3; k++) {
new[i][j] += tmp[i][k] * matrix_translate_back[k][j];
} }
     //функции для нахождения точек центра масс
      float CenterX(float new_AB[2][3], float new_CD[2][3])
     {
         float   k_AB   =   (new_AB[1][1]   -   new_AB[0][1])   /
(new_AB[1][0] - new_AB[0][0]);
         float b_AB = new_AB[0][1] - k_AB * new_AB[0][0];
         float   k_CD   =   (new_CD[1][1]   -   new_CD[0][1])   /
(new_CD[1][0] - new_CD[0][0]);
         float b_CD = new_CD[0][1] - k_CD * new_CD[0][0];
         float centerX = (b_CD - b_AB) / (k_AB - k_CD);
         return centerX;
     }
     float CenterY(float new_AB[2][3], float new_CD[2][3])
     {
         float   k_AB   =   (new_AB[1][1]   -   new_AB[0][1])   /
(new_AB[1][0] - new_AB[0][0]);
         float b_AB = new_AB[0][1] - k_AB * new_AB[0][0];
         float   k_CD   =   (new_CD[1][1]   -   new_CD[0][1])   /
(new_CD[1][0] - new_CD[0][0]);
         float b_CD = new_CD[0][1] - k_CD * new_CD[0][0];
         float centerX = CenterX(new_AB, new_CD);
         float centerY = k_AB * centerX + b_AB;
         return centerY;
     }
     //функция рисования
void win_paint(HWND hwnd, float new_AB[2][3], float new_CD[2][3]){
         PAINTSTRUCT ps;
         HDC hdc = BeginPaint(hwnd, &ps);
           RECT rc;
         GetClientRect(hwnd, &rc);
         FillRect(hdc, &rc, (HBRUSH)GetStockObject(WHITE_BRUSH));
         // Вызываем функции для рисования
         HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
         HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
         MoveToEx(hdc,                      roundf(new_AB[0][0]),
roundf(new_AB[0][1]), NULL);
         LineTo(hdc, roundf(new_AB[1][0]), roundf(new_AB[1][1]));
         MoveToEx(hdc,                      roundf(new_CD[0][0]),
roundf(new_CD[0][1]), NULL);
         LineTo(hdc, roundf(new_CD[1][0]), roundf(new_CD[1][1]));
         SelectObject(hdc, hOldPen);
         DeleteObject(hPen);
         EndPaint(hwnd, &ps);
     }
