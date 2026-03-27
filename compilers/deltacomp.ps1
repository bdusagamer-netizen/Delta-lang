Push-Location "$PSScriptRoot/../delta"

$files = Get-ChildItem -Recurse -Filter *.cpp | ForEach-Object { $_.FullName }

g++ `
    -std=c++20 `
    -O2 `
    -I "./src" `
    $files `
    -o "./bin/delta.exe"

Pop-Location