# Tower-of-Hanoi

To 'make' the program you must have the SDL2 libraries installed.
The following command automates the installation process for you:
Note: You may have to uncomment lines 28-31 for it to work.
<br>
<b>
* make install_SDL2
</b>

This command actually triggers a makefile rule which runs the following commands:
<br>
<b>
* sudo apt-get install libsdl2-2.0
* sudo apt-get install libsdl2-dev
</b>

Then to start the program just do:
<b>
* make run
</b>

This project is a simulation solving the Tower of Hanoi. The algorithm for moving the disks is more efficient that the usual naive implementation because it is iterative instad of recursive, and consequently it does not take up space to store the recursive runtime stack and also it does not it go into repeated recursion. If we have N disks, the space complexity is O(N) and the time complexity is O(2^N). This algorithm is able to achieve such efficienty because it is based on the properties of binary mathematics. Each disk is represented as a bit in a binary number. Every time the 2^0 bit is flipped the 0 disk (the smallest disk) moves. Every time the 2^1 bit is flipped the 1 disk (the next smallest) disk is moves, and so on.
<br>

In addition to the algorithm which is responsible for moving the bits, this project also utilizes another algorithm, invented by myself, which is responsible for assigning colors to the disks. This algorithm generates N evenly spaced colors on the color wheel in order to give each of N disks a distinctive color for improved human-computer interaction and aesthetics. No matter how many disks there are, the colors of the disks will always be equidistant on the color wheel. This ensures that all disks will be easily distinguishable even by people with poor vision. This algorithm is based on the mathematical properties of the color wheel that I discovered. We can't just pick random colors for each of the disks, because there is a chance that since random numbers may be very close together, like 10 and 12, the random colors may also be very close together, like red and a slightly ligher red. It means that the disks will not be easily distinguishable in this case.

![Alt text](/Screenshots/Tower_of_Hanoi.png?raw=true "Cover")

When you run this program, it opens a terminal and asks you to enter the number of disks that you want to be moved around the pegs. Theoretically, the algorithm can accept an arbitrary number of disks and work with them successfully. However, it is not practical to have lots of disks, mainly because the widest disks can't fit on the screen! This is a problem with the UI, not the algorithm itself. Future versions may include a feature to scale down the sizes of individual disks on the screen as the number of disks increases in order to make them fit on the screen.

The GUI window will execute in full-screen, non-resizable mode to maximize the space for displaying disks. Note: there may be bugs attempting to run the program in a dual-monitor setup.

The user can quit the program at any time without waiting for all th disks move onto the rightmost peg by hitting the 'Q' key or Ctrl-C.
