function Run-Test-Folder {
    param($source)
    foreach ($file in Get-ChildItem($source)) {
        $res = Get-Content -Raw $file.FullName | .\wal.exe
        Write-Host $file.Name '->' $res
    }
}

function Run-BigTest {
    param($in, $out)
    foreach ($file in Get-ChildItem($in)) {
        $name = [System.IO.Path]::GetFileName($file)
        $new =  [System.IO.Path]::ChangeExtension($name, '.out')
        $path = [System.IO.Path]::Combine($out, $new)

        $expected = Get-Content -Raw $path
        $output = Get-Content -Raw $file.FullName | .\wal.exe

        if ($expected -ne $output) {
            Write-Host "TEST FAILED:" $in $file $expected $output
        }
        # $res = Get-Content -Raw $file.FullName | .\wal.exe
        # Write-Host $file.Name '->' $res
    }
}

# clang++ wal.cpp -DBIGTEST -std=c++20 -o wal.exe
# Run-BigTest "bigtest/walrob/input1" "bigtest/walrob/output1"

clang++ wal.cpp -std=c++20 -o wal.exe
Write-Host "=== MANUAL TEST OUTPUT ==="
Run-Test-Folder "input"
Write-Host "=== GENERATED TEST OUTPUT ==="
Run-Test-Folder "test"
