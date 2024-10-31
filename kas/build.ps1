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
    foreach ($file in Get-ChildItem($in)) {

        $name = [System.IO.Path]::GetFileName($file)
        $output = Get-Content -Raw $file.FullName | .\kas.exe

        Write-Host $name $output
    }
}

clang++ kas.cpp -DHOME -std=c++20 -o kas.exe

Run-BigTest "in"
