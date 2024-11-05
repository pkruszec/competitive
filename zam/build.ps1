function Run-Test {
    param($path)
    Get-Content -Raw $path | .\zam.exe
}

function Run-Test-Folder {
    param($source)
    foreach ($file in Get-ChildItem($source)) {

        $StopWatch = new-object system.diagnostics.stopwatch
        $StopWatch.Start()
        $res = Get-Content -Raw $file.FullName | .\zam.exe
        $StopWatch.Stop()
        $time = $StopWatch.Elapsed.TotalSeconds

        Write-Host $file.Name '->' $res '---' $time 's'
    }
}

function Run-BigTest {
    param($in, $out)

    $counter = 0
    foreach ($file in Get-ChildItem($in)) {
        $name = [System.IO.Path]::GetFileName($file)
        $new =  [System.IO.Path]::ChangeExtension($name, '.out')
        $path = [System.IO.Path]::Combine($out, $new)

        $expected = Get-Content $path

        $StopWatch = new-object system.diagnostics.stopwatch
        $StopWatch.Start()
        $output = Get-Content -Raw $file.FullName | .\zam.exe
        $StopWatch.Stop()
        $time = $StopWatch.Elapsed.TotalSeconds

        if ($expected -ne $output) {
            Write-Host $new '---' $time 's' 'exp' $expected 'got' $output
        }

        $counter++
        if (($counter % 1000) -eq 0) {
            Write-Host $in $counter
        }
    }
    Write-Host "DONE" $in $counter
}

clang++ zam.cpp -O2 -o zam.exe
if ($LastExitCode -ne 0) {
    throw
}

# Run-Test "C:\home\tmp\testy_in\test0.in"
# Run-Test "in/smallones.in"

# Start-Transcript -Path .\test.log
Run-BigTest "in" "out"
#Run-BigTest "c:/home/tmp/testy_small" "c:/home/tmp/testy_small_out"
# Run-BigTest "c:/home/tmp/testy_in" "c:/home/tmp/testy_out"
# Stop-Transcript

# Write-Host "=== MANUAL TEST RESULTS ==="
# Run-Test-Folder "input"
