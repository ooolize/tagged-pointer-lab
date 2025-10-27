param(
    [string]$Mode = ""
)

if (-not $Mode) {
    Write-Host ""
    Write-Host "=== Build Menu ==="
    Write-Host "1. Full Debug Build (Configure + Build)"
    Write-Host "2. Full Release Build (Configure + Build)"
    Write-Host "3. Quick Debug Build (Build only)"
    Write-Host "4. Quick Release Build (Build only)"
    Write-Host ""
    $choice = Read-Host "Select option (1-4)"
    
    switch ($choice) {
        "1" { $Mode = "full-debug" }
        "2" { $Mode = "full-release" }
        "3" { $Mode = "quick-debug" }
        "4" { $Mode = "quick-release" }
        default { 
            Write-Host "Invalid choice. Exiting."
            exit 1 
        }
    }
}

switch ($Mode) {
    "full-debug" {
        Write-Host "Starting Full Debug Build..."
        conan install . --build=missing --settings=build_type=Debug
        cmake --preset conan-default
        cmake --build --preset conan-debug
    }
    "full-release" {
        Write-Host "Starting Full Release Build..."
        conan install . --build=missing --settings=build_type=Release
        cmake --preset conan-default
        cmake --build --preset conan-release
    }
    "quick-debug" {
        Write-Host "Starting Quick Debug Build..."
        cmake --build --preset conan-debug
    }
    "quick-release" {
        Write-Host "Starting Quick Release Build..."
        cmake --build --preset conan-release
    }
    default {
        Write-Host "Unknown mode: $Mode"
        exit 1
    }
}