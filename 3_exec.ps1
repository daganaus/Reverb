# ================================================
# Script PowerShell d'execution du binaire JUCE Standalone
# Compatible Windows
# ================================================

$ScriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
$JUCE_PROJ = Split-Path $ScriptDir -Parent
$PROJECT = Split-Path $ScriptDir -Leaf
$BUILD_TYPE = "Debug"
$BUILD_DIR = Join-Path $ScriptDir "build"

# Recherche du dossier *_artefacts
$ArtefactDir = Get-ChildItem -Directory -Path $BUILD_DIR | Where-Object { $_.Name -like '*_artefacts' } | Select-Object -First 1

if (-not $ArtefactDir) {
    Write-Host "Aucun dossier *_artefacts trouve dans build/. Compilation requise."
    exit 1
}

$AppName = $ArtefactDir.Name -replace '_artefacts$', ''
$Executable = Join-Path $ArtefactDir.FullName "$BUILD_TYPE\Standalone\Fred_${AppName}.exe"

Write-Host "`nLancement de l'application JUCE Standalone..."

if (Test-Path $Executable) {
    Start-Process $Executable
} else {
    Write-Host "Executable introuvable : $Executable"
    Write-Host "Compilez d'abord avec .\\2_build.ps1"
}
