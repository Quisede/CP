#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <conio.h>
#include <string.h>

#define roundf(x) floor((x) + 0.5f) //округление

//объявление начальных массивов с координатами отрезков
float ABCT[3][3] = {{300, 400, 1},// A, x0, y0, 1
                   {600, 400, 1},// B, x1, y1, 1
                   {450, 140, 1}};// C, x2, y2, 1

//интерфейсы используемых функций
void move(float new[3][3], float ABCT[3][3]);
void rotate(float new[3][3], float ABCT[3][3], float centerX, float centerY);
void scale(float new[3][3], float ABCT[3][3], float centerX, float centerY);
float CenterX(float new_ABC[3][3]);
float CenterY(float new_ABC[3][3]);
void call_func(float new_ABC[3][3], float ABCT[3][3], float centerX, float centerY, HWND hwnd);

//объявление глобальных переменных
float dx = 0;    //смещение по оси x
float dy = 0;    //смещение по оси y
float ang = 0; //угловой поворот в радианах
float S = 1;  //масштабирование
//изначальные координаты точки центра
float centerX;
float centerY;

//основная функция обработки клавиш и вызова остальных функций
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    float new_ABC[3][3] = {{300, 400, 1},// A, x0, y0, 1
                   {600, 400, 1},// B, x1, y1, 1
                   {450, 140, 1}};// C, x2, y2, 1


    centerX = CenterX(new_ABC);
    centerY = CenterY(new_ABC);

    //обработка клавиш
    switch (msg) {
    case WM_PAINT:
    case WM_KEYDOWN: {

        switch (wParam) {
        case 'W':
        case 'w': {
            dy -= 5;
            call_func(new_ABC, ABCT, centerX, centerY, hwnd);
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        }
        case 'S':
        case 's': {
            dy += 5;
            call_func(new_ABC, ABCT, centerX, centerY, hwnd);
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        }
        case 'A':
        case 'a': {
            dx -= 5;
            call_func(new_ABC, ABCT, centerX, centerY, hwnd);
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        }
        case 'D':
        case 'd': {
            dx += 5;
            call_func(new_ABC, ABCT, centerX, centerY, hwnd);
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        }
        case 'Q':
        case 'q': {
            ang -= 0.05;
            call_func(new_ABC, ABCT, centerX, centerY, hwnd);
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        }
        case 'E':
        case 'e': {
            ang += 0.05;
            call_func(new_ABC, ABCT, centerX, centerY, hwnd);
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        }
        case 'V':
        case 'v': {
            S *= 0.95;
            call_func(new_ABC, ABCT, centerX, centerY, hwnd);
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        }
        case 'B':
        case 'b': {
            S *= 1.05;
            call_func(new_ABC, ABCT, centerX, centerY, hwnd);
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        }
        }
        break;
    }
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

//основная функция main
int main(){
    //Определение структуры оконного класса и установка начальных значений
    WNDCLASS wc = { 0 };
        wc.lpfnWndProc = WndProc;
        wc.hInstance = GetModuleHandle(NULL);
        wc.lpszClassName = L"myWindowClass";

        RegisterClass(&wc);
        //Создание окна и определение его свойств
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
        //Создаем цикл сообщений для обработки сообщений окна
        MSG msg = { 0 };
        while (GetMessage(&msg, NULL, 0, 0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        return 0;
}

//функция смещения по x и y
void move(float new[3][3], float ABCT[3][3]){
    int cnt = 0; //счетчик
    float out[3][3] = { {0, 0, 0},
                        {0, 0, 0},
                        {0, 0, 0} }; //выходной массив с новыми значениями
    float MATRIX_1[3][3] = { {1, 0, 0},
                             {0, 1, 0},
                             {dx, dy, 1} };//матрица смещения

    for (int i = 0; i < 3; i++)
           for (int j = 0; j < 3; j++)
           {
               out[i][j] = 0;
               for (int k = 0; k < 3; k++) {
                   out[i][j] += ABCT[i][k] * MATRIX_1[k][j];
                   cnt++;
                   if (cnt == 3) {
                       new[i][j] = out[i][j]; //копируем в матрицу new                             //использования данных в других функциях
                       cnt = 0;
                   }
               }
           }
}

//функция углового поворота
void rotate(float new[3][3], float ABCT[3][3], float centerX, float centerY)
{
    int cnt = 0; //счетчик
    float out[3][3] = { {0, 0, 0},
                        {0, 0, 0},
                        {0, 0, 0} }; //выходной массив с новыми значениями
    float matrix_translate[3][3] = { {1, 0, 0},
                                     {0, 1, 0},
                                     {-centerX, -centerY, 1} }; //матрица для переноса точек к началу координат
    float MATRIX_2[3][3] = { {cos(ang), sin(ang), 0},
                             {-sin(ang), cos(ang), 0},
                             {0, 0, 1} }; //матрица углового поворота
    float matrix_translate_back[3][3] = { {1, 0, 0},
                                          {0, 1, 0},
                                          {centerX, centerY, 1} }; //матрица для переноса точек обратно после вращения
    float tmp[3][3] = { {0, 0, 0},
                        {0, 0, 0},
                        {0, 0, 0} }; //массив для промежуточных вычислений
    //перенос
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            out[i][j] = 0;
            for (int k = 0; k < 3; k++) {
                out[i][j] += ABCT[i][k] * matrix_translate[k][j];
            }
        }
    //поворот
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            tmp[i][j] = 0;
            for (int k = 0; k < 3; k++) {
                tmp[i][j] += out[i][k] * MATRIX_2[k][j];
            }
        }
    //обратный перенос
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            new[i][j] = 0;
            for (int k = 0; k < 3; k++) {
                new[i][j] += tmp[i][k] * matrix_translate_back[k][j];
            }
        }
}

//фукнкция масштабирования
void scale(float new[3][3], float current[3][3], float centerX, float centerY) {
    int cnt = 0;
    float out[3][3] = { {0, 0, 0},
                        {0, 0, 0},
                        {0, 0, 0} }; //выходной массив с новыми значениями
    float matrix_translate[3][3] = { {1, 0, 0},
                                     {0, 1, 0},
                                     {-centerX, -centerY, 1} };
    float matrix_scale[3][3] = { {S, 0, 0},
                                 {0, S, 0},
                                 {0, 0, 1} };
    float matrix_translate_back[3][3] = { {1, 0, 0},
                                          {0, 1, 0},
                                          {centerX, centerY, 1} };
    float tmp[3][3] = { {0, 0, 0},
                        {0, 0, 0},
                        {0, 0, 0} }; //массив для промежуточных вычислений

    // Перевод в начало координат
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            out[i][j] = 0;
            for (int k = 0; k < 3; k++) {
                out[i][j] += current[i][k] * matrix_translate[k][j];
            }
        }

    // Масштабирование
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            tmp[i][j] = 0;
            for (int k = 0; k < 3; k++) {
                tmp[i][j] += out[i][k] * matrix_scale[k][j];
            }
        }


    // Возвращение обратно
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            new[i][j] = 0;
            for (int k = 0; k < 3; k++) {
                new[i][j] += tmp[i][k] * matrix_translate_back[k][j];
            }
        }
}


//функции для нахождения точек центра масс
float CenterX(float new_ABC[2][3])
{
    float centerX = (new_ABC[0][0] + new_ABC[1][0] + new_ABC[2][0]) / 3.0;
    return centerX;
}

float CenterY(float new_ABC[3][3])
{
    float centerY = (new_ABC[0][1] + new_ABC[1][1] + new_ABC[2][1]) / 3.0;
    return centerY;
}


//функция рисования
void win_paint(HWND hwnd, float new_ABC[2][3]){
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    RECT rc;
    GetClientRect(hwnd, &rc);
    FillRect(hdc, &rc, (HBRUSH)GetStockObject(BLACK_BRUSH));

    // Вызываем функции для рисования
    HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

    MoveToEx(hdc, roundf(new_ABC[0][0]), roundf(new_ABC[0][1]), NULL);//x0, y0
    LineTo(hdc, roundf(new_ABC[1][0]), roundf(new_ABC[1][1]));
    MoveToEx(hdc, roundf(new_ABC[1][0]), roundf(new_ABC[1][1]), NULL);//x1,y1
    LineTo(hdc, roundf(new_ABC[2][0]), roundf(new_ABC[2][1]));
    MoveToEx(hdc, roundf(new_ABC[2][0]), roundf(new_ABC[2][1]), NULL);//x2, y2
    LineTo(hdc, roundf(new_ABC[0][0]), roundf(new_ABC[0][1]));

    // Сортировка вершин
    for (int i = 0; i < 3; i++) {
       for (int j = i + 1; j < 3; j++) {
          if (new_ABC[j][1] < new_ABC[i][1]) {
             float temp[2] = {new_ABC[i][0], new_ABC[i][1]};
             new_ABC[i][0] = new_ABC[j][0];
             new_ABC[i][1] = new_ABC[j][1];
             new_ABC[j][0] = temp[0];
             new_ABC[j][1] = temp[1];
          }
       }
    }



    for (float y = new_ABC[0][1]; y <= new_ABC[2][1]; y++) {
        float x_start, x_end;
        if (y <= new_ABC[1][1]) {
            x_start = new_ABC[0][0] + (new_ABC[2][0] - new_ABC[0][0]) * (y - new_ABC[0][1]) / (new_ABC[2][1] - new_ABC[0][1]);
            x_end = new_ABC[0][0] + (new_ABC[1][0] - new_ABC[0][0]) * (y - new_ABC[0][1]) / (new_ABC[1][1] - new_ABC[0][1]);
        } else {
            x_start = new_ABC[0][0] + (new_ABC[2][0] - new_ABC[0][0]) * (y - new_ABC[0][1]) / (new_ABC[2][1] - new_ABC[0][1]);
            x_end = new_ABC[1][0] + (new_ABC[2][0] - new_ABC[1][0]) * (y - new_ABC[1][1]) / (new_ABC[2][1] - new_ABC[1][1]);
        }

        MoveToEx(hdc, roundf(x_start), roundf(y), NULL);
        LineTo(hdc, roundf(x_end), roundf(y));

    }


    SelectObject(hdc, hOldPen);
    DeleteObject(hPen);

    EndPaint(hwnd, &ps);
}





void call_func(float new_ABC[3][3], float ABCT[3][3], float centerX, float centerY, HWND hwnd){
    move(new_ABC, ABCT);
    centerX = CenterX(new_ABC); //расчитываем координаты нового центра
    centerY = CenterY(new_ABC);
    rotate(new_ABC, new_ABC, centerX, centerY);
    scale(new_ABC, new_ABC, centerX, centerY);
    win_paint(hwnd, new_ABC);
}
