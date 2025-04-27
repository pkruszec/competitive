function Run-Test-Folder {
    param($source)
    foreach ($file in Get-ChildItem($source)) {
        $res = Get-Content -Raw $file.FullName | .\exp.exe
        Write-Host $file.Name '->' $res
    }
}

clang++ exp.cpp -std=c++20 -o exp.exe
cat 'in/exp0.in' | ./exp
# Run-Test-Folder 'in'
