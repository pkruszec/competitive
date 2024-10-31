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
        # $new =  [System.IO.Path]::ChangeExtension($name, '.out')
        # $path = [System.IO.Path]::Combine($out, $new)
        # $expected = Get-Content $path

        $output = Get-Content -Raw $file.FullName | .\kas.exe

        Write-Host $name '---' 'got' $output
    }
}

clang++ kas.cpp -std=c++20 -o kas.exe
.\kas.exe
