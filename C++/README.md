# C++ Advent of code solutions.

## Building the vs solution
To build this project, I chose to use premake5. You can download it yourself on the official page [Premake on github](https://premake.github.io/), or use the bat script "Get_premake.bat" to install it directly in the folder.

Use premake to generate a visual studio sln file (premake5 vs2022), and any relevant project files. While premake does give you the option to generate project files via gmake, I cannot gurantee that it will work since I do not develop with those.

Once the the sln file has been created you may open up the solution in visual studio.
However, I personally recommend using vscode instead. This will require you to also generate json tasks for vscode. you can do this by using the command premake5 vscode, which will run a premake script to generate the necessary files.

## Libraries
In this project, I use libcurl. This is mainly to gather input data from the advent of code website through http requests. To keep the size of this repo, and to not have any duplicates across multiple repos, I have chosen to save the static library outside of this repo.

Unfortunatley I have yet to develop a script to generate these files for any user of this repo.

Therefore it is up to the user to compile the libcurl static library and make sure it is linked correctly to this project.
The user may therefore need to change the linking paths stated in premake5.lua.

## Config
As stated before, this project will download inputs from the advent of code website. The user will therefore have to provide their unique session cookie in "Resources/Conf.txt". The format of this file is most probably going to be changed in the future, but as I only use this one unique setting for now, the user will only have to copy in their session cookie there.