//#include <stdio>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <sys/types.h>
#include <inttypes.h>

using namespace std;

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

struct piece
{
    bool used;
    uint8_t numbers[4];
};

piece unsorted[36];
piece *sorted[6][6];

int solution_count = 0;
int ret_func_call = 0;

void print_solved () {
    solution_count++;
    int array_pos;
    int x_pos;
    int y_pos;
    for (int x = 0; x < 6; x++) {
        for (int y = 0; y < 6; y++) {
            array_pos = sorted[x][y] - &unsorted[0];
            cout << x + 1 << " " << y + 1 << ": " << (array_pos % 6) + 1 << " " << (array_pos / 6) + 1 << endl;
        }
    }
}

bool find_next_piece (uint8_t x_pos, uint8_t y_pos)
{
    //ret_func_call++;
    if (y_pos == 6) {
        print_solved ();
        //cout << "asd" << endl;
        return (true);
    } else {
        for (uint8_t i = 0; i <36; i++) {
            if (unsorted[i].used == false) {
                if (((x_pos == 0) || (sorted[x_pos - 1][y_pos]->numbers[RIGHT] == unsorted[i].numbers[LEFT]))
                    && ((y_pos == 0) || (sorted[x_pos][y_pos - 1]->numbers[DOWN] == unsorted[i].numbers[UP]))) {
                    sorted[x_pos][y_pos] = &unsorted[i];
                    unsorted[i].used = true;
                    uint8_t new_y_pos = y_pos;
                    uint8_t new_x_pos = (x_pos + 1);
                    if (new_x_pos == 6) {
                        new_x_pos = 0;
                        new_y_pos++;
                    }
                    if (find_next_piece (new_x_pos, new_y_pos)) {
                        return (true);
                    }
                    unsorted[i].used = false;
                }
            }
        }
    }
    return (false);
};

void read_pieces ()
{
    string piece;
    ifstream piece_numbers;
    string number_char;
    int line = 0;
    int number;
    piece_numbers.open ("piece_numbers_2.txt");
    while (! piece_numbers.eof ()) {
        getline (piece_numbers, piece);
        unsorted[line].used = false;
        for (int j = 0; j < 4; j++) {
            number_char = piece[j];
            stringstream number_convertion (number_char);
            number_convertion >> number;
            unsorted[line].numbers[j] = number;
            //cout << unsorted[line].numbers[j] << " ";
        }
        //cout << endl;
        line++;
    }
    if (line != 36) {
        cout << "error" << endl;
    }
}

int main (void)
{
    read_pieces ();
    find_next_piece (0, 0);
    std::cout << solution_count << std::endl;

    return (0);
};
