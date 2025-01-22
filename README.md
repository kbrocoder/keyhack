# keyhack
Create a method for launching Windows 11 apps without clicking on desktop icons (I have all my desktop icons turned off for the clean look).

The C code simply runs in the background (can put in your start-up) and waits for CTRL+Alt+0 (zero) to open the "Desktop" folder.

Note that some programs don't add a desktop icon - so you'd have to create a short-cut and add it to your User Desktop folder for launch.
Also Note that some icons go into the "All Users" Desktop so you'll have to grab those icon and put them into your user folder too.
