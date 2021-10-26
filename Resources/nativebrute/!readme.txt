1. What is it ?
This is template based hash bruteforce for GTA V natives with multithread support.

2. How do I use it ?
- Set optimal thread count in "in.config.txt", optimal value should represent your processor core count, or
  you can set less threads in order to avoid your OS freezing, setting more threads will cause performance drop.
- Open run.bat in notepad. Command line parameter for "optimized.exe" is the template what will be used, as you
  can see it includes {filename} variables, such variable represent a list with words which is named either 
  "filename" or "list.filename.txt", all word lists I had been using are included. Change the template the way
  you need it to be, for example SET_ACTOR_{native_mids}_{native_postfixes}, letter case doesn't matter. 
- Run the bat!  
  
3. Where is the result ?
After bruteforce finishes you will have "found_natives.txt" file created in the same folder as bat is. Open it, and what
you see is called hash collisions. Now you need to check everything that you see in that file ! Be ware that even 
good looking native names usually are fake, so you need to check header with natives (see below) for the hash of bruted
native, and if it fits the category then probably you got a match. 
Data format in "found_natives.txt" is: register address, address, hash, name1 name2 nameN

Header with natives (file #5) is here:
http://gtaforums.com/topic/717612-scriptnative-documentation-and-research/ 

						(C) Alexander Blade 2013-2014