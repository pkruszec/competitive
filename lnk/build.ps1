function Run-Test {
    param($path)
    Get-Content -Raw $path | .\lnk.exe
}

function Run-Test-Folder {
    param($source)
    foreach ($file in Get-ChildItem($source)) {

        $StopWatch = new-object system.diagnostics.stopwatch
        $StopWatch.Start()
        $res = Get-Content -Raw $file.FullName | .\lnk.exe
        $StopWatch.Stop()
        $time = $StopWatch.Elapsed.TotalSeconds

        Write-Host $file.Name '->' $res '---' $time 's'
    }
}

function Run-BigTest {
    param($in, $out)
    foreach ($file in Get-ChildItem($in)) {
        $name = [System.IO.Path]::GetFileName($file)
        $new =  [System.IO.Path]::ChangeExtension($name, '.out')
        $path = [System.IO.Path]::Combine($out, $new)

        $expected = Get-Content $path

        $StopWatch = new-object system.diagnostics.stopwatch
        $StopWatch.Start()
        $output = Get-Content -Raw $file.FullName | .\lnk.exe
        $StopWatch.Stop()
        $time = $StopWatch.Elapsed.TotalSeconds

        Write-Host $new '---' $time 's' 'exp' $expected 'got' $output
        if ($expected -ne $output) {
        }
    }
}

clang++ lnk.cpp -O2 -o lnk.exe
if ($LastExitCode -ne 0) {
    throw
}

Run-BigTest "input" "output"

# Write-Host "=== MANUAL TEST RESULTS ==="
# Run-Test-Folder "input"
