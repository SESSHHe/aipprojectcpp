#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

using namespace std;

// Функция задержки вывода сообщений пользователю и игрового поля
void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

// Функция отображения игрового поля
void Display(char board[8][8])
{
    system("cls"); // Очистка консоли
    int i;
    // Генерация игрового поля
    for (i = 0; i < 8; i++)
    {
        cout << "  +---+---+---+---+---+---+---+---+" << endl;
        cout << i + 1 << " | " << board[i][0] << " | " << board[i][1] << " | " << board[i][2] << " | " << board[i][3] << " | " << board[i][4] << " | " << board[i][5] << " | " << board[i][6] << " | " << board[i][7] << " |" << endl;
    }
    cout << "  +---+---+---+---+---+---+---+---+" << endl;
    cout << "    A   B   C   D   E   F   G   H  " << endl;
}

// Функция перемещения курсора консоли по координатам
void gotoxy(int m, int n)
{
    COORD c;
    c.X = m;
    c.Y = n;
    // Перемещение курсора на позицию
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

// Реализация логики игры
int main()
{
// Раздел подготовки к игре
intro:
    system("cls"); // Очистка консоли
    int i, j, X, Y, type, user_score, opponent_score, variants_of_moves = 0, limit = 0; // Инициализация переменных
    char board[8][8], A, B, pos[2]; // Инициализация доски
    for (i = 0; i < 8; i++) // Заполнение доски пустыми клеткам
    {
        for (j = 0; j < 8; j++)
            board[i][j] = ' ';
    }
    
    // Приветствие пользователя, выбор символов шашек
    cout << "Enter Your Symbol: ";
    cin >> A;
    cout << "Enter Opponent's Symbol: ";
    cin >> B;
    
    char tick_A = A;
    char tick_B = B;
    
    // Заполнение доски шашками
    board[0][0] = B;    board[0][2] = B;    board[0][4] = B;
    board[0][6] = B;    board[1][1] = B;    board[1][3] = B;
    board[1][5] = B;    board[1][7] = B;    board[2][0] = B;
    board[2][2] = B;    board[2][4] = B;    board[2][6] = B;

    board[5][1] = A;    board[5][3] = A;    board[5][5] = A;
    board[5][7] = A;    board[6][0] = A;    board[6][2] = A;
    board[6][4] = A;    board[6][6] = A;    board[7][1] = A;
    board[7][3] = A;    board[7][5] = A;    board[7][7] = A;

// Реализация хода пользователя
start:
    Display(board); // Вывод доски в консоль
    
    cout << "Your Turn ";
    delay(1000);
    cout << endl
              << "Enter Position: ";
    scanf("%s", pos); // Считывание выбранной позиции шашки
    cout << endl;

    if (pos[0] == 'z' && pos[1] == 'z') // Вспомогательное условие для перехода к концу игры
        goto end;
    
    // Преобразование символов в числа
    if (pos[0] == 'A')
        X = 0;
    else if (pos[0] == 'B')
        X = 1;
    else if (pos[0] == 'C')
        X = 2;
    else if (pos[0] == 'D')
        X = 3;
    else if (pos[0] == 'E')
        X = 4;
    else if (pos[0] == 'F')
        X = 5;
    else if (pos[0] == 'G')
        X = 6;
    else if (pos[0] == 'H')
        X = 7;
    else // Если введенная буква не соответствует алфавиту поля
    {
        cout << "Enter again";
        delay(1000);
        goto start;
    }
    // Преобразование чисел в индексы
    if (pos[1] == '1')
        Y = 0;
    else if (pos[1] == '2')
        Y = 1;
    else if (pos[1] == '3')
        Y = 2;
    else if (pos[1] == '4')
        Y = 3;
    else if (pos[1] == '5')
        Y = 4;
    else if (pos[1] == '6')
        Y = 5;
    else if (pos[1] == '7')
        Y = 6;
    else if (pos[1] == '8')
        Y = 7;
    else // Если введенная цифра не соответствует алфавиту поля
    {
        cout << "Enter again";
        delay(1000);
        goto start;
    }
    if (board[Y][X] != A) // Если введенная позиция не соответствует координатам шашек
    {
        cout << "Enter again";
        delay(1000);
        goto start;
    }
    // Вариация ходов
    cout << "1 (Upper-Left) , 2 (Upper-Right) " << endl;
    cout << "3 (Lower-Left) , 4 (Lower-Right) ";
    cin >> type;

    A = tick_A;
    B = tick_B;

    // Реализация хода Upper-Left
    if (type == 1)
    {
        if (X == 0 || Y == 0)
        {
            cout << "Checker can't move";
            delay(1000);
            goto start;
        }
        
        if (board[Y - 1][X - 1] == A) // Если на позиции стоит союзная шашка
        {
            cout << "Checker can't move";
            delay(1000);
            goto start;
        }

        if (board[Y - 1][X - 1] == ' ') // Если позиция пустая
        {
            board[Y][X] = ' ';
            board[--Y][--X] = A;
            goto transition_to_opponent;
        }

        if (board[Y - 1][X - 1] == B) // Если на позиции стоит вражеская шашка
        {
            if (X <= 1)
            {
                cout << "Checker can't move";
                delay(1000);
                goto start;
            }

            if (board[Y - 2][X - 2] != ' ') // Если место при побитии вражеской шашки не пустое
            {
                cout << "Checker can't move";
                delay(1000);
                goto start;
            }

            else // Реализация побития вражеской шашки
            {
                board[Y][X] = ' ';
                board[Y - 1][X - 1] = ' ';
                Y -= 2;
                X -= 2;
                board[Y][X] = A;
                goto transition_to_opponent;
            }
        }
    }

    // Реализация хода Upper-Right
    if (type == 2)
    {
        if (X == 7 || Y == 0)
        {
            cout << "Checker can't move";
            delay(1000);
            goto start;
        }

        if (board[Y - 1][X + 1] == A)
        {
            cout << "Checker can't move";
            delay(1000);
            goto start;
        }

        if (board[Y - 1][X + 1] == ' ')
        {
            board[Y][X] = ' ';
            board[--Y][++X] = A;
            goto transition_to_opponent;
        }

        if (board[Y - 1][X + 1] == B)
        {
            if (X >= 6)
            {
                cout << "Checker can't move";
                delay(1000);
                goto start;
            }

            if (board[Y - 2][X + 2] != ' ')
            {
                cout << "Checker can't move";
                delay(1000);
                goto start;
            }

            else
            {
                board[Y][X] = ' ';
                board[Y - 1][X + 1] = ' ';
                Y -= 2;
                X += 2;
                board[Y][X] = A;
                goto transition_to_opponent;
            }
        }
    }

    // Реализация хода Down-Left
    if (type == 3)
    {
        if (X == 0 || Y == 7)
        {
            cout << "Checker can't move";
            delay(1000);
            goto start;
        }

        if (board[Y + 1][X - 1] == A)
        {
            cout << "Checker can't move";
            delay(1000);
            goto start;
        }

        if (board[Y + 1][X - 1] == ' ')
        {
            board[Y][X] = ' ';
            board[++Y][--X] = A;
            goto transition_to_opponent;
        }

        if (board[Y + 1][X - 1] == B)
        {
            if (X <= 1)
            {
                cout << "Checker can't move";
                delay(1000);
                goto start;
            }

            if (board[Y + 2][X - 2] != ' ')
            {
                cout << "Checker can't move";
                delay(1000);
                goto start;
            }

            else
            {
                board[Y][X] = ' ';
                board[Y + 1][X - 1] = ' ';
                Y += 2;
                X -= 2;
                board[Y][X] = A;
                goto transition_to_opponent;
            }
        }
    }

    // Реализация хода Down-Right
    if (type == 4)
    {
        if (X == 7 || Y == 7)
        {
            cout << "Checker can't move";
            delay(1000);
            goto start;
        }

        if (board[Y + 1][X + 1] == A)
        {
            cout << "Checker can't move";
            delay(1000);
            goto start;
        }

        if (board[Y + 1][X + 1] == ' ')
        {
            board[Y][X] = ' ';
            board[++Y][++X] = A;
            goto transition_to_opponent;
        }

        if (board[Y + 1][X + 1] == B)
        {
            if (X >= 6)
            {
                cout << "Checker can't move";
                delay(1000);
                goto start;
            }

            if (board[Y + 2][X + 2] != ' ')
            {
                cout << "Checker can't move";
                delay(1000);
                goto start;
            }

            else
            {
                board[Y][X] = ' ';
                board[Y + 1][X + 1] = ' ';
                Y += 2;
                X += 2;
                board[Y][X] = A;
                goto transition_to_opponent;
            }
        }
    }

// Раздел реализации подсчёта очков после успешного хода пользователя и переход к ходу компьютера
transition_to_opponent:
    Display(board); // Вывод поля на дисплей
    delay(1000);

    // Инициализация очков пользователя и компьютера
    user_score = 0;
    opponent_score = 0;

    A = tick_A;
    B = tick_B;

    // Увлечение количества очков пользователя
    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 8; j++)
        {
            if (board[i][j] == A)
                user_score++;
        }
    }

    // Увеличение количества очков компьютера
    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 8; j++)
        {
            if (board[i][j] == B)
                opponent_score++;
        }
    }

    if (user_score == 0 || opponent_score == 0)
        goto end;

    // Ход компьютера
    cout << endl
              << "Opponent's Turn";
    delay(1000);

// Раздел подбора ходов компьютера
again:
    if (limit == 15) // Если не подобрался вариант хода
    {
        cout << endl
                  << "The Opponent Couldn't Go";
        limit = 0;
        delay(1000);
        goto start;
    }

    if (variants_of_moves == 15) // Контроль потока выполнения программы, если на возможном ходу стоит шашка, то увеличение лимита
    {
        for (i = 0; i < 8; i++)
        {
            for (j = 0; j < 8; j++)
            {
                if (board[i][j] == B)
                {
                    Y = i;
                    X = j;
                }
            }
        }
        variants_of_moves = 0;
        limit++;
    }

    else // Рандомные координаты хода
    {
        Y = rand() % 8;
        X = rand() % 8;
    }

    if (board[Y][X] != B)
        goto again;
    
    type = rand() % (4) + 1; // Рандомное направление хода
    // Выбор направления хода компьютера
    if (board[Y - 1][X - 1] == A && X > 1 && Y > 1)
        type = 1;
    if (board[Y - 1][X + 1] == A && X < 6 && Y > 1)
        type = 2;
    if (board[Y + 1][X - 1] == A && X > 1 && Y < 6)
        type = 3;
    if (board[Y + 1][X + 1] == A && X < 6 && Y < 6)
        type = 4;

    A = tick_A;
    B = tick_B;

    // Реализация хода Upper-Left
    if (type == 1)
    {
        if (X == 0 || Y == 0)
        {
            variants_of_moves++;
            goto again;
        }

        if (board[Y - 1][X - 1] == B)
        {
            variants_of_moves++;
            goto again;
        }

        if (board[Y - 1][X - 1] == ' ')
        {
            board[Y][X] = ' ';
            board[--Y][--X] = B;
            goto transition_to_user;
        }

        if (board[Y - 1][X - 1] == A)
        {
            if (X >= 1)
            {
                variants_of_moves++;
                goto again;
            }

            if (board[Y - 2][X - 2] != ' ')
            {
                variants_of_moves++;
                goto again;
            }

            else
            {
                board[Y][X] = ' ';
                board[Y - 1][X - 1] = ' ';
                Y -= 2;
                X -= 2;
                board[Y][X] = B;
                goto transition_to_user;
            }
        }
    }

    // Реализация хода Upper-Right
    if (type == 2)
    {
        if (X == 7 || Y == 0)
        {
            variants_of_moves++;
            goto again;
        }

        if (board[Y - 1][X + 1] == B)
        {
            variants_of_moves++;
            goto again;
        }

        if (board[Y - 1][X + 1] == ' ')
        {
            board[Y][X] = ' ';
            board[--Y][++X] = B;
            goto transition_to_user;
        }

        if (board[Y - 1][X + 1] == A)
        {
            if (X >= 6)
            {
                variants_of_moves++;
                goto again;
            }
            
            if (board[Y - 2][X + 2] != ' ')
            {
                variants_of_moves++;
                goto again;
            }

            else
            {
                board[Y][X] = ' ';
                board[Y - 1][X + 1] = ' ';
                Y -= 2;
                X += 2;
                board[Y][X] = B;
                goto transition_to_user;
            }
        }
    }

    // Реализация хода Down-Left
    if (type == 3)
    {
        if (X == 0 || Y == 7)
        {
            variants_of_moves++;
            goto again;
        }

        if (board[Y + 1][X - 1] == B)
        {
            variants_of_moves++;
            goto again;
        }

        if (board[Y + 1][X - 1] == ' ')
        {
            board[Y][X] = ' ';
            board[++Y][--X] = B;
            goto transition_to_user;
        }

        if (board[Y + 1][X - 1] == A)
        {
            if (X >= 1)
            {
                variants_of_moves++;
                goto again;
            }

            if (board[Y + 2][X - 2] != ' ')
            {
                variants_of_moves++;
                goto again;
            }

            else
            {
                board[Y][X] = ' ';
                board[Y + 1][X - 1] = ' ';
                Y += 2;
                X -= 2;
                board[Y][X] = B;
                goto transition_to_user;
            }
        }
    }

    // Реализация хода Down-Right
    if (type == 4)
    {
        if (X == 7 || Y == 7)
        {
            variants_of_moves++;
            goto again;
        }

        if (board[Y + 1][X + 1] == B)
        {
            variants_of_moves++;
            goto again;
        }

        if (board[Y + 1][X + 1] == ' ')
        {
            board[Y][X] = ' ';
            board[++Y][++X] = B;
            goto transition_to_user;
        }

        if (board[Y + 1][X + 1] == A)
        {
            if (X >= 6)
            {
                variants_of_moves++;
                goto again;
            }

            if (board[Y + 2][X + 2] != ' ')
            {
                variants_of_moves++;
                goto again;
            }

            else
            {
                board[Y][X] = ' ';
                board[Y + 1][X + 1] = ' ';
                Y += 2;
                X += 2;
                board[Y][X] = B;
                goto transition_to_user;
            }
        }
    }

// Раздел реализации подсчёта очков после успешного хода компьютера и переход к ходу пользователя 
transition_to_user:
    Display(board); // Вывод доски на консоль
    delay(1000);
    // Инициализация очков игроков
    user_score = 0;
    opponent_score = 0;

    A = tick_A;
    B = tick_B;
    // Увеличение очков пользователя
    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 8; j++)
        {
            if (board[i][j] == A)
                user_score++;
        }
    }
    // Увеличение очков компьютера
    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 8; j++)
        {
            if (board[i][j] == B)
                opponent_score++;
        }
    }
    if (user_score == 0 || opponent_score == 0)
        goto end;
    else
        goto start;

// Раздел завершения игры
end:
    system("cls"); // Очистка консоли

    if (user_score > opponent_score) // Если количество очков пользователя больше, чем компьютера
    {
        delay(2000);
        gotoxy(30, 10);
        cout << "YOU WON!";
    }

    if (user_score < opponent_score) // Если количество очков компьютера больше, чем пользователя
    {
        delay(2000);
        gotoxy(30, 10);
        cout << "YOU LOSE!";
    }

    if (user_score == opponent_score) // Если количество очков одинаково
    {
        delay(2000);
        gotoxy(30, 10);
        cout << "DRAW!";
    }

    system("pause");
}