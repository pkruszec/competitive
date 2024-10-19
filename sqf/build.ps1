function Run-Test {
    param($path)
    Get-Content -Raw $path | .\sqf.exe
}

function Run-Test-Folder {
    param($source)
    foreach ($file in Get-ChildItem($source)) {

        $StopWatch = new-object system.diagnostics.stopwatch
        $StopWatch.Start()
        $res = Get-Content -Raw $file.FullName | .\sqf.exe
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
        $output = Get-Content -Raw $file.FullName | .\sqf.exe
        $StopWatch.Stop()
        $time = $StopWatch.Elapsed.TotalSeconds

        Write-Host $new '---' $time 's' 'exp' $expected 'got' $output

        # if ([int]$output -gt [int]$expected) {
        #     Write-Host "------ TEST FAILED:" $in $file $expected $output
        # }
    }
}

# clang++ sqf.cpp -DMEASURE -O2 -o sqf.exe
clang++ sqf.cpp -O2 -o sqf.exe
if ($LastExitCode -ne 0) {
    throw
}

# Get-Content -Raw "archive/aga_01.in" | .\sqf.exe

Run-BigTest "aga" "out"

# Run-Test "input/01.in"

# Write-Host "=== MANUAL TEST RESULTS ==="
# Run-Test-Folder "input"
# Write-Host "=== GENERATED TEST RESULTS ==="
# Run-Test-Folder "test"
