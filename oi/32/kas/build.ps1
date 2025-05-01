function Run-Test {
    param($path)
    Get-Content -Raw $path | .\kas.exe
}

function Run-Test-Folder {
    param($source)
    foreach ($file in Get-ChildItem($source)) {
        $res = Get-Content -Raw $file.FullName | .\kas.exe
        Write-Host $file.Name '->' $res
    }
}

function Run-BigTest {
    param($in)
    $full = ""
    foreach ($file in Get-ChildItem($in)) {

        $name = [System.IO.Path]::GetFileName($file)
        $output = Get-Content -Raw $file.FullName | .\kas.exe

        Write-Host $name $output
        $full = "$($full)`n$($output)"
    }

    $full | python points.py
}

clang++ kas.cpp -O3 -DHOME -std=c++20 -o kas.exe

# Run-Test "in/a01.in"
Run-BigTest "in"
