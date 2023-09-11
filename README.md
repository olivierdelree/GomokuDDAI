# Gomoku DDAI

## What this repo is about

The Gomoku Dynamic Difficulty Artificial Intelligence (GomokuDDAI) repo provides a C++/Qt-based application to play [Gomoku](https://en.wikipedia.org/wiki/Gomoku) against an AI agent that dynamically adapts to the level its opponent.  
The current implementation is rather simple and only has a main menu and a Gomoku game grid. However, in the future, different types of agents, including the dynamic difficulty agent, will be implemented to reflect the state of its [sibling Python project](https://github.com/olivierdelree/AIADissertation).

## How to run locally
Simply clone the repository to your own machine and create a symbolic link inside of `lib` that points to your own installation of Qt. The structure should look something like `GomokuDDAI/lib/Qt` where `Qt` is a symbolic link pointing to the root of the installation directory of your Qt installation.  
You will therefore need to install Qt on your own machine before being able to run the project.  

## Miscellaneous
This repo follows the same style guide as [SerenityOS](https://github.com/SerenityOS/serenity/blob/master/Documentation/CodingStyle.md) (which is where `.clang-format` came from) except when working with signals and slots to maintain a more Qt-like approach.  
This could become quite confusing in the future when the project grows. Therefore, a future commit will most likely switch the coding style to be entirely [Qt-based](https://wiki.qt.io/Qt_Coding_Style) to keep a more focused style for the whole project.  

Additionally, this project is still in its infancy and does not have a license. In the next few commits, one will be added to reflect [what is required by Qt](https://www.qt.io/download-open-source) to use their library in an open source project.