#ifndef HANOI_H
#define HANOI_H

#include "tower.h"

// Some of these includes are also in the file tower.h
// However they will not be included twice because their header guards will prevent it,
// so it's safe to write these includes here also.
// I am writing these includes here also to explicitly specify which portions of the standard library
// are used by the class Hanoi and it's member functions.
#include <cstdlib>   // for std::size_t
#include <iostream>  // for std::cout, std::endl
#include <vector>    // for std::vector

using std::cout;
using std::endl;
using std::vector;
using std::size_t;


// Forward declaration, to make Drawer recogniziable as a data type.
class Drawer;

class Hanoi {
  // class Drawer is responsible for drawing the state of each Tower with the Disks,
  // therefore it must be a friend class.
  friend class Drawer;

  public:
    /**
     * This constructor sets up and initializes the data structures used in the game.
     * 1. Initializes the disk_bits vector.
     * 2. Connects the towers in a "circular linked list" like data structure.
     * 3. calls set_init_disks(): pushes all the disks onto tower1.
     *
     * @param size_t num_disks - The number of disks in the game.
     */
    Hanoi(size_t num_disks);

    /**
     * This function moves all the disks one by one from the leftmost tower (tower1) to the rightmost tower (tower3).
     * Each iteration of the while loop it moves a single disk.
     * Then it displays the state of the game (the state of all the three towers with their disks and the disk_bits vector).
     * This function returns when all the disks have been placed onto the tower3, which means that the game has been solved.
     *
     * @param Drawer* draw - A Drawer object which is responsible for displaying the state of the game.
     */
    void play(Drawer* draw);

  private:
    /* The private member helper functions. */

    /**
     * This function gets called once at the start of the program by Hanoi::Hanoi(size_t num_disks) constructor.
     * It pushes all the disks onto tower1.
     * Pushes the following disks: num_disks - 1, num_disks - 2, ..., 1, 0.
     */
    void set_init_disks();

    /**
     * This function adds 1 to the disk_bits vector of bools which is considered as a binary number.
     * Every time it adds 1, it flips a bit.
     * When a bit other than disk_bits[0] (the least significant bit) is flipped from 0 to 1,
     * all the lower order 1 bits before it "roll over" from 1 to 0, preserving the new value of the binary number.
     *
     * @return int - This function returns the index of the bit which got flipped.
     *               The index is the position of the 2^power bit.
     *               This is the name of the next disk to be moved.
     *   This function returns int because the returned value is saved into int next_disk,
     *   a local variable inside Hanoi::play().
     *   NOTE: a special value -1 is returned if all the bits in the disk_bits vector have been zeroed out due to roll over.
     *   When this happens it signifies that we need to repeat the process of counting up to 11...11 again.
     *   Hanoi::play() function which calls this function knows how to handle the -1 returned value.
     *
     */
    int add_one();

    /**
     * This function just prints the disk_bits vector of bools as a binary number.
     * Used for debugging and console output.
     *
     * The "bits" are printed from left to right.
     * The "bits" corresponding to higher powers of 2 are printed first.
     * Therefore we must iterate through the disk_bits vector in reverse.
     */
    void print_disk_bits();

    /* The private data members. */

    // The number of disks in the game.
    size_t num_disks;

    Tower tower1;
    Tower tower2;
    Tower tower3;
    // This vector of bools has the size of num_disks elements.
    // Each "bit" represents a disk.
    // disk_bits[0], the 2^0 "bit" represents disk 0, the smallest disk.
    // disk_bits[1], the 2^1 "bit" represents disk 1.
    // disk_bits[2], the 2^2 "bit" represents disk 2.
    // etc, etc...
    vector<bool> disk_bits;
};

#endif /* HANOI_H */

