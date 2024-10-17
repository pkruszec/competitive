function Run-Test {
    param($path)
    Get-Content -Raw $path | .\noi.exe
}

function Run-Test-Folder {
    param($source)
    foreach ($file in Get-ChildItem($source)) {
        $res = Get-Content -Raw $file.FullName | .\noi.exe
        Write-Host $file.Name '->' $res
    }
}

clang++ noi.cpp -o noi.exe

Write-Host "=== MANUAL TEST RESULTS ==="
Run-Test-Folder "input"
Write-Host "=== GENERATED TEST RESULTS ==="
Run-Test-Folder "TEST"
