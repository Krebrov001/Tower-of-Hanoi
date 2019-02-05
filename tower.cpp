#include "tower.h"

Tower::~Tower()
{
    while (top_disk != nullptr) {
        pop();  // Pop the top disk off the tower;
    }
}


void Tower::push(int n)
{
    // If the Tower is empty.
    // TODO: Do I need to add a bot_disk == nullptr condition?
    if (top_disk == nullptr) {
	top_disk = new Disk(n, nullptr, nullptr);
	bot_disk = top_disk;
    } else {
        Disk* temp = top_disk;
	top_disk = new Disk(n, temp, nullptr);
	temp->next = top_disk;
    }

    ++size;
}


void Tower::pop()
{
    // If the Tower is empty.
    // TODO: Do I need to add a bot_disk == nullptr condition?
    if (top_disk == nullptr) {
	return;
    }

    Disk* temp = top_disk->prev;
    // If the current top disk is not at the very bottom of the tower,
    // If it is not the only disk in the tower.
    if (temp != nullptr) {
	temp->next = nullptr;
    }

    // delete the current top disk.
    delete top_disk;
    // Move the temp_disk pointer to point to the previous disk in the tower.
    // if temp != nullptr, then top_disk points to the previous disk.
    // if temp == nullptr, then there are no more disks, so top_disk points to nullptr,
    //     which is good because it indicates that the tower is empty.
    top_disk = temp;

    if (top_disk == nullptr) {
	bot_disk = nullptr;
    }

    --size;
}


void Tower::printTower() const
{
    cout << '|';
    // Start at the bottom disk.
    Disk* temp = bot_disk;
    while (temp != nullptr) {
	cout << temp->number << ' ';
	temp = temp->next;
    }
    cout << endl;
}

