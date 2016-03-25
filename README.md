# HandForce

## Summary (for everybody)

Handforce is a poker software which gives the "force" of a poker hand in online games. It was originally designed for PokerStars games. 
HandForce is published under the **GNU GPL license**.

The software was developed with C++ and SDL 1.2. It is very easy to use, you just launch the `.exe` with all the proper DLLs and you'll
get a small screen that will give you the force of the current hand in the current window you're playing in in real time.

Though a professional player may be able to play on multiple tables at the same time and still be able to read his hand very quickly, an
average player who still wants to be successful in poker may have difficulties playing with more than 2-3 tables at the same time given the
few milliseconds he has to take a decision. HandForce shortens that time by analyzing the current hand for him, thus allowing him to play
on more tables at the same time.

This software was created by Hachem Benyahia.


## Repository information (for developers only)

### `/cards`
The directory `/cards` contains the images that the program uses to perform OCR on cards (pattern recognition). This is due to the fact
that online poker softwares don't allow access to any data about the game. So the only way to retrieve such information is to capture the
cards in real time and call a function that matches the capture with the real card (in the directory `/cards`), and then from that deduces
its value.

### `/codeblocks`
As I initially developed the software on the IDE CodeBlocks, this directory contains exactly the same files as my project directory. 
Therefore, if you also use this IDE, you can simply download this directory as it is and resume the development from there. Just remember 
the terms of the **GNU GPL license**, under which is published this software.

### `/src`
Now, if you don't use CodeBlocks, or you just want the source files, you can find them in the directory `/src`.

<br>
##### Important :
The software uses SDL 1.2 and SDL_Image 1.2, so you will have problems when compiling, whether you're under CodeBlocks or not, you'll have
to set the proper files (DLLs) in your directory and link to the correspondings `.lib` or `.a`. You can find information about that on
Google.


## Release information (for users only)

You can find all the releases on this page : https://github.com/ToStand/HandForce/releases