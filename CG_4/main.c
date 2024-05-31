#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <conio.h>
#include <string.h>

#define roundf(x) floor((x) + 0.5f) //округление

//объявление начальных массивов с координатами отрезков
float ABCD[4][4] = { {150, 260, 0, 1},// A, x0, y0, 1
    {270, 150, 0, 1},// B, x1, y1, 1
    {290, 260, -20, 1},// C, x2, y2, 1
    {265, 270, 50, 1} };//D, x3, y3, 1

//интерфейсы используемых функций
void move(float new[4][4], float ABCD[4][4]);
void rotateX(float new[4][4], float ABCD[4][4], float centerX, float centerY, float centerZ);
void rotateY(float new[4][4], float ABCD[4][4], float centerX, float centerY, float centerZ);
void rotateZ(float new[4][4], float ABCD[4][4], float centerX, float centerY, float centerZ);
void scale(float new[4][4], float ABCD[4][4], float centerX, float centerY, float centerZ);
float CenterX(float new_ABC[4][4]);
float CenterY(float new_ABC[4][4]);
float CenterZ(float new_ABC[4][4]);
void call_func(float new_ABC[4][4], float ABCD[4][4], float centerX, float centerY, float centerZ, HWND hwnd);

//объявление глобальных переменных
float dx = 0;    //смещение по оси x
float dy = 0;    //смещение по оси y
float dz = 0;   //смещение по оси z
float angX = 0; //угловой поворот в радианах
float angY = 0;
float angZ = 0;
float S = 1;  //масштабирование
//изначальные координаты точки центра
float centerX;
float centerY;
float centerZ;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    float new_ABC[4][4] = { {150, 260, 0, 1},// A, x0, y0, 1
        {270, 150, 0, 1},// B, x1, y1, 1
        {290, 260, -20, 1},// C, x2, y2, 1
        {265, 270, 50, 1} };//D, x3, y3, 1



    // Получение центра
    centerX = CenterX(new_ABC);
    centerY = CenterY(new_ABC);
    centerZ = CenterZ(new_ABC);

    //обработка клавиш
    switch (msg) {
    case WM_PAINT:
    case WM_KEYDOWN: {
        switch (wParam) {
        case 'W':
        case 'w': {
            dy -= 5;
            call_func(new_ABC, ABCD, centerX, centerY, centerZ, hwnd);
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        }
        case 'S':
        case 's': {
            dy += 5;
            call_func(new_ABC, ABCD, centerX, centerY, centerZ, hwnd);
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        }
        case 'A':
        case 'a': {
            dx -= 5;
            call_func(new_ABC, ABCD, centerX, centerY, centerZ, hwnd);
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        }
        case 'D':
        case 'd': {
            dx += 5;
            call_func(new_ABC, ABCD, centerX, centerY, centerZ, hwnd);
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        }
        case 'Z':
        case 'z': {
            dz -= 5;
            call_func(new_ABC, ABCD, centerX, centerY, centerZ, hwnd);
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        }
        case 'X':
        case 'x': {
            dz += 5;
            call_func(new_ABC, ABCD, centerX, centerY, centerZ, hwnd);
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        }
        case 'Q':
        case 'q': {
            angX -= 0.05;
            call_func(new_ABC, ABCD, centerX, centerY, centerZ, hwnd);
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        }
        case 'E':
        case 'e': {
            angX += 0.05;
            call_func(new_ABC, ABCD, centerX, centerY, centerZ, hwnd);
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        }
        case 'U':
        case 'u': {
            angY -= 0.05;
            call_func(new_ABC, ABCD, centerX, centerY, centerZ, hwnd);
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        }
        case 'I':
        case 'i': {
            angY += 0.05;
            call_func(new_ABC, ABCD, centerX, centerY, centerZ, hwnd);
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        }
        case 'K':
        case 'k': {
            angZ -= 0.05;
            call_func(new_ABC, ABCD, centerX, centerY, centerZ, hwnd);
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        }
        case 'L':
        case 'l': {
            angZ += 0.05;
            call_func(new_ABC, ABCD, centerX, centerY, centerZ, hwnd);
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        }
        case 'V':
        case 'v': {
            if (S > 0) {
                S -= 0.01;
            }
            call_func(new_ABC, ABCD, centerX, centerY, centerZ, hwnd);
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        }
        case 'B':
        case 'b': {
            S += 0.01;
            call_func(new_ABC, ABCD, centerX, centerY, centerZ, hwnd);
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
int main() {
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
void move(float new[4][4], float ABCD[4][4]) {
    int cnt = 0; //счетчик
    float out[4][4] = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }; //выходной массив с новыми значениями

    float MATRIX_1[4][4] = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {dx, dy, dz, 1}
    };//матрица смещения

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            out[i][j] = 0;
            for (int k = 0; k < 4; k++) {
                out[i][j] += ABCD[i][k] * MATRIX_1[k][j];
            }
            new[i][j] = out[i][j]; // Копируем в матрицу new для дальнейшего использования данных в других функциях
        }
}


//функция углового поворота по оси x
void rotateX(float new[4][4], float ABCD[4][4], float centerX, float centerY, float centerZ)
{
    int cnt = 0; //счетчик
    float out[4][4] = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }; //выходной массив с новыми значениями
    float matrix_translate[4][4] = {
            {1, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 1, 0},
            {-centerX, -centerY, -centerZ, 1}
    };//матрица для переноса точек к началу координат
    float MATRIX_2[4][4] = {
        {1, 0, 0, 0},
        {0, cos(angX), -sin(angX), 0},
        {0, sin(angX), cos(angX), 0},
        {0, 0, 0, 1}
    }; //матрица углового поворота
    float matrix_translate_back[4][4] = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {centerX, centerY, centerZ, 1}
    }; //матрица для переноса точек обратно после вращения
    float tmp[4][4] = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }; //массив для промежуточных вычислений
    //перенос
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            out[i][j] = 0;
            for (int k = 0; k < 4; k++) {
                out[i][j] += ABCD[i][k] * matrix_translate[k][j];
            }
        }
    //поворот
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            tmp[i][j] = 0;
            for (int k = 0; k < 4; k++) {
                tmp[i][j] += out[i][k] * MATRIX_2[k][j];
            }
        }
    //обратный перенос
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            new[i][j] = 0;
            for (int k = 0; k < 4; k++) {
                new[i][j] += tmp[i][k] * matrix_translate_back[k][j];
            }
        }
}

//функция углового поворота по оси y
void rotateY(float new[4][4], float ABCD[4][4], float centerX, float centerY, float centerZ)
{
    int cnt = 0; //счетчик
    float out[4][4] = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }; //выходной массив с новыми значениями
    float matrix_translate[4][4] = {
            {1, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 1, 0},
            {-centerX, -centerY, -centerZ, 1}
    };//матрица для переноса точек к началу координат
    float MATRIX_2[4][4] = {
        {cos(angY), 0, sin(angY), 0},
        {0, 1, 0, 0},
        {-sin(angY), 0, cos(angY), 0},
        {0, 0, 0, 1}
    };//матрица углового поворота
    float matrix_translate_back[4][4] = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {centerX, centerY, centerZ, 1}
    }; //матрица для переноса точек обратно после вращения
    float tmp[4][4] = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }; //массив для промежуточных вычислений
    //перенос
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            out[i][j] = 0;
            for (int k = 0; k < 4; k++) {
                out[i][j] += ABCD[i][k] * matrix_translate[k][j];
            }
        }
    //поворот
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            tmp[i][j] = 0;
            for (int k = 0; k < 4; k++) {
                tmp[i][j] += out[i][k] * MATRIX_2[k][j];
            }
        }
    //обратный перенос
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            new[i][j] = 0;
            for (int k = 0; k < 4; k++) {
                new[i][j] += tmp[i][k] * matrix_translate_back[k][j];
            }
        }
}

//функция углового поворота по оси x
void rotateZ(float new[4][4], float ABCD[4][4], float centerX, float centerY, float centerZ)
{
    int cnt = 0; //счетчик
    float out[4][4] = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }; //выходной массив с новыми значениями
    float matrix_translate[4][4] = {
            {1, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 1, 0},
            {-centerX, -centerY, -centerZ, 1}
    };//матрица для переноса точек к началу координат
    float MATRIX_2[4][4] = {
        {cos(angZ), -sin(angZ), 0, 0},
        {sin(angZ), cos(angZ), 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    }; //матрица углового поворота
    float matrix_translate_back[4][4] = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {centerX, centerY, centerZ, 1}
    }; //матрица для переноса точек обратно после вращения
    float tmp[4][4] = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }; //массив для промежуточных вычислений
    //перенос
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            out[i][j] = 0;
            for (int k = 0; k < 4; k++) {
                out[i][j] += ABCD[i][k] * matrix_translate[k][j];
            }
        }
    //поворот
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            tmp[i][j] = 0;
            for (int k = 0; k < 4; k++) {
                tmp[i][j] += out[i][k] * MATRIX_2[k][j];
            }
        }
    //обратный перенос
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            new[i][j] = 0;
            for (int k = 0; k < 4; k++) {
                new[i][j] += tmp[i][k] * matrix_translate_back[k][j];
            }
        }
}


//фукнкция масштабирования
void scale(float new[4][4], float current[4][4], float centerX, float centerY, float centerZ) {
    int cnt = 0;
    float out[4][4] = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };//выходной массив с новыми значениями
    float matrix_translate[4][4] = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {-centerX, -centerY, -centerZ, 1}
    };
    float matrix_scale[4][4] = {
        {S, 0, 0, 0},
        {0, S, 0, 0},
        {0, 0, S, 0},
        {0, 0, 0, 1}
    };
    float matrix_translate_back[4][4] = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {centerX, centerY, centerZ, 1}
    };
    float tmp[4][4] = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }; //массив для промежуточных вычислений

    // Перевод в начало координат
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) {
            out[i][j] = 0;
            for (int k = 0; k < 4; k++) {
                out[i][j] += current[i][k] * matrix_translate[k][j];
            }
        }

    // Масштабирование
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) {
            tmp[i][j] = 0;
            for (int k = 0; k < 4; k++) {
                tmp[i][j] += out[i][k] * matrix_scale[k][j];
            }
        }

    // Возвращение обратно
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) {
            new[i][j] = 0;
            for (int k = 0; k < 4; k++) {
                new[i][j] += tmp[i][k] * matrix_translate_back[k][j];
            }
        }
}

//функции для нахождения точек центра масс
float CenterX(float new_ABC[4][4])
{
    float centerX = (new_ABC[0][0] + new_ABC[1][0] + new_ABC[2][0] + new_ABC[3][0]) / 4.0;
    return centerX;
}

float CenterY(float new_ABC[4][4])
{
    float centerY = (new_ABC[0][1] + new_ABC[1][1] + new_ABC[2][1] + new_ABC[3][1]) / 4.0;
    return centerY;
}

float CenterZ(float new_ABC[4][4]) {
    float centerZ = (new_ABC[0][2] + new_ABC[1][2] + new_ABC[2][2] + new_ABC[3][2]) / 4.0;
    return centerZ;
}

//функция рисования
void win_paint(HWND hwnd, float new_ABC[4][4]) {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    RECT rc;
    GetClientRect(hwnd, &rc);
    FillRect(hdc, &rc, (HBRUSH)GetStockObject(WHITE_BRUSH));

    // Вызываем функции для рисования
    HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

    //матрица кабинетной проекции
    float MATRIX_2[4][4] = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0.5, -0.5, 1, 0},
        {0, 0, 0, 1}
    };

    float new_paint[4][4] = { 0 };

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            new_paint[i][j] = 0;
            for (int k = 0; k < 4; k++) {
                new_paint[i][j] += new_ABC[i][k] * MATRIX_2[k][j];
            }
        }
    }



    MoveToEx(hdc, roundf(new_paint[0][0]), roundf(new_paint[0][1]), NULL);
    LineTo(hdc, roundf(new_paint[1][0]), roundf(new_paint[1][1]));
    LineTo(hdc, roundf(new_paint[2][0]), roundf(new_paint[2][1]));
    LineTo(hdc, roundf(new_paint[0][0]), roundf(new_paint[0][1]));
    LineTo(hdc, roundf(new_paint[3][0]), roundf(new_paint[3][1]));
    LineTo(hdc, roundf(new_paint[1][0]), roundf(new_paint[1][1]));
    MoveToEx(hdc, roundf(new_paint[3][0]), roundf(new_paint[3][1]), NULL);
    LineTo(hdc, roundf(new_paint[2][0]), roundf(new_paint[2][1]));



    SelectObject(hdc, hOldPen);
    DeleteObject(hPen);

    EndPaint(hwnd, &ps);
}

void call_func(float new_ABC[4][4], float ABCD[4][4], float centerX, float centerY, float centerZ, HWND hwnd) {
    move(new_ABC, ABCD);
    centerX = CenterX(new_ABC); //расчитываем координаты нового центра
    centerY = CenterY(new_ABC);
    centerZ = CenterZ(new_ABC);
    rotateX(new_ABC, new_ABC, centerX, centerY, centerZ);
    rotateY(new_ABC, new_ABC, centerX, centerY, centerZ);
    rotateZ(new_ABC, new_ABC, centerX, centerY, centerZ);
    scale(new_ABC, new_ABC, centerX, centerY, centerZ);
    win_paint(hwnd, new_ABC);
}
