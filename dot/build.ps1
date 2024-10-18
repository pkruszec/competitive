function Run-Test {
    param($path)
    Get-Content -Raw $path | .\dot.exe
}

function Run-Test-Folder {
    param($source)
    foreach ($file in Get-ChildItem($source)) {

        $StopWatch = new-object system.diagnostics.stopwatch
        $StopWatch.Start()
        $res = Get-Content -Raw $file.FullName | .\dot.exe
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

        $expected = Get-Content -Raw $path

        $StopWatch = new-object system.diagnostics.stopwatch
        $StopWatch.Start()
        $output = Get-Content -Raw $file.FullName | .\dot.exe
        $StopWatch.Stop()
        $time = $StopWatch.Elapsed.TotalSeconds

        Write-Host $new '---' $time 's' 'exp' $expected 'got' $output
    }
}

clang++ dot.cpp -O2 -o dot.exe
if ($LastExitCode -ne 0) {
    throw
}

Write-Host "=== MANUAL TEST RESULTS ==="
Run-Test-Folder "input"
