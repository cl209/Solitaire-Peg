// UMBC - CMSC 341 - Fall 2024 - Proj0
    #include "solitaire.h"

    Solitaire::Solitaire() {
        //Default values
        m_numRows = 0;
        m_numColumns = 0;
        m_numMarbles = 0;
        m_shape = NONE;
        m_board = nullptr;
    }

    Solitaire::Solitaire(BOARDSHAPE board) {

        //Check for the input for the board shape
        if (board == DIAMOND) {
            m_numRows = DIAMONDSIZE;
            m_numColumns = DIAMONDSIZE;
            m_shape = DIAMOND;
            m_numMarbles = NUMDIAMONDMARBLES;

            //Allocate memory for the board
            m_board = new int*[m_numRows];
            for (int i = 0; i < m_numRows; i++) {
                m_board[i] = new int[m_numColumns];
            }
            for (int i = 0; i < m_numRows; ++i) {
                for (int j = 0; j < m_numColumns; ++j) {
                    if ((i == 0 && j <= 3) || (i == 0 && j >= 5) ||
                        (i == 1 && j <= 2) || (i == 1 && j >= 6) ||
                        (i == 2 && j <= 1) || (i == 2 && j >= 7) ||
                        (i == 3 && j <= 0) || (i == 3 && j >= 8) ||
                        (i == 5 && j < 1) || (i == 5 && j >= 8) ||
                        (i == 6 && j < 2) || (i == 6 && j >= 7) ||
                        (i == 7 && j < 3) || (i == 7 && j >= 6) ||
                        (i == 8 && j < 4) || (i == 8 && j >= 5)) {
                        m_board[i][j] = OUT;
                    } else if (i == 4 && j == 4) {
                        m_board[i][j] = HOLE;
                    } else {
                        m_board[i][j] = MARBLE;
                    }
                }
            }
        } else if (board == ENGLISH) {
            m_numRows = ENGLISHSIZE;
            m_numColumns = ENGLISHSIZE;
            m_shape = ENGLISH;
            m_numMarbles = NUMENGLISHMARBLES;

            m_board = new int*[m_numRows];
            for (int i = 0; i < m_numRows; i++) {
                m_board[i] = new int[m_numColumns];
            }
            for (int i = 0; i < m_numRows; ++i) {
                for (int j = 0; j < m_numColumns; ++j) {
                    if ((i <= 1 && j <= 1) || (i <= 1 && j >= 5) ||
                        (i >= 5 && j <= 1) || (i >= 5 && j >= 5)) {
                        m_board[i][j] = OUT;
                    } else if (i == 3 && j == 3) {
                        m_board[i][j] = HOLE;
                    } else {
                        m_board[i][j] = MARBLE;
                    }
                }
            }
        } else {
            m_numRows = 0;
            m_numColumns = 0;
            m_numMarbles = 0;
            m_shape = NONE;
            m_board = nullptr;
        }
    }

    Solitaire::Solitaire(const Solitaire &rhs) {
        //Check if board is empty
        if (rhs.m_board == nullptr) {
            m_board = nullptr;
            return;
        }
        //Copy the board
        m_numRows = rhs.m_numRows;
        m_numColumns = rhs.m_numColumns;
        m_numMarbles = rhs.m_numMarbles;
        m_shape = rhs.m_shape;

        //Allocate new memeory for the new board
        m_board = new int*[m_numRows];
        for (int i = 0; i < m_numRows; i++) {
            m_board[i] = new int[m_numColumns];
        }

        for (int i = 0; i < m_numRows; i++) {
            for (int j = 0; j < m_numColumns; j++)
                m_board[i][j] = rhs.m_board[i][j];
        }
    }

    Solitaire::~Solitaire() {
        //Delete memeory by row
        for (int i = 0; i < m_numRows; i++) {
            delete[] m_board[i];
            m_board[i] = nullptr;
        }
        //Delete m_board memeory allocation
        delete[] m_board;
        m_board = nullptr;
    }

    void Solitaire::clear() {
        //Delete memeory by row
        for (int i = 0; i < m_numRows; i++) {
            delete[] m_board[i];
            m_board[i] = nullptr;
        }
        //Delete m_board memeory allocation
        delete[] m_board;
        m_board = nullptr;

        //Reinitialize variables to default
        m_numRows = 0;
        m_numColumns = 0;
        m_numMarbles = 0;
        m_shape = NONE;
    }

    bool Solitaire::play(pair<int, int> origin, pair<int, int> destination) {
        //Initialize int origin and destination
        int origin_x = origin.first, origin_y = origin.second;
        int dest_x = destination.first, dest_y = destination.second;

        //Check if the origin or destination are out of bounds
        if (m_shape == DIAMOND) {
            if ((origin_x == 0 && (origin_y <= 3 || origin_y >= 5)) ||
                (origin_x == 1 && (origin_y <= 2 || origin_y >= 6)) ||
                (origin_x == 2 && (origin_y <= 1 || origin_y >= 7)) ||
                (origin_x == 3 && (origin_y <= 0 || origin_y >= 8)) ||
                (origin_x == 5 && (origin_y < 1 || origin_y >= 8)) ||
                (origin_x == 6 && (origin_y < 2 || origin_y >= 7)) ||
                (origin_x == 7 && (origin_y < 3 || origin_y >= 6)) ||
                (origin_x == 8 && (origin_y < 4 || origin_y >= 5)) ||
                (dest_x == 0 && (dest_y <= 3 || dest_y >= 5)) ||
                (dest_x == 1 && (dest_y <= 2 || dest_y >= 6)) ||
                (dest_x == 2 && (dest_y <= 1 || dest_y >= 7)) ||
                (dest_x == 3 && (dest_y <= 0 || dest_y >= 8)) ||
                (dest_x == 5 && (dest_y < 1 || dest_y >= 8)) ||
                (dest_x == 6 && (dest_y < 2 || dest_y >= 7)) ||
                (dest_x == 7 && (dest_y < 3 || dest_y >= 6)) ||
                (dest_x == 8 && (dest_y < 4 || dest_y >= 5))) {
                return false;
            }
        } else if (m_shape == ENGLISH) {
            if ((origin_x <= 1 && origin_y <= 1) ||
                (origin_x <= 1 && origin_y >= 5) ||
                (origin_x >= 5 && origin_y <= 1) ||
                (origin_x >= 5 && origin_y >= 5) ||
                (dest_x <= 1 && dest_y <= 1) ||
                (dest_x <= 1 && dest_y >= 5) ||
                (dest_x >= 5 && dest_y <= 1) ||
                (dest_x >= 5 && dest_y >= 5)) {
                return false;
            }
        }

        //Check if the origin has a marble
        if (m_board[origin_x][origin_y] != MARBLE) {
            return false;
        }

        //Check if the destination has a hole
        if (m_board[dest_x][dest_y] != HOLE) {
            return false;
        }
        
        //Check if its a valid move for the horizontal
        if (origin_x == dest_x && abs(origin_y - dest_y) == 2) {
            //Make the move
            m_board[origin_x][origin_y] = HOLE;
            if (origin_y - dest_y > 0) {
                m_board[origin_x][origin_y - 1] = HOLE;
            } else {
                m_board[origin_x][origin_y + 1] = HOLE;
            }
            m_board[dest_x][dest_y] = MARBLE;

        //Check if its a valid move for the vertical
        } else if (origin_y == dest_y && abs(origin_x - dest_x) == 2) {
            //Make the move
            m_board[origin_x][origin_y] = HOLE;
            if (origin_x - dest_x > 0) {
                m_board[origin_x - 1][origin_y] = HOLE;
            } else {
                m_board[origin_x + 1][origin_y] = HOLE;
            }
            m_board[dest_x][dest_y] = MARBLE;
        } else {
            return false;
        }

        return true;
    }

    void Solitaire::changeBoard(BOARDSHAPE board) {
        clear();

        //Check if the asking shape is the same, then only reinitialize
        if (board == m_shape) {
            if (m_shape == DIAMOND) {
                m_numRows = DIAMONDSIZE;
                m_numColumns = DIAMONDSIZE;
                m_numMarbles = NUMDIAMONDMARBLES;
                for (int i = 0; i < m_numRows; ++i) {
                    for (int j = 0; j < m_numColumns; ++j) {
                        if ((i == 0 && j <= 3) || (i == 0 && j >= 5) ||
                            (i == 1 && j <= 2) || (i == 1 && j >= 6) ||
                            (i == 2 && j <= 1) || (i == 2 && j >= 7) ||
                            (i == 3 && j <= 0) || (i == 3 && j >= 8) ||
                            (i == 5 && j < 1) || (i == 5 && j >= 8) ||
                            (i == 6 && j < 2) || (i == 6 && j >= 7) ||
                            (i == 7 && j < 3) || (i == 7 && j >= 6) ||
                            (i == 8 && j < 4) || (i == 8 && j >= 5)) {
                            m_board[i][j] = OUT;
                        } else if (i == 4 && j == 4) {
                            m_board[i][j] = HOLE;
                        } else {
                            m_board[i][j] = MARBLE;
                        }
                    }
                }
            } else if (m_shape == ENGLISH) {
                m_numRows = ENGLISHSIZE;
                m_numColumns = ENGLISHSIZE;
                m_numMarbles = NUMENGLISHMARBLES;
                for (int i = 0; i < m_numRows; ++i) {
                    for (int j = 0; j < m_numColumns; ++j) {
                        if ((i <= 1 && j <= 1) || (i <= 1 && j >= 5) ||
                            (i >= 5 && j <= 1) || (i >= 5 && j >= 5)) {
                            m_board[i][j] = OUT;
                        } else if (i == 3 && j == 3) {
                            m_board[i][j] = HOLE;
                        } else {
                            m_board[i][j] = MARBLE;
                        }
                    }
                }
            }
        } else {
            //The asking shape is different
            if (board == DIAMOND) {
                m_numRows = DIAMONDSIZE;
                m_numColumns = DIAMONDSIZE;
                m_shape = DIAMOND;
                m_numMarbles = NUMDIAMONDMARBLES;

                //Create new allocated memeory for the different board
                m_board = new int*[m_numRows];
                for (int i = 0; i < m_numRows; i++) {
                    m_board[i] = new int[m_numColumns];
                }

                for (int i = 0; i < m_numRows; ++i) {
                    for (int j = 0; j < m_numColumns; ++j) {
                        if ((i == 0 && j <= 3) || (i == 0 && j >= 5) ||
                            (i == 1 && j <= 2) || (i == 1 && j >= 6) ||
                            (i == 2 && j <= 1) || (i == 2 && j >= 7) ||
                            (i == 3 && j <= 0) || (i == 3 && j >= 8) ||
                            (i == 5 && j < 1) || (i == 5 && j >= 8) ||
                            (i == 6 && j < 2) || (i == 6 && j >= 7) ||
                            (i == 7 && j < 3) || (i == 7 && j >= 6) ||
                            (i == 8 && j < 4) || (i == 8 && j >= 5)) {
                            m_board[i][j] = OUT;
                        } else if (i == 4 && j == 4) {
                            m_board[i][j] = HOLE;
                        } else {
                            m_board[i][j] = MARBLE;
                        }
                    }
                }
            } else if (board == ENGLISH) {
                m_numRows = ENGLISHSIZE;
                m_numColumns = ENGLISHSIZE;
                m_shape = ENGLISH;
                m_numMarbles = NUMENGLISHMARBLES;

                //Create new allocated memeory for the different board
                m_board = new int*[m_numRows];
                for (int i = 0; i < m_numRows; i++) {
                    m_board[i] = new int[m_numColumns];
                }

                for (int i = 0; i < m_numRows; ++i) {
                    for (int j = 0; j < m_numColumns; ++j) {
                        if ((i <= 1 && j <= 1) || (i <= 1 && j >= 5) ||
                            (i >= 5 && j <= 1) || (i >= 5 && j >= 5)) {
                            m_board[i][j] = OUT;
                        } else if (i == 3 && j == 3) {
                            m_board[i][j] = HOLE;
                        } else {
                            m_board[i][j] = MARBLE;
                        }
                    }
                }
            }
        }
    }

bool Solitaire::newBoard() {
    // Checks if board is empty or not
    if (m_board != nullptr){
        clear();
        changeBoard(m_shape);
        return true;
    } else {
        return false;
    }

}

void Solitaire::dumpBoard(){
    // this is to facilitate debugging 
    cout << "  ";
    for (int k=0;k<m_numColumns;k++){
        cout << k << " ";
    }
    cout << endl;
    for (int i=1;i <= m_numRows;i++){
        cout << i-1 << " ";
        for (int j=1;j<=m_numColumns;j++){
            if (m_board[i-1][j-1] == OUT)
                cout << "  ";
            else if (m_board[i-1][j-1] == HOLE)
                cout << BLACKSTAR;
            else
                cout << REDSTAR;
        }
        cout << endl;
    }
    cout << endl;
}
int Solitaire::reportNumMarbles(){
    // this is to facilitate debugging 
    cout << "You have " << m_numMarbles << " marbles to remove!" << endl;
    return m_numMarbles;
}