## Compile Instruction:

- Use the following command to compile and the main file:
  g++ -std=c++11 graph.cpp dijkstra.cpp main.cpp -o bfs && ./bfs

- Use the following command to compile and run the test file:

  g++ -std=c++11 graph.cpp dijkstra.cpp test.cpp -o test && ./test


## Todos:

- [ ] Add a function to record the time spent on searching
- [ ] Write a auto-test for bfs

## Reference Materials

- [ ] [Parallel Dij Repo with OpenMP and MPI](https://github.com/Emilylulu/parallel-Dijkstra-s-Algorithm)
- [ ] [Buffalu CSE's presentation](https://cse.buffalo.edu/faculty/miller/Courses/CSE633/Ye-Fall-2012-CSE633.pdf)

## Vscode Debugger Setup

**task.json file**

```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "build test.cpp",
            "type": "shell",
            "command": "clang++",
            "args": [
                "-std=c++17",
                "-g",
                "${workspaceFolder}/test.cpp",
                "${workspaceFolder}/graph.cpp",
                "${workspaceFolder}/bfs.cpp",
                "-o",
                "${workspaceFolder}/test.out"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "problemMatcher": [
                "$gcc"
            ]
        }
    ]
}
```

**launch.json file**

```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "Debug test.cpp",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceFolder}/test.out",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "lldb",
            "preLaunchTask": "build test.cpp",
            "setupCommands": [
                {
                    "description": "Enable pretty-printing for gdb",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ]
        }
    ]
}

```

