function Run-Test-Folder {
    param($source)
    foreach ($file in Get-ChildItem($source)) {
        $res = Get-Content -Raw $file.FullName | .\wal.exe
        Write-Host $file.Name '->' $res
    }
}

clang++ wal.cpp -std=c++20 -o wal.exe

Write-Host "=== MANUAL TEST OUTPUT ==="
Run-Test-Folder "input"

Write-Host "=== GENERATED TEST OUTPUT ==="
Run-Test-Folder "test"
