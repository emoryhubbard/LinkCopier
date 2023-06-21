# LinkCopier

A utility for copying image links to the clipboard. This is to facilitate note-taking,
so you can past links to images inside of a txt file of personal notes.

I often take screenshots when taking notes. I wanted a way to automatically detect
the most-recently created screenshot in my downloads folder (taken from my browser's Take
Screenshot option), move it to an images folder, and create a link that can be opened
automatically with a double-click in my txt editor (Notepad++).

In pratice, I simply use Take Screenshot on Firefox, click download in the popup,
click this app on my taskbar, then ctrl-v into my notes. I'll make an integrated
extension for Firefox in the future, so instead of clicking an app on the taskbar
for the final step, I can click a button on the browser.

## How to Install

Clone this repo and modify LinkCopier.cpp to use your downloads directory and your desired images folder directory
(just be sure that the directory already exists).
These two string variables are near the top of the LinkCopier.cpp source file.

Then, build the installer yourself from source.
You can skip to the Build step (Step 11) once you are satisfied that this code
is safe (I only wrote one source file, called LinkCopier.cpp, which you can inspect yourself):
https://learn.microsoft.com/en-us/cpp/ide/walkthrough-deploying-your-program-cpp?view=msvc-170
