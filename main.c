#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// curent rule:
// 111 -> 0
// 110 -> 0
// 101 -> 0
// 100 -> 1
// 011 -> 1
// 010 -> 1
// 001 -> 1
// 000 -> 0

//  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 

#define row_length 189 // this can be changed later.

int current_cell_states[row_length] = {  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int next_cell_states[row_length] = {};

typedef struct cell {
  int left;
  int selected;
  int right;
}cell;

void newline() {printf("\n");}

cell find_nabours(int cell_coordinate) {
  cell cell;

  cell.selected = current_cell_states[cell_coordinate];
  cell.left = current_cell_states[(cell_coordinate - 1 + row_length) % row_length];
  cell.right = current_cell_states[(cell_coordinate + 1) % row_length];
  return cell;
}

void compute_next_generation() {
  for (int x = 0; x < row_length; x++) {
    if (find_nabours(x).left == 1 && find_nabours(x).selected == 1 && find_nabours(x).right == 1) {next_cell_states[x] = 0;} // 1 of 8
    if (find_nabours(x).left == 1 && find_nabours(x).selected == 1 && find_nabours(x).right == 0) {next_cell_states[x] = 0;} // 2 of 8
    if (find_nabours(x).left == 1 && find_nabours(x).selected == 0 && find_nabours(x).right == 1) {next_cell_states[x] = 0;} // 3 of 8
    if (find_nabours(x).left == 1 && find_nabours(x).selected == 0 && find_nabours(x).right == 0) {next_cell_states[x] = 1;} // 4 of 8
    if (find_nabours(x).left == 0 && find_nabours(x).selected == 1 && find_nabours(x).right == 1) {next_cell_states[x] = 1;} // 5 of 8
    if (find_nabours(x).left == 0 && find_nabours(x).selected == 1 && find_nabours(x).right == 0) {next_cell_states[x] = 1;} // 6 of 8
    if (find_nabours(x).left == 0 && find_nabours(x).selected == 0 && find_nabours(x).right == 1) {next_cell_states[x] = 1;} // 7 of 8
    if (find_nabours(x).left == 0 && find_nabours(x).selected == 0 && find_nabours(x).right == 0) {next_cell_states[x] = 0;} // 8 of 8
  }
}

void make_next_generation_current() {
  for (int x = 0; x < row_length; x++) {
    current_cell_states[x] = next_cell_states[x];
  }
}

void print_current_generation() {
  printf("%d%d%d%d%d\n", current_cell_states[0], current_cell_states[1], current_cell_states[2], current_cell_states[3], current_cell_states[4]);
}

void generation_step() {
  compute_next_generation();
  make_next_generation_current();
}

void display_generation() {
  for (int x = 0; x < row_length; x++) {
    switch (current_cell_states[x]) {
      case 1:
      printf("\u2588");
      break;
      case 0:
      printf("\u2800");
      break;
      default:
      printf("something went wrong with displaying this generation");
      break;
    }
  }
  newline();
}

void generate_and_display_generations(int number_of_generations) {
  for (int x = 0; x < number_of_generations; x++) {
    generation_step();
    display_generation();
  }
}

int main() {
  printf("enter a number lower than 256: ");
  int user_input;
  scanf("%d", &user_input);
  if (user_input > 255) {
    printf("\n255 is the max, either you entered a greater number or an invalid input. also the program crashed, so..... well done?");
    return -1;
  }

  newline();
  display_generation();
  generate_and_display_generations(user_input);

  return 0;
}
