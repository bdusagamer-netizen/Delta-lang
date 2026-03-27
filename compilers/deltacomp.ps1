cd "../delta"
& "C:\msys64\ucrt64\bin\g++.exe" `
    -std=c++20 `
    -O2 `
    -I "./src" `
    ./src/*.cpp `
    -o "./bin/delta.exe"