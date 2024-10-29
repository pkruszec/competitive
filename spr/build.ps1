function Run-Test {
    param($path)
    Get-Content -Raw $path | .\spr.exe
}

function Run-Test-Folder {
    param($source)
    foreach ($file in Get-ChildItem($source)) {
        $res = Get-Content -Raw $file.FullName | .\spr.exe
        Write-Host $file.Name '->' $res
    }
}

function Run-BigTest {
    param($in, $out)
    foreach ($file in Get-ChildItem($in)) {
        $name = [System.IO.Path]::GetFileName($file)
        $new =  [System.IO.Path]::ChangeExtension($name, '.out')
        $path = [System.IO.Path]::Combine($out, $new)

        $expected = Get-Content $path
        $output = Get-Content -Raw $file.FullName | .\spr.exe

        Write-Host $new '---' $time 's' 'got' $output
        if ($expected -ne $output) {
        }
    }
}

clang++ spr.cpp -std=c++20 -o spr.exe
Run-BigTest "in" "out"

# Run-Test "in/spr3ocen.in"
# Run-Test "in/spr2ocen.in"
