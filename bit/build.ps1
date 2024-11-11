function Run-Test {
    param($path)
    Get-Content -Raw $path | .\bit.exe
}

function Run-Test-Folder {
    param($source)
    foreach ($file in Get-ChildItem($source)) {
        $res = Get-Content -Raw $file.FullName | .\bit.exe
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
        $output = Get-Content -Raw $file.FullName | .\bit.exe

            Write-Host $new '---' $time 's' 'exp' $expected 'got' $output
        if ($expected -ne $output) {
        }
    }
}

clang++ bit.cpp -g -DBIGTEST -std=c++20 -o bit.exe
# Run-Test "ocen/in/bit0.in"
# Run-Test "ocen/in/bit1ocen.in"
# Run-Test "ocen/in/bit2ocen.in"
# Run-BigTest "in" "out"
Run-BigTest "ocen/in" "ocen/out"
