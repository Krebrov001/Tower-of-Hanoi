#ifndef TOWER_H
#define TOWER_H

#include <cstdlib>   // for std::size_t
#include <iostream>  // for std::cout, std::endl

using std::cout;
using std::endl;
using std::size_t;

// Represents a disk in a tower.
struct Disk {
    // The default consructor.
    Disk() : number{0}, prev{nullptr}, next{nullptr} {}

    // The parametrized constructor allows us to create a struct Disk with it's desired contents.
    Disk(int n, Disk* prv, Disk* nxt) : number{n}, prev{prv}, next{nxt} {}

    // The number of the disk (ex. 0, 1, 2, ...)
    int number;
    // A pointer to the previous disk below the current disk in the tower.
    // if prev == nullptr, then it means that there are no more disks below of the current disk,
    // and the current disk is at the very bottom of the Tower.
    Disk* prev;
    // A pointer to the next disk on top of the current disk in the tower.
    // if next == nullptr, then it means that there are no more disks on top of the current disk,
    // and the current disk is the topmost disk.
    Disk* next;
};


#define EMPTY -1

/**
 * A Tower is a stack-like data structure.
 * The only difference is it allows you to access it's internal data members
 * for determining in what order the Disks are in the Tower.
 */
struct Tower {
  /* In C++, All the data members and member functions of a struct are public by default. */

    // A default constructed tower has no disks, and it's next Tower isn't identified.
    Tower() : bot_disk{nullptr}, top_disk{nullptr}, next{nullptr}, size{0} {}

    // I forbid you to copy or assign a Tower.
    Tower(const Tower& other) = delete;
    Tower& operator=(const Tower& other) = delete;

    /**
     * Pops all disks from the Tower.
     * All the dynamic memory is reclaimed.
     */
    ~Tower();

    // Member functions defined inside the class are inline by default,
    // but it's good practice to write inline anyway for clarity.

    /**
     * Returns the disk at the top of the Tower.
     * const function - does not pop that disk off the Tower.
     * @return int - returns the name/number of the top disk as an int.
     *               does not return the Disk object itself.
     *    if the Tower is empty (contains no disks),
     *        the special constant EMPTY is returned, which is == -1.
     */
    inline int top() const
    {
	if (top_disk != nullptr) {
	    // top_disk is a Disk*.
            return top_disk->number;
	} else {
	    return EMPTY;
	}
    }

    /**
     * Pushes a Disk onto the Tower, updates the corresponding pointers, and increments the size in O(1) time.
     */
    void push(int n);

    /**
     * Pops a Disk off the Tower, updates the corresponding pointers, and decrements the size in O(1) time.
     * If the Tower is empty, does nothing and just returns.
     */
    void pop();

    /**
     * @return size_t - The number of disks on the Tower.
     */
    inline size_t getSize() const { return this->size; }

    /**
     * @return bool - true if the Tower is empty (contains no disks)
     *                false if there is at least one disk on the Tower.
     */
    inline bool empty() const
    {
	// If top_disk == nullptr, then the Tower is empty,
	// otherwise it has some disks on it.
	// To bool conversions:
	// 0 == nullptr == false.  Anything else == true.
        return !top_disk;
    }

    /**
     * Sets the current Tower's next Tower using the pointer parameter.
     */
    inline void setNext(Tower* next)
    {
        this->next = next;
    }

    /**
     * @return Tower* - this->next, the current Tower's next Tower.
     */
    inline Tower* getNext() const
    {
        return this->next;
    }

    /**
     * Prints the names/numbers of all disks in the Tower from bottom to top.
     * This is an example. You can replace the print statements with drawing graphics.
     */
    void printTower() const;

  //private:
    // Points to the bottom Disk in the Tower.
    Disk* bot_disk;
    // Points to the top Disk in the Tower.
    Disk* top_disk;
    // Points to the next tower to the right of the current tower.
    // If the current tower is the rightmost one, next loops around and points back to the first Tower.
    Tower* next;
    // The number of disks in the Tower.
    size_t size;
};

#endif /* TOWER_H */

