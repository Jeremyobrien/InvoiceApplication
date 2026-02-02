# 1. Paths
$srcPath = "@CMAKE_CURRENT_SOURCE_DIR@\src".Replace("/", "\")
$searchRoot = "@CMAKE_BINARY_DIR@".Replace("/", "\")
$reportDir = Join-Path $searchRoot "CoverageReport"

Write-Host "--- Debugging Coverage Runner ---" -ForegroundColor Yellow

# 2. Cleanup (Crucial for fresh start)
if (Test-Path $reportDir) { Remove-Item -Recurse -Force $reportDir }
New-Item -ItemType Directory -Path $reportDir -Force | Out-Null

# 3. Find Tests
$testExes = Get-ChildItem -Path "$searchRoot" -Filter "*test*.exe" -Recurse | 
            Where-Object { $_.FullName -notmatch "CMakeFiles" -and $_.FullName -notmatch "vcpkg" }

# 4. Run Coverage and capture errors
foreach ($exe in $testExes) {
    $name = $exe.Name
    $fullPath = $exe.FullName.Replace("/", "\")
    $outputPath = Join-Path $reportDir "$($exe.BaseName).cov"
    
    Write-Host "Running: $name" -ForegroundColor Cyan
    
    # We add --verbose here to see internal OpenCppCoverage errors
    & OpenCppCoverage.exe --sources="$srcPath" --modules="$name" --export_type=binary:"$outputPath" -- "$fullPath"
    
    if (Test-Path $outputPath) {
        Write-Host "  [OK] Generated binary: $($exe.BaseName).cov" -ForegroundColor Green
    } else {
        Write-Host "  [FAILED] No .cov file created for $name" -ForegroundColor Red
    }
}

# 5. Merge Step
$covFiles = Get-ChildItem -Path $reportDir -Filter "*.cov"
Write-Host "Found $($covFiles.Count) .cov files to merge." -ForegroundColor Yellow

if ($covFiles.Count -gt 0) {
    # Create an array of arguments starting with the basic flags
    $mergeArgs = @(
        "--sources=$srcPath",
        "--export_type=html:$reportDir\HtmlReport"
    )

    # Add each .cov file as an individual argument to the array
    foreach ($file in $covFiles) {
        $mergeArgs += "--input_coverage=$($file.FullName)"
    }
    
    Write-Host "Executing Final Merge..." -ForegroundColor Cyan
    
    # Run the command using the array
    & OpenCppCoverage.exe @mergeArgs
    
    if (Test-Path "$reportDir\HtmlReport\index.html") {
        Write-Host "REPORT CREATED: $reportDir\HtmlReport\index.html" -ForegroundColor Green
        Start-Process "$reportDir\HtmlReport\index.html"
    } else {
        Write-Host "ERROR: Merge command finished but index.html is missing." -ForegroundColor Red
    }
} else {
    Write-Host "ERROR: Cannot merge. Zero .cov files were generated." -ForegroundColor Red
}