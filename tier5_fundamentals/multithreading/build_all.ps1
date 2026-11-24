$ErrorActionPreference = 'Stop'

$root = Split-Path -Parent $MyInvocation.MyCommand.Path
$build = Join-Path $root 'build'
New-Item -ItemType Directory -Force -Path $build | Out-Null

Get-ChildItem (Join-Path $root 'exercises') -Filter '*.cpp' | Sort-Object Name | ForEach-Object {
    $output = Join-Path $build ($_.BaseName + '.exe')
    Write-Host "[build] $($_.Name)"
    & g++ -std=c++23 -Wall -Wextra -Wpedantic -O2 -pthread -static $_.FullName -o $output
    if ($LASTEXITCODE -ne 0) { throw "Build failed: $($_.Name)" }
}

Write-Host 'All multithreading exercises compiled successfully.'

