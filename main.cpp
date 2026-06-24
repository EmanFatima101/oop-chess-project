#include "piece.h"
#include <iostream>
using namespace std;

// ================= GLOBAL VARIABLES =================
int halfMoveClock = 0;

// ================= MENU =================

void showTitle()
{
    cout << "====================================" << endl;
    cout << "           OOP CHESS GAME          " << endl;
    cout << "====================================" << endl;
}

void showRules()
{
    system("cls");

    cout << "=========== CHESS RULES ===========" << endl;
    cout << "White moves first." << endl;
    cout << "Basic chess rules apply." << endl;
    cout << "Special moves included: Castling, En Passant, Promotion." << endl;

    cout << "\nPress any key..." << endl;
    system("pause");
}

void aboutProject()
{
    system("cls");

    cout << "=========== PROJECT INFO ===========" << endl;
    cout << "OOP Chess Game using C++" << endl;
    cout << "Includes advanced chess mechanics." << endl;

    cout << "\nPress any key..." << endl;
    system("pause");
}

// ================= BOARD CLEANUP =================

void deleteBoard(Piece* board[8][8])
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board[i][j] != nullptr)
            {
                delete board[i][j];
                board[i][j] = nullptr;
            }
        }
    }
}

// ================= MAIN =================

int main()
{
    int choice;

    while (true)
    {
        system("cls");

        showTitle();

        cout << "1. Start Game" << endl;
        cout << "2. Project Info" << endl;
        cout << "3. Rules" << endl;
        cout << "4. Exit" << endl;

        cout << "\nEnter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            Piece* board[8][8] = { nullptr };

            string turn = "white";
            bool gameRunning = true;

            while (gameRunning)
            {
                system("cls");

                cout << "\nTURN: " << turn << endl;

                cout << "\n   A  B  C  D  E  F  G  H" << endl;
                cout << "  -------------------------" << endl;

                for (int i = 0; i < 8; i++)
                {
                    cout << 8 - i << " |";

                    for (int j = 0; j < 8; j++)
                    {
                        if (board[i][j] != nullptr)
                        {
                            if (board[i][j]->getColor() == "white")
                                cout << "W" << board[i][j]->getSymbol() << " ";
                            else
                                cout << "B" << board[i][j]->getSymbol() << " ";
                        }
                        else
                        {
                            cout << ".. ";
                        }
                    }

                    cout << "| " << 8 - i << endl;
                }

                cout << "  -------------------------" << endl;

                string from, to;
                int fromRow, fromCol, toRow, toCol;

                cout << "Enter FROM (e.g. E2): ";
                cin >> from;

                cout << "Enter TO (e.g. E4): ";
                cin >> to;

                // ===== BASIC VALIDATION =====
                if (from.length() != 2 || to.length() != 2)
                {
                    cout << "Invalid input format!" << endl;
                    system("pause");
                    continue;
                }

                fromCol = toupper(from[0]) - 'A';
                fromRow = 8 - (from[1] - '0');
                toCol = toupper(to[0]) - 'A';
                toRow = 8 - (to[1] - '0');

                if (fromRow < 0 || fromRow > 7 || fromCol < 0 || fromCol > 7 ||
                    toRow < 0 || toRow > 7 || toCol < 0 || toCol > 7)
                {
                    cout << "Invalid coordinates!" << endl;
                    system("pause");
                    continue;
                }

                if (board[fromRow][fromCol] == nullptr)
                {
                    cout << "No piece selected!" << endl;
                    system("pause");
                    continue;
                }

                if (board[fromRow][fromCol]->getColor() != turn)
                {
                    cout << "Not your turn!" << endl;
                    system("pause");
                    continue;
                }

                // ===== MOVE VALIDATION =====
                if (board[fromRow][fromCol]->isValid_Move(toRow, toCol, board))
                {
                    board[toRow][toCol] = board[fromRow][fromCol];
                    board[fromRow][fromCol] = nullptr;

                    board[toRow][toCol]->setPosition(toRow, toCol);

                    turn = (turn == "white") ? "black" : "white";
                }
                else
                {
                    cout << "Invalid move!" << endl;
                    system("pause");
                }
            }

            deleteBoard(board);
        }
        else if (choice == 2)
        {
            aboutProject();
        }
        else if (choice == 3)
        {
            showRules();
        }
        else if (choice == 4)
        {
            cout << "Game Closed!" << endl;
            break;
        }
        else
        {
            cout << "Invalid choice!" << endl;
            system("pause");
        }
    }

    return 0;
}
