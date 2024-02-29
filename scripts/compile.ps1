# Determine the script's current directory
$scriptPath = Split-Path -Path $MyInvocation.MyCommand.Definition -Parent

# Determine the base (root) project directory
# If the script is run from the scripts folder, it's one level up; otherwise, it's the current directory
if ($scriptPath -match "scripts$") {
    $baseDir = Resolve-Path "$scriptPath\.."
}
else {
    $baseDir = $scriptPath
}

# Define src and build directories based on the base directory
$srcDir = "$baseDir\src"
$buildDir = "$baseDir\build"

# # Compile the program
Write-Host "Compiling from source directory: $srcDir"
g++ -Wall -std=c++14 $srcDir\*.cpp -o $buildDir\PokerProbabilitySimulator.exe

# # Output a completion message
Write-Host "Compilation complete. Executable is in the build folder: $buildDir"
