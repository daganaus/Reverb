# ================================================
# Script PowerShell pour compiler un projet JUCE
# Compatible PowerShell Windows
# Options : --release / --fast
# ================================================

param(
    [string]$mode = ""
)

# Determine les chemins
$ScriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
$JUCE_PROJ = Split-Path $ScriptDir -Parent
$PROJECT = Split-Path $ScriptDir -Leaf
$JUCE_DIR = Join-Path $JUCE_PROJ "JUCE-master"
$BUILD_DIR = Join-Path $ScriptDir "build"

# Options par defaut
$BUILD_TYPE = "Debug"
$FULL_REBUILD = $true

# Analyse des options
switch ($mode) {
    "--release" { $BUILD_TYPE = "Release" }
    "--fast"    { $FULL_REBUILD = $false }
}

Write-Host ""
Write-Host "Compilation du projet : $PROJECT [$BUILD_TYPE]"

# Verifie que JUCE_DIR est valide
if (-not (Test-Path (Join-Path $JUCE_DIR "CMakeLists.txt"))) {
    Write-Host "Erreur : JUCE_DIR invalide ($JUCE_DIR)"
    exit 1
}

# Nettoyage du dossier build si necessaire
if ($FULL_REBUILD) {
    Write-Host "Suppression du dossier build..."
    if (Test-Path $BUILD_DIR) { Remove-Item -Recurse -Force $BUILD_DIR }
    New-Item -ItemType Directory -Path $BUILD_DIR | Out-Null
}

Set-Location $BUILD_DIR

# Configuration CMake (Visual Studio generator)
if ($FULL_REBUILD -or -not (Test-Path "CMakeCache.txt")) {
    Write-Host "Configuration de CMake..."
    cmake "-DJUCE_DIR=$JUCE_DIR" ..
}

# Compilation
Write-Host "Compilation en cours..."
cmake --build . --config $BUILD_TYPE

# Packaging avec CPack (uniquement si Release et exe existe)
$exePath = Join-Path $BUILD_DIR "$PROJECT`_artefacts\$BUILD_TYPE\Standalone\Fred_${PROJECT}.exe"

if ($FULL_REBUILD -and $BUILD_TYPE -eq "Release" -and (Test-Path $exePath)) {
    Write-Host "Packaging avec cpack..."
    $ENV:CONFIGURATION = $BUILD_TYPE
    try {
        cpack .
    } catch {
        Write-Host "Aucun package genere (facultatif)"
    }
} elseif ($BUILD_TYPE -eq "Release") {
    Write-Host "Fichier manquant : $exePath"
    Write-Host "Packaging annule"
} else {
    Write-Host "Packaging ignore (build Debug)"
}

# Retour dans le dossier du projet
Set-Location $ScriptDir
Write-Host "Retour dans le dossier du projet : $ScriptDir"


# Message final
Write-Host ""
Write-Host "Compilation terminee."
Write-Host "Lancez ensuite : .\3_exec.ps1"

