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

        if ($expected -ne $output) {
            Write-Host $new '---' $time 's' 'exp' $expected 'got' $output
        }
    }
}

clang++ bit.cpp -DBIGTEST -std=c++20 -o bit.exe
Run-Test "in/01.in"
# Run-BigTest "in" "out"
