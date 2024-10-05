#include "solitaire.h"
using namespace std;

class Tester {
  public:
    bool errBoardShapeTest();
    bool normBoardShapeTest();
    bool errNewBoardTest();
    bool normNewBoardTest();
    bool normChangeBoardTest();
    bool norm2ChangeBoardTest();
    bool normPlayTest();
    bool errPlayTest();
    bool errDeepCopyTest();
    bool normDeepCopyTest();

};

// Error constructor test
bool Tester::errBoardShapeTest() {
    Solitaire obj(FRENCH);
    // Check if the obj is French or None or any other unsupported boardshape
    if (obj.m_shape != DIAMOND && obj.m_shape != ENGLISH) {
        if (obj.m_shape == NONE && obj.m_numRows == 0 && obj.m_numColumns == 0 && obj.m_board == nullptr) {
            return true;
        } else {
            return false;
        }    
    }
    // Error test does not apply
    return false;
}

// Normal constructor test
bool Tester::normBoardShapeTest() {
    Solitaire obj(DIAMOND);
    if (obj.m_shape == DIAMOND) {
        if (obj.m_numRows == DIAMONDSIZE && obj.m_numColumns == DIAMONDSIZE 
            && obj.m_numMarbles == NUMDIAMONDMARBLES) {
            return true;
        }
    } else if (obj.m_shape == ENGLISH) {
        if (obj.m_numRows == ENGLISHSIZE && obj.m_numColumns == ENGLISHSIZE
            && obj.m_numMarbles == NUMENGLISHMARBLES) {
            return true;
        }
    } else {
        return false;
    }
    // Error test does not apply
    return false;
}

// Error test for newBoard
bool Tester::errNewBoardTest() {
    Solitaire obj(FRENCH);
    if (obj.m_board != nullptr) {
        obj.clear();
    }
    bool result = obj.newBoard();
    if (result == false) {
        return true;
    }
    return false;
}

bool Tester::normNewBoardTest() {
    Solitaire obj(DIAMOND);
    
    //Change the board shape
    if (obj.m_shape == DIAMOND) {
        obj.changeBoard(ENGLISH);

        //Check default values
        if (obj.m_shape == ENGLISH &&
            obj.m_numRows == ENGLISHSIZE &&
            obj.m_numColumns == ENGLISHSIZE &&
            obj.m_numMarbles == NUMENGLISHMARBLES) {
            return true;
        }
        return false;
    }
    return false;
}



// Normal test for changeBoard, same shape
bool Tester::normChangeBoardTest() {
    Solitaire obj(DIAMOND);
    for (int i = 0; i < DIAMONDSIZE; i++) {
        for (int j = 0; j < DIAMONDSIZE; j++) {
            if ((i == 0 && j <= 3) || (i == 0 && j >= 5) ||
                (i == 1 && j <= 2) || (i == 1 && j >= 6) ||
                (i == 2 && j <= 1) || (i == 2 && j >= 7) ||
                (i == 3 && j <= 0) || (i == 3 && j >= 8) ||
                (i == 5 && j < 1) || (i == 5 && j >= 8) ||
                (i == 6 && j < 2) || (i == 6 && j >= 7) ||
                (i == 7 && j < 3) || (i == 7 && j >= 6) ||
                (i == 8 && j < 4) || (i == 8 && j >= 5)) {
                if (obj.m_board[i][j] != OUT) {
                    return false;
                }
            } 
            // Check for hole
            else if (i == 4 && j == 4) {
                if (obj.m_board[i][j] != HOLE) {
                    return false; 
                }
            } 
            // Check for marbles
            else {
                if (obj.m_board[i][j] != MARBLE) {
                    return false; 
                }
            }
        }
    }
    return true;
}

// Normal test for changeBoard, different shape
bool Tester::norm2ChangeBoardTest() {
    // Change the board to a new shape
    Solitaire obj(DIAMOND);
    obj.changeBoard(ENGLISH);

    // Now check if the board is correctly initialized to the new shape
    if (obj.m_shape == DIAMOND) {
        // Check DIAMOND shape board initialization
        for (int i = 0; i < DIAMONDSIZE; i++) {
            for (int j = 0; j < DIAMONDSIZE; j++) {
                if ((i == 0 && j <= 3) || (i == 0 && j >= 5) ||
                    (i == 1 && j <= 2) || (i == 1 && j >= 6) ||
                    (i == 2 && j <= 1) || (i == 2 && j >= 7) ||
                    (i == 3 && j <= 0) || (i == 3 && j >= 8) ||
                    (i == 5 && j < 1) || (i == 5 && j >= 8) ||
                    (i == 6 && j < 2) || (i == 6 && j >= 7) ||
                    (i == 7 && j < 3) || (i == 7 && j >= 6) ||
                    (i == 8 && j < 4) || (i == 8 && j >= 5)) {
                    if (obj.m_board[i][j] != OUT) {
                        return false; // Incorrect OUT value
                    }
                } 
                // Check for the center HOLE
                else if (i == 4 && j == 4) {
                    if (obj.m_board[i][j] != HOLE) {
                        return false; // Incorrect HOLE value
                    }
                } 
                // Check for marbles
                else {
                    if (obj.m_board[i][j] != MARBLE) {
                        return false; 
                    }
                }
            }
        }
    } 
    else if (obj.m_shape == ENGLISH) {
        // Check english shape board
        for (int i = 0; i < ENGLISHSIZE; i++) {
            for (int j = 0; j < ENGLISHSIZE; j++) {
                if ((i <= 1 && j <= 1) || (i <= 1 && j >= 5) ||
                    (i >= 5 && j <= 1) || (i >= 5 && j >= 5)) {
                    if (obj.m_board[i][j] != OUT) {
                        return false;
                    }
                } 
                // Check for hole
                else if (i == 3 && j == 3) {
                    if (obj.m_board[i][j] != HOLE) {
                        return false;
                    }
                } 
                // Check for marbles
                else {
                    if (obj.m_board[i][j] != MARBLE) {
                        return false;
                    }
                }
            }
        }
    } 
    else {
        return false;
    }
    return true;
}

bool Tester::normPlayTest(){
    Solitaire obj(DIAMOND);
    //Checker for play move
    bool result = false;
    //Check for shape
    if (obj.m_shape == DIAMOND){
        result = obj.play(pair<int,int>(6,4), pair<int,int>(4,4));
    } else if (obj.m_shape == ENGLISH){
        result = obj.play(pair<int,int>(3,5), pair<int,int>(3,3));
    }
    if (!result){
        return false;
    }
    return true;
}
bool Tester::errPlayTest(){
    Solitaire obj(DIAMOND);
    // Test invalid moves for both Diamond and English shapes
    if (obj.m_shape == DIAMOND) {
        //Return opposite since play funct returns false
        return !obj.play(pair<int, int>(0, 1), pair<int, int>(1, 0));
    } else if (obj.m_shape == ENGLISH) {
        return !obj.play(pair<int, int>(1, 0), pair<int, int>(1, 0));
    }
    //Else return false
    return false;
}
    


// Check for deep copy, empty object
bool Tester::errDeepCopyTest() {
    Solitaire obj(FRENCH); 
    Solitaire copy(obj);

    if (obj.m_numColumns != copy.m_numColumns ||
        obj.m_numRows != copy.m_numRows ||
        obj.m_shape != copy.m_shape ||
        obj.m_numMarbles != copy.m_numMarbles) {
        return false;
    }

    // Ensure both boards are nullptr for unsupported shapes
    if (obj.m_board != nullptr || copy.m_board != nullptr) {
        return false;
    }

    return true;
}

bool Tester::normDeepCopyTest() {
    Solitaire obj(DIAMOND);
    Solitaire copy(obj);
    //Check initialized default values
    if (obj.m_numColumns != copy.m_numColumns || 
        obj.m_numRows != copy.m_numRows || 
        obj.m_shape != copy.m_shape || 
        obj.m_numMarbles != copy.m_numMarbles) {
        return false;
    }

    //Check if empty
    if (obj.m_board == nullptr || copy.m_board == nullptr) {
        return false; 
    }

    // Check if the boards are identical
    for (int i = 0; i < obj.m_numRows; ++i) {
        for (int j = 0; j < obj.m_numColumns; ++j) {
            if (obj.m_board[i][j] != copy.m_board[i][j]) {
                return false;
            }
        }
    }
    return true;
}
int main() {
    Tester t;

    
    //Call test functions
    cout << "Testing Error Board Shape: ";
    cout << (t.errBoardShapeTest() ? "PASS" : "FAIL") << endl;

    cout << "Testing Normal Board Shape: ";
    cout << (t.normBoardShapeTest() ? "PASS" : "FAIL") << endl;

    cout << "Testing Error New Board (Unsupported Board): ";
    cout << (t.errNewBoardTest() ? "PASS" : "FAIL") << endl;

    cout << "Testing Normal New Board (Change Shape): ";
    cout << (t.normNewBoardTest() ? "PASS" : "FAIL") << endl;

    cout << "Testing Change Board (Same Shape): ";
    cout << (t.normChangeBoardTest() ? "PASS" : "FAIL") << endl;

    cout << "Testing Change Board (Different Shape): ";
    cout << (t.norm2ChangeBoardTest() ? "PASS" : "FAIL") << endl;

    cout << "Testing Play Function (Correct Move): ";
    cout << (t.normPlayTest() ? "PASS" : "FAIL") << endl;

    cout << "Testing Play Function (Incorrect Move): ";
    cout << (t.errPlayTest() ? "PASS" : "FAIL") << endl;

    cout << "Testing Deep Copy Constructor (Error): ";
    cout << (t.errDeepCopyTest() ? "PASS" : "FAIL") << endl;

    cout << "Testing Deep Copy Constructor (Normal): ";
    cout << (t.normDeepCopyTest() ? "PASS" : "FAIL") << endl;

    return 0;
}
