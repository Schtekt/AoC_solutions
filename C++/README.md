# C++ Advent of code solutions.

## Building the vs solution
To build this project, I chose to use premake5. You can download it yourself on the official page [Premake on github](https://premake.github.io/), or use the bat script "Get_premake.bat" to install it directly in the folder.

Use premake to generate a visual studio sln file (premake5 vs2022), and any relevant project files. While premake does give you the option to generate project files via gmake, I cannot gurantee that it will work since I do not develop with those.

Once the the sln file has been created you may open up the solution in visual studio.
However, I personally recommend using vscode instead. This will require you to also generate json tasks for vscode. you can do this by using the command premake5 vscode, which will run a premake script to generate the necessary files.

## Input data
The solutions require the user to add input files themselves.
These inputs may be fetched from the Advent of code website, where the user must log in in order to get puzzle inputs.
To add an input for a specific puzzle, the user must add a file with the input data in "Resources/\<year number\>/day_\<day number\>/input.txt", eg. for 2023, day 1 the puzzle input would be placed in "Resources/2023/day_1/input.txt".