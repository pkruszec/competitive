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
    param($in)
    foreach ($file in Get-ChildItem($in)) {

        $name = [System.IO.Path]::GetFileName($file)
        # $new =  [System.IO.Path]::ChangeExtension($name, '.out')
        # $path = [System.IO.Path]::Combine($out, $new)
        # $expected = Get-Content $path

        $output = Get-Content -Raw $file.FullName | .\spr.exe

        if ($output -eq "BUG baj jealous" -or $output -eq "BUG bit jealous" -or $output -eq "BUG best_index < 0") {
            Write-Host $name '---' 'got' $output
        }
    }
}

clang++ spr.cpp -std=c++20 -o spr.exe

Run-BigTest "in"
Run-BigTest "C:\home\tmp\spr\testy"

# Run-Test "C:\home\tmp\spr\testy\spr1.in"
# Run-Test "in/spr2ocen.in"
