function Run-Test-Folder {
    param($source)
    foreach ($file in Get-ChildItem($source)) {
        $res = Get-Content -Raw $file.FullName | .\boi.exe
        Write-Host $file.Name '->' $res
    }
}

clang++ boi.cpp -std=c++20 -o boi.exe
cat 'in/boi0.in' | ./boi
# Run-Test-Folder 'in'
