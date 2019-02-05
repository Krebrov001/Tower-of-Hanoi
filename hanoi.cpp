#include "hanoi.h"
#include "drawer.h"


Hanoi::Hanoi(size_t num_disks) : num_disks{num_disks}
{
    // The disk_bits vector starts out as 00...00
    disk_bits.resize(num_disks, 0);

    // Set the next tower for each tower.
    tower1.setNext(&tower2);
    tower2.setNext(&tower3);
    tower3.setNext(&tower1);  // tower3's next tower is tower1.

    // Pushes all the disks onto tower1.
    set_init_disks();
}


void Hanoi::play(Drawer* draw)
{
    draw->draw_Hanoi(*this);

    // We want all the disks to make their way onto the tower3.
    // If tower3 has num_disks on it, then we're done.
    while (tower3.getSize() != num_disks) {
	// add_one() function returns the name of the next disk to be moved.
	// next_disk is an int because it is compared with the returned value of Tower::top(), which is int.
	int next_disk = add_one();
	// add_one() returns either the name of the next disk, or -1.
	// -1 is returned if disk_bits has been reset to 00...00 and all the disks have still not been moved onto tower3.
	// This happens when we have an odd number of disks and all the disks have been moved to tower2.
	// We want to repeat the algorithm again in order to move all the disks from tower2 to tower3.
	if (next_disk == -1) {
	    continue;
	}

	// You always start from tower1.
	Tower* current_tower = &tower1;
	// First we need to find in which Tower the next_disk is, and we need to pop it from that Tower.
	// This loop searches for the Tower which has next_disk as it's top disk.
	// This loop stops when such a Tower whose top disk is next_disk is found.
	while (current_tower->top() != next_disk) {
	    // Go one tower to the right.
	    current_tower = current_tower->next;
	}
	// Since we stopped at a Tower which has next_disk as it's top disk,
	// this command pops next_disk off that Tower.
	current_tower->pop();

	// Now the next_disk should be placed onto a tower to the right.
	current_tower = current_tower->next;
	// We cannot put a larger disk on top a smaller one.
	// If the top disk in the current tower is smaller than next_disk, we go one tower to the right.
	//
	// This loop stops at a Tower where we can place the next_disk.
	// This loop stops when such a Tower whose top_disk is > next_disk is found,
	// or it stops at an empty Tower.
	while (current_tower->top() != EMPTY && current_tower->top() < next_disk) {
	    current_tower = current_tower->next;
	}
	// Since we stopped at a Tower where next_disk can be placed,
	// where the top disk is > next_disk or the Tower is empty,
	// this command pushes next_disk onto that Tower.
        current_tower->push(next_disk);

	/*
	print_disk_bits();
	tower1.printTower();
	tower2.printTower();
	tower3.printTower();
	cout << endl;
	*/

	draw->draw_Hanoi(*this);
    }
}


void Hanoi::set_init_disks()
{
    // size_t(0) is a function-style cast in C++, similar to a constructor for PODs.
    // Constructs a size_t with a value of 0.
    for (size_t i = num_disks - 1; i != ~size_t(0); --i) {
	tower1.push(i);
    }
}


int Hanoi::add_one()
{
    size_t i = 0;
    // This loop starts at the 2^0 "bit" position and keeps flipping all the non-0 bits.
    // This loop stops when it gets to a value disk_bits[i] which is == 0.
    // Flipping all the non-0 (means 1) bits until it gets to a 0 bit has the same effect as a
    // binary roll over when adding a bit.
    //while (disk_bits[i] != 0)
    while (disk_bits[i]) {
	// Flip the current bit from a 1 to a 0.
        disk_bits[i] = !disk_bits[i];

	++i;
	// if i goes out of bounds of the disk_bits vector, this is supposed to prevent accessing an undefined value:
	// disk_bits[i].
	// The only time i will go out of bounds is if all elements in the disk_bits vector are set to 1: 11...11
	// This effectively "rolls over" all the 1 bits, and discards the carry out.
	// It resets the number back to 00...00 and return -1 to uniquely specify that result.
	if (i >= num_disks) {
	    return -1;
	}
    }
    // Now we've stopped at a bit position where disk_bits[i] is == 0
    // Flip the current bit from a 0 to a 1.
    disk_bits[i] = !disk_bits[i];

    // return the number of bits rolled over,
    // return the bit position at which the 0 was flipped to a 1,
    // return the name of the next disk to be moved.
    return i;
}


void Hanoi::print_disk_bits()
{
    auto end = disk_bits.crend();
    for (auto it = disk_bits.crbegin(); it != end; ++it) {
	cout << *it;  // dist_bits[i]
    }
    cout << endl;
}

